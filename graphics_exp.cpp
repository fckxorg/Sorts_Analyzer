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
sf::Font ROBOTO_MEDIUM;

bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}



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
}

class Plot 
{

};

class Axis : public sf::Drawable
{
    public:
        sf::VertexArray axis;

        Axis(){}

        Axis(sf::Vector2f axis_start, sf::Vector2f axis_end)
        {
            axis = sf::VertexArray(sf::Lines, 2);
            axis[0].position = axis_start;
            axis[1].position = axis_end;
            axis[0].color = sf::Color::Black;
            axis[1].color = sf::Color::Black;
           
        }

        void draw (sf::RenderTarget& target, sf::RenderStates states) const override
        {
            target.draw(axis);
        }

};

class Figure : public sf::Drawable
{
    public:
        sf::RectangleShape base;
        Axis axisX;
        Axis axisY;
        Plot plot;

        Figure(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
        {
            setSize(size);
            setColor(color);
            setPosition(pos);

            sf::Vector2f axisX_start = sf::Vector2f(pos.x + OFFSET, pos.y + size.y - OFFSET);
            sf::Vector2f axisX_end = sf::Vector2f(axisX_start.x + size.x - 2 * OFFSET, axisX_start.y);

            sf::Vector2f axisY_start = axisX_start;
            sf::Vector2f axisY_end = sf::Vector2f(axisY_start.x, axisY_start.y - size.y + 2 * OFFSET);

            axisX = Axis(axisX_start, axisX_end);
            axisY = Axis(axisY_start, axisY_end);
        }

        void setSize(sf::Vector2f base_size)
        {
            base.setSize(base_size);
        }

        void setColor(const sf::Color& base_color)
        {
            base.setFillColor(base_color);
        }

        void setPosition(const sf::Vector2f& pos)
        {
            base.setPosition(pos); // add boundary cases
        }

        sf::Vector2f getPosition() const
        {
            return base.getPosition();
        }

        sf::Vector2f getSize() const
        {
            return base.getSize();
        }

        sf::Color getColor() const
        {
            return base.getFillColor();
        }


        void draw (sf::RenderTarget& target, sf::RenderStates states) const override
        {
            target.draw(base);
            target.draw(axisX);
            target.draw(axisY);
        }


};

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

    bool IS_ANY_CLICKABLE_UNDER_CURSOR = false;
    std::queue<Event*> event_queue;
    std::list<Clickable*> clickable_objects;

    Figure plot = Figure(sf::Vector2f(600.f, 600.f), sf::Vector2f(50.f, 50.f), PRIMARY_LIGHT);

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Sorts analyzer");
    sf::RectangleShape rect(sf::Vector2f(1600.f, 700.f)); //leave it here for graphics background
    rect.setFillColor(SECONDARY_DARK);

    char button_names[5][20] = {"MergeSort", "QuickSort", "SelectionSort", "InsertionSort", "BubbleSort"};
    for(int i = 0; i < 5; ++i) 
    {
        sf::Vector2f pos = sf::Vector2f(first_button_pos.x + i * SORT_BUTTON_SIZE.x + i * OFFSET, first_button_pos.y);
        rectButton* button = createSortStyledButton(pos, button_names[i]);
        clickable_objects.push_back(button);
    }

    sf::Cursor arrow_cursor;
    arrow_cursor.loadFromSystem(sf::Cursor::Arrow);


    while (window.isOpen())
    {
        IS_ANY_CLICKABLE_UNDER_CURSOR = false;
        generateEvents(window, event_queue, clickable_objects, IS_ANY_CLICKABLE_UNDER_CURSOR);
        handleEvents(window, event_queue);
       
        if(!IS_ANY_CLICKABLE_UNDER_CURSOR)
        {
            window.setMouseCursor(arrow_cursor);
        }

        window.clear(PRIMARY_LIGHT); // clearing window with black color
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