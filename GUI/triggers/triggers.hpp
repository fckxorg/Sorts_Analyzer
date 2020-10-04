#ifndef TRIGGERS_HPP
#define TRIGGERS_HPP

#include <SFML/Graphics.hpp>

#include "../button_trigger/button_trigger.hpp"
#include "../plot/plot.hpp"
#include "../../benchmark/benchmark/service.hpp"

template <typename Sort>
class SortBenchmarkTrigger : public ButtonTrigger
{ 
    private:
        sf::Color color;
        Figure* assignments_plot;
        Figure* comparisons_plot;
    public:
        SortBenchmarkTrigger<Sort>(const sf::Color& color, Figure* assignments_plot, Figure* comparisons_plot) : 
            color(color),
            assignments_plot(assignments_plot),
            comparisons_plot(comparisons_plot){}

        void operator()() override
        {
            printf("Trigger invoked\n");
            std::pair<int, int>* results = benchmarkSort(N_SAMPLES, Sort());

            int* n_compares = new int[N_SAMPLES]();
            int* n_assignments = new int[N_SAMPLES]();
            int* x_vals = new int[N_SAMPLES]();

            for(int i = 0; i < N_SAMPLES; ++i)
            {
                x_vals[i] = i;
                n_compares[i] = results[i].first;
                n_assignments[i] = results[i].second;
            }

            comparisons_plot->plotData(x_vals, n_compares, N_SAMPLES, color);
            assignments_plot->plotData(x_vals, n_assignments, N_SAMPLES, color);

            clickable_objects.push_back(comparisons_plot->plots.back());
            clickable_objects.push_back(assignments_plot->plots.front());

            delete[] n_compares;
            delete[] n_assignments;
            delete[] x_vals;
            delete[] results;
        }
};

class ClearTrigger : public ButtonTrigger
{
    private:
        Figure* assignments_plot;
        Figure* comparisons_plot;

    public:
        ClearTrigger(Figure* assignments_plot, Figure* comparisons_plot) : assignments_plot(assignments_plot), comparisons_plot(comparisons_plot){}

        void operator()() override
        {
            assignments_plot->clear();
            comparisons_plot->clear();
        }
};

#endif
