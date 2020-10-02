
#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "../constants/constants.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <functional>
#include <cassert>


class Clickable : public sf::Drawable
{
    public:
        virtual bool isUnderCursor(sf::RenderWindow& window) const = 0;
        virtual void onClick(sf::RenderWindow& window) = 0;
        virtual ~Clickable();
};

class ButtonTrigger
{
    public:
        virtual void operator()() = 0; 
        virtual ~ButtonTrigger();
};

class rectButton : public Clickable
{
        sf::RectangleShape base;
        sf::Text text;
        ButtonTrigger* trigger;

    public:
        void setSize(sf::Vector2f base_size);

        rectButton();
        
        virtual ~rectButton();

        void setColor(const sf::Color& base_color);

        void setTextColor(const sf::Color& text_color);

        void setPosition(const sf::Vector2f& pos);

        void setTrigger(ButtonTrigger* trigger);

        sf::Vector2f getPosition() const;

        sf::Vector2f getSize() const;

        sf::Color getColor() const;

        void setTextFont(const sf::Font& font);

        void setTextSize(const unsigned int& text_size);

        void setTextString(const char* string);

        void draw (sf::RenderTarget& target, sf::RenderStates states) const override;

        bool isUnderCursor(sf::RenderWindow& window) const override;

        void onClick(sf::RenderWindow& window) override;

        void animatePush(sf::RenderWindow& window);
};

#endif
