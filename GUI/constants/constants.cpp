#include "constants.hpp"
#include <SFML/Graphics/Color.hpp>

// ---------------- Coloring ----------------------
const sf::Color     PRIMARY_DARK                    = sf::Color( 37,  61,  91);
const sf::Color     PRIMARY_LIGHT                   = sf::Color(239, 247, 246);
const sf::Color     SECONDARY_LIGHT                 = sf::Color( 58,  51,  53); 
const sf::Color     SECONDARY_DARK                  = sf::Color(108, 142, 173); 
const sf::Color     PRIMARY_ACCENT                  = sf::Color(255,  58,  32);

// ---------------------- TICK SETTINGS --------------------
const float         TICK_STEPS[]                    = {0.5, 1, 5, 10, 100, 200, 500, 1000};
const int           N_TICK_STEPS                    = sizeof(TICK_STEPS);
const unsigned int  TICK_TEXT_SIZE                  = 15;
//                  TICK_LABEL_BUFFER_SIZE          = 10; defined in constants.hpp
const float         TICK_LABEL_OFFSET_X             = -7.f;
const float         TICK_LABEL_OFFSET_Y             = 7.f;
const float         Y_AXIS_TICK_ROTATION            = 90.f;
const float         Y_AXIS_TICK_LABEL_ROTATION      = -90.f;
const float         Y_AXIS_TICK_LABEL_OFFSET_X      = -28.f;
const float         Y_AXIS_TICK_LABEL_OFFSET_Y      = 7.f;

const float         N_MARKERS_LOWER_BOUNDARY        = 5.f;
const float         N_MARKERS_UPPER_BOUNDARY        = 10.f;

// ---------------------- Plot Hint Settings --------------------
//                  HINT_BUFFER_SIZE                = 10 defined in constants.hpp

// ----------------------- AXIS SETTINGS ------------------------
const float         Y_AXIS_LABEL_ROTATION           = -90.f;

// ----------------------- BUTTONS SETTINGS ---------------------
char                button_names[][20]              = {"MergeSort", 
                                                       "QuickSort", 
                                                       "SelectionSort", 
                                                       "InsertionSort", 
                                                       "BubbleSort"};
sf::Color  button_colors[]                          = {sf::Color::Red, 
                                                       sf::Color::Blue, 
                                                       sf::Color::Green,
                                                       sf::Color::Cyan,
                                                       sf::Color::Magenta};
const unsigned int  N_SORT_BUTTONS                  = 5;

const sf::Vector2f  FIRST_BUTTON_POS                = sf::Vector2f(50.f, 750.f);
const sf::Vector2f  LEFT_PLOT_POS                   = sf::Vector2f(133.f, 50.f);
const sf::Vector2f  RIGHT_PLOT_POS                  = sf::Vector2f(866.f, 50.f);
const sf::Vector2f  SORT_BUTTON_SIZE                = sf::Vector2f(180.f, 50.f);
const sf::Vector2f  PLOT_FIGURE_SIZE                = sf::Vector2f(600.f, 600.f);
const sf::Vector2f  TICK_SIZE                       = sf::Vector2f(2.f, 10.f);

const float         OFFSET                          = 50.f;
const float         LABEL_OFFSET                    = 25.f;
const float         EPSILON                         = 10.f;

const unsigned int  BUTTON_TEXT_SIZE                = 24;
const unsigned int  BUTTON_PUSH_ANIMATION_DURATION  = 150;
const unsigned int  N_SAMPLES                       = 100;
const unsigned int  COLOR_INDICATOR_OFFSET          = 5.f;


sf::Font            ROBOTO_MEDIUM;

const sf::VideoMode WINDOW_SIZE                     = sf::VideoMode(1600, 900);
const sf::Vector2f  PLOT_BACKGROUND_SIZE            = sf::Vector2f(1600.f, 700.f);

