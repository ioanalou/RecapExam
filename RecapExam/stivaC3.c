#include<stdio.h>
#include<malloc.h>


typedef struct
{
	int cod;
	char* titlu;
	float pret;
}carte;

typedef struct
{
	carte inf;
	struct nodStiva* next;
}nodStiva;

typedef struct
{
	carte inf;
	struct nodLista* next;
}nodLista;

void push(nodStiva** varf, carte c)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));

	nou->inf.cod = c.cod;
	nou->inf.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->inf.titlu, c.titlu);
	nou->inf.pret = c.pret;

	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, carte* val)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*val).cod = (*varf)->inf.cod;
		(*val).titlu = (char*)malloc((strlen((*varf)->inf.titlu) + 1) * sizeof(char));
		strcpy((*val).titlu, (*varf)->inf.titlu);
		(*val).pret = (*varf)->inf.pret;

		nodStiva* temp = *varf;
		*varf=(*varf)->next;
		free(temp->inf.titlu);
		free(temp);

		return 0;
	}
}

void traversare(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp)
	{
		printf("\nCod: %d, Titlu: %s, Pret: %5.2f", 
			temp->inf.cod, temp->inf.titlu, temp->inf.pret);
		temp = temp->next;
	}
}

void traversareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("\nCod: %d, Titlu: %s, Pret: %5.2f",
			temp->inf.cod, temp->inf.titlu, temp->inf.pret);
		temp = temp->next;
	}
}

void dezalocareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		nodLista* temp2 = temp->next;
		free(temp->inf.titlu);
		free(temp);
		temp = temp2;
	}
}

void inserareLista(nodLista** cap, carte val)
{
	nodStiva* nou = (nodLista*)malloc(sizeof(nodLista));

	nou->inf.cod = val.cod;
	nou->inf.titlu = (char*)malloc((strlen(val.titlu) + 1) * sizeof(char));
	strcpy(nou->inf.titlu, val.titlu);
	nou->inf.pret = val.pret;

	nou->next = NULL;
	if (*cap == NULL)
		*cap = nou;
	else
	{
		nodLista* temp = *cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void conversieStivaListaSimpla(nodStiva** varf, nodLista** cap)
{
	carte val;
	while (pop(varf, &val) == 0)
	{
		inserareLista(cap, val);
	}
}

void conversieStivaVector(nodStiva** varf, carte* vect, int* nr)
{
	carte val;
	while (pop(varf, &val) == 0)
	{
		vect[*nr] = val;
		(*nr)++;
	}
}

void main()
{
	int n;
	/*printf("Nr. carti: ");
	scanf("%d", &n);*/
	nodStiva* varf = NULL;
	carte c;
	carte val;
	char buffer[20];
	
	FILE* f = fopen("fisierC3.txt", "r");
	fscanf(f, "%d", &n);

	for (int i = 0; i < n; i++)
	{
		//printf("\nCod: ");
		fscanf(f,"%d", &c.cod);
		//printf("\nTitlu: ");
		fscanf(f," %s", buffer);
		c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.titlu, buffer);
		//printf("\nPret: ");
		fscanf(f,"%f", &c.pret);

		push(&varf, c);
	}
	fclose(f);
	traversare(varf);

	pop(&varf, &val);
	printf("\nCartea extrasa are codul %d si titlul %s", val.cod, val.titlu);
	free(val.titlu);

	printf("\n*****************CONVERSIE STIVA-LISTA**********************");
	nodLista* cap = NULL;
	conversieStivaListaSimpla(&varf, &cap);
	traversareLista(cap);
	dezalocareLista(cap);


	printf("\n*****************CONVERSIE STIVA-VECTOR**********************");
	carte* vect = (carte*)malloc(n * sizeof(carte));
	int nr = 0;
	conversieStivaVector(&varf, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nCod: %d, Titlu: %s, Pret: %5.2f",
			vect[i].cod, vect[i].titlu, vect[i].pret);
	for (int i = 0; i < nr; i++)
		free(vect[i].titlu);
	free(vect);

	/*while (pop(&varf, &val) == 0)
		free(val.titlu);*/
}