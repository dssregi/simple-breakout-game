#ifndef __INTERACTIONS_HPP__
#define __INTERACTIONS_HPP__

#include <core/ball.hpp>
#include <core/paddle.hpp>
#include <core/brick.hpp>

// Determine whether two entities overlap
bool is_Interacting(const Entity& e1, const Entity& e2);

// Resolve pontential collisions between the ball and the paddle
void handle_collision(Ball& b, const Paddle& p);

// Resolve pontential collisions between the ball and a brick
void handle_collision(Ball& b, Brick& p);

#endif   // __INTERACTIONS_HPP__
