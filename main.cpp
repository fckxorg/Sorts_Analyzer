#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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
#include "GUI/triggers/triggers.hpp"

#include "benchmark/benchmark/stat.hpp"
#include "benchmark/sorts/sorts.hpp"
#include "benchmark/benchmark/service.hpp"

class App
{
    private:
        Figure comparisons_plot;
        Figure assignments_plot;

        sf::RenderWindow window;
        sf::RectangleShape plots_background;
    public:
        App() : window(WINDOW_SIZE, "Sorts analyzer")
        {
            comparisons_plot = Figure(PLOT_FIGURE_SIZE, LEFT_PLOT_POS,"array length", "n_compares", ROBOTO_MEDIUM, PRIMARY_LIGHT);
            assignments_plot = Figure(PLOT_FIGURE_SIZE, RIGHT_PLOT_POS,"array length", "n_assignments", ROBOTO_MEDIUM, PRIMARY_LIGHT);
            ROBOTO_MEDIUM.loadFromFile("fonts/Roboto-Light.ttf");

            plots_background = sf::RectangleShape(PLOT_BACKGROUND_SIZE); //leave it here for graphics background
            plots_background.setFillColor(SECONDARY_DARK);
            plots_background.setPosition(sf::Vector2f(0.f, 0.f));
            
            for(int i = 0; i < N_SORT_BUTTONS; ++i) 
            {
                sf::Vector2f pos = sf::Vector2f(FIRST_BUTTON_POS.x + i * SORT_BUTTON_SIZE.x + i * OFFSET, FIRST_BUTTON_POS.y);
                auto trigger = new SortBenchmarkTrigger<InsertionSort<Stat<int>>>(button_colors[i], &assignments_plot, &comparisons_plot);
                SortButton* button = new SortButton(pos, button_names[i], trigger, button_colors[i]);
                clickable_objects.push_back(button);
            }

            sf::Vector2f clear_button_pos = sf::Vector2f(FIRST_BUTTON_POS.x + N_SORT_BUTTONS * SORT_BUTTON_SIZE.x + N_SORT_BUTTONS * OFFSET, FIRST_BUTTON_POS.y);
            auto trigger = new ClearTrigger(&assignments_plot, &comparisons_plot);
            rectButton* clear_button = new rectButton(clear_button_pos, button_names[N_SORT_BUTTONS], trigger);

            clickable_objects.push_back(clear_button);
        }

        void run()
        {
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
                    window.draw(plots_background);
                    window.draw(assignments_plot);
                    window.draw(comparisons_plot);
                    window.display();
                }
            }
        }

        ~App()
        {
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
        }
        

};


int main() 
{
    App app;
    app.run();
    return 0;
}
