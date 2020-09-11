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
sf::Font ROBOTO_MEDIUM;

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

int main() 
{
    ROBOTO_MEDIUM.loadFromFile("fonts/Roboto-Light.ttf");

    int x_vals[] = {0, 1, 2, 3, 4, 5};
    int y_vals[] = {0, 1, 4, 9, 16, 25};

    int linear_x[5] = {0, 1, 2, 3, 4};
    int linear_y[5] = {0, 1, 2, 3, 4};

    bool IS_ANY_CLICKABLE_UNDER_CURSOR = false;
    std::queue<Event*> event_queue;
    std::list<Clickable*> clickable_objects;

    Figure plot = Figure(PLOT_FIGURE_SIZE, sf::Vector2f(50.f, 50.f),"bababa", "bebebe", ROBOTO_MEDIUM, PRIMARY_LIGHT);
    plot.plotData(linear_x, linear_y, 5, sf::Color::Blue);
    plot.plotData(x_vals, y_vals, 6, sf::Color::Red);

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Sorts analyzer");
    sf::RectangleShape rect(sf::Vector2f(1600.f, 700.f)); //leave it here for graphics background
    rect.setFillColor(SECONDARY_DARK);

    char button_names[5][20] = {"MergeSort", "QuickSort", "SelectionSort", "InsertionSort", "BubbleSort"};
    for(int i = 0; i < 5; ++i) 
    {
        sf::Vector2f pos = sf::Vector2f(FIRST_BUTTON_POS.x + i * SORT_BUTTON_SIZE.x + i * OFFSET, FIRST_BUTTON_POS.y);
        rectButton* button = createSortStyledButton(pos, button_names[i]);
        clickable_objects.push_back(button);
    }

    clickable_objects.push_back(&plot.plots.front());
    clickable_objects.push_back(&plot.plots.back());


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
        window.draw(plot);
        window.display();
    }
    return 0;
}