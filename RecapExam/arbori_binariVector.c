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

nodArb* creare(student s, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;

	nou->stanga = NULL;
	nou->dreapta = NULL;

	return nou;
}

nodArb* inserare(student s, nodArb* rad)
{
	nodArb* temp = rad;
	if (rad == NULL)
	{
		temp = creare(s, NULL, NULL);
		return temp;
	}
	else
		while (1)
		{
			if (s.cod < temp->inf.cod)
				if (temp->stanga != NULL)
					temp = temp->stanga;
				else
				{
					temp->stanga = creare(s, NULL, NULL);
					return rad;
				}
			else
				if (s.cod > temp->inf.cod)
					if (temp->dreapta != NULL)
						temp = temp->dreapta;
					else
					{
						temp->dreapta = creare(s, NULL, NULL);
						return rad;

					}
				else
					return rad;
				
		}
		
}

void preordine(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nCod: %d, Nume: %s, Medie: %5.2f",
			rad->inf.cod, rad->inf.nume, rad->inf.medie);
		preordine(rad->stanga);
		preordine(rad->dreapta);
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

nodArb* stergereRad(nodArb* rad)
{
	nodArb* aux = rad;
	if (rad->stanga != NULL)
	{
		rad = aux->stanga;
		if (aux->dreapta != NULL)
		{
			nodArb* temp = aux->stanga;
			while (temp->dreapta != NULL)
			{
				temp = temp->dreapta;
			}
			temp->dreapta = aux->dreapta;
		}
	}
	else
		if (aux->dreapta != NULL)
			rad = aux->dreapta;
		else
			rad = NULL;
	free(aux->inf.nume);
	free(aux);
	return rad;
}

nodArb* stergereNodIterativ(nodArb* rad, int cheie)
{
	if (rad == NULL)
		return NULL;
	else
		if (rad->inf.cod == cheie)
		{
			rad = stergereRad(rad);
			return rad;
		}
		else
		{
			nodArb* aux = rad;
			while (1)
			{
				if (cheie < aux->inf.cod)
					if (aux->stanga == NULL)
						break;
					else
					{
						nodArb* st = aux->stanga;
						if (st->inf.cod == cheie)
						{
							aux->stanga = stergereRad(aux->stanga);

						}
						else
							aux = aux->stanga;
					}
				else
					if (cheie > aux->inf.cod)
						if (aux->dreapta == NULL)
							break;
						else
						{
							nodArb* dr = aux->dreapta;
							if (dr->inf.cod == cheie)
							{
								aux->dreapta = stergereRad(aux->dreapta);
							}
							else
								aux = aux->dreapta;
						}
			}
			return rad;
		}
}

void salvareNoduriFrunzaVector(nodArb* rad, student* vect, int* nr)
{
	if (rad != NULL)
	{
		if (rad->stanga == NULL && rad->dreapta == NULL)
		{
			vect[*nr].cod = rad->inf.cod;
			vect[*nr].nume = (char*)malloc((strlen(rad->inf.nume) + 1) * sizeof(char));
			strcpy(vect[*nr].nume, rad->inf.nume);
			vect[*nr].medie = rad->inf.medie;
			(*nr)++;
		}
		salvareNoduriFrunzaVector(rad->stanga, vect, nr);
		salvareNoduriFrunzaVector(rad->dreapta, vect, nr);
	}
}

void conversieArboreVector(nodArb* rad, student* vect, int* nr)
{
	if (rad != NULL)
	{
		vect[*nr].cod = rad->inf.cod;
		vect[*nr].nume = (char*)malloc((strlen(rad->inf.nume) + 1) * sizeof(char));
		strcpy(vect[*nr].nume, rad->inf.nume);
		vect[*nr].medie = rad->inf.medie;
		(*nr)++;
	}
	conversieArboreVector(rad->stanga, vect, nr);
	conversieArboreVector(rad->dreapta, vect, nr);
}

int maxim(int a, int b)
{
	int max = a;
	if (max < b)
		max = b;
	return max;
}

int nrNiveluri(nodArb* rad)
{
	if (rad != NULL)
	{
		return 1 + maxim(nrNiveluri(rad->stanga),nrNiveluri(rad->dreapta));
	}
	else
		return 0;
}
void main()
{
	nodArb* rad = NULL;
	student s;
	int n;
	char buffer[20];

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

	preordine(rad);

	/*rad = stergereNodIterativ(rad, 10);
	printf("\n***********DUPA STERGERE************");
	preordine(rad);*/

	printf("\n************VECTOR*************");
	student* vect = (student*)malloc(n * sizeof(student));
	int nr = 0;
	salvareNoduriFrunzaVector(rad, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nCod: %d, Nume: %s, Medie: %f",
			vect[i].cod, vect[i].nume, vect[i].medie);

	for (int i = 0; i < nr; i++)
		free(vect[i].nume);
	free(vect);

	printf("\nInaltimea arborelui: %d", nrNiveluri(rad));
	printf("\nInaltimea arborelui stang: %d", nrNiveluri(rad->stanga));
	printf("\nInaltimea arborelui drept: %d", nrNiveluri(rad->dreapta));



	//gradul de echilibru

	int gradEchilibru = nrNiveluri(rad->dreapta) - nrNiveluri(rad->stanga);
	if (gradEchilibru <= 1 && gradEchilibru >= -1)
	{
		printf("\nArborele este echilibrat, gradul de echilibru: %d", gradEchilibru);
	}
	else
	{
		printf("\nArborele nu este echilibrat, gradul de echilibru: %d", gradEchilibru);
	}

	dezalocare(rad);
}