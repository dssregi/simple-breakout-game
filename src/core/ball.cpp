#include <core/ball.hpp>

// Constructor
Ball::Ball(float x, float y) {
   texture.emplace();
   if (!texture->loadFromFile("../res/ball.png")) {
      std::cerr << "Error loading texture!" << std::endl;
   }
   
   sprite.emplace(*texture);
   // sprite.setTexture(texture);
   // Set the intial position and velocity of the ball
   // Use ({x, y}) for the intial position of the ball
   sprite->setPosition({x, y});

   velocity = {Constants::BALL_SPEED, Constants::BALL_SPEED};
}

// Compute the ball's new position
void Ball::update() {
   // Move the position of the ball
   sprite->move(velocity);

   // We check if the ball has moved off the left hand side of the window
   // If so, we change sign of the x-component of the velocity
   // This will make it move at the same speed, but to the right
   // The ball will appear to bounce back into the window
   if (x() < 0)
      velocity.x = -velocity.x;
   // And similarly for the right hand side of the screen
   if (x() > Constants::WINDOW_WIDTH)
      velocity.x = -velocity.x;

   // Do the same for the top and bottom of the screen
   if (y() < 0)
      velocity.y = -velocity.y;
   if (y() > Constants::WINDOW_HEIGHT)
      destroy();
}

void Ball::move_up() noexcept {
   velocity.y = -Constants::BALL_SPEED;
}

void Ball::move_down() noexcept {
   velocity.y = Constants::BALL_SPEED;
}

void Ball::move_left() noexcept {
   velocity.x = -Constants::BALL_SPEED;
}

void Ball::move_right() noexcept {
   velocity.x = Constants::BALL_SPEED;
}

void Ball::draw(sf::RenderWindow& window) {
   // Ask the window to draw the sprite for us
   window.draw(*sprite);
}
