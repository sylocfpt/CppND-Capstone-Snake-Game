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

  void ChangeDirection(Direction input_direction);
  bool Alive() const { return alive; }
  float GetHeadX() const { return head_x; }
  float GetHeadY() const { return head_y; }
  const std::vector<SDL_Point> &GetBody() const { return body; }
  void SpeedScale(float factor) { speed *= factor; }
  int GetSize() const { return size; }

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