#include "interface.h"

Interface::Interface(sf::RenderWindow& mainWindow) : window(mainWindow) {
    var=0;
}
void Interface::read() { std::cin>>var;}
void Interface::write() const {std::cout<<var;}
void Interface::run() {
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); // Clear the window with a black color

        // Draw your game elements here

        window.display(); // Display what was drawn
    }
}
