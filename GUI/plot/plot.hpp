#ifndef PLOT_HPP
#define PLOT_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <cmath>

#include "../constants/constants.hpp"
#include "../controls/controls.hpp"

class Tick : public sf::Drawable
{
    private:
        sf::RectangleShape tick;
        sf::Text label;
    public:
        Tick() = delete;
        ~Tick() = default;

        Tick(sf::Vector2f pos, sf::Vector2f size, float value, bool rotate);
        void draw (sf::RenderTarget& target, sf::RenderStates states) const override;
};

int max_in_array(const int* array, const int n_elements);

class Plot : public Clickable
{
    private:
        sf::VertexArray plot;
        sf::Vector2f start_point;
        float max_y_coord;
        float max_x_coord;
        float x_step;
        float y_step;
        char hint_buffer[HINT_BUFFER_SIZE];

        float scale_value(const float value, const float step, const float offset);
        
        float unscale_value(const float value, const float step, const float offset);

    public:

        Plot();

        Plot(sf::Vector2f start_point, 
            const int* x_values, 
            const int* y_values, 
            const int n_elements, 
            const float x_step, 
            const float y_step, 
            sf::Color color);

        void rescale(const float new_x_step, const float new_y_step, const float old_x_step, const float old_y_step);

        void draw (sf::RenderTarget& target, sf::RenderStates states) const override;

        bool isUnderCursor(sf::RenderWindow& window) const override;

        virtual void onClick(sf::RenderWindow& window) override;

};

class Axis : public sf::Drawable
{
    public:
        sf::VertexArray axis;
        sf::Text label;

        Axis();

        Axis(sf::Vector2f axis_start, sf::Vector2f axis_end);
       

        void setLabelString(const char* string);

        void setLabelFont(sf::Font& font);

        void setLabelSize(const unsigned int& size);

        void setLabelPosition(const sf::Vector2f& pos);

        void setLabelColor(const sf::Color& color);

        void draw (sf::RenderTarget& target, sf::RenderStates states) const override;

};

class Figure : public sf::Drawable
{
    private:
        float selectTickStep(float max_value);

        void rescale_X(const int new_x_max_value);

        void rescale_Y(const int new_y_max_value);

        void rescale_ticks(const float max_value, bool y_axis);

    public:
        sf::RectangleShape base;
        Axis axisX;
        Axis axisY;
        std::list<Plot> plots;
        std::list<Tick> x_ticks;
        std::list<Tick> y_ticks;
        int y_max_value;
        int x_max_value;
        float x_step;
        float y_step;


        Figure() = default;
        Figure (const sf::Vector2f size, 
                const sf::Vector2f pos, 
                const char* x_label, const char* y_label, 
                sf::Font& font,
                const sf::Color& base_color = sf::Color::White,
                const unsigned int& label_size = 15,
                const sf::Color& label_color = sf::Color::Black);

        void plotData(const int* x_values, const int* y_values, const int n_values, const sf::Color color);

        void clear();

        void setSize(sf::Vector2f base_size);

        void setColor(const sf::Color& base_color);

        void setPosition(const sf::Vector2f& pos);

        sf::Vector2f getPosition() const;

        sf::Vector2f getSize() const;

        sf::Color getColor() const;

        void draw (sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
