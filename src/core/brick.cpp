#include <core/brick.hpp>

// Use different colors, depending on the strength of the brick
// Format: RGBA
const sf::Color brick_color_hit1{0, 255, 0, 80};   // Dull green
const sf::Color brick_color_hit2{0, 255, 0, 170};  // Medium green
const sf::Color brick_color_hit3{0, 255, 0, 255};  // Bright green

Brick::Brick(float x, float y) {
   texture.emplace();
   if(!texture->loadFromFile("../res/brick01.png")) {
      std::cerr << "Could not load brick's texture" << std::endl;
   }
   // Apply the texture
   sprite.emplace(*texture);

   // By default, operations are relative to the sprite's top lefthand corner
   // Make them relative to the sprite's center
   sprite->setOrigin(get_center());

   // Set the position of the brick
   sprite->setPosition({x, y});
}

void Brick::setStrength(int s) noexcept { strength = s; }
void Brick::weaken() noexcept { --strength; }
bool Brick::isTooWeak() const noexcept { return strength <= 0; }

// Compute the brick's new appearance
void Brick::update() {
   // Change the color of the brick, depending on how many times it has been hit
   if (strength == 1)
      sprite->setColor(brick_color_hit1);
   else if (strength == 2)
      sprite->setColor(brick_color_hit2);
   else if (strength == 3)
      sprite->setColor(brick_color_hit3);
}

// Draw the sprite asking to the window
void Brick::draw(sf::RenderWindow& window) {
   // Ask the window to draw the sprite for us
   window.draw(*sprite);
}
