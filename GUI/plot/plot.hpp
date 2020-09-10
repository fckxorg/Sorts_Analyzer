#ifndef PLOT_HPP
#define PLOT_HPP

#include <SFML/Graphics.hpp>

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

#endif