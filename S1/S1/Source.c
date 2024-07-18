#include<stdio.h>
#include<malloc.h>

struct Cofetarie {
	char* nume;
	int nrAngajati;
	float* salarii;
};


void afiseazaCofetarie(struct Cofetarie c)
{
	if (c.nume != NULL)
	{
		printf("Nume: %s\n", c.nume);
	}
	printf("Numar angajati: %d\n", c.nrAngajati);
	if (c.salarii != NULL)
	{
		printf("Salarii: ");
		for (int i = 0; i < c.nrAngajati; i++)
		{
			printf("%5.2f,", c.salarii[i]);
		}
	}
	printf("\n");
}

struct Cofetarie initializareCofetarie(const char* nume, int nrAgajati, const float* salarii)
{
	struct Cofetarie c;
	c.nume = malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrAngajati = nrAgajati;
	c.salarii = malloc(sizeof(float) * nrAgajati);
	for (int i = 0; i < nrAgajati; i++)
	{
		c.salarii[i] = salarii[i];
	}
	return c;
}

void stergereCofetarie(struct Cofetarie* c)
{
	if (c->nume != NULL)
	{
		free(c->nume);
	}
	free(c->salarii);
	c->nume = NULL;
	c->salarii = NULL;
}

int main()
{
	struct Cofetarie c1;
	c1.nume = (char*)malloc(strlen("Dulce") + 1);
	strcpy(c1.nume, "Dulce");
	c1.nrAngajati = 3;
	c1.salarii = malloc(sizeof(float) * c1.nrAngajati);
	for (int i = 0; i < c1.nrAngajati; i++)
	{
		c1.salarii[i] = (i + 1) * 1000;
	}
	afiseazaCofetarie(c1);

	float* vector = malloc(sizeof(float) * 2);
	vector[0] = 4567;
	vector[1] = 3456;

	struct Cofetarie c2 = initializareCofetarie("Mara", 2, vector);

	afiseazaCofetarie(c2);

	free(vector);
	stergereCofetarie(&c2);

	afiseazaCofetarie(c2);

	free(c1.nume);
	free(c1.salarii);
	


}
