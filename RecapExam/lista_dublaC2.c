#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
}produs;

typedef struct
{
	produs* inf;
	struct nodLS* next, * prev;
}nodLS;

nodLS* inserareLista(nodLS* cap, nodLS** coada, produs* p)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->inf = (produs*)malloc(sizeof(produs));
	nou->inf->cod = (int*)malloc(sizeof(int));
	*(nou->inf->cod) = *(p->cod);
	nou->inf->denumire = (char*)malloc((strlen(p->denumire) + 1) * sizeof(char));
	strcpy(nou->inf->denumire, p->denumire);
	nou->inf->pret = p->pret;
	nou->inf->cantitate = p->cantitate;

	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL)
	{
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodLS* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}
	return cap;
}

void traversareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
			*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->next;
	}
}

void traversareInversa(nodLS* coada)
{
	nodLS* temp = coada;
		while (temp != NULL)
		{
			printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
				*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
			temp = temp->prev;
		}
}

void dezalocareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf->cod);
		free(temp->inf->denumire);
		free(temp->inf);
		free(temp);
		temp = temp2;
		
	}
}

void conversieListaVector(nodLS* cap, produs** vect, int* nr)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		vect[*nr] = (produs*)malloc(1 * sizeof(produs));
		vect[*nr]->cod = (int*)malloc(1 * sizeof(int));
		*(vect[*nr]->cod) = *(temp->inf->cod);
		vect[*nr]->denumire = (char*)malloc((strlen(temp->inf->denumire) + 1) * sizeof(char));
		strcpy(vect[*nr]->denumire, temp->inf->denumire);
		vect[*nr]->pret = temp->inf->pret;
		vect[*nr]->cantitate = temp->inf->cantitate;

		(*nr)++;

		temp = temp->next;
	}
}

void main()
{
	int n;
	printf("Nr. produse: ");
	scanf("%d", &n);

	nodLS* cap = NULL, * coada = NULL;
	produs* p;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		p = (produs*)malloc(sizeof(produs));

		p->cod = (int*)malloc(sizeof(int));
		printf("Cod: ");
		scanf("%d", p->cod);

		printf("Denumire: ");
		scanf("%s", buffer);
		p->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->denumire, buffer);
		
		printf("Pret: ");
		scanf("%f", &p->pret);

		printf("Cantitate: ");
		scanf("%f", &p->cantitate);

		cap = inserareLista(cap, &coada, p);
		free(p->cod);
		free(p->denumire);
		free(p);
	}
	traversareLista(cap);
	traversareInversa(coada);

	printf("\nApel conversie lista vector");

	produs** vect = (produs**)malloc(n * sizeof(produs*));
	int nr = 0;
	conversieListaVector(cap, vect, &nr);
	for (int i = 0; i < n; i++)
		printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
			*(vect[i]->cod), vect[i]->denumire, vect[i]->pret, vect[i]->cantitate);

	for (int i = 0; i < nr; i++)
	{
		free(vect[i]->denumire);
		free(vect[i]->cod);
		free(vect[i]);
	}
	free(vect);

	dezalocareLista(cap);
}