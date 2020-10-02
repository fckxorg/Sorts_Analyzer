#ifndef BUTTON_TRIGGER_HPP
#define BUTTON_TRIGGER_HPP

#include <SFML/Graphics.hpp>
#include "../constants/constants.hpp"

class ButtonTrigger
{
    public:
        virtual void operator()() = 0; 
        virtual ~ButtonTrigger();
};

#endif


