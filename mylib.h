// Hexiang Li

typedef unsigned short u16;

#define REG_DISPCNT *(u16 *)0x4000000
#define MODE_3 3
#define BG2_EN (1<<10)
#define RGB(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define RED RGB(31,0,0)
#define GREEN RGB(0,31,0)
#define BLUE RGB(0,0,31)
#define CYAN RGB(0,31,31)
#define MAGENTA RGB(31, 0,31)
#define YELLOW RGB(31,31,0)
#define WHITE RGB(31,31,31)
#define GREY RGB(26,26,26)
#define BLACK 0
#define BGRGB 0x05b76
#define LTGRAY RGB(25, 25, 25)
#define SCANLINECOUNTER  (*(volatile u16 *)0x4000006)

#define OFFSET(r, c, numcols) ((r)*(numcols)+(c))
#define HOME 1
#define GAME 2
#define END 3

// Buttons
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130
#define NUMOBJS2 6
extern u16 *videoBuffer;
extern int numOfDeath;

typedef struct {		
		int r;
		int c;
		int dr;
		int dc;
		int leftlimC;
		int rightlimC;
		int toplimR;
		int botlimR;
		} CIRCLES;

typedef struct {
		int r;
		int c;
		} PLY;

// Prototype
void setPixel(int row, int col, u16 color);
void drawRect(int row, int col, int height, int width, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);
void delay(int x);
int play();
void waitForVblank();
void drawCirc(int r, int c, int rad, u16 color);
