#ifndef CLICKABLE_HPP
#define CLICKABLE_HPP

#include <SFML/Graphics.hpp>

class Clickable : public sf::Drawable
{
    public:
        virtual bool isUnderCursor(sf::RenderWindow& window) const = 0;
        virtual void onClick(sf::RenderWindow& window) = 0;
        virtual ~Clickable();
};



#endif
