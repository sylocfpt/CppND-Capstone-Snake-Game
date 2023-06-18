#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <utility>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height);

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

// STUDENT CODE -->
  // Classes encapsulate behavior
  void ChangeDirection(Direction input_direction);
  // Classes encapsulate behavior
  bool Alive() const { return alive; }
  // Classes encapsulate behavior
  float GetHeadX() const { return head_x; }
  // Classes encapsulate behavior
  float GetHeadY() const { return head_y; }
  // The project makes use of references in function declarations.
  const std::vector<SDL_Point> &GetBody() const { return body; }
  // Classes encapsulate behavior
  void SpeedScale(float factor) { speed *= factor; }
  // Classes encapsulate behavior
  int GetSize() const { return size; }
// <-- STUDENT CODE

private:

  float speed{0.1f};
  int size{3};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  std::pair<float, float> HeadNextPosition(float x, float y);
  std::pair<int, int> NextCell();

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif