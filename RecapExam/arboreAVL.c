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
	int BF;
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
				if (aux->stanga != NULL)
					aux = aux->stanga;
				else
				{
					aux->stanga = creare(s, NULL, NULL);
					return rad;
				}
			else
				if (s.cod > aux->inf.cod)
					if (aux->dreapta != NULL)
						aux = aux->dreapta;
					else
					{
						aux->dreapta = creare(s, NULL, NULL);
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
		printf("\nCod: %d, Nume: %s, Medie: %5.2f, BF: %d",
			rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

void inordine(nodArb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->stanga);
		printf("\nCod: %d, Nume: %s, Medie: %5.2f, BF: %d",
			rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
		inordine(rad->dreapta);

	}
}

void postordine(nodArb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->stanga);
		postordine(rad->dreapta);
		printf("\nCod: %d, Nume: %s, Medie: %5.2f, BF: %d",
			rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
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
		return 1 + maxim(nrNiveluri(rad->stanga), nrNiveluri(rad->dreapta));
	else
		return 0;
}

//functie pentru initializare grad de echilibru la nivelul fiecarui nod
void calculBF(nodArb* rad)
{
	if (rad != NULL)
	{
		rad->BF = nrNiveluri(rad->dreapta) - nrNiveluri(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}

nodArb* rotatie_dreapta(nodArb* rad)
{
	printf("\nRotatie dreapta\n");
	nodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga(nodArb* rad)
{
	printf("\nRotatie stanga\n");
	nodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_dreapta_stanga(nodArb* rad)
{
	printf("\nRotatie dreapta-stanga\n");
	nodArb* nod1 = rad->dreapta;
	nodArb* nod2 = nod1->stanga;
	nod1->stanga = nod2->dreapta;
	nod2->dreapta = nod1;
	rad->dreapta = nod2->stanga;
	nod2->stanga = rad;
	rad = nod2;
	return rad;
}

nodArb* rotatie_stanga_dreapta(nodArb* rad)
{
	printf("\nRotatie stanga-dreapta\n");
	nodArb* nod1 = rad->stanga;
	nodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2->dreapta = rad;
	rad = nod2;
	return rad;
}

nodArb* reechilibrare(nodArb* rad)
{
	calculBF(rad);
	nodArb* stanga = rad->stanga;
	nodArb* dreapta = rad->dreapta;

	if (rad->BF <= -2 && stanga->BF <= -1)
	{
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else
		if (rad->BF >= 2 && dreapta->BF >= 1)
		{
			rad = rotatie_stanga(rad);
			calculBF(rad);
		}
		else
			if (rad->BF >= 2 && dreapta->BF <= -1)
			{
				rad = rotatie_dreapta_stanga(rad);
				calculBF(rad);
			}
			else
				if (rad->BF <= -2 && stanga->BF >= 1)
				{
					rad = rotatie_stanga_dreapta(rad);
					calculBF(rad);
				}
	return rad;
}

//functia de afisare noduri de pe un anumit nivel
void afisareNivel(nodArb* rad, int nivel)
{
	if (rad == NULL)
		return;
	if (nivel == 1)
		printf("\nCod: %d, Nume: %s, Medie: %5.2f, BF: %d",
			rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
	else
		if (nivel > 1)
		{
			afisareNivel(rad->stanga, nivel - 1);
			afisareNivel(rad->dreapta, nivel-1);
		}
}

//functie pentru traversare arbore pe niveluri
void traversareNiveluri(nodArb* rad)
{
	int h = nrNiveluri(rad);
	for (int i = 0; i <= h; i++)
		afisareNivel(rad, i);
}

// functia care valideaza daca exista drum de la radacina la un anumit nod
int existaDrum(nodArb* rad, int* vector, int* nr, int nod)
{
	if (!rad)
		return 0;

	//se adauga nodul curent in vector
	vector[*nr] = rad->inf.cod;
	(*nr)++;

	//daca nodul primit ca parametru este egal cu radacina returnam true
	if (rad->inf.cod == nod)
		return 1;

	//altfel verificam daca nodul catat este in subarborele stang sau drept
	if (existaDrum(rad->stanga, vector, nr, nod) || existaDrum(rad->dreapta, vector, nr, nod))
		return 1;

	//daca nu se afla in niciunul dintre cei 2 subarbori se elimina din vector si returnam false
	(*nr)--;
	return 0;
}

// functie care afiseaza drumul de la radacina la un anumit nod
void afiseazaDrum(nodArb* rad, int* vector, int nr, int nod)
{
	if (existaDrum(rad, vector, &nr, nod))
	{
		for (int i = 0; i < nr; i++)
			printf("%d->", vector[i]);
	}
	else
		printf("\nNu exista drum!\n");
}

void spargereAVLdoiArbori(nodArb* rad, nodArb** rad1, nodArb** rad2, int cod)
{
	if (rad != NULL)
	{
		if (rad->inf.cod <= cod)
		{
			*rad1 = inserare(rad->inf, *rad1);
			*rad1 = reechilibrare(*rad1);
		}
		else
		{
			*rad2 = inserare(rad->inf, *rad2);
			*rad2 = reechilibrare(*rad2);
		}
		spargereAVLdoiArbori(rad->stanga, rad1, rad2, cod);
		spargereAVLdoiArbori(rad->dreapta, rad1, rad2, cod);
	}
}

void main()
{
	nodArb* rad = NULL;
	student s;
	char buffer[20];
	int n;

	FILE* f = fopen("fisierC7.txt", "r");
	fscanf(f, "%d", &n);

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		rad = inserare(s, rad);

		rad = reechilibrare(rad);
	}
	fclose(f);

	printf("\n***********INORDINE***********");	
	inordine(rad);
	/*printf("\n***********STANGA***********");
	inordine(rad->stanga);
	printf("\n***********DREAPTA***********");
	inordine(rad->dreapta);

	printf("\nInaltimea arborelui este: %d", nrNiveluri(rad));
	printf("\nInaltimea subarborelui stang este: %d", nrNiveluri(rad->stanga));
	printf("\nInaltimea subarborelui drept este: %d", nrNiveluri(rad->dreapta));*/

	printf("\nNoduri de pe nivelul 1: \n");
	afisareNivel(rad, 1);

	printf("\nTraversare pe niveluri: \n");
	traversareNiveluri(rad);

	printf("\nDrumul de la radacina la un anumit nod: \n");
	int* vector = (int*)malloc(n * sizeof(int));
	int nr = 0;
	afiseazaDrum(rad, vector, nr, 1);

	printf("\nSpargerea unui arbore in doi subarbori binari");
	nodArb* rad1 = NULL, * rad2 = NULL;
	spargereAVLdoiArbori(rad, &rad1, &rad2, 18);
	printf("\nPrimul subarbore: \n");
	inordine(rad1);
	printf("\nAl doilea subarbore: \n");
	inordine(rad2);

	dezalocare(rad);
}