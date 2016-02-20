// Hexiang Li

#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "title.c"
#include "title.h"


int main() {
	REG_DISPCNT = MODE_3 | BG2_EN;

	while (1) {
		drawImage3(0, 0, 240, 160, title);
		while(!KEY_DOWN_NOW(BUTTON_START));
		drawRect(0,0,240,160,GREY);

		while(play()) {

		}
	
	}
	return 0;
}