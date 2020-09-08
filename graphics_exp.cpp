#include <SFML/Graphics.hpp>
#include <cstdio>

const sf::Color PRIMARY_DARK = sf::Color(37, 61, 91);
const sf::Color PRIMARY_LIGHT = sf::Color(239, 247, 246);
const sf::Color SECONDARY_LIGHT = sf::Color(108, 142, 173);
const sf::Color SECONDARY_DARK = sf::Color(58, 51, 53);
const sf::Color PRIMARY_ACCENT = sf::Color(255, 58, 32);

class rectButton
{
    public:
        sf::RectangleShape base;
        sf::Text text;
};

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Sorts analyzer");

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
        sf::RectangleShape rect(sf::Vector2f(1600.f, 700.f));
        rect.setFillColor(SECONDARY_DARK);

        /*sf::Font font;
        if(!font.loadFromFile("fonts/Roboto-Thin.ttf"))
        {
            fprintf(stderr, "Error loading fonts");
        }
        sf::Text text;
        text.setFont(font);
        text.setPosition(50.f, 300.f);
        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(24);
        text.setString("MergeSort");
        window.draw(text);*/

        
        rectButton button = {};
        button.base = sf::RectangleShape(sf::Vector2f(120.f, 50.f)); //leave it here for graphics background
        button.base.setFillColor(PRIMARY_DARK);
        button.base.setPosition(sf::Vector2f(50.f, 750.f));
        sf::Font font;
        font.loadFromFile("fonts/Roboto-Light.ttf");
        button.text.setFont(font);
        button.text.setFillColor(PRIMARY_LIGHT);
        button.text.setPosition(sf::Vector2f(54.f, 760.f));
        button.text.setCharacterSize(24);
        button.text.setString("MergeSort");

        window.draw(button.base);
        window.draw(button.text);
        window.draw(rect);
        window.display();

    }
    return 0;
}