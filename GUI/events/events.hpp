#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SFML/Graphics.hpp>
#include <cassert>
#include <queue>
#include <list>

#include "../controls/controls.hpp"


class Event
{
    public:
        virtual ~Event();
        virtual void handle(sf::RenderWindow& window) = 0;
};

extern std::queue<Event*> event_queue;
extern std::list<Clickable*> clickable_objects;
extern bool IS_ANY_CLICKABLE_UNDER_CURSOR;

class NoHoveredClickable : public Event
{
    public:
    ~NoHoveredClickable() = default;
    NoHoveredClickable() = default;
    void handle(sf::RenderWindow& window) override;
};

class HoveredClickable : public Event
{
    public:
        ~HoveredClickable() = default;
        HoveredClickable() = default;
        void handle(sf::RenderWindow& window) override;

};

class Clicked : public Event
{
    private:
        Clickable* object;
    public:
        ~Clicked() = default;

        Clicked(Clickable* object);

        void handle(sf::RenderWindow& window) override;
};

void handleEvents(sf::RenderWindow& window);

void generateEvents(sf::RenderWindow& window);

#endif
