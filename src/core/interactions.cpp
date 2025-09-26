#include <core/interactions.hpp>

// Determine whether two entities overlap
bool is_Interacting(const Entity& e1, const Entity& e2) {
   auto box1 = e1.get_bounding_box();
   auto box2 = e2.get_bounding_box();
   if (const std::optional intersection = box1.findIntersection(box2))
      return true;
   else
      return false;
}

// Resolve pontential collision between the ball and the paddle
void handle_collision(Ball& b, const Paddle& p) {
   if (is_Interacting(p, b)) {
      // Make the ball bounce upwards
      b.move_up();

      // Make the new direction depend on where the collision occurs on the paddle
      // If the collision is on the left of the paddle, make the ball bounce to the left
      if (b.x() < p.x())
         b.move_left();
      else
         b.move_right();
   }
}

// Resolve potencial collision between the ball and a brick
void handle_collision(Ball& the_ball, Brick& block) {
   if (is_Interacting(block, the_ball)) {
      // Update the brick's strength
      block.weaken();

      if (block.isTooWeak()) {
         // The brick is destroyed
         block.destroy();
      }

      // Make the new direction depend on where the collision occurs on the brick
      // If the ball collides on the side of the brick, make the ball bounce to the left
      // If the ball collides on the top/bottom of the brick, make the ball bounce upwards/downwards
      //
      // First we find the amount of overlap in each direction
      // The smaller the left overlap, the closer the ball is to the left of the brick
      // And similarly for the other sides of the brick
      float left_overlap = the_ball.right() - block.left();
      float right_overlap = block.right() - the_ball.left();
      float top_overlap = the_ball.bottom() - block.top();
      float bottom_overlap = block.bottom() - the_ball.top();

      // If the left overlap is smaller than the right overlap, the ball hit the left side ofthe brick
      bool from_left = std::abs(left_overlap) < std::abs(right_overlap);
      bool from_top = std::abs(top_overlap) < std::abs(bottom_overlap);
      
      // Use the right or left overlap as appropriate
      float min_x_overlap = from_left ? left_overlap : right_overlap;
      float min_y_overlap = from_top ? top_overlap : bottom_overlap;

      // If the ball hit the left or right side of the brick, change its horizontal direction
      // If the ball hit the top or bottom of the brick, change its vertical direction
      if (std::abs(min_x_overlap) < std::abs(min_y_overlap)) {
         if (from_left)
            the_ball.move_left();
         else
            the_ball.move_right();
      }
      else {
         if (from_top)
            the_ball.move_up();
         else
            the_ball.move_down();
      }
   }
}
