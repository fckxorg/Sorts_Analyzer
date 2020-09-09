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