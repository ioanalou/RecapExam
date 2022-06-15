#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
}produs;

void citireVector(produs* vp, int n)
{
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("Cod produs:");
		vp[i].cod = (int*)malloc(1*sizeof(int));
		scanf("%d", vp[i].cod);

		printf("Denumire produs:");
		scanf("%s", buffer);
		vp[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(vp[i].denumire, buffer);

		printf("Pret:");
		scanf("%f", &vp[i].pret);
		
		printf("Cantitate:");
		scanf("%f", &vp[i].cantitate);
		
	}
}

void afisareVector(produs* vp, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Cod: %d", *(vp[i].cod));
		printf(", Denumire: %s", vp[i].denumire);
		printf(", Pret: %5.2f", vp[i].pret);
		printf(", Cantitate: %5.2f", vp[i].cantitate);;
		printf("\n");

	}
}

void dezalocareVector(produs* vp, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(vp[i].cod);
		free(vp[i].denumire);
	}
	free(vp);
}


void citire4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati,int n)
{
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("Cod:");
		scanf("%d", &coduri[i]);
		
		printf("Denumire:");
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(denumiri[i], buffer);

		printf("Pret:");
		scanf("%f", &preturi[i]);

		printf("Cantitate");
		scanf("%f", &cantitati[i]);
	}
}

void afisare4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Cod: %d", coduri[i]);
		printf(", Denumire: %s", denumiri[i]);
		printf(", Pret: %5.2f", preturi[i]);
		printf(", Cantitate: %5.2f", cantitati[i]);
		printf("\n");
	}
}

void dezalocare4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int n)
{
	for (int i = 0; i < n; i++)
		free(denumiri[i]);
	free(denumiri);
	free(coduri);
	free(preturi);
	free(cantitati);
	
}

void citireMatrice(float** matrice, char** denumiri, int n)
{
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("Denumire: ");
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(denumiri[i], buffer);
		for (int j = 0; j < 3; j++)
		{
			printf("mat[%d][%d]: ", i, j);
			scanf("%f", &matrice[i][j]);
		}
	}
}

void afisareMatrice(float** matrice, char** denumiri, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Denumire: %s", denumiri[i]);
		for (int j = 0; j < 3; j++)
			printf("%5.2f ", matrice[i][j]);
		printf("\n");
	}
}

void dezalocareMatrice(float** matrice, char** denumiri, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(denumiri[i]);
		free(matrice[i]);
	}
	free(matrice);
	free(denumiri);
}

float sumaProduseVector(produs* vp, int n)
{
	float suma = 0.0f;
	for (int i = 0; i < n; i++)
		suma += vp[i].pret * vp[i].cantitate;
	return suma;
}

void main()
{
	int n;
	printf("Nr. produse: ");
	scanf("%d", &n);

	produs* vp = (produs*)malloc(n * sizeof(produs));

	/*citireVector(vp, n);
	afisareVector(vp, n);
	dezalocareVector(vp, n);*/

	/*int* coduri = (int*)malloc(n * sizeof(int));
	char** denumiri = (char**)malloc(n * sizeof(char*));
	float* preturi = (float*)malloc(n * sizeof(float));
	float* cantitati = (float*)malloc(n * sizeof(float));
	citire4Vectori(coduri, denumiri, preturi, cantitati, n);
	afisare4Vectori(coduri, denumiri, preturi, cantitati, n);
	dezalocare4Vectori(coduri, denumiri, preturi, cantitati, n);*/

	/*char** denumiri = (char**)malloc(n * sizeof(char*));
	float** matrice = (float**)malloc(n * sizeof(float*));
	for (int i = 0; i < n; i++)
		matrice[i] = (float*)malloc(3 * sizeof(float));
	citireMatrice(matrice, denumiri, n);
	afisareMatrice(matrice, denumiri, n);
	dezalocareMatrice(matrice, denumiri, n);*/



}