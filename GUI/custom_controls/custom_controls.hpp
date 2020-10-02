#ifndef CUSTOM_CONTROLS_HPP
#define CUSTOM_CONTROLS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include "../controls/controls.hpp"

class SortButton : public rectButton
{
        sf::RectangleShape color_indicator;
    public:
        void setIndicatorSize(const sf::Vector2f& indicator_size);
        
        void setIndicatorColor(const sf::Color& indicator_color);

        sf::Color getIndicatorColor();
        
        void setPosition(const sf::Vector2f& pos);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
};

#endif
