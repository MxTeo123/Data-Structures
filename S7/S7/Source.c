#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Galerie Galerie;
typedef struct Nod Nod;
typedef struct Hash Hash;


struct Galerie
{
	int cod;
	char* nume;
	float pretIntrare;
};


struct Nod
{
	Galerie info;
	Nod* next;
};

struct Hash
{
	Nod** vector;
	int dim;
};

Hash initializareHash(int dim)
{
	Hash hash;
	hash.dim = dim;
	hash.vector = (Nod**)malloc(sizeof(Nod)*dim);
	for (int i = 0; i < dim; i++)
	{
		hash.vector[i] = NULL;
	}
	return hash;
}

int calculHash(int cod, const char* nume, int dim)
{
	if (dim > 0)
	{
		int rez = cod * strlen(nume);
		return rez % dim;
	}
	return -1;
}

Galerie initGalerie(int cod, const char* nume, float pret) {
	Galerie g;
	g.cod = cod;
	g.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(g.nume, nume);
	g.pretIntrare = pret;
	return g;
}

void inserareLaFinal(Nod** cap, Galerie g)
{
	Nod* temp = malloc(sizeof(Nod));
	temp->info = g;
	temp->next = NULL;
	if (*cap)
	{
		Nod* aux = *cap;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = temp;
	}
	else
	{
		*cap = temp;
	}
}

void afisareGalerie(Galerie g) {
	printf("%d. Intrarea la galeria %s costa %.2f\n", g.cod, g.nume, g.pretIntrare);
}

void afisareListaGalerii(Nod* cap) {
	while (cap) {
		afisareGalerie(cap->info);
		cap = cap->next;
	}
}

void afisareTabela(Hash tabela) {
	for (int i = 0; i < tabela.dim; i++) {
		if (tabela.vector[i] != NULL) {
			printf("Clusterul: %d\n", (i + 1));
			afisareListaGalerii(tabela.vector[i]);
		}
	}
}

void main() {

	Galerie g1 = initGalerie(1, "Orizont", 10);
	Galerie g2 = initGalerie(2, "Cercul armatei", 6);
	Galerie g3 = initGalerie(3, "Louvre", 30);
	Galerie g4 = initGalerie(4, "Antipa", 20);
	Galerie g5 = initGalerie(5, "Istorie", 15);
	Galerie g6 = initGalerie(6, "Geologie", 17);

	Hash tabela = initializareHash(5);

	inserareGalerieInTabela(tabela, g1);
	inserareGalerieInTabela(tabela, g2);
	inserareGalerieInTabela(tabela, g3);
	inserareGalerieInTabela(tabela, g4);
	inserareGalerieInTabela(tabela, g5);
	inserareGalerieInTabela(tabela, g6);

	afisareTabela(tabela);

	printf("cautare:\n");
	//afisareGalerie(g);
}