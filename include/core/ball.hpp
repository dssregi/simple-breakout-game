#ifndef __BALL_HPP__
#define __BALL_HPP__

#include <iostream>
#include <optional>

#include <app/constants.hpp>
#include <core/entity.hpp>

class Ball: public MovingEntity {
private:
   std::optional<sf::Texture> texture;
public:
   // Interface of the class
   
   // Constructor
   // Arguments are the initial coordinates of the center of the ball
   // SFML uses computer graphics convention
   // (0, 0) is the top left corner of the screen
   // x increases to the right
   // y increases downwards
   Ball(float x, float y);

   // Static function to initialize shared resources
   // static bool initialize();

   // Implement the pure virtual functions
   void update() override;
   void draw(sf::RenderWindow& window) override;
   void move_up() noexcept override;
   void move_down() noexcept override;
   void move_left() noexcept override;
   void move_right() noexcept override;
};

#endif   // __BALL_HPP__
