#ifndef PLOT_HPP
#define PLOT_HPP

#include <SFML/Graphics.hpp>
#include <list>

#include "../controls/controls.hpp"

int max_in_array(const int* array, const int n_elements)
{
    int max_elem = array[0];
    for(int i = 1; i < n_elements; ++i)
    {
        if(array[i] > max_elem)
        {
            max_elem = array[i];
        }
    }
    return max_elem;
}

class Plot : public Clickable
{
    private:
        sf::VertexArray plot;
        int n_elements;
        sf::Vector2f start_point;
        float max_y_coord;
        float max_x_coord;
        float x_step;
        float y_step;

        float scale_value(const float value, const float step, const float offset)
        {
            return value * step + offset;
        }
        
        float unscale_value(const float value, const float step, const float offset)
        {
            return (value - offset) / step;
        }

    public:

        Plot(){};

        Plot(sf::Vector2f start_point, 
            const int* x_values, 
            const int* y_values, 
            const int n_elements, 
            const float x_step, 
            const float y_step, 
            sf::Color color) : start_point(start_point), n_elements(n_elements), max_x_coord(0), max_y_coord(0), x_step(x_step), y_step(y_step)
        {
            assert(x_values != nullptr);
            assert(y_values != nullptr);

            plot = sf::VertexArray(sf::LineStrip, n_elements);

            printf("Plot vertices: \n");
            for(int i = 0; i < n_elements; ++i) {
                float curr_x_val = scale_value(x_values[i], x_step, start_point.x);
                float curr_y_val = scale_value(y_values[i], y_step, start_point.y);

                max_x_coord = max_x_coord < curr_x_val ? curr_x_val : max_x_coord;
                max_y_coord = max_y_coord < curr_y_val ? curr_y_val : max_y_coord;

                printf("(%.2f, %.2f)\n", curr_x_val, curr_y_val);
                plot[i].position = sf::Vector2f(curr_x_val, curr_y_val);
                plot[i].color = color;
            }   
        }

        void rescale(const float new_x_step, const float new_y_step, const float old_x_step, const float old_y_step)
        {
            for(int i = 0; i < n_elements; ++i)
            {
                printf("Iteration %d\n", i);
                plot[i].position.x = scale_value(unscale_value(plot[i].position.x, old_x_step, start_point.x), new_x_step, start_point.x);
                plot[i].position.y = scale_value(unscale_value(plot[i].position.y, old_y_step, start_point.y), new_y_step, start_point.y);
                x_step = new_x_step;
                y_step = new_y_step;
            }
        }

        void draw (sf::RenderTarget& target, sf::RenderStates states) const override
        {
            target.draw(plot);
        }

        bool isUnderCursor(sf::RenderWindow& window) const override 
        {
            for(int i = 1; i < n_elements; ++i)
            {
                sf::Vector2f first_vertex = plot[i].position;
                sf::Vector2f second_vertex = plot[i - 1].position;
                
                float k_coeff = (first_vertex.y - second_vertex.y) / (first_vertex.x - second_vertex.x);
                float b_coeff = first_vertex.y - k_coeff * first_vertex.x;

                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

                if(abs(mouse_position.y - mouse_position.x * k_coeff - b_coeff) < EPSILON && mouse_position.x < max_x_coord && mouse_position.y < max_y_coord)
                {
                    printf("Hovered plot at (%d, %d)\n", mouse_position.x, mouse_position.y);
                    return true;
                }
            }
            return false;
        }

        virtual void onClick(sf::RenderWindow& window) override 
        {
            sf::Font ROBOTO_MEDIUM;
            ROBOTO_MEDIUM.loadFromFile("fonts/Roboto-Light.ttf");
            sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
            sf::Text hint;
            hint.setFillColor(sf::Color::Black);
            hint.setFont(ROBOTO_MEDIUM);
            hint.setPosition(mouse_position.x + 15.f, mouse_position.y);
            hint.setCharacterSize(15);
            hint.setString("(test_hint)");

            window.draw(hint);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }

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
        std::list<Plot> plots;
        int y_max_value;
        int x_max_value;
        float x_step;
        float y_step;

        Figure (const sf::Vector2f size, 
                const sf::Vector2f pos, 
                const char* x_label, const char* y_label, 
                sf::Font& font,
                const sf::Color& base_color = sf::Color::White,
                const unsigned int& label_size = 15,
                const sf::Color& label_color = sf::Color::Black) : x_max_value(0), y_max_value(0)
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

            axisX.setLabelSize(label_size);
            axisY.setLabelSize(label_size);

            axisX.setLabelColor(label_color);
            axisY.setLabelColor(label_color);

            axisX.setLabelFont(font);
            axisY.setLabelFont(font);

            axisX.setLabelPosition(sf::Vector2f((axisX_start.x + axisX_end.x) / 2, axisX_start.y + LABEL_OFFSET));
            axisY.setLabelPosition(sf::Vector2f(axisY_start.x - 2 * LABEL_OFFSET, (axisY_start.y + axisY_end.y) / 2));

        }

        void plotData(const int* x_values, const int* y_values, const int n_values, const sf::Color color)
        {
            printf("Plotting data...\n");
            const int new_plot_x_max_value = static_cast<float>(max_in_array(x_values, n_values));
            const int new_plot_y_max_value = static_cast<float>(max_in_array(y_values, n_values));

            printf("Data max values are x: %d, y: %d\n", new_plot_x_max_value, new_plot_y_max_value);

            if(new_plot_x_max_value > x_max_value) 
            {
                x_max_value = new_plot_x_max_value;
                float new_x_step = (axisX.axis[1].position.x - axisX.axis[0].position.x) / static_cast<float>(x_max_value);
                for(auto& plot : plots) 
                {
                    plot.rescale(new_x_step, y_step, x_step, y_step);
                }

                x_step = new_x_step;
            }

            if(new_plot_y_max_value > y_max_value)
            {
                y_max_value = new_plot_y_max_value;
                float new_y_step = (axisY.axis[1].position.y - axisY.axis[0].position.y) / static_cast<float>(y_max_value);
                for(auto& plot : plots) 
                {
                    plot.rescale(x_step, new_y_step, x_step, y_step);
                }

                y_step = new_y_step;
            }

            printf("Figure adjusted max values are x: %d, y: %d\n", x_max_value, y_max_value);

            printf("Figure adjusted steps are x_step: %.2f, y_step: %.2f\n", x_step, y_step);
            printf("Creating plot...\n");
            plots.push_back(Plot(axisX.axis[0].position, x_values, y_values, n_values, x_step, y_step, color));
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

            for(auto& plot : plots)
            {
                target.draw(plot);
            }
        }
};

#endif