#include "custom_controls.hpp"
#include <SFML/System/Vector2.hpp>

void SortButton::setIndicatorSize(const sf::Vector2f& indicator_size) 
{
    color_indicator.setSize(indicator_size);
}

void SortButton::setIndicatorColor(const sf::Color& indicator_color)
{
    color_indicator.setFillColor(indicator_color);
}

sf::Color SortButton::getIndicatorColor()
{
    return color_indicator.getFillColor();
}

void SortButton::setPosition(const sf::Vector2f& pos)
{
    rectButton::setPosition(pos);
    sf::Vector2f button_pos = rectButton::getPosition(); 
    sf::Vector2f button_size = rectButton::getSize();
    sf::Vector2f color_indicator_size = color_indicator.getSize();

    const float color_indicator_pos_x = button_pos.x + button_size.x - color_indicator_size.x - COLOR_INDICATOR_OFFSET;
    
    sf::Vector2f indicator_pos = sf::Vector2f(color_indicator_pos_x, button_pos.y + COLOR_INDICATOR_OFFSET); 

    color_indicator.setPosition(indicator_pos);
    
}

void SortButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    rectButton::draw(target, states);
    target.draw(color_indicator);
}
SortButton::SortButton(const sf::Vector2f& pos, const char* string, const sf::Color indicator_color, ButtonTrigger* trigger)
        {
            assert(string != nullptr);
            assert(trigger != nullptr);


            this->setColor(PRIMARY_DARK);
            this->setSize(SORT_BUTTON_SIZE);
            this->setTextFont(ROBOTO_MEDIUM);
            this->setTextColor(PRIMARY_LIGHT);
            this->setTextSize(BUTTON_TEXT_SIZE);
            this->setTextString(string);
            this->setTrigger(trigger);
            
            this->setIndicatorColor(indicator_color);
            this->setIndicatorSize(sf::Vector2f(20.f, 20.f));

            this->setPosition(pos);

        }



