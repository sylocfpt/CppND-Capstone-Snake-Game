#include "snake.h"
#include <cmath>
#include <iostream>
#include <algorithm>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
    // STUDENT CODE -->
    bool is_reach_bound = false;
    std::pair<float, float> head_next_position = HeadNextPosition(head_x, head_y);
    float next_x = head_next_position.first;
    float next_y = head_next_position.second;
    int head_x_cast = static_cast<int>(head_x);
    int head_y_cast = static_cast<int>(head_y);
    int next_x_cast = static_cast<int>(next_x);
    int next_y_cast = static_cast<int>(next_y);

    switch (direction) {
    case Direction::kUp:
        if (next_y < 0 || (head_y_cast != next_y_cast && SnakeCell(next_x_cast, next_y_cast)))
        {
            is_reach_bound = true;
            if (head_x_cast <= 0 || SnakeCell(head_x_cast - 1, head_y_cast)) 
                direction = Direction::kRight;
            else
                direction = Direction::kLeft;
        }
        break;

    case Direction::kDown:
        if (next_y >= grid_height || (head_y_cast != next_y_cast && SnakeCell(next_x_cast, next_y_cast)))
        {
            is_reach_bound = true;
            if (head_x_cast >= grid_width - 1 || SnakeCell(head_x_cast + 1, head_y_cast))
                direction = Direction::kLeft;
            else
                direction = Direction::kRight;
        }
        break;

    case Direction::kLeft:
        if (next_x <= 0 || head_x_cast != next_x_cast && SnakeCell(next_x_cast, next_y_cast))
        {
            is_reach_bound = true;
            if (head_y_cast >= grid_height - 1 || SnakeCell(head_x_cast, head_y_cast + 1))
                direction = Direction::kUp;
            else
                direction = Direction::kDown;
        }
        break;

    case Direction::kRight:
        if (next_x >= grid_width || head_x_cast != next_x_cast && SnakeCell(next_x_cast, next_y_cast))
        {
            is_reach_bound = true;
            if (head_y_cast <= 0 || SnakeCell(head_x_cast, head_y_cast - 1)) 
                direction = Direction::kDown;
            else
                direction = Direction::kUp;
        }
        break;
    }

    // Wrap the Snake around to the beginning if going off of the screen.
    if (is_reach_bound)
        head_next_position = HeadNextPosition(head_x, head_y);

    head_x = head_next_position.first;
    head_y = head_next_position.second;
    // <-- STUDENT CODE
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  // STUDENT CODE -->
  if(std::any_of(body.begin(), body.end(), [&](const SDL_Point &p){return p.x == x && p.y == y;}))
  {
    return true;
  }
  // <-- STUDENT CODE
  return false;
}

// STUDENT CODE -->
Snake::Snake(int grid_width, int grid_height)
    : grid_width(grid_width),
      grid_height(grid_height),
      head_x(grid_width / 2),
      head_y(grid_height / 2)
{

    int plus_x, plus_y;
    switch (direction)
    {
    case Direction::kUp:
        plus_x = 0;
        plus_y = -1;
        break;
    case Direction::kDown:
        plus_x = 0;
        plus_y = 1;
        break;
    case Direction::kLeft:
        plus_x = -1;
        plus_y = 0;
        break;
    case Direction::kRight:
        plus_x = 1;
        plus_y = 0;
    }
    for (auto count = 1; count < size; count++)
    {
        SDL_Point cell{
            static_cast<int>(head_x - (size - count) * plus_x),
            static_cast<int>(head_y - (size - count) * plus_y)};
        body.push_back(cell);
    }
}

std::pair<float, float> Snake::HeadNextPosition(float x, float y) {
    switch (direction)
    {
    case Direction::kUp:
        y -= speed;
        break;

    case Direction::kDown:
        y += speed;
        break;

    case Direction::kLeft:
        x -= speed;
        break;

    case Direction::kRight:
        x += speed;
        break;
    }
    return std::pair<float, float>(x, y);
}

std::pair<int, int> Snake::NextCell()
{
    std::pair<int, int> next_cell(0, 0);
    int x = static_cast<int>(head_x);
    int y = static_cast<int>(head_y);
    switch (direction)
    {
    case Direction::kUp:
        y -= 1;
        break;

    case Direction::kDown:
        y += 1;
        break;

    case Direction::kLeft:
        x -= 1;
        break;

    case Direction::kRight:
        x += 1;
        break;
    }
    next_cell = std::pair(x , y);
    return next_cell;
}

void Snake::ChangeDirection(Direction input_direction)
{
    Direction cur_direction = direction;
    direction = input_direction;
    std::pair<int, int> next_cell = NextCell();
    if (SnakeCell(next_cell.first, next_cell.second))
        direction = cur_direction; 
    else
    {
        if (next_cell.first < 0 || next_cell.first >= grid_width ||
            next_cell.second < 0 || next_cell.second >= grid_height)
            direction = cur_direction;
    }
}
// <-- STUDENT CODE