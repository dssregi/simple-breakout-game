#ifndef __GAME_HPP__
#define __GAME_HPP__

// Standard headers
#include <optional>
#include <string>
#include <memory>
#include <typeinfo>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <cstdlib>  // for std::exit()

// Breakout headers
#include <app/constants.hpp>
#include <core/background.hpp>
#include <core/ball.hpp>
#include <core/brick.hpp>
#include <core/paddle.hpp>

using namespace std::string_literals;

// A class to manage the entities in the game
// It stores the entities in a vector of std::unique_ptr
// The manager can create an entity object and add it to the vector

// Example: create a ball object at position (x, y) on the screen
// manager.create<ball>(x, y);

// When an entity is destroyed, the game will mark it as destroyed, but not delete it.
// Instead, the manager will scan all entities and clean up the destroyed ones

// The manager can also locate all the objects with a given entity type
// These are stored as alias pointers (non-owning) to the allocated objects
// This is useful for performing an operation on e.g. all bricks

// Use aliases to simplify the code
using entity_vector = std::vector<std::unique_ptr<Entity>>;
using entity_alias_vector = std::vector<Entity *>;

class EntityManager {
private:
   // A vector to store all the entities in the game ( all brick objects, background, ball, paddle)
   entity_vector all_entities;

   // A map to store the entities grouped by type
	// We can iterate over this to get a vector of all brick objects, then a vector of all ball objects, etc
	// The vector will contain non-owning pointers to the objects
	// Do not delete these pointers!
	// Do not use them after the objects they point to have been destroyed!
   std::map<size_t, entity_alias_vector> grouped_entities;

public:
   // Function to create an entity object of type T using args as the constructor arguments
	// We use a variadic template to pass any number of arguments
	// We use perfect forwarding to avoid any unnecessary copying of the arguments
   template <typename T, typename... Args>
   T& create(Args&&... args) {
      // Check that the type parameter is derived from the entity base class
      static_assert(std::is_base_of<Entity, T>::value,
            R"("T" type parameter in create() must be derived from "Entity")");

      // Create a unique_ptr to the entity
      // Forward the arguments to the entity's constructor
      auto ptr{std::make_unique<T>(std::forward<Args>(args)...)};

      // Make an alias pointer to the allocated memory
      // This will be stored in the entity_type_vector
      auto ptr_alias = ptr.get();

      // Get the hash code for the entity object's type
      auto hash = typeid(T).hash_code();

      // Insert the alias pointer into the map
      grouped_entities[hash].emplace_back(ptr_alias);

      // Insert the object's pointer into the entities vector
      all_entities.emplace_back(std::move(ptr));

      // Return the new object
      return *ptr_alias;
   }

   // Function to scan all entities and clean up the destroyed ones
   void refresh();

   // Function to destroy all entities
   void clear();

   // Function to retrieve all the objects of a given type
   template <typename T>
   auto& get_all() {
      return grouped_entities[typeid(T).hash_code()];
   }

   // Apply a function to all entities of a given type
   template <typename T, typename Func>
      void apply_all(const Func& func) {
         auto& entity_group{get_all<T>()};
         for (auto ptr: entity_group)
            func(*dynamic_cast<T*>(ptr));
      }

   // Function to update all the entities
   void update();

   // Function to make all the entities draw themselves
   void draw(sf::RenderWindow& window);

};

class Game {
private:
   // Enum with allowed values for game states
   enum class GameState { start, paused, game_over, running, player_wins };
   
   // Create the game's window using an object of class RenderWindow
   // The constructor takes an SFML 2D vector with window dimensions
   // and an std::string with the window title
   // The SFML code is in the sf namespace
   sf::RenderWindow window{
      sf::VideoMode(sf::Vector2u{
         Constants::WINDOW_WIDTH,
         Constants::WINDOW_HEIGHT
      }),
      "Simple Breakout Game v0.12.0"
   };

   // Instead of embedding every entity in the game class, use an entity_manager
	EntityManager manager;

   // Use SFML text and font classes to communicate with the player
   std::optional<sf::Font> game_font;
   std::optional<sf::Text> text_state;
   std::optional<sf::Text> text_lives;
   
   // Member to store the current state of the game
   GameState state{GameState::game_over}; 

   // How many lives does the player have left?
   int lives{Constants::PLAYER_LIVES};

   // Function to update texts
   void update_text(std::optional<sf::Text>& sfText, const std::string& text, const sf::Color color, const sf::Vector2f positionOffset);

   public:
   // Constructor
   Game();

   // Initialize shared resouces
   // static bool initializeSharedResources();

   // Reset the game
   void reset();

   // Game loop
   void run();

};

#endif   // __GAME_HPP__
