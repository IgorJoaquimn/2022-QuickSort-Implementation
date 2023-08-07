#include "str_funcs.h"

void insertionSort(std::string lista[], int inicio, int fim)
{
    std::string key;
    for (int i = inicio + 1; i < fim; i++)
    {
        LEMEMLOG((long int)(&(lista[i])),sizeof(std::string),1);
        key = lista[i];
        int j = i - 1;
        while (j >= 0 && isLessEqual(key, lista[j]))
        {
            ESCREVEMEMLOG((long int)(&(lista[j + 1])),sizeof(std::string),1);
            lista[j + 1] = lista[j];
            j--;
        }
        ESCREVEMEMLOG((long int)(&(lista[j + 1])),sizeof(std::string),1);
        lista[j + 1] = key;
    }
}

int mediana_simples(std::string lista[], int inicio, int fim)
{
    insertionSort(lista, inicio, fim + 1);
    return (fim + inicio) / 2;
}

int mediana(std::string lista[], int inicio, int fim, int m)
{
    int l = inicio + m - 1;
    l = (l > fim) ? inicio + 1 : l;
    return mediana_simples(lista, inicio, l);
}

int partition(std::string lista[], int inicio, int fim, int m)
{
    int indice_mediana = mediana(lista, inicio, fim, m);
    std::swap(lista[indice_mediana], lista[fim]);
    ESCREVEMEMLOG((long int)(&(lista[indice_mediana])),sizeof(std::string),2);
    ESCREVEMEMLOG((long int)(&(lista[fim])),sizeof(std::string),2);

    std::string pivot = lista[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++)
    {
        LEMEMLOG((long int)(&(lista[j])),sizeof(std::string),2);
        if (isLessEqual(lista[j], pivot))
        {
            i++;
            std::swap(lista[i], lista[j]);
            ESCREVEMEMLOG((long int)(&(lista[i])),sizeof(std::string),2);
            ESCREVEMEMLOG((long int)(&(lista[j])),sizeof(std::string),2);

        }
    }
    std::swap(lista[i+1], lista[fim]);
    ESCREVEMEMLOG((long int)(&(lista[i+1])),sizeof(std::string),2);
    ESCREVEMEMLOG((long int)(&(lista[fim])),sizeof(std::string),2);
    return (i + 1);
}

void quicksort(std::string lista[], int inicio, int fim, int size = 0, int m = 0)
{
    if (inicio < fim)
    {
        if ((fim - inicio + 1) <= size)
            insertionSort(lista, inicio, fim + 1);
        else
        {
            int pi = partition(lista, inicio, fim, m);
            quicksort(lista, inicio, pi - 1, size, m);
            quicksort(lista, pi + 1, fim, size, m);
        }
    }
}