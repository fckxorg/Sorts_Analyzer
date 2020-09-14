#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <functional>
#include <cassert>

#include "../constants/constants.hpp"

class Clickable : public sf::Drawable
{
    public:
        virtual bool isUnderCursor(sf::RenderWindow& window) const = 0;
        virtual void onClick(sf::RenderWindow& window) = 0;
        virtual ~Clickable(){};
};

class ButtonTrigger
{
    public:
        virtual void operator()() = 0;
        virtual ~ButtonTrigger(){};
};

class rectButton : public Clickable
{
        sf::RectangleShape base;
        sf::Text text;
        ButtonTrigger* trigger;

    public:
        
        void setSize(sf::Vector2f base_size)
        {
            base.setSize(base_size);
        }

        rectButton()
        {
            base = sf::RectangleShape();
            text = sf::Text();
            trigger = nullptr;
        }

        ~rectButton() = default;

        void setColor(const sf::Color& base_color)
        {
            base.setFillColor(base_color);
        }

        void setTextColor(const sf::Color& text_color)
        {
            text.setFillColor(text_color);
        }

        void setPosition(const sf::Vector2f& pos)
        {
            base.setPosition(pos); // add boundary cases
            text.setPosition(sf::Vector2f(pos.x + 4, pos.y + 10));
        }

        void setTrigger(ButtonTrigger* trigger)
        {
            this->trigger = trigger;
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

        void setTextFont(const sf::Font& font)
        {
            text.setFont(font);
        }

        void setTextSize(const unsigned int& text_size)
        {
            text.setCharacterSize(text_size);
        }

        void setTextString(const char* string)
        {
            assert(string != nullptr);

            text.setString(string);
        }

        void draw (sf::RenderTarget& target, sf::RenderStates states) const override
        {
            target.draw(base);
            target.draw(text);
        }

        bool isUnderCursor(sf::RenderWindow& window) const override
        {
            sf::Vector2i local_position = sf::Mouse::getPosition(window);
            sf::Vector2f button_size  = getSize();
            sf::Vector2f button_pos = getPosition();
            
            if(button_pos.x <= local_position.x 
            && button_pos.y <= local_position.y 
            && button_pos.x + button_size.x >= local_position.x
            && button_pos.y + button_size.y >= local_position.y)
            {
                return true;
            }
            return false;
        }

        void onClick(sf::RenderWindow& window) override
        {
            animatePush(window);
            
            assert(trigger != nullptr);
            (*trigger)();
        }

        void animatePush(sf::RenderWindow& window)
        {
            sf::Color old_color = getColor();
            setColor(sf::Color(old_color.r - 20, old_color.g - 20, old_color.b - 20)); // process values for dark buttons < 20
            
            window.draw(*this);
            window.display();

            std::this_thread::sleep_for(std::chrono::milliseconds(BUTTON_PUSH_ANIMATION_DURATION));
            setColor(old_color);

            window.draw(*this);
            window.display();
        }
};

#endif