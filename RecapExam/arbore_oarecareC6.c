#include<stdio.h>
#include<malloc.h>

typedef struct
{
	struct nodAO* adr;
	struct nodAdr* next;
}nodAdr;

typedef struct
{
	int id;
	nodAdr* desc;
}nodAO;

void cautaNod(nodAO* rad, int idp, nodAO** t)
{
	if (rad)
	{
		if (rad->id == idp)
			*t = rad;
		nodAdr* q = rad->desc;
		while (q)
		{
			cautaNod(q->adr, idp, t);
			q = q->next;
		}
	}
}

nodAO* inserareNodAO(nodAO* rad, int idp, int idins)
{
	if (!rad)
	{
		//inserare nod radacina

		nodAO* nou = (nodAO*)malloc(sizeof(nodAO));
		nou->id = idins;
		nou->desc = NULL;
		return nou;
	}
	else
	{
		nodAO* t = NULL;
		cautaNod(rad, idp, &t);
		if (t)
		{
			//inserare nod in lista de descendenti ai nodului t
			nodAO* nou = (nodAO*)malloc(sizeof(nodAO));
			nou->id = idins;
			nou->desc = NULL;			
			nodAdr* q = t->desc;

			//inserare nod in lista de descendenti
			nodAdr* nouAdr = (nodAdr*)malloc(sizeof(nodAdr));
			nouAdr->adr = nou;
			nouAdr->next = NULL;

			if (q)
			{
				while (q->next)
				{
					q = q->next;
					q->next = nouAdr;
				}
			}
			else
			{
				t->desc = nouAdr;
			}

		}
		return rad;
	}

}

void afisare(nodAO* rad)
{
	nodAO* p = rad;
	while (p->desc != NULL)
	{
		printf("\n%d", p->id);
		nodAdr* t = p->desc;
		printf("\n");
		while (t != NULL)
		{
			nodAO* q = t->adr;
			printf("%d", q->id);
			t = t->next;
		}
		if (p->desc)
			p = p->desc->adr;
	}
}

void afisareAO(nodAO* rad)
{
	nodAO* p = rad;
	afisare(p);

	nodAdr* q = rad->desc->next;
	while (q != NULL)
	{
		afisare(q->adr);
		q = q->next;
	}
}

void main()
{
	nodAO* rad = NULL;
	int idP, idIns;

	FILE* f = fopen("arbore_oarecare.txt", "r");
	
	while (!feof(f))
	{
		fscanf(f, "%d", &idP);

		fscanf(f, "%d", &idIns);

		rad = inserareNodAO(rad, idP, idIns);
	}
	fclose(f);

	afisareAO(rad);
}