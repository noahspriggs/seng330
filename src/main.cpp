#include <SFML/Graphics.hpp>
#include "uimanager.h"

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
                    window.close();
                }
            }
                
        }

        window.clear();
        uimanager.draw(&window);
        window.display();
            
        
        
    }

    return 0;
}
