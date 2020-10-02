#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <chrono>
#include <thread>
#include <functional>
#include <list>
#include <queue>
#include <cassert>
#include <cmath>

#include "GUI/constants/constants.hpp"
#include "GUI/controls/controls.hpp"
#include "GUI/custom_controls/custom_controls.hpp"
#include "GUI/events/events.hpp"
#include "GUI/plot/plot.hpp"

#include "benchmark/benchmark/stat.hpp"
#include "benchmark/sorts/sorts.hpp"
#include "benchmark/benchmark/service.hpp"

Figure left_plot; 
Figure right_plot;


template <typename Sort>
class SortBenchmarkTrigger : public ButtonTrigger
{ 
    private:
        sf::Color color;
    public:
        explicit SortBenchmarkTrigger<Sort>(const sf::Color& color)
        {
            this->color = color;
        }
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

            left_plot.plotData(x_vals, n_compares, N_SAMPLES, color);
            right_plot.plotData(x_vals, n_assignments, N_SAMPLES, color);

            clickable_objects.push_back(left_plot.plots.back());
            clickable_objects.push_back(right_plot.plots.front());

            delete[] n_compares;
            delete[] n_assignments;
            delete[] x_vals;
            delete[] results;
        }
};

class ClearTrigger : public ButtonTrigger
{
    private:
        Figure* left_plot;
        Figure* right_plot;

    public:
        ClearTrigger(Figure* left_plot, Figure* right_plot) : left_plot(left_plot), right_plot(right_plot){}

        void operator()() override
        {
            left_plot->clear();
            right_plot->clear();
        }
};


int main() 
{
    left_plot = Figure(PLOT_FIGURE_SIZE, LEFT_PLOT_POS,"array length", "n_compares", ROBOTO_MEDIUM, PRIMARY_LIGHT);
    right_plot = Figure(PLOT_FIGURE_SIZE, RIGHT_PLOT_POS,"array length", "n_assignments", ROBOTO_MEDIUM, PRIMARY_LIGHT);

    ROBOTO_MEDIUM.loadFromFile("fonts/Roboto-Light.ttf");

    sf::RenderWindow window(WINDOW_SIZE, "Sorts analyzer");
    sf::RectangleShape rect(PLOT_BACKGROUND_SIZE); //leave it here for graphics background
    rect.setFillColor(SECONDARY_DARK);

    for(int i = 0; i < N_SORT_BUTTONS; ++i) 
    {
        sf::Vector2f pos = sf::Vector2f(FIRST_BUTTON_POS.x + i * SORT_BUTTON_SIZE.x + i * OFFSET, FIRST_BUTTON_POS.y);
        auto trigger = new SortBenchmarkTrigger<InsertionSort<Stat<int>>>(button_colors[i]);
        SortButton* button = new SortButton(pos, button_names[i], trigger, button_colors[i]);
        clickable_objects.push_back(button);
    }

    sf::Vector2f clear_button_pos = sf::Vector2f(FIRST_BUTTON_POS.x + N_SORT_BUTTONS * SORT_BUTTON_SIZE.x + N_SORT_BUTTONS * OFFSET, FIRST_BUTTON_POS.y);
    auto trigger = new ClearTrigger(&left_plot, &right_plot);
    rectButton* clear_button = new rectButton(clear_button_pos, button_names[N_SORT_BUTTONS], trigger);

    clickable_objects.push_back(clear_button);

    while (window.isOpen())
    {
        IS_ANY_CLICKABLE_UNDER_CURSOR = false;
        generateEvents(window);
        if(!event_queue.empty())
        {
            handleEvents(window);

            window.clear(PRIMARY_LIGHT); 
            for(auto& object : clickable_objects)
            {
                window.draw(*object);
            }
            window.draw(rect);
            window.draw(left_plot);
            window.draw(right_plot);
            window.display();
        }
    }

    // cleaning up
    for(auto& object : clickable_objects)
    {
        delete object;
    }

    while(!event_queue.empty())
    {
        Event* event = event_queue.front();
        delete event;
        event_queue.pop();
    }

    
    return 0;
}
