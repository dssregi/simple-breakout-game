#include <core/background.hpp>

Background::Background(float x, float y) {
   texture.emplace();
   if (!texture->loadFromFile("../res/background.jpg")) {
      std::cerr << "Error loading texture!" << std::endl;
   }
   sprite.emplace(*texture);

   // sprite.setTexture(texture);
   // Set the initial position and velocity of the background
   // Use (x, y) for the initial position of the background
   sprite->setPosition({x, y});
}

// Compute the background's new position
void Background::update() {
   // Nothing to do here
}

void Background::draw(sf::RenderWindow& window) {
   // 1. Get the current size of the window
   sf::Vector2u window_size = window.getSize();

   // 2. Get the dimensions of the texture
   sf::Vector2u texture_size = texture->getSize();

   // 3. Calculate the scale factors
   float scale_x = static_cast<float>(window_size.x) / texture_size.x;
   float scale_y = static_cast<float>(window_size.y) / texture_size.y;

   // 4. Apply the scale to the sprite
   sprite->setScale({scale_x, scale_y});

   // Ask the window to draw the sprite for us
   window.draw(*sprite);
}

