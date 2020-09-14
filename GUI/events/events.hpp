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

#endif