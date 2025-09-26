#ifndef __BACKGROUND_HPP__
#define __BACKGROUND_HPP__

#include <iostream>
#include <optional>

#include <app/constants.hpp>
#include <core/entity.hpp>

// Class to represent the background
// Inherits from entity
class Background: public Entity {
private:
   std::optional<sf::Texture> texture;
public:
   // Interface of the class
   //
   // Constructor
   // Arguments are the initial coordinates of the centre of the background
   // SFML uses the computer graphics convention
   // (0, 0) is the top left corner of the screen
   // x increases to the right
   // y increases downwards
   Background(float x, float y);

   // New static function to initialize shared resources.
   // static bool initialize();

   // Implement the pure virtual functions
   void update() override;
   void draw(sf::RenderWindow& window) override;
};

#endif   // __BACKGROUND_HPP__
