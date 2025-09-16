#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include "maze_generation.h"

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
