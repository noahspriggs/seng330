
#include <SFML/Graphics.hpp>
#include "uimanager.h"

#ifndef RISKTEST
//! this is the main file of the program, which is directing to other files in order for the game to work.
int main()
{
    int xincrease = 600;
    int yincrease = 10;
    sf::RenderWindow window(sf::VideoMode(900+xincrease, 900+yincrease), "SENG 300 Group 6 - Risk");
    UIManager uimanager;
    uimanager.xincrease = xincrease/2;
    uimanager.yincrease = yincrease/2;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                uimanager.save(); // saves any changed made in any of the classes in unimanager
				window.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
				//! if left clicked then uimanager will change as following otherwise it will not
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    uimanager.handleClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
            else if(event.type == sf::Event::KeyPressed)
            {
				//! if keyboard is used then following occurs
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
