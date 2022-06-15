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

//functie pentru initializarea unui nod
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

nodArb* inserareRecursiv(student s, nodArb* rad)
{
	if (rad != NULL)
	{
		if (s.cod < rad->inf.cod)
		{
			rad->stanga = inserareLista(s, rad->stanga);
			return rad;
		}
		else
			if (s.cod > rad->inf.cod)
			{
				rad->dreapta = inserareLista(s, rad->dreapta);
				return rad;
			}
			else
				return rad;
	}
	else
		return creare(s, NULL, NULL);
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

void inordine(nodArb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->stanga);
		printf("\nCod: %d, Nume: %s, Medie: %5.2f",
			rad->inf.cod, rad->inf.nume, rad->inf.medie);
		inordine(rad->dreapta);
	}
}

void postordine(nodArb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->stanga);
		postordine(rad->dreapta);
		printf("\nCod: %d, Nume: %s, Medie: %5.2f",
			rad->inf.cod, rad->inf.nume, rad->inf.medie);
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

//FUNCTII

//functie pentru cautarea unui nod dupa cheie
nodArb* cautare(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->inf.cod)
			return rad;
		else
			if (cheie < rad->inf.cod)
				return cautare(rad->stanga, cheie);
			else
				return cautare(rad->dreapta, cheie);
	}
	else
		return NULL;
}

//functie pentru stergerea nodului radacina
nodArb* stergeRad(nodArb* rad)
{
	nodArb* aux = rad;
	if (aux->stanga != NULL)
	{
		rad = aux->stanga;
		if (aux->dreapta != NULL)
		{
			nodArb* temp = aux->stanga;
			while (temp->dreapta)
				temp = temp->dreapta;
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

nodArb* stergereNod(nodArb* rad, int cheie)
{
	if (rad == NULL)
		return NULL;
	else
		if (rad->inf.cod == cheie)
		{
			rad = stergeRad(rad);
			return rad;
		}
		else
			if (cheie < rad->inf.cod)
			{
				rad->stanga = stergereNod(rad->stanga, cheie);
				return rad;
			}
			else
			{
				rad->dreapta = stergereNod(rad->dreapta,cheie);
				return rad;
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
	{
		int st = nrNiveluri(rad->stanga);
		int dr = nrNiveluri(rad->dreapta);
		return 1 + maxim(st, dr);
	}
	else
		return 0;
}

void main()
{
	int n;
	FILE* f = fopen("fisierC6.txt", "r");
	fscanf(f, "%d", &n);
	nodArb* rad = NULL;
	student s;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		rad = inserareRecursiv(s, rad);
	}
	fclose(f);
	preordine(rad);
	printf("\n******************PREORDINE****************");
	
	printf("\n******************INORDINE****************");
	inordine(rad);
	printf("\n******************POSTORDINE****************");
	postordine(rad);

	printf("\n-------subarbore stang-------------\n");
	inordine(rad->stanga);
	printf("\n-------subarbore drept-------------\n");
	inordine(rad->dreapta);

	nodArb* nodCautat = cautare(rad, 7);
	if (nodCautat != NULL)
		printf("\nStudentul cautat care are codul %d se numeste %s", nodCautat->inf.cod,nodCautat->inf.nume);
	else
		printf("\nStudentul nu exista!");

	//?? e scrisa pt functia de stergereNod dupa o cheie, dar poate merge si singura
	rad = stergeRad(rad, 10);
	printf("\n******Dupa stergerea radacinii******");
	preordine(rad);

	rad = stergereNod(rad, 9);
	printf("\n******Dupa stergere cheie 9******");
	preordine(rad);

	//inaltimea arborelui

	printf("\nInaltimea arborelui este: %d", nrNiveluri(rad));
	printf("\nInaltimea arborelui stang este: %d", nrNiveluri(rad->stanga));
	printf("\nInaltimea arborelui drept este: %d", nrNiveluri(rad->dreapta));



	dezalocare(rad);
}