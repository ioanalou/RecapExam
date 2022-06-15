#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int id;
	char* nume;
}student;

typedef struct
{
	struct nodLS* next;
	struct nodLP* info;
}nodLS;

typedef struct
{
	struct nodLS* vecini;
	student info;
	struct nodLP* next;
}nodLP;

nodLP* inserareLP(nodLP* cap, student s)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->info.id = s.id;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);

	nou->vecini = NULL;
	nou->next = NULL;

	if (cap)
	{
		nodLP* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
		return cap;
	}
	else
	{
		return nou;
	}
}

nodLS* inserareLS(nodLS* cap, nodLP* info)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info = info;
	nou->next = NULL;
	if (cap)
	{
		nodLS* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
		return cap;
	}
	else
	{
		return nou;
	}
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		nodLP* temp2 = temp->info;
		printf("%d.%s", temp2->info.id + 1, temp2->info.nume);
		temp = temp->next;
	}
}

void traversareLP(nodLP* cap)
{
	nodLP* temp = cap;
	while (temp)
	{
		printf("%d.%s are urmatorii vecini: \n", temp->info.id + 1, temp->info.nume);
		traversareLS(temp->vecini);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP* cap)
{
	nodLP* temp = cap;
	while (temp)
	{
		nodLP* temp2 = temp->next;
		if (temp->vecini)
			dezalocareLS(temp->vecini);
		printf("\nAm sters: %s", temp->info.nume);
		free(temp->info.nume);
		free(temp);
		temp = temp2;
	}
}

void main()
{

}