#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int* val;
	int* lin;
	int* col;
	int m;
	int n;
	int nrNenule;
}matriceRara;

int** citireMat(int* nrlin, int* nrcol)
{
	printf("Nr. de linii: ");
	scanf("%d", nrlin);
	printf("Nr. de coloane: ");
	scanf("%d", nrcol);

	int** a = (int**)malloc((*nrlin) * sizeof(int*));
	for (int i = 0; i < (*nrlin); i++)
		a[i] = (int*)malloc((*nrcol) * sizeof(int));

	for(int i=0;i<(*nrlin);i++)
		for (int j = 0; j < (*nrcol); j++)
		{
			printf("mat[%d][%d]: ", i, j);
			scanf("%d", &a[i][j]);
		}
	return a;
}

void afisare(int** a, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		printf("\n");
		for (int j = 0; j < n; j++)
			printf("%d", a[i][j]);
	}
}

int rara(int** a, int nrlin, int nrcol)
{
	float grad = 0;
	for (int i = 0; i < nrlin; i++)
		for (int j = 0; j < nrcol; j++)
			if (a[i][j] != 0)
				grad++;
	if (grad / (float)(nrlin * nrcol) < 0.3)
		return grad;
	else
		return 0;
}

void afisareRara(matriceRara mat)
{
	printf("\n");
	for (int i = 0; i < mat.nrNenule; i++)
		printf("%d (%d,%d)", mat.val[i], mat.lin[i], mat.col[i]);
}

void dezalocareMatrice(int** a, int nrlin, int nrcol)
{
	for (int i = 0; i < nrlin; i++)
		free(a[i]);
	free(a);
}

matriceRara transformare(int** a, int nrlin, int nrcol)
{
	matriceRara b;
	b.m = b.n = b.nrNenule = 0;
	b.col = b.lin = b.val = NULL;

	int k = 0, temp;

	if (temp = rara(a, nrlin, nrcol))
	{
		b.val = (int*)malloc(temp * sizeof(int));
		b.col = (int*)malloc(temp * sizeof(int));
		b.lin = (int*)malloc(temp * sizeof(int));
		b.m = nrlin;
		b.n = nrcol;
		b.nrNenule = rara(a, nrlin, nrcol);

		for (int i = 0; i < nrlin; i++)
			for (int j = 0; j < nrcol; j++)
			{
				if (a[i][j])
				{
					b.val[k] = a[i][j];
					b.lin[k] = i;
					b.col[k] = j;
					k++;
				}
			}
	}
	else
		printf("\nMatricea nu este rara!");
	return b;
}

int** transformareInvers(matriceRara a)
{
	int** b = (int**)malloc(a.m * sizeof(int*));
	for (int i = 0; i < a.m; i++)
		b[i] = (int*)malloc(a.n * sizeof(int));

	int k = 0, i, j;
	for (i = 0; i < a.m; i++)
		for (j = 0; j < a.n; j++)
			if ((a.lin[k] == i) && (a.col[k] == j))
			{
				b[i][j] = a.val[k];
				k++;
			}
			else
				b[i][j] = 0;
	return b;
}

void dezalocareVectori(matriceRara mat)
{
	free(mat.lin);
	free(mat.col);
	free(mat.val);
}

void main()
{
	int** mat1, ** mat2;
	int m, n;
	
	mat1 = citireMat(&m, &n);
	afisare(mat1,m, n);

	matriceRara a;
	a = transformare(mat1, m, n);
	printf("\nMatricea rara: \n");
	afisareRara(a);

	mat2 = transformareInvers(a);
	printf("\nMatrice normala: \n");
	for (int i = 0; i < a.m; i++)
	{
		for (int j = 0; j < a.n; j++)
			printf("%d", mat2[i][j]);
		printf("\n");
	}

	dezalocareMatrice(mat1, m, n);
	dezalocareMatrice(mat2, m, n);
	dezalocareVectori(a);
	

}