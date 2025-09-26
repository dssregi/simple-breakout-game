#include <core/game.hpp>
#include <core/interactions.hpp>
#include <app/constants.hpp>

// --------- EntityManager --------
//
// Function to scan all entities and clean up the destroyed ones
void EntityManager::refresh() {
   // Clean up the alias pointers first, to avoid dangling pointers
   // Simply remove them from their vector
   for (auto& [type, alias_vector]: grouped_entities) {
     // std::remove_if taks an iterator range and a predicate
     // All the elements for which the precidate if true are moved to the back
     // It returns an iterator to the first moved element
     // std::erase takes an interator range and deletes all the elements in the range
     alias_vector.erase(std::remove_if(std::begin(alias_vector), std::end(alias_vector),
             [](auto p) { return p->is_destroyed(); }),
          std::end(alias_vector));
   }

   // Now we can safely destroy the objects, now that there are no aliases to them
   all_entities.erase(std::remove_if(std::begin(all_entities), std::end(all_entities),
            [](const auto& p) { return p->is_destroyed(); }),
         std::end(all_entities));

}

// Function to destroy all entities
void EntityManager::clear() {
   // Again, we must clean up the alias pointers first
   grouped_entities.clear();
   all_entities.clear();
}

// Function to update all the entities
void EntityManager::update() {
   for (auto& e: all_entities)
      e->update();
}

// Function to make the entities draw temselves
void EntityManager::draw(sf::RenderWindow& window) {
   for (auto& e: all_entities)
      e->draw(window);
}

// --------- Game --------
// Constructor
Game::Game() {
   // Load the font from file
   // Used Adwaita which was located at /usr/share/fonts/Adwaita
   // Copied to res directory in the project
   game_font.emplace();
   if (!game_font->openFromFile("../res/FreeSans.otf")) {
      std::cerr << "Error loading font file." << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // Configure text objects
   text_state.emplace(*game_font, "Start"s, 20);
   if (!text_state) {
      std::cerr << "Error creating text object." << std::endl,
      std::exit(EXIT_FAILURE);
   }

   text_lives.emplace(*game_font, "Lives: "s + std::to_string(lives), 20);
   if (!text_lives) {
      std::cerr << "Error creating text object." << std::endl,
      std::exit(EXIT_FAILURE);
   }

   // Limit the framerate
   // This allows other processes to run and reduces power consumption
   window.setFramerateLimit(60);
}

void Game::update_text(std::optional<sf::Text>& sfText, const std::string& text, const sf::Color color = sf::Color::White, const sf::Vector2f positionOffset = {0.0f, 0.0f}) {
      if (!sfText) {
         std::cerr << "Error: sf::Text object is not initialized." << std::endl;
         return;
      }
      sfText->setString(text);
      sf::FloatRect textBounds = sfText->getGlobalBounds();
      sfText->setOrigin({textBounds.size.x/2.0f, textBounds.size.y/2.0f});
      sfText->setPosition({Constants::WINDOW_WIDTH/2.0f + positionOffset.x, Constants::WINDOW_HEIGHT/2.0f + positionOffset.y});
      sfText->setFillColor(color);
   }

// (Re)initialize the game
void Game::reset() {
   // Set the game state to start
   state = GameState::start;
   update_text(text_state, "Press P or Spacebar to Start"s, sf::Color::White, {0.0f, -100.0f});
   
   // Reset the number of lives
   lives = Constants::PLAYER_LIVES;
   update_text(text_lives, "Lives: "s + std::to_string(lives), sf::Color::White, {0.0f, -50.0f});

   // Destroy all the entities and re-create them
   manager.clear();

   manager.create<Background>(0.0f, 0.0f);
   manager.create<Ball>(Constants::WINDOW_WIDTH/2.0f, Constants::WINDOW_HEIGHT/2.0f);
   manager.create<Paddle>(Constants::WINDOW_WIDTH/2.0f, Constants::WINDOW_HEIGHT - Constants::PADDLE_HEIGHT);

   for (int i = 0; i < Constants::BRICK_COLUMNS; ++i) {
      for (int j = 0; j < Constants::BRICK_ROWS; ++j) {
         // Calculate the brick's position
         float x = Constants::BRICK_OFFSET + (i + 1) * Constants::BRICK_WIDTH;
         float y = (j + 1) * Constants::BRICK_HEIGHT;

          // Create the brick object
			manager.create<Brick>(x, y);     }
   }
}

// Game loop
void Game::run() {
   // Was the pause key pressed in the last frame?
   bool pause_key_active{false};

   // Clear the screan
   // Check for new events;
   // Calculate the updated graphics
   // Display the updated graphics
   while (window.isOpen()) {
      // Clear the screen
      window.clear(sf::Color::Black);

      // check all the window's events that were triggered since the last iteration of the loop
      while (const std::optional event = window.pollEvent()) {
         // "close requested" event: we close the window
         if (event->is<sf::Event::Closed>()) {
            window.close();
         }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
         }
         // If the user presses 'P', we pause/unpause the game
         // To prevent repeated use, we ignore it if it was pressed on the last iterarion
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            // If it was not pressed on the last iteration, toggle the status
            if (!pause_key_active) {
               if (state == GameState::paused || state == GameState::start)
                  state = GameState::running;
               else
                  state = GameState::paused;
            }
            pause_key_active = true;
         }
         else
            pause_key_active = false;

         // If the user presses 'R', we reset the game
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
         {
            reset();
         }
      }

      // If the game is not running, the entities are not updated
      // They are redrawn only if the game is paused
      if (state == GameState::paused || state == GameState::start) {
         // Display the graphics
         manager.draw(window);
      }

      // Choose the correct text for the state of the game
      if (state != GameState::running) {
         switch (state) {
            case GameState::start:
               update_text(text_state, "Press P or Spacebar to Start"s, sf::Color::White, {0.0f, -100.0f});
               break;
            case GameState::paused:
               update_text(text_state, "Paused"s, sf::Color::White, {0.0f, -100.0f});
               break;
            case GameState::game_over:
               update_text(text_state, "Game Over!"s, sf::Color::Red, {0.0f, -100.0f});
               break;
            case GameState::player_wins:
               update_text(text_state, "Player Wins"s, sf::Color::Green, {0.0f, -100.0f});
               break;
            default:
               break;
         }
         window.draw(*text_state);
         window.draw(*text_lives);
      } else {
         // If there are no remaining balls on the screen
         if (manager.get_all<Ball>().empty()) {
            // Spawn a new one and reduce the player's remaining lives
            manager.create<Ball>(Constants::WINDOW_WIDTH/2.0f, Constants::WINDOW_HEIGHT/2.0f);
            --lives;

            state = GameState::paused;
         }
         
         // If there are no remaining bricks on the screen, the player has won!
         if (manager.get_all<Brick>().empty())
            state = GameState::player_wins;

         // If the player has used up all their lives, the game is over
         if (lives <= 0)
            state = GameState::game_over;

         // Update the text for the number of remaining lives
         update_text(text_lives, "Lives: " + std::to_string(lives), sf::Color::White, {0.0f, -50.0f});

         // Calculate the updated graphics
         manager.update();

         // Bricks interaction
         // For every ball, call a function which
         //    For every brick, call a function which
         //       Calls handleColision with the ball and the brick as arguments
         manager.apply_all<Ball>([this](auto& the_ball) {
               manager.apply_all<Brick>([&the_ball](auto& the_brick) {
                     handle_collision(the_ball, the_brick);
                     });
               });

         // Paddle interaction
         manager.apply_all<Ball>([this](auto& the_ball) {
               manager.apply_all<Paddle>([&the_ball](auto& the_paddle) {
                     handle_collision(the_ball, the_paddle);
                     });
               });
        
         manager.refresh();
         
         // Display the updated graphics
         manager.draw(window);

      }

      // Display the updated graphics
      window.display();
   }

}
