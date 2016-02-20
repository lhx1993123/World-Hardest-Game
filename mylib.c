// Hexiang Li

#include "mylib.h"
#include "HAHAHA.c"
#include "HAHAHA.h"
#include "WOWWOWWOW.c"
#include "WOWWOWWOW.h"
#include "tryagain.c"
#include "tryagain.h"
#include "seriouly.c"
#include "seriouly.h"

u16 *videoBuffer = (u16 *) 0x6000000;
int numOfDeath = 0;

void setPixel(int r, int c, u16 color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

void drawRect(int r, int c, int width, int height, u16 color) {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			setPixel(r + i, c + j, color);
		}
	}
}


void drawHollowRect(int r, int c, int width, int height, u16 color) {
	for (int i = 0; i < height; i ++) {
		setPixel(r + i, c, color);
		setPixel(r + i, c + width - 1, color);
	}

	for (int j = 1; j < width - 1; j++) {
		setPixel(r, c + j, color);
		setPixel(r + height - 1, c + j, color);
	}
}

void drawImage3(int r, int c, int width, int height, const u16* image) {
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j< width; j++) {
			videoBuffer[(c + i) * 240 + (r+j)] = image[(i * width) + j];
		}
	}
}

void delay(int x){
	volatile int i;
	for (i = 0; i < (x * 1000); i++) {
	}
}

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

int play() {

	drawRect(65,30,170,30,BLACK);
	drawRect(65,15,15,30,GREEN);
	drawRect(65,200,15,30,GREEN);

	CIRCLES circs[6];
	CIRCLES oldcircs[6];
	CIRCLES *ptr;
	PLY usr[1];
	PLY oldusr[1];
	

	usr->r=78;
	usr->c=15;	
	oldusr[0]=usr[0];
	int i;
	int playing = 1;
	for(i=0;i<3;i++){
		(circs+i)->r=(((3+i)%3)*9+70);
		(circs+i)->c=(((2+i)%2)*70+55);
		(circs+i)->dr=0;
		(circs+i)->dc=2;
		(circs+i)->toplimR=0;
		(circs+i)->botlimR=160;
		(circs+i)->leftlimC=(((2+i)%2)*70+40);
		(circs+i)->rightlimC=(((2+i)%2)*70+126);
		oldcircs[i]=circs[i];
	}

	for(i=3;i<6;i++){
		(circs+i)->r=(((3+i)%3)*9+70);
		(circs+i)->c=(((2+i)%2)*70+55);
		(circs+i)->dr=0;
		(circs+i)->dc=2;
		(circs+i)->toplimR=0;
		(circs+i)->botlimR=160;
		(circs+i)->leftlimC=(((2+i)%2)*70+50);
		(circs+i)->rightlimC=(((2+i)%2)*70+126);
		oldcircs[i]=circs[i];
	}


	while(playing == 1) {
		if(KEY_DOWN_NOW(BUTTON_SELECT)) {
			return 0;
		}
		
		if(KEY_DOWN_NOW(BUTTON_UP)) {
			(usr->r)--;
			if (usr->r<65) {
				usr->r++;
			}

		}
		if(KEY_DOWN_NOW(BUTTON_DOWN)) {
			usr->r++;
			if(usr->r >= 90) {
				usr->r--;
			}
		}	
		if(KEY_DOWN_NOW(BUTTON_LEFT)) {
			usr->c--;
			if((usr->r>90) && (usr->c<145)){
				usr->c++;
			}
			if((usr->r<65) && (usr->c<75)){
				usr->c++;
			}
			if(usr->c<15) {
				usr->c++;
			}
		}

		if(KEY_DOWN_NOW(BUTTON_RIGHT)) {
			usr->c++;
			if((usr->r > 90)&&(usr->c > 150)){
				usr->c--;
			}
			if((usr->r < 65) && (usr->c > 80)){
				usr->c--;
			}

			// goal
			if(usr->c > 195) {
				drawImage3(0, 0, 240, 160, WOWWOWWOW);
				delay(1500);
				playing = 0;
			}
		}

		for(i=0; i<6; i++) {
			ptr = circs+i;

			ptr->r += ptr->dr;
			ptr->c += ptr->dc;
		
			// Collision detection
			if(ptr->r<ptr->toplimR) {
				ptr->r = ptr->toplimR;
				ptr->dr = -ptr->dr;
			}
			if(ptr->r>ptr->botlimR) {
				ptr->r = ptr->botlimR;
				ptr->dr = -ptr->dr;
			}
			if(ptr->c < ptr->leftlimC) {
				ptr->c = ptr->leftlimC;
				ptr->dc = -ptr->dc;
			}
			if(ptr->c > ptr->rightlimC) {
				ptr->c = ptr->rightlimC;
				ptr->dc = -ptr->dc;
			}	
			
			
			if (((ptr->r)-3)<((usr->r)+5)&&((ptr->r)+3)>((usr->r))) {

				if (((ptr->c)+3)>(usr->c)&&((ptr->c)-3)<(usr->c+5)){
					numOfDeath++;
					if (numOfDeath <= 2) {
						drawImage3(40,40,160,80,tryagain);
						delay(1000);
					}
					else if (numOfDeath == 3) {
						drawImage3(0,0,240,160, seriouly);

						delay(1000);
					}
					else {
						drawImage3(0,0,240,160,HAHAHA);
						delay(1000);
					}

					drawRect(0,0,240,160,GREY);
					return 1;
				}
			}
				
			
		}		
		waitForVblank();

		
		for(i=0; i<6; i++) {
			drawCirc(oldcircs[i].r, oldcircs[i].c, 3, BLACK);
		}
		
		for(i=0; i<6; i++) {
			drawCirc(circs[i].r, circs[i].c, 3, YELLOW);
			oldcircs[i] = circs[i];
		}
		if(usr->c<30){
			drawRect(oldusr->r,oldusr->c,5,5,GREEN);
		}

		else {
		drawRect(oldusr->r,oldusr->c,5,5,BLACK);
		}
		drawRect(65,30,6,30,BLACK);
		drawRect(65,29,1,30,GREEN);
		drawRect(usr->r,usr->c,5,5,MAGENTA);
		oldusr[0]=usr[0];
		delay(4);
	}
	return 0;
}

void drawCirc(int r, int c, int rad, u16 color){
	int dist=rad*rad;
	if (rad==0){
		;
	}
	else{
		for (int row=(r-rad);row<(r+rad);row++){
			for (int col=(c-rad);col<(c+rad);col++){
				if ((((row-r)*(row-r))+((col-c)*(col-c)))<=dist){
					setPixel(row,col,color);
				}
			}
		}
	}
}
