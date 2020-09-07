#include <iostream>
#include <random>

#include "sorts.h"


int main(int argc, char** argv)
{
    int* array = new int[1]();
    for(size_t i = 0; i < 1; ++i)
    {
        array[i] = rand() % 10;
    }

    for(size_t i = 0; i < 1; ++i)
    {
        printf("%d ", array[i]);
    }

    printf("\n");

    insertionSort(array, array + 1);

    for(size_t i = 0; i < 1; ++i)
    {
        printf("%d ", array[i]);
    }
}
