#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int cod;
	char* nume;
	float medie;
}student;

typedef struct
{
	student inf;
	struct nodArb* stanga, * dreapta;
}nodArb;

typedef struct
{
	student inf;
	struct nodStiva* next;
}nodStiva;

nodArb* creare(student s, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;

	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodArb* inserare(student s, nodArb* rad)
{
	nodArb* aux = rad;
	if (rad == NULL)
	{
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else
		while (1)
		{
			if (s.cod < aux->inf.cod)
				if (aux->stanga != NULL) aux = aux->stanga;
				else
				{
					aux->stanga = creare(s, NULL, NULL);
					return rad;
				}
			else
				if (s.cod > aux->inf.cod)
					if (aux->dreapta != NULL) aux = aux->dreapta;
					else
					{
						aux->dreapta = creare(s, NULL, NULL);
						return rad;
					}
				else
				{
					printf("\nNod existent!");
					return rad;
				}
		}
}

void inordine(nodArb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->stanga);
		printf("\nCod: %d, Nume: %s, Medie: %f",
			rad->inf.cod, rad->inf.nume, rad->inf.medie);
		inordine(rad->dreapta);
	}
}

void dezalocare(nodArb* rad)
{
	if (rad != NULL)
	{
		nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;
		free(rad->inf.nume);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

void inserareStiva(nodStiva** varf, student s)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;

	

	if (*varf == NULL)
	{
		nou->next = NULL;
		*varf = nou;
	}
		
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

void conversieArboreStiva(nodArb* rad, nodStiva** varf)
{
	if (rad != NULL)
	{
		inserareStiva(varf, rad->inf);
		conversieArboreStiva(rad->stanga, varf);
		conversieArboreStiva(rad->dreapta, varf);
	}
}

void afisareStiva(nodStiva* varf)
{
	nodStiva* aux = varf;
	while (aux != NULL)
	{
		printf("\nStudentul %s are codul %d si media %5.2f",
			aux->inf.nume, aux->inf.cod, aux->inf.medie);
		aux = aux->next;
	}
}

void main()
{
	nodArb* rad = NULL;
	student s;
	char buffer[20];
	int n;

	FILE* f = fopen("fisierC6.txt", "r");
	fscanf(f, "%d", &n);

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		rad = inserare(s, rad);
	}
	fclose(f);

	inordine(rad);

	printf("\n*******CONVERSIE ARBORE STIVA************");
	nodStiva* varf = NULL;
	conversieArboreStiva(rad, &varf);
	afisareStiva(varf);

	dezalocare(rad);
}