#ifndef __PADDLE_HPP__
#define __PADDLE_HPP__

#include <iostream>
#include <optional>

#include <app/constants.hpp>
#include <core/entity.hpp>

// A class to represent a paddle
// Inherits form MovingEntity
// The paddle moves across the bottom of the screen, under the user's control
// When the ball hits the paddle, it will bounce and change its direction
class Paddle: public MovingEntity {
private:
   // Private data and member functions
   std::optional<sf::Texture> texture;
   
   // Respond to input from the player
   void process_player_input();

public:
   // Interface of the class
   // Constructor with initial coordinates of the center of the paddle
   Paddle(float x, float y);

   // static bool initialize();

   // Implement the pure virtual functions
   void update() override;
   void draw(sf::RenderWindow& window) override;
   void move_up() noexcept override;
   void move_down() noexcept override;
   void move_left() noexcept override;
   void move_right() noexcept override;
};

#endif   // __PADDLE_HPP__
