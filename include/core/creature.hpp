#ifndef __CREATURE_HPP__
#define __CREATURE_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <random>
#include <app/constants.hpp>

using namespace std::literals;

class Creature {
private:
   // Static random number engine and Bernoulli distribution objects
   static std::mt19937 mt;
   static std::bernoulli_distribution bd;

   // Define some properties of the creature
   // SFML uses float internally
   float vx{4.0f};
   float vy{4.0f};
   sf::Vector2f velocity;

   // We use the SFML CircleShape
   sf::CircleShape circle;

public:
   // Constructor
   // Arguments are the initial coordinates of the center of the ball
   // SFML uses the computer graphics convention
   // (0, 0) is the top left corner of the screen
   // x increases to the left
   // y increases downwards
   Creature(float x, float y) {
      // Set the initial position and velocity
      // Use (x, y) for the initial position
      velocity = {vx, vy};
      circle.setPosition({x, y});

      // Set the graphical properties
      circle.setRadius(5.0f);
      circle.setFillColor(sf::Color::Red);
   }

   void draw(sf::RenderWindow& window) {
      // Ask the window to draw the shape for us
      window.draw(circle);
   }
   
   // Compute the creature's new position
   void update() {
      // Change the direction of movement at random
      vx = bd(mt) ? vx : -vx;
      vy = bd(mt) ? vy : -vy;

      // Move the creature to its new position
      circle.move({vx, vy});
   }

};

#endif   // __CREATURE_HPP__
