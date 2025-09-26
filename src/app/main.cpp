// Code for a siimple "breakout" game
// Based on the lectures from James Raynard´s "Modern C++: From Intermediate to Advanced"
// https://www.udemy.com/course/learn-intermediate-modern-c/
// Based on a talk by Vittorio Romeo and code by "FamTrimli"
// Uses the SFML graphics library

#include <core/game.hpp>

int main() {
   // Create an instance of the game
   Game the_game;

   // (Re)initialize the game
   the_game.reset();

   // Run the game
   the_game.run();

   return 0;
}
