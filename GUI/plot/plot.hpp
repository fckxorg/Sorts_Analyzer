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
        sf::Text label;

        Axis(){}

        Axis(sf::Vector2f axis_start, sf::Vector2f axis_end)
        {
            axis = sf::VertexArray(sf::Lines, 2);
            axis[0].position = axis_start;
            axis[1].position = axis_end;
            axis[0].color = sf::Color::Black;
            axis[1].color = sf::Color::Black;
           
        }

        void setLabelString(const char* string)
        {
            label.setString(string);
        }

        void setLabelFont(sf::Font& font)
        {
            label.setFont(font);
        }

        void setLabelSize(const unsigned int& size)
        {
            label.setCharacterSize(size);
        }

        void setLabelPosition(const sf::Vector2f& pos)
        {
            label.setPosition(pos);
            if(axis[0].position.x == axis[1].position.x)
            {
                label.rotate(-90.f);
            }
        }

        void setLabelColor(const sf::Color& color)
        {
            label.setFillColor(color);
        }

        void draw (sf::RenderTarget& target, sf::RenderStates states) const override
        {
            target.draw(axis);
            target.draw(label);
        }

};

class Figure : public sf::Drawable
{
    public:
        sf::RectangleShape base;
        Axis axisX;
        Axis axisY;
        Plot plot;

        Figure(sf::Vector2f size, sf::Vector2f pos, sf::Color base_color, const char* x_label, const char* y_label)
        {
            setSize(size);
            setColor(base_color);
            setPosition(pos);

            sf::Vector2f axisX_start = sf::Vector2f(pos.x + OFFSET, pos.y + size.y - OFFSET);
            sf::Vector2f axisX_end = sf::Vector2f(axisX_start.x + size.x - 2 * OFFSET, axisX_start.y);

            sf::Vector2f axisY_start = axisX_start;
            sf::Vector2f axisY_end = sf::Vector2f(axisY_start.x, axisY_start.y - size.y + 2 * OFFSET);

            axisX = Axis(axisX_start, axisX_end);
            axisY = Axis(axisY_start, axisY_end);

            axisX.setLabelString(x_label);
            axisY.setLabelString(y_label);

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