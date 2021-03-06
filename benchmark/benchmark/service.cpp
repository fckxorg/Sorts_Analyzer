#include "service.hpp"

void generateArray(Stat<int>* begin, Stat<int>* end, size_t mod) 
{
    assert(begin != nullptr);
    assert(end != nullptr);

    for(Stat<int>* current = begin; current != end; ++current)
    {
        *current = rand() % mod;
    }
}

std::pair<int, int>* benchmarkSort(size_t n_samples, const AbstractSort<Stat<int>>& sort)
{
    auto results = new std::pair<int, int>[n_samples]();
    Stat<int>* array = new Stat<int>[n_samples]();

    for(size_t current_size = 1; current_size < n_samples; ++current_size) 
    {
        Stat<int>::n_comparisons = 0;
        Stat<int>::n_assignments = 0;
        generateArray(array, array + current_size);
        sort(array, array + current_size);
        results[current_size] = {Stat<int>::n_comparisons, Stat<int>::n_assignments};
    }

    delete[] array;
    return results;
}



