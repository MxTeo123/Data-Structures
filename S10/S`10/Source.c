#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct Elev Elev;
typedef struct Nod Nod;

struct Elev
{
	int id;
	int nrMedii;
	float* medii;
};

struct Nod
{
	Elev info;
	Nod* st;
	Nod* dr;
};


void inserareArbore(Nod** rad, Elev e)
{
	if ((*rad) != NULL)
	{
		if ((*rad)->info.id > e.id)

		{
			inserareArbore(&((*rad)->st), e);
		}
		else
		{
			inserareArbore(&((*rad)->dr), e);
		}
	}
	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = e;
		nod->st = NULL;
		nod->dr = NULL;            //inserarea se face intr un nod frunza, nod frunza daca si dr si st e null

		*rad = nod;
	}
}

Elev citireElev(FILE* fp)
{
	Elev e;
	fscanf(fp, "%d",&e.id);
	fscanf(fp, "%d", &e.nrMedii);
	e.medii = malloc(e.nrMedii * sizeof(float));
	for (int i = 0; i < e.nrMedii; i++)
	{
		fscanf(fp, "%d", &e.medii[i]);
	}
	return e;
}


Nod* citireFisier(char* numeFisier)
{
	Nod* arbore = NULL;

	if (numeFisier) {
		return NULL;
	}
	else
	{
		FILE* fp = fopen(numeFisier, "r");
		
		int nrElevi;
		fscanf("%d", &nrElevi);

		for (int i = 0; i < nrElevi; i++)
		{
			Elev e = citireElev(fp);
			inserareArbore(&arbore, e);

		}
		fclose(fp);

	}

	return arbore;
}

void afisareElev(Elev e)
{
	printf("Elevul cu id-ul %d are mediile ", e.id);
	for (int i = 0; i < e.nrMedii; i++)
	{
		printf("%5.2f ", e.medii[i]);
	}
	printf("\n");
}

void afisareInOrdine(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareInOrdine(arbore->st);
		afisareElev(arbore->info);
		afisareInOrdine(arbore->dr);

	}
}

float calculeazaMedie(Elev e)
{
	if (e.nrMedii != 0)
	{


		float sum = 0;
		for (int i = 0; i < e.nrMedii; i++)
		{
			sum += e.medii[i];
		}
		return sum / e.nrMedii;
	}
	else
	{
		printf("elevul nu are medii");
	}
}

float calculeazaSumaNote(Nod* arbore, int* nrNote)
{
	if (arbore != NULL)
	{
		float suma = 0;
		for (int i = 0; i < arbore->info.nrMedii; i++)
		{
			suma += arbore->info.medii[i];
		}
		float sumaS=calculeazaSumaNote(arbore->st, nrNote + arbore->info.nrMedii);
		float sumaD = calculeazaSumaNote(arbore->dr, nrNote + arbore->info.nrMedii);
		return suma + sumaD + sumaS;
	}
	else
	{
		return 0;
	}
}


float calculeazaMedieGenerala(Nod* arbore)
{
	int nrNote = 0;
	float suma= calculeazaSumaNote(arbore, &nrNote);
	if (nrNote > 0)
	{
		return suma / nrNote;
	}
	else
	{
		return 0;
	}
}
void main()
{
	Nod* arbore = citireFisier("Elevi.txt");
	afisareInOrdine(arbore);

	printf("media este: %5.2f", calculeazaMedieGenerala(arbore));

	//3 tipuri de citire: in ordine, pre ordine, post ordine 
	//in ordine - SRD
	//pre ordine - RSD
	//post ordine - SDR
}






