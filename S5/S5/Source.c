#include<stdio.h>
#include<malloc.h>


typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

struct Biblioteca
{
	char* nume;
	int nrCarti;
	int nrCititori;
};


struct Nod {
	Biblioteca info;
	Nod* next;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori)
{
	Biblioteca b;
	b.nume = (char*)malloc(sizeof(char*) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = b.nrCarti;
	b.nrCititori = nrCititori;
	return b;
}

Nod* inserareInceput(Nod* cap, Biblioteca b)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializare(b.nume, b.nrCarti, b.nrCititori);
	nou->next = cap;
	return nou;
}

void afisareLista(Nod* cap)
{
	while (cap!= NULL)
	{
		printf("biblioteca %s are %d carti si %d cititori\n",
			cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
		cap = cap->next;
	}
}

char* getBibliotecaNrCartiPerCititor(Nod* cap)
{
	float max = 0;
	const char* nume_aux = NULL;
	while (cap)
	{
		//procesare
		if (cap->info.nrCarti / cap->info.nrCititori > max)
		{
			max = cap->info.nrCarti / cap->info.nrCititori;
			nume_aux = cap->info.nume;
		}
		cap = cap->next;
	}
	char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux) + 1));
	strcpy(nume, nume_aux);
	return nume;
}

void stergeLista(Nod** cap)
{
	while ((*cap)!=NULL)
	{
		free((*cap)->info.nume);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
}

void inserareSfarsit(Nod** cap, Biblioteca b)
{
	Nod* sfarsit = (Nod*)malloc(sizeof(Nod));
	sfarsit->info = initializare(b.nume, b.nrCarti, b.nrCititori);
	sfarsit->next = NULL;
	if ((*cap) != NULL)
	{
		Nod* capA = (*cap);
		while (capA->next!=NULL)
		{
			capA = capA->next;
		}
		capA->next = sfarsit;
	}
	else
	{
		*cap = sfarsit;
		
	}
}

int main()
{
	Nod* cap = NULL;
	Biblioteca b1 = initializare("Mihai Eminescu", 4, 2);
	cap = inserareInceput(cap, b1);
	Biblioteca b2 = initializare("Ioan Slavici", 10, 8);
	cap = inserareInceput(cap, b2);
	Biblioteca b3 = initializare("Mihail Sadoveanu", 6, 5);
	cap = inserareInceput(cap, b3);
	
	afisareLista(cap);
	char* numeDeAfisat = getBibliotecaNrCartiPerCititor(cap);
	printf("biblioteca cu nr max de cititori este %s", getBibliotecaNrCartiPerCititor(cap));
	free(numeDeAfisat);
	Biblioteca b4 = initializare("Tudor Arghezi", 9, 8);
	inserareSfarsit(&cap, b4);
	afisareLista(cap);
	stergeLista(&cap);
	free(b1.nume);
	free(b2.nume);
	free(b3.nume);
	free(b4.nume);
}
//stergere nod din mijloc
//interschimbarea a 2 noduri