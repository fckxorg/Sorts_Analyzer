#include "plot.hpp"


Tick::Tick(sf::Vector2f pos, sf::Vector2f size, float value, bool rotate)
{
    tick.setPosition(pos);
    tick.setFillColor(sf::Color::Black);
    tick.setSize(size);

    char buffer[TICK_LABEL_BUFFER_SIZE] = "";
    sprintf(buffer, "%.1f", value);

    label = sf::Text(buffer, ROBOTO_MEDIUM);
    label.setCharacterSize(TICK_TEXT_SIZE);
    label.setPosition(sf::Vector2f(pos.x + TICK_LABEL_OFFSET_X, pos.y + TICK_LABEL_OFFSET_Y));
    label.setFillColor(sf::Color::Black);

    if(rotate)
    {
        tick.setRotation(Y_AXIS_TICK_ROTATION);
        label.setRotation(Y_AXIS_TICK_LABEL_ROTATION);
        label.setPosition(sf::Vector2f(pos.x + Y_AXIS_TICK_LABEL_OFFSET_X, pos.y + Y_AXIS_TICK_LABEL_OFFSET_Y));
    }
}

void Tick::draw (sf::RenderTarget& target, sf::RenderStates states) const 
        {
            target.draw(tick);
            target.draw(label);
        }

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


float Plot::scale_value(const float value, const float step, const float offset)
{
    return value * step + offset;
}

float Plot::unscale_value(const float value, const float step, const float offset)
{
    return (value - offset) / step;
}


Plot::Plot(){};

Plot::Plot(sf::Vector2f start_point, 
            const int* x_values, 
            const int* y_values, 
            const int n_elements, 
            const float x_step, 
            const float y_step, 
            sf::Color color) : start_point(start_point), max_x_coord(0), max_y_coord(0), x_step(x_step), y_step(y_step)
        {
            assert(x_values != nullptr);
            assert(y_values != nullptr);

            plot = sf::VertexArray(sf::LineStrip, n_elements);

            for(int i = 0; i < n_elements; ++i) {
                float curr_x_val = scale_value(x_values[i], x_step, start_point.x);
                float curr_y_val = scale_value(y_values[i], y_step, start_point.y);

                max_x_coord = max_x_coord < curr_x_val ? curr_x_val : max_x_coord;
                max_y_coord = max_y_coord < curr_y_val ? curr_y_val : max_y_coord;

                plot[i].position = sf::Vector2f(curr_x_val, curr_y_val);
                plot[i].color = color;
            }   
        }

void Plot::rescale(const float new_x_step, const float new_y_step, const float old_x_step, const float old_y_step)
        {
            for(int i = 0; i < plot.getVertexCount(); ++i)
            {
                plot[i].position.x = scale_value(unscale_value(plot[i].position.x, old_x_step, start_point.x), new_x_step, start_point.x);
                plot[i].position.y = scale_value(unscale_value(plot[i].position.y, old_y_step, start_point.y), new_y_step, start_point.y);
                x_step = new_x_step;
                y_step = new_y_step;
            }
        }

void Plot::draw (sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(plot);
}

bool Plot::isUnderCursor(sf::RenderWindow& window) const  
{
    for(int i = 1; i < plot.getVertexCount(); ++i)
    {
        sf::Vector2f first_vertex = plot[i].position;
        sf::Vector2f second_vertex = plot[i - 1].position;
        
        float k_coeff = (first_vertex.y - second_vertex.y) / (first_vertex.x - second_vertex.x);
        float b_coeff = first_vertex.y - k_coeff * first_vertex.x;

        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

        if(fabs(mouse_position.y - mouse_position.x * k_coeff - b_coeff) < EPSILON && mouse_position.x < max_x_coord && mouse_position.y < max_y_coord)
        {
            return true;
        }
    }
    return false;
}

void Plot::onClick(sf::RenderWindow& window)  
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    sf::Text hint;
    hint.setFillColor(sf::Color::Black);
    hint.setFont(ROBOTO_MEDIUM);
    hint.setPosition(mouse_position.x + 15.f, mouse_position.y);
    hint.setCharacterSize(15);

    float unscaled_x = unscale_value(mouse_position.x, x_step, start_point.x);
    float unscaled_y = unscale_value(mouse_position.y, y_step, start_point.y);

    sprintf(hint_buffer, "(%.1f, %.1f)", unscaled_x, unscaled_y);

    hint.setString(hint_buffer);

    window.draw(hint);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

Axis::Axis(){}

Axis::Axis(sf::Vector2f axis_start, sf::Vector2f axis_end)
{
    axis = sf::VertexArray(sf::Lines, 2);
    axis[0].position = axis_start;
    axis[1].position = axis_end;
    axis[0].color = sf::Color::Black;
    axis[1].color = sf::Color::Black;
   
}

void Axis::setLabelString(const char* string)
{
    label.setString(string);
}

void Axis::setLabelFont(sf::Font& font)
{
    label.setFont(font);
}

void Axis::setLabelSize(const unsigned int& size)
{
    label.setCharacterSize(size);
}

void Axis::setLabelPosition(const sf::Vector2f& pos)
{
    label.setPosition(pos);
    if(axis[0].position.x == axis[1].position.x)
    {
        label.rotate(Y_AXIS_LABEL_ROTATION);
    }
}

void Axis::setLabelColor(const sf::Color& color)
{
    label.setFillColor(color);
}

void Axis::draw (sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(axis);
    target.draw(label);
}


float Figure::selectTickStep(float max_value)
{
    for(int i = 0; i < N_TICK_STEPS; ++i)
    {
        float n_markers = max_value / TICK_STEPS[i];
        printf("N_markers %f\n", n_markers);
        if(n_markers >= N_MARKERS_LOWER_BOUNDARY && n_markers <= N_MARKERS_UPPER_BOUNDARY)
        {
            return TICK_STEPS[i];
        }
        printf("%f not suitable step\n", TICK_STEPS[i]);
    }

    return TICK_STEPS[N_TICK_STEPS - 1];
}

void Figure::rescale_X(const int new_x_max_value) 
{
    float new_x_step = (axisX.axis[1].position.x - axisX.axis[0].position.x) / static_cast<float>(x_max_value);
    for(auto& plot : plots) 
    {
        plot->rescale(new_x_step, y_step, x_step, y_step);
    }

    x_step = new_x_step;
}

void Figure::rescale_Y(const int new_y_max_value)
{
    float new_y_step = (axisY.axis[1].position.y - axisY.axis[0].position.y) / static_cast<float>(y_max_value);
    for(auto& plot : plots) 
    {
        plot->rescale(x_step, new_y_step, x_step, y_step);
    }
    y_step = new_y_step;
}

void Figure::rescale_ticks(const float max_value, bool y_axis)
{

    float step = 0;

    sf::Vector2f start_pos = axisX.axis[0].position;

    if(y_axis)
    {
        y_ticks.clear();
        step = y_step;
    }
    else 
    {
        x_ticks.clear();
        step = x_step;
    }

    const float tick_step = selectTickStep(max_value);


    for(float i = 0; i < max_value; i += tick_step)
    {   
        if(y_axis)
        {
            sf::Vector2f tick_pos = sf::Vector2f(start_pos.x, start_pos.y + i * step);
            y_ticks.push_back(Tick(tick_pos, TICK_SIZE, i, true));
        }
        else 
        {
            sf::Vector2f tick_pos = sf::Vector2f(i * step + start_pos.x, start_pos.y);
            x_ticks.push_back(Tick(tick_pos, TICK_SIZE, i, false));
        }
    }
}

Figure::Figure (const sf::Vector2f size, 
                const sf::Vector2f pos, 
                const char* x_label, const char* y_label, 
                sf::Font& font,
                const sf::Color& base_color,
                const unsigned int& label_size,
                const sf::Color& label_color) : x_max_value(0), y_max_value(0)
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

void Figure::plotData(const int* x_values, const int* y_values, const int n_values, const sf::Color color)
{
    printf("Plotting data...\n");
    const int new_plot_x_max_value = static_cast<float>(max_in_array(x_values, n_values));
    const int new_plot_y_max_value = static_cast<float>(max_in_array(y_values, n_values));

    printf("Data max values are x: %d, y: %d\n", new_plot_x_max_value, new_plot_y_max_value);

    if(new_plot_x_max_value > x_max_value) 
    {   
        x_max_value = new_plot_x_max_value;
        rescale_X(new_plot_x_max_value);
        rescale_ticks(x_max_value, false);
    }

    if(new_plot_y_max_value > y_max_value)
    {
        y_max_value = new_plot_y_max_value;
        rescale_Y(new_plot_y_max_value);
        rescale_ticks(y_max_value, true);
    }
    Plot* new_plot = new Plot(axisX.axis[0].position, x_values, y_values, n_values, x_step, y_step, color);
    plots.push_back(new_plot);
    clickable_objects.push_back(new_plot);
}

void Figure::clear()
{
    for(auto plot: plots)
    {
        auto it = std::find(clickable_objects.begin(), clickable_objects.end(), plot);
        
        assert(it != clickable_objects.end());

        clickable_objects.erase(it);
    }
    plots.clear();
}

void Figure::setSize(sf::Vector2f base_size)
{
    base.setSize(base_size);
}

void Figure::setColor(const sf::Color& base_color)
{
    base.setFillColor(base_color);
}

void Figure::setPosition(const sf::Vector2f& pos)
{
    base.setPosition(pos); // add boundary cases
}

sf::Vector2f Figure::getPosition() const
{
    return base.getPosition();
}

sf::Vector2f Figure::getSize() const
{
    return base.getSize();
}

sf::Color Figure::getColor() const
{
    return base.getFillColor();
}

void Figure::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(base);
    target.draw(axisX);
    target.draw(axisY);
    for(auto& plot : plots)
    {
        target.draw(*plot);
    }

    for(auto& tick : x_ticks)
    {
        target.draw(tick);
    }

    for(auto& tick : y_ticks)
    {
        target.draw(tick);
    }
}
