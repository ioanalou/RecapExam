#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int varsta;
	char* nume;
	float medie;
}student;

typedef struct
{
	student inf;
	struct nodCoada* next;
}nodCoada;

typedef struct
{
	student inf;
	struct nodStiva* next;
}nodStiva;

void put(nodCoada** prim, nodCoada** ultim, student s)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));

	nou->inf.varsta = s.varsta;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;

	nou->next = NULL;

	if (*prim == NULL && *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, student* s)
{
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
	else
	{
		(*s).varsta = (*prim)->inf.varsta;
		(*s).nume = (char*)malloc((strlen((*prim)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*prim)->inf.nume);
		(*s).medie = (*prim)->inf.medie;

		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.nume);
		free(temp);
		return 0;
	}
}

void traversareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp)
	{
		printf("\nVarsta: %d, Nume: %s, Medie: %5.2f",
			temp->inf.varsta, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void conversieCoadaVector(nodCoada** prim, nodCoada** ultim, student* vect, int* nr)
{
	student s;
	while (get(prim, ultim, &s) == 0)
	{
		vect[*nr] = s;
		(*nr)++;
	}
}

void push(nodStiva** varf, student s)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	
	nou->inf.varsta = s.varsta;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;

	nou->next = NULL;

	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, student* s)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*s).varsta = (*varf)->inf.varsta;
		(*s).nume = (char*)malloc((strlen((*varf)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*varf)->inf.nume);
		(*s).medie = (*varf)->inf.medie;

		nodStiva* temp = *varf;
		(*varf) = (*varf)->next;
		free(temp->inf.nume);
		free(temp);
		return 0;
	}
}

void traversareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp)
	{
		printf("\nVarsta: %d, Nume: %s, Medie: %5.2f",
			temp->inf.varsta, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void conversieCoadaStiva(nodCoada** prim, nodCoada** ultim, nodStiva** varf)
{
	student s;
	while (get(prim, ultim, &s) == 0)
		push(varf, s);
}

void main()
{
	int n;

	nodCoada* prim = NULL, * ultim = NULL;
	student s;
	char buffer[20];
	FILE* f = fopen("fisierCoadaC3.txt", "r");
	fscanf(f, "%d", &n);

	

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.varsta);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		put(&prim, &ultim, s);
		free(s.nume);
	}
	fclose(f);
	traversareCoada(prim);

	student s1;
	get(&prim, &ultim, &s1);
	printf("\nStudentul extras se numeste %s ", s1.nume);
	free(s1.nume);

	printf("\n*************************CONVERSIE COADA-VECTOR************************");
	student* vect = (student*)malloc(n * sizeof(student));
	int nr = 0;
	conversieCoadaVector(&prim, &ultim, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nVarsta: %d, Nume: %s, Medie: %5.2f",
			vect[i].varsta, vect[i].nume, vect[i].medie);
	for (int i = 0; i < nr; i++)
		free(vect[i].nume);
	free(vect);

	printf("\n*************************CONVERSIE COADA-STIVA************************");
	nodStiva* varf = NULL;
	conversieCoadaStiva(&prim, &ultim, &varf);
	traversareStiva(varf);

	while (pop(&varf, &s1) == 0)
		free(s1.nume);


	/*while (get(&prim, &ultim, &s) == 0) {
		free(s.nume);
	}*/
}