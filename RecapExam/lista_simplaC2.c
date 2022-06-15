#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int cod;
	char* denumire;
	float pret;
	float cantitate;
}produs;

typedef struct
{
	produs inf;
	struct nodLS* next;
}nodLS;

nodLS* inserare(nodLS* cap, produs p)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;

	nou->next = NULL;
	if (cap == NULL)
		cap = nou;
	else
	{
		nodLS* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

void traversare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
			temp->inf.cod, temp->inf.denumire, temp->inf.pret, temp->inf.cantitate);
		temp = temp->next;
	}
}

void dezalocare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = temp2;
	}
}


void main()
{
	int n;
	/*printf("Nr. produse: ");
	scanf("%d", &n);*/

	nodLS* cap = NULL;
	produs p;
	char buffer[20];

	/*for (int i = 0; i < n; i++)
	{
		printf("Cod: ");
		scanf("%d", &p.cod);
		printf("Denumire: ");
		scanf("%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		printf("Pret: ");
		scanf("%f", &p.pret);
		printf("Cantitate: ");
		scanf("%f", &p.cantitate);

		cap = inserare(cap, p);
		free(p.denumire);
	}*/

	FILE* f = fopen("fisierC2.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);
		fscanf(f, "%f", &p.cantitate);

		cap = inserare(cap, p);
		free(p.denumire);
	}
	fclose(f);

	traversare(cap);
	dezalocare(cap);
}