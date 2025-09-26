#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

struct Constants {
   static constexpr unsigned int WINDOW_WIDTH{520};
   static constexpr unsigned int WINDOW_HEIGHT{450};
   static constexpr float BALL_SPEED{3.0f};
   static constexpr float PADDLE_WIDTH{60.0f};
   static constexpr float PADDLE_HEIGHT{20.0f};
   static constexpr float PADDLE_SPEED{8.0f};
   static constexpr float BRICK_WIDTH{43.0f};
   static constexpr float BRICK_HEIGHT{20.0f};
   static constexpr float BRICK_OFFSET{BRICK_WIDTH/2.0f};
   static constexpr int BRICK_STRENGTH{3};
   static constexpr int BRICK_COLUMNS{10};
   static constexpr int BRICK_ROWS{4};
   static constexpr int PLAYER_LIVES{3};
};

#endif   // __CONSTANTS_HPP__
