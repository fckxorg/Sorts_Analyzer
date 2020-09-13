#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

const sf::Color PRIMARY_DARK = sf::Color(37, 61, 91);
const sf::Color PRIMARY_LIGHT = sf::Color(239, 247, 246);
const sf::Color SECONDARY_LIGHT = sf::Color(58, 51, 53); 
const sf::Color SECONDARY_DARK = sf::Color(108, 142, 173); 
const sf::Color PRIMARY_ACCENT = sf::Color(255, 58, 32);

const sf::Vector2f FIRST_BUTTON_POS = sf::Vector2f(50.f, 750.f);
const sf::Vector2f SORT_BUTTON_SIZE = sf::Vector2f(180.f, 50.f);
const sf::Vector2f PLOT_FIGURE_SIZE = sf::Vector2f(600.f, 600.f);
const sf::Vector2f TICK_SIZE = sf::Vector2f(2.f, 10.f);

const float TICK_STEPS[] = {0.5, 1, 5, 10, 100, 1000};
const int N_TICK_STEPS = sizeof(TICK_STEPS);

const float OFFSET = 50.f;
const float LABEL_OFFSET = 25.f;
const float EPSILON = 10.f;

const unsigned int BUTTON_TEXT_SIZE = 24;
const unsigned int BUTTON_PUSH_ANIMATION_DURATION = 150;
const unsigned int TICK_BUFFER_SIZE = 10;

sf::Font ROBOTO_MEDIUM;

#endif