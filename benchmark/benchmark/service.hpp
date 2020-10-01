#ifndef SERVICE_HPP
#define SERVICE_HPP


#include <cassert>
#include <random>
#include <utility>

#include "stat.hpp"
#include "../sorts/sorts.hpp"

void generateArray(Stat<int>* begin, Stat<int>* end, size_t mod = 10);

// TODO replace std::pair<int, int>* with std::pair<int*, int*>

std::pair<int, int>* benchmarkSort(size_t n_samples, const AbstractSort<Stat<int>>& sort);
#endif
