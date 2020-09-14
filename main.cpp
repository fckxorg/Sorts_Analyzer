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
std::list<Clickable*> clickable_objects;

rectButton* createSortStyledButton(const sf::Vector2f& pos, const char* string)
{
        assert(string != nullptr);

        rectButton* button = new rectButton();

        button->setColor(PRIMARY_DARK);
        button->setSize(SORT_BUTTON_SIZE);
        button->setPosition(pos);
        button->setTextFont(ROBOTO_MEDIUM);
        button->setTextColor(PRIMARY_LIGHT);
        button->setTextSize(BUTTON_TEXT_SIZE);
        button->setTextString(string);

        return button;
}

void generateEvents(sf::RenderWindow& window, std::queue<Event*>& event_queue, std::list<Clickable*> clickable_objects, bool& IS_ANY_CLICKABLE_UNDER_CURSOR)
{
    for(auto object : clickable_objects) 
    {
        if(object->isUnderCursor(window))
        {
            IS_ANY_CLICKABLE_UNDER_CURSOR = true;
            HoveredClickable* event = new HoveredClickable();
            event_queue.push(event);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Clicked* event = new Clicked(object);
                event_queue.push(event);
            }
            break;
        }
    }

    if(!IS_ANY_CLICKABLE_UNDER_CURSOR)
    {
        NoHoveredClickable* event = new NoHoveredClickable();
        event_queue.push(event);
    } 
}

void handleEvents(sf::RenderWindow& window, std::queue<Event*>& event_queue)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    while(!event_queue.empty())
    {
        Event* event = event_queue.front();
        event->handle(window);
        event_queue.pop();
        delete event;
    }
}




class InsertionSortBenchmarkTrigger : public ButtonTrigger
{
    public:
        void operator()() override
        {
            printf("Trigger invoked\n");
            auto results = benchmarkSort(100, InsertionSort<Stat<int>>());

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

    bool IS_ANY_CLICKABLE_UNDER_CURSOR = false;
    std::queue<Event*> event_queue;

    auto results = benchmarkSort(100, InsertionSort<Stat<int>>());

    InsertionSortBenchmarkTrigger trigger;
    //trigger();

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Sorts analyzer");
    sf::RectangleShape rect(sf::Vector2f(1600.f, 700.f)); //leave it here for graphics background
    rect.setFillColor(SECONDARY_DARK);



    char button_names[5][20] = {"MergeSort", "QuickSort", "SelectionSort", "InsertionSort", "BubbleSort"};
    for(int i = 0; i < 5; ++i) 
    {
        sf::Vector2f pos = sf::Vector2f(FIRST_BUTTON_POS.x + i * SORT_BUTTON_SIZE.x + i * OFFSET, FIRST_BUTTON_POS.y);
        rectButton* button = createSortStyledButton(pos, button_names[i]);
        button->setTrigger(&trigger);
        clickable_objects.push_back(button);
    }

    while (window.isOpen())
    {
        IS_ANY_CLICKABLE_UNDER_CURSOR = false;
        generateEvents(window, event_queue, clickable_objects, IS_ANY_CLICKABLE_UNDER_CURSOR);
        handleEvents(window, event_queue);

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