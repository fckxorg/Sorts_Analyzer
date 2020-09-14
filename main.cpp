#include <SFML/Graphics.hpp>
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
#include "GUI/events/events.hpp"
#include "GUI/plot/plot.hpp"

#include "benchmark/benchmark/stat.hpp"
#include "benchmark/sorts/sorts.hpp"
#include "benchmark/benchmark/service.hpp"

Figure left_plot = Figure(PLOT_FIGURE_SIZE, LEFT_PLOT_POS,"array length", "n_compares", ROBOTO_MEDIUM, PRIMARY_LIGHT);
Figure right_plot = Figure(PLOT_FIGURE_SIZE, RIGHT_PLOT_POS,"array length", "n_assignments", ROBOTO_MEDIUM, PRIMARY_LIGHT);

rectButton* createSortButton(const sf::Vector2f& pos, const char* string, ButtonTrigger* trigger)
{
        assert(string != nullptr);
        assert(trigger != nullptr);

        rectButton* button = new rectButton();

        button->setColor(PRIMARY_DARK);
        button->setSize(SORT_BUTTON_SIZE);
        button->setPosition(pos);
        button->setTextFont(ROBOTO_MEDIUM);
        button->setTextColor(PRIMARY_LIGHT);
        button->setTextSize(BUTTON_TEXT_SIZE);
        button->setTextString(string);
        button->setTrigger(trigger);

        return button;
}


template <typename Sort>
class SortBenchmarkTrigger : public ButtonTrigger
{ 
    public:
        void operator()() override
        {
            printf("Trigger invoked\n");
            auto results = benchmarkSort(100, Sort());

            int* n_compares = new int[100]();
            int* n_assignments = new int[100]();
            int* x_vals = new int[100]();

            for(int i = 0; i < 100; ++i)
            {
                x_vals[i] = i;
                n_compares[i] = results[i].first;
                n_assignments[i] = results[i].second;
                printf("%d %d\n", results[i].first, results[i].second);
            }

            left_plot.plotData(x_vals, n_compares, 100, sf::Color::Blue);
            right_plot.plotData(x_vals, n_assignments, 100, sf::Color::Blue);

            clickable_objects.push_back(&left_plot.plots.back());
            clickable_objects.push_back(&right_plot.plots.front());

            delete[] n_compares;
            delete[] n_assignments;
            delete[] x_vals;

        }
};


int main() 
{
    ROBOTO_MEDIUM.loadFromFile("fonts/Roboto-Light.ttf");

    SortBenchmarkTrigger<InsertionSort<Stat<int>>> trigger;

    sf::RenderWindow window(WINDOW_SIZE, "Sorts analyzer");
    sf::RectangleShape rect(PLOT_BACKGROUND_SIZE); //leave it here for graphics background
    rect.setFillColor(SECONDARY_DARK);

    for(int i = 0; i < N_SORT_BUTTONS; ++i) 
    {
        sf::Vector2f pos = sf::Vector2f(FIRST_BUTTON_POS.x + i * SORT_BUTTON_SIZE.x + i * OFFSET, FIRST_BUTTON_POS.y);
        rectButton* button = createSortButton(pos, button_names[i], &trigger);
        clickable_objects.push_back(button);
    }

    while (window.isOpen())
    {
        IS_ANY_CLICKABLE_UNDER_CURSOR = false;
        generateEvents(window);
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
    return 0;
}