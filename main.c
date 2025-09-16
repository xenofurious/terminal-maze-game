#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include "maze_generation.h"

enum direction input_handle(char input) {

  return none;
}


//where the main game loop happens
int gameloop() {
 
  // init
  init_maze();
  int player_x, player_y;
  player_x = player_y = 1;
  generate_maze(player_x, player_y);
  enum direction input;
  print_maze();
  curs_set(0);
  noecho();
  int rows, cols;
  
  // loop
  bool looping = true;
  while (looping) {
    draw_player(player_x, player_y);
    refresh();
    char input = getch();
    
    switch (input) {
      case 'w':
        if (maze[player_x][player_y-1]==empty) {
          undraw_player(player_x, player_y);
          player_y--;
        } else if (maze[player_x][player_y-1]==end) {
          looping = false;
        }
        break;
      case 'a':
        if (maze[player_x-1][player_y]==empty) {
          undraw_player(player_x, player_y);
          player_x--;
        } else if (maze[player_x-1][player_y]==end) {
          looping = false;
        }
        break;
      case 's':
        if (maze[player_x][player_y+1]==empty) {
          undraw_player(player_x, player_y);
          player_y++;
        } else if (maze[player_x][player_y+1]==end) {
          looping = false;
        }
        break;
      case 'd':
        if (maze[player_x+1][player_y]==empty) {
          undraw_player(player_x, player_y);
          player_x++;
        } else if (maze[player_x+1][player_y]==end) {
          looping = false;
        }
        break;
      case 'q':
        looping = false;
        break;
      default:
        break;
    }
  }
  echo();
  return 0;
}




int main() {
  initscr();
  gameloop();
  endwin();


  // debug
//  printf("michaelgirafortniteskin\n");
  return 0;
}


