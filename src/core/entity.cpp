#include <core/entity.hpp>

// Helper function to get the bounding box of the sprite
sf::FloatRect Entity::get_bounding_box() const noexcept {
   return sprite->getGlobalBounds();
}

// Helper function to get the center of the sprite
sf::Vector2f Entity::get_center() const noexcept {
   auto box = get_bounding_box();
   // return {box.width/2.0f, box.height/2.0f};
   return box.getCenter();
}

// Helper functions to get the position of the sprite
float Entity::x() const noexcept {
   return sprite->getPosition().x;
}

float Entity::y() const noexcept {
   return sprite->getPosition().y;
}

// Helper functions to get the edges of the sprite
float Entity::left() const noexcept {
   auto box = get_bounding_box();
   return x() - box.size.x/2.0f;
}

float Entity::right() const noexcept {
   auto box = get_bounding_box();
   return x() + box.size.x/2.0f;
}

float Entity::top() const noexcept {
   auto box = get_bounding_box();
   return y() - box.size.y/2.0f;
}

float Entity::bottom() const noexcept {
   auto box = get_bounding_box();
   return y() + box.size.y/2.0f;
}

// Helper functions for the state of the entity
void Entity::destroy() noexcept {
   destroyed = true;
}

bool Entity::is_destroyed() const noexcept {
   return destroyed;
}

