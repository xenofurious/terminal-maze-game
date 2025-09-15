#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define WIDTH 50
#define HEIGHT 24

enum object {invalid, empty, boundary, wall, start, end};
enum object maze[WIDTH][HEIGHT] = {invalid};

enum direction {up, left, down, right, none};
enum direction rand_direction[] = {up, left, down, right};
enum direction *rand_direction_ptr = &rand_direction[0];

struct coord {
  int x;
  int y;
};

struct coord stack[WIDTH*HEIGHT];
struct coord *stack_ptr = &stack[0];

void push(struct coord c) { 
  printf("pushed value = %d %d\n", c.x, c.y);
  *stack_ptr = c;
  stack_ptr++;
}

struct coord pop() {
  stack_ptr--;
  struct coord c = *stack_ptr;
  printf("popped value = %d %d\n", c.x, c.y);
  return c;
}


void init_maze() {
  srand(time(NULL));
  for (int i=0; i<WIDTH; i++){
    maze[i][0] = boundary;
    maze[i][HEIGHT-1] = boundary;
  }
  for (int j=0; j<HEIGHT; j++){
    maze[0][j] = boundary;
    maze[WIDTH-1][j] = boundary;
  }
  maze[1][1] = start;
  maze[WIDTH-2][HEIGHT-2] = end;
}


void print_maze() {
  char printchar;
  int w, h;
  for (h = 0; h < HEIGHT; h++){
    for (w = 0; w < WIDTH; w++) {
      switch (maze[w][h]){
        case empty: printchar = ' '; break;
        case boundary: printchar = 'B'; break;
        case wall: printchar = '#'; break;
        case start: printchar = 's'; break;
        case end: printchar = '*'; break;
        default: printchar = '_'; break; // includes invalid
      }
      mvprintw(h, w, "%c", printchar);
    }
  }
}

void draw_player(int player_x, int player_y) {
  mvprintw(player_x, player_y, "@");

}


// now we try and implement the algorithm

void permute_directions() {
  enum direction temp;
  for (int i=3; i>=0; i--){
    int swap = rand() % (i+1);
    temp = rand_direction[i];
    rand_direction[i] = rand_direction[swap];
    rand_direction[swap] = temp;
  }
}

bool check_valid_cell(enum object cell){
  if (cell == invalid || cell == end || cell == boundary) {
    return true;
  } else {
    return false;
  }
}

bool check_valid_cell_for_walls(int x, int y, enum direction my_dir) {
  switch (my_dir){
    case up:
      if ((maze[x-1][y] == wall) && (maze[x-1][y-1] == wall) && (maze[x][y-1] == wall) && (maze[x+1][y-1] == wall) && (maze[x+1][y] == wall)) {
        return true;
      }
      break;
    case left:
      if ((maze[x][y+1] == wall) && (maze[x-1][y+1] == wall) && (maze[x-1][y] == wall) && (maze[x-1][y-1] == wall) && (maze[x][y-1] == wall)) {
        return true;
      }
      break; 
    case down:
      if ((maze[x+1][y] == wall) && (maze[x+1][y+1] == wall) && (maze[x][y+1] == wall) && (maze[x-1][y+1] == wall) && (maze[x-1][y] == wall)) {
        return true;
      }
      break; 
    case right:
      if ((maze[x][y-1] == wall) && (maze[x+1][y-1] == wall) && (maze[x+1][y] == wall) && (maze[x+1][y+1] == wall) && (maze[x][y+1] == wall)) {
        return true;
      }
      break; 
    default: 
      return false;
  }  
  return false;
}

enum direction check_for_walls(int w, int h) {
  bool found_wall = false;
  permute_directions();
  for (int i=0; i<4 &&found_wall==false; i++){
    switch (rand_direction[i]) {
      case up:
        if (maze[w][h-1] == wall) {
          if (check_valid_cell(maze[w][h-2]) || check_valid_cell_for_walls(w, h-1, up)){
            found_wall = true;
            return up;
          }
        }
        break; 
      case left:
        if (maze[w-1][h] == wall){
          if (check_valid_cell(maze[w-2][h]) || check_valid_cell_for_walls(w-1, h, left)) {
            found_wall = true;
            return left;
          }
        }
        break; 
      case down:
        if (maze[w][h+1] == wall){
          if (check_valid_cell(maze[w][h+2] || check_valid_cell_for_walls(w, h+1, down))){
            found_wall = true;
            return down;
          }
        }
        break; 
      case right:
        if (maze[w+1][h] == wall) {
          if (check_valid_cell(maze[w+2][h] || check_valid_cell_for_walls(w+1, h, right))){
            found_wall = true;
            return right;
          }
        }
        break; 
      default: return none;
    }
  }
  return none;
}

int replace_cell(int x, int y) {
  if (maze[x][y] != invalid) {
    return 1;
  } else {
    maze[x][y] = wall;
    return 0;
  }
}

void generate_walls(enum direction input_dir, int* player_x, int* player_y) {
  switch (input_dir) {
    case up:
      (*player_y)--;
      replace_cell(*player_x-1, *player_y);
      replace_cell(*player_x-1, *player_y-1);
      replace_cell(*player_x, *player_y-1);
      replace_cell(*player_x+1, *player_y-1);
      replace_cell(*player_x+1, *player_y);
      break;
    case left:
      (*player_x)--;
      replace_cell(*player_x, *player_y+1);
      replace_cell(*player_x-1, *player_y+1);
      replace_cell(*player_x-1, *player_y);
      replace_cell(*player_x-1, *player_y-1);
      replace_cell(*player_x, *player_y-1);
      break; 
    case down:
      (*player_y)++;
      replace_cell(*player_x+1, *player_y);
      replace_cell(*player_x+1, *player_y+1);
      replace_cell(*player_x, *player_y+1);
      replace_cell(*player_x-1, *player_y+1);
      replace_cell(*player_x-1, *player_y);
      break; 
    case right:
      (*player_x)++;
      replace_cell(*player_x, *player_y-1);
      replace_cell(*player_x+1, *player_y-1);
      replace_cell(*player_x+1, *player_y);
      replace_cell(*player_x+1, *player_y+1);
      replace_cell(*player_x, *player_y+1);
      break; 
    default: 
      replace_cell(*player_x-1, *player_y);
      replace_cell(*player_x-1, *player_y-1);
      replace_cell(*player_x, *player_y-1);
      replace_cell(*player_x+1, *player_y-1);
      replace_cell(*player_x+1, *player_y);
      replace_cell(*player_x+1, *player_y+1);
      replace_cell(*player_x, *player_y+1);
      replace_cell(*player_x-1, *player_y+1);
      break;
  }
  maze[*player_x][*player_y] = empty;
  push( (struct coord){*player_x, *player_y});
}


void generate_maze(int player_x, int player_y) {
  // need to think of a predictable test case
  generate_walls(none, &player_x, &player_y);
  enum direction thing = check_for_walls(player_x, player_y);
  
  while (stack_ptr != &stack[0]) {
    if (thing != none){
      generate_walls(thing, &player_x, &player_y);
      thing = check_for_walls(player_x, player_y);
      push( (struct coord){player_x, player_y});
    } else {
      pop();
      player_x = (stack_ptr-1)->x;
      player_y = (stack_ptr-1)->y;
      thing = check_for_walls(player_x, player_y);
    }
  }



}



int main() {


  initscr();
  init_maze();

  int player_x, player_y;
  player_x = player_y = 1;
  generate_maze(player_x, player_y);

  print_maze();
  draw_player(player_x, player_y);
  refresh();
  char a = getch();
  endwin();
  

  

  // debug
  printf("%d %d %d %d\n", rand_direction[0], rand_direction[1], rand_direction[2], rand_direction[3]);
  //printf("%d\n", thing);
  printf("michaelgirafortniteskin\n");
  return 0;
}


//where the main game loop happens

int gameloop() {

  return 0;
}
