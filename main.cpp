#include <iostream>
#include <random>
#include <utility>

#include "sorts.h"
#include "stat.h"

void generateArray(Stat<int>* array, size_t size, int mod = 10) 
{
    for(size_t i = 0; i < size; ++i)
    {
        array[i] = rand() % mod;
    }
}

std::pair<int, int>* benchmarkSort(size_t n_samples, AbstractSort<Stat<int>>&& sort)
{
    auto results = new std::pair<int, int>[n_samples]();

    for(size_t current_size = 1; current_size < n_samples; ++current_size) 
    {
        Stat<int>::n_comparisons = 0;
        Stat<int>::n_assignments = 0;

        Stat<int>* array = new Stat<int>[current_size]();
        generateArray(array, current_size);
        sort(array, array + current_size);
        results[current_size] = {Stat<int>::n_comparisons, Stat<int>::n_assignments};

        delete[] array;
    }

    return results;
}


int main(int argc, char** argv)
{
    const size_t N_SAMPLES = 100;

    /*Stat<int>* array = new Stat<int>[N_SAMPLES]();
    generateArray(array, N_SAMPLES);
    auto sort = InsertionSort<Stat<int>>();
    sort(array, array + N_SAMPLES);
    printf("%d %d\n", Stat<int>::n_assignments, Stat<int>::n_comparisons);
*/

   auto results = benchmarkSort(N_SAMPLES, InsertionSort<Stat<int>>());


    printf("|  Array size | Comparisons | Assignments |\n");
    for(size_t i = 0; i < N_SAMPLES; ++i) 
    {
        printf("| %11.1d | %11.1d | %11.1d |\n", i, results[i].first, results[i].second);
    }

    delete[] results;
}
