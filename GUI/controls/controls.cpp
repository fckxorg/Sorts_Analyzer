#include "controls.hpp"

Clickable::~Clickable(){}

ButtonTrigger::~ButtonTrigger(){}

        
void rectButton::setSize(sf::Vector2f base_size)
{
        base.setSize(base_size);
}

rectButton::rectButton()
{
    base = sf::RectangleShape();
    text = sf::Text();
    trigger = nullptr;
}


void rectButton::setColor(const sf::Color& base_color)
{
    base.setFillColor(base_color);
}

void rectButton::setTextColor(const sf::Color& text_color)
{
    text.setFillColor(text_color);
}

void rectButton::setPosition(const sf::Vector2f& pos)
{
    base.setPosition(pos); // add boundary cases
    text.setPosition(sf::Vector2f(pos.x + 4, pos.y + 10));
}

void rectButton::setTrigger(ButtonTrigger* trigger)
{
    this->trigger = trigger;
}

sf::Vector2f rectButton::getPosition() const
{
    return base.getPosition();
}

sf::Vector2f rectButton::getSize() const
{
    return base.getSize();
}

sf::Color rectButton::getColor() const
{
    return base.getFillColor();
}

void rectButton::setTextFont(const sf::Font& font)
{
    text.setFont(font);
}

void rectButton::setTextSize(const unsigned int& text_size)
{
    text.setCharacterSize(text_size);
}

void rectButton::setTextString(const char* string)
{
    assert(string != nullptr);

    text.setString(string);
}

void rectButton::draw (sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(base);
    target.draw(text);
}

bool rectButton::isUnderCursor(sf::RenderWindow& window) const 
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

void rectButton::onClick(sf::RenderWindow& window) 
{
    animatePush(window);
    
    assert(trigger != nullptr);
    (*trigger)();
}

void rectButton::animatePush(sf::RenderWindow& window)
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
