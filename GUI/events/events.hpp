#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SFML/Graphics.hpp>
#include <cassert>

#include "../controls/controls.hpp"


class Event
{
    public:
        virtual ~Event(){};
        virtual void handle(sf::RenderWindow& window) = 0;
};

std::queue<Event*> event_queue;
std::list<Clickable*> clickable_objects;
bool IS_ANY_CLICKABLE_UNDER_CURSOR = false;

class NoHoveredClickable : public Event
{
    public:
    ~NoHoveredClickable() = default;
    NoHoveredClickable() = default;
    void handle(sf::RenderWindow& window) override
    {
        sf::Cursor arrow_cursor;
        arrow_cursor.loadFromSystem(sf::Cursor::Arrow);
        window.setMouseCursor(arrow_cursor);
    }
};

class HoveredClickable : public Event
{
    public:
        ~HoveredClickable() = default;
        HoveredClickable() = default;
        void handle(sf::RenderWindow& window) override
        {
            sf::Cursor hand_cursor;
            hand_cursor.loadFromSystem(sf::Cursor::Hand);
            window.setMouseCursor(hand_cursor);
        }

};

class Clicked : public Event
{
    private:
        Clickable* object;
    public:
        ~Clicked(){}

        Clicked(Clickable* object)
        {
            assert(object != nullptr);
            this->object = object;
        }

        void handle(sf::RenderWindow& window) override
        {
            object->onClick(window);
        }
};

void handleEvents(sf::RenderWindow& window)
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

void generateEvents(sf::RenderWindow& window)
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


#endif