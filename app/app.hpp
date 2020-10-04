#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>

#include "../GUI/plot/plot.hpp"
#include "../GUI/constants/constants.hpp"
#include "../GUI/triggers/triggers.hpp"
#include "../GUI/custom_controls/custom_controls.hpp"
#include "../GUI/events/events.hpp"

#include "../benchmark/benchmark/stat.hpp"
#include "../benchmark/sorts/sorts.hpp"

class App
{
    private:
        Figure comparisons_plot;
        Figure assignments_plot;

        sf::RenderWindow window;
        sf::RectangleShape plots_background;
    public:
        App();

        void run();
        
        ~App();
};

#endif
