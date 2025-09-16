#ifndef MAZE_GEN_H
#define MAZE_GEN_H

#include <stdbool.h>

#define WIDTH 50
#define HEIGHT 25


enum object {invalid, empty, boundary, wall, start, end};
enum direction { up, left, down, right, none };


struct coord {
  int x;
  int y;
};

extern enum direction rand_direction[];
extern enum direction *rand_direction_ptr;

extern struct coord stack[WIDTH*HEIGHT];
extern struct coord *stack_ptr;

extern enum object maze[WIDTH][HEIGHT];


// functions
void push(struct coord c);
struct coord pop();
void init_maze();
void print_maze();
void draw_player(int player_x, int player_y);
void undraw_player(int player_x_old, int player_y_old);
void permute_directions();
bool check_valid_cell(enum object cell);
bool check_valid_cell_for_walls(int x, int y, enum direction my_dir);
enum direction check_for_walls(int w, int h);
int replace_cell(int x, int y);
void generate_walls(enum direction input_dir, int* player_x, int* player_y);
void generate_maze(int player_x, int player_y);



#endif
