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
	nodlp* graf = NULL;
	int nrNoduri;
	printf("Nr de noduri: ");
	scanf("%d", &nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		//id-ul va fi i-ul, numele citit de la tastatura
		student s;
		s.id = i;
		char buffer[20];
		printf("Numele studentului : ");
		scanf("%s", &buffer);
		s.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s.nume, buffer);
		graf = inserareLP(graf, s);
	}

	//inserare arce(vecinii pt fiecare nod)
	int nrArce = 0;
	printf("Nr de arce: ");
	scanf("%d", &nrArce);

	for (int i = 0; i < nrArce; i++)
	{
		int idStart;
		printf("Id-ul nodului de start: ");
		scanf("%d", &idStart);
		int idStop;
		printf("Id-ul nodului de stop: ");
		scanf("%d", &idStop);
		inserareArcInGraf(graf, idStart, idStop);
	}

	//afisare
	traversareLP(graf);
	//parcurgere in adancime
	printf("\nParcurgere in adancime de la nodul 1:\n");
	parcurgereAdancime(graf, 0);

	dezalocareLP(graf);
}