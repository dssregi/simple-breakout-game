#ifndef __BRICK_HPP__
#define __BRICK_HPP__

#include <iostream>
#include <optional>
#include <vector>

#include <app/constants.hpp>
#include <core/entity.hpp>

// Class to represent a brick
// Inherits from Entity
// A grid of bricks is displayed across the top of the screen
// This grid will be represented by a std::vector of brick objects
// When the ball hits a brick, the brick is destroyed and disappears
// When a brick is destroyed, it is deleted from the vector
class Brick: public Entity {
private:
   std::optional<sf::Texture> texture;

   // How many times the brick can be hit before destroying it
   int strength{Constants::BRICK_STRENGTH};

public:
   // Constructor
   Brick(float x, float y);

   // Helper functions for brick strength
   void setStrength(int) noexcept;
   void weaken() noexcept;
   bool isTooWeak() const noexcept;

   // Pure virtual functions implemented
   void update() override;
   void draw(sf::RenderWindow& windos) override;
};

#endif   // __BRICK_HPP__
