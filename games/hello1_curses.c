#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses/curses.h>

int main()
{
	initscr();

	clear();
	move(10 , 20 );
	addstr("Hello World!");
	move(LINES - 1 , 0 );
	refresh();
	getch();
	endwin();
	return 0 ;
}