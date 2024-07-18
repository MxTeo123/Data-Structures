#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Biblioteca Biblioteca;

struct Biblioteca {
    char* nume;
    int nrCarti;
    int nrCititori;
};
typedef struct Nod Nod;
struct Nod {
    Biblioteca info;
    Nod* prev;
    Nod* next;
};
typedef struct ListaDubla ListaDubla;
struct ListaDubla {
    Nod* head;
    Nod* tail;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca b;
    b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(b.nume, nume);
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}

void inserareInceput(ListaDubla* listaDubla, Biblioteca b) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->info = b;
    nod->next = listaDubla->head;
    nod->prev = NULL;
    if (listaDubla->head) {
        listaDubla->head->prev = nod;
        
    }
    else {
        listaDubla->tail = nod;
    }
    listaDubla->head = nod;
    
}
void afisareInceputLista(ListaDubla lista) {
    while (lista.head) {
        printf("Biblioteca: %s,numar cititori %d, numar carti %d\n"
            , lista.head->info.nume, lista.head->info.nrCarti, lista.head->info.nrCititori);
        lista.head = lista.head->next;
    }
}

void stergeNodNume(ListaDubla* listaDubla, const char* nume)
{
    Nod* aux = listaDubla->head;
    while (aux && strcmp(nume, aux->info.nume)!=0)
    {
        aux = aux->next;
    }
    if (aux == listaDubla->head)
    {
        if (aux == listaDubla->tail)
        {
            listaDubla->head = NULL;
            listaDubla->tail = NULL;
        }
        else
        {
            listaDubla->head = listaDubla->head->next;
            listaDubla->head->prev = NULL;
        }
    }
    else
    {
        if (aux == listaDubla->tail)
        {
            aux->prev->next = NULL;
            listaDubla->tail = aux->prev;
        }
        else
        {
            aux->next->prev = aux->prev;
            aux->prev->next = aux->prev;
        }
    }
    free(aux->info.nume);
    free(aux);
}

void stergeToataLista(ListaDubla* listaDubla)
{
    while (listaDubla->head)
    {
        free(listaDubla->head->info.nume);
        Nod* aux = listaDubla->head;
        listaDubla->head = listaDubla->head->next;
        free(aux);
    }
    listaDubla->head = NULL;
    listaDubla->tail = NULL;
}

int nrCartiTotal(ListaDubla listaDubla)
{
    int rezultat = 0;
    while (listaDubla.tail)
    {
        listaDubla.tail = listaDubla.tail->prev;
        listaDubla.tail = listaDubla.tail->next;
    }
    return rezultat;
}


void main() {
    
    Biblioteca b1 = initializare("Mihai Eminescu", 150, 30);
    Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
    Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);

    ListaDubla listaDubla;
    listaDubla.head = NULL;
    listaDubla.tail = NULL;

    inserareInceput(&listaDubla, b1);
    inserareInceput(&listaDubla, b2);
    inserareInceput(&listaDubla, b3);
   
    afisareInceputLista(listaDubla);

   /* stergeNodNume(&listaDubla, "Ioan Slavici");
    afisareInceputLista(listaDubla);
    stergeNodNume(&listaDubla, "Mihai Eminescu");
    afisareInceputLista(listaDubla);
    stergeNodNume(&listaDubla, "Tudor Arghezi");
    afisareInceputLista(listaDubla);*/

    /*stergeToataLista(&listaDubla);
    afisareInceputLista(listaDubla);*/

    int rezultat = nrCartiTotal(listaDubla);
    printf("nr total de carti: %d", rezultat);


}