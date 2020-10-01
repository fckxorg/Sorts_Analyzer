#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

// ---------------- Coloring ----------------------
extern const sf::Color     PRIMARY_DARK;                    
extern const sf::Color     PRIMARY_LIGHT;                   
extern const sf::Color     SECONDARY_LIGHT;                 
extern const sf::Color     SECONDARY_DARK;                
extern const sf::Color     PRIMARY_ACCENT;                 
 
// ---------------------- TICK SETTINGS --------------------
extern const float         TICK_STEPS[];                   
extern const int           N_TICK_STEPS;                  
extern const unsigned int  TICK_TEXT_SIZE;                 
static constexpr unsigned int  TICK_LABEL_BUFFER_SIZE = 10;
extern const float         TICK_LABEL_OFFSET_X;           
extern const float         TICK_LABEL_OFFSET_Y;           
extern const float         Y_AXIS_TICK_ROTATION;          
extern const float         Y_AXIS_TICK_LABEL_ROTATION;     
extern const float         Y_AXIS_TICK_LABEL_OFFSET_X;     
extern const float         Y_AXIS_TICK_LABEL_OFFSET_Y;     
 
extern const float         N_MARKERS_LOWER_BOUNDARY;        
extern const float         N_MARKERS_UPPER_BOUNDARY;        
 
// ---------------------- Plot Hint Settings --------------------
static constexpr unsigned int  HINT_BUFFER_SIZE = 10;               
 
// ----------------------- AXIS SETTINGS ------------------------
extern const float         Y_AXIS_LABEL_ROTATION;         

// ----------------------- BUTTONS SETTINGS ---------------------
extern char                button_names[][20];           
                                                       
                                                       
                                                       
                                                       
extern const unsigned int  N_SORT_BUTTONS;                  
extern const sf::Vector2f  FIRST_BUTTON_POS;                
extern const sf::Vector2f  LEFT_PLOT_POS;                   
extern const sf::Vector2f  RIGHT_PLOT_POS;                  
extern const sf::Vector2f  SORT_BUTTON_SIZE;                
extern const sf::Vector2f  PLOT_FIGURE_SIZE;                
extern const sf::Vector2f  TICK_SIZE;                       
extern const float         OFFSET;                          
extern const float         LABEL_OFFSET;                   
extern const float         EPSILON;                         
extern const unsigned int  BUTTON_TEXT_SIZE;                
extern const unsigned int  BUTTON_PUSH_ANIMATION_DURATION;  
extern const unsigned int  N_SAMPLES;                       

//---------------------------- MISC -----------------------------------------
extern sf::Font            ROBOTO_MEDIUM;
extern const sf::VideoMode WINDOW_SIZE;                     
extern const sf::Vector2f  PLOT_BACKGROUND_SIZE;            

#endif
