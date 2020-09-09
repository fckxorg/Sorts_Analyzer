#include <SFML/Graphics.hpp>
#include <cstdio>

const sf::Color PRIMARY_DARK = sf::Color(37, 61, 91);
const sf::Color PRIMARY_LIGHT = sf::Color(239, 247, 246);
const sf::Color SECONDARY_LIGHT = sf::Color(108, 142, 173);
const sf::Color SECONDARY_DARK = sf::Color(58, 51, 53);
const sf::Color PRIMARY_ACCENT = sf::Color(255, 58, 32);

const sf::Vector2f SORT_BUTTON_SIZE = sf::Vector2f(120.f, 50.f);
const unsigned int BUTTON_TEXT_SIZE = 24;

sf::Font ROBOTO_MEDIUM;


class rectButton
{
    public:
        sf::RectangleShape base;
        sf::Text text;
        
        void setSize(sf::Vector2f base_size)
        {
            base.setSize(base_size);
        }

        rectButton()
        {
            base = sf::RectangleShape();
            text = sf::Text();
        }

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
            text.setString(string);
        }

        void render(sf::RenderWindow& window)
        {
            window.draw(base);
            window.draw(text);
        }

};

rectButton createSortStyledButton(const sf::Vector2f& pos, const char* string)
{
        rectButton button;

        button.setColor(PRIMARY_DARK);
        button.setSize(SORT_BUTTON_SIZE);
        button.setPosition(pos);
        button.setTextFont(ROBOTO_MEDIUM);
        button.setTextColor(PRIMARY_LIGHT);
        button.setTextSize(BUTTON_TEXT_SIZE);
        button.setTextString(string);

        return button;
}

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Sorts analyzer");
    ROBOTO_MEDIUM.loadFromFile("fonts/Roboto-Light.ttf");

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(PRIMARY_LIGHT); // clearing window with black color
        sf::RectangleShape rect(sf::Vector2f(1600.f, 700.f)); //leave it here for graphics background
        rect.setFillColor(SECONDARY_DARK);

        rectButton button = createSortStyledButton(sf::Vector2f(50.f, 750.f), "MergeSort");

        button.render(window);
        window.draw(rect);
        window.display();

    }
    return 0;
}