#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "display.h"

int main() {
	struct game *G;
	enum input input;
	enum status stat;

	do {
		int start = 1;

		display_open();

		G = game_create();

		if(G == NULL) {
			display_close();
			fprintf(stderr,"Error: cannot initialize the game\n");
			return 1;
		}

		do {
			do {
				display_plot(G);
				stat  = CONTINUE;
				input = NONE;
			  switch (display_read()) {
					case QUIT_KEY    :  stat = GAMEOVER; break;
					case RESTART_KEY :  stat = RESTART;  break;
					case LEFT_KEY    : input = LEFT;     break;
	    		case RIGHT_KEY   : input = RIGHT;    break;
	    		case DOWN_KEY    : input = DOWN;     break;
	    		case UP_KEY      : input = UP;       break;
	    		case FLAG_KEY    : input = FLAG;     break;
					case EXPAND_KEY  : input = EXPAND;   break;
	    		case DISPLAY_KEY : input = DISPLAY;
														 if(start) {
																start = 0;
																game_init(G);
															
														 }
														 break;
					default:           input = NONE;     break;
				}
					
				if(stat == CONTINUE && input != NONE && game_update(G,input) == GAMEOVER) {
					do {
						display_gameover(G);
						switch(display_read()) {
							case QUIT_KEY   : stat = GAMEOVER; break;
							case RESTART_KEY: stat = RESTART;  break;
							default:          stat = CONTINUE; break;
						}
					} while(stat == CONTINUE);
				}
			} while(input == NONE && stat == CONTINUE); 
		} while(stat == CONTINUE); 

		game_destroy(G);
		display_close();
	} while(stat == RESTART);

  return 0;
}
