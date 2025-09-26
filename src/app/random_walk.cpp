#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <string>

#include <app/constants.hpp>
#include <core/creature.hpp>

using namespace std::literals;

std::mt19937 Creature::mt;
std::bernoulli_distribution Creature::bd;

int main() {
   // Create a creature object in the middle of the screen
   Creature the_creature(constants::WINDOW_WIDTH/2.0, constants::WINDOW_HEIGHT/2.0);

   // Create the game's window using an object of class RenderWindow
   // The constructor takes an SFML 2D vector with window dimensions
   // and an std::string with the window title
   // The SFML code is in the sf namespace
   sf::RenderWindow window{
      sf::VideoMode(sf::Vector2u{
         // static_cast<unsigned int>(constants::WINDOW_WIDTH),
         // static_cast<unsigned int>(constants::WINDOW_HEIGHT)
         constants::WINDOW_WIDTH,
         constants::WINDOW_HEIGHT
      }),
      "Random Walk"s
   };

   // Limit the framerate
   // This allows other processes to run and reduces power consumption
   window.setFramerateLimit(60);

   window.setPosition({300, 300});

   // Game loop
   // Clear the screan
   // Check for new events;
   // Calculate the updated graphics
   // Display the updated graphics
   while (window.isOpen()) {

      window.clear(sf::Color::Black);

      // check all the window's events that were triggered since the last iteration of the loop
      while (const std::optional event = window.pollEvent()) {
         // "close requested" event: we close the window
         if (event->is<sf::Event::Closed>()) {
            window.close();
         }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
         }

         if (event->is<sf::Event::FocusLost>())
            std::cout << "game paused" << std::endl;

         if (event->is<sf::Event::FocusGained>())
            std::cout << "game resumed" << std::endl;

         if (const auto* resized = event->getIf<sf::Event::Resized>())
         {
            std::cout << "new width: " << resized->size.x << std::endl;
            std::cout << "new height: " << resized->size.y << std::endl;
         }

         /* if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
         {
            std::cout << "new mouse x: " << mouseMoved->position.x << std::endl;
            std::cout << "new mouse y: " << mouseMoved->position.y << std::endl;
         } */

         if (const auto* mouseMovedRaw = event->getIf<sf::Event::MouseMovedRaw>())
         {
            std::cout << "new mouse x: " << mouseMovedRaw->delta.x << std::endl;
            std::cout << "new mouse y: " << mouseMovedRaw->delta.y << std::endl;
         }

         if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
         {
            if (mouseButtonPressed->button == sf::Mouse::Button::Right)
            {
               std::cout << "the right button was pressed" << std::endl;
               std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
               std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;
            }
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) 
            {
               std::cout << "the left button was pressed" << std::endl;
               std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
               std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;
            }
         }

      }

      // Calculate the updated graphics
      the_creature.update();

      // Display the updated graphics
      the_creature.draw(window);
      window.display();
   }

   return 0;
}
