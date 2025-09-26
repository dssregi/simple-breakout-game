#include <core/paddle.hpp>

// Constructor
Paddle::Paddle(float x, float y) {
   texture.emplace();
   // Load texture
   if(!texture->loadFromFile("../res/paddle.png")) {
      std::cerr << "Could not load paddle texture" << std::endl;
   }

   // Apply the texture to the sprite
   sprite.emplace(*texture);

   // By default, operations are relative to the sprite's top left corner
   // Make them relative to the sprite's center
   sprite->setOrigin(get_center());

   // Set the initial position of the paddle
   sprite->setPosition({x, y});

   // Set the velocity of the paddle which can move only sideways
   // velocity = {Constants::PADDLE_SPEED, 0.0f};
   velocity = {0.0f, 0.0f};
}

// Compute the paddle's new position
void Paddle::update() {
   // Respond to user input as this will affect how the paddle moves
   process_player_input();

   // Move the position of the paddle
   sprite->move(velocity);
}

// Draw the paddle in the new position
void Paddle::draw(sf::RenderWindow& window) {
   // Ask the windows to draw the shape for us
   window.draw(*sprite);
}

// Respond to input from the player
// If the player presses the left arrow key, move to the left (negative velocity)
// If the player presses the right arrow key, move to the right (positive velocity)
// Otherwise, do not move (zero velocity)
void Paddle::process_player_input() {
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
      // Left arrow key pressed - move to the left
      // Unless the paddle has gone past the left hand side
      if (x() >= 0)
         velocity.x = -Constants::PADDLE_SPEED;
      else
         velocity.x = 0;
   } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
      // Right arrow key pressed - move to the right
      // Unless the paddle has gone past the right hand side
      if (x() <= Constants::WINDOW_WIDTH)
         velocity.x = Constants::PADDLE_SPEED;
      else
         velocity.x = 0;
   }
   else {
      // Some other key pressed, or no key at all
      velocity.x = 0;
   }
}

// No action here, since the paddle moves only sideways
void Paddle::move_up() noexcept {}

// No action here, since the paddle moves only sideways
void Paddle::move_down() noexcept {}

void Paddle::move_left() noexcept {
   velocity.x = -Constants::PADDLE_SPEED;
}

void Paddle::move_right() noexcept {
   velocity.x = Constants::PADDLE_SPEED;
}

