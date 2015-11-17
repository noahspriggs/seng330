
#include <SFML/Graphics.hpp>
#include "uimanager.h"

#ifndef RISKTEST
//! this is the main file of the program, which is directing to other files in order for the game to work. 
int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "SENG 300 Group 6 - Risk");
    UIManager uimanager;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                uimanager.save();
                window.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    uimanager.handleClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    uimanager.handleEsc();
                }
            }

        }

        window.clear();
        uimanager.draw(&window);
        window.display();



    }

    return 0;
}

#endif
