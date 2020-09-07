#include <iostream>
#include <random>

#include "sorts.h"
#include "stat.h"

void generateArray(Stat<int>* array, size_t size, int mod = 10) 
{
    for(size_t i = 0; i < size; ++i)
    {
        array[i] = rand() % mod;
    }
}

void printArray(Stat<int>* array, size_t size) 
{
    for(size_t i = 0; i < size; ++i)
    {
        printf("%d ", array[i].value);
    }
    printf("\n");
}



int main(int argc, char** argv)
{
    const size_t ARRAY_SIZE = 10;

    Stat<int>::n_assignments = 0;
    Stat<int>::n_comparisons = 0;

    Stat<int>* array = new Stat<int>[ARRAY_SIZE]();
    generateArray(array, ARRAY_SIZE);
    printArray(array, ARRAY_SIZE);
    insertionSort(array, array + ARRAY_SIZE);
    printArray(array, ARRAY_SIZE);

    printf("Comaprisons: %d\n", Stat<int>::n_comparisons);
    printf("Assignments: %d\n", Stat<int>::n_assignments);

}
