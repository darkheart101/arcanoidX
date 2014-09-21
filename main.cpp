#include<stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"level.h"
#include "misc.h"
//#include"collide.h"

const int WIDTH = 640;
const int HEIGHT = 480;
const int BPP = 32;

SDL_Event event;

SDL_Surface *screen = NULL;
SDL_Surface *bg = NULL;
SDL_Surface *sprite = NULL;
SDL_Surface *ball = NULL;
SDL_Surface *brick[4];
SDL_Surface *lose = NULL;
SDL_Surface *gameover = NULL;
SDL_Surface *levl = NULL;
SDL_Surface *finished = NULL;
SDL_Surface *sprt_lv = NULL;
SDL_Surface *bl = NULL;
SDL_Surface *arc = NULL;
SDL_Surface *cr = NULL;
SDL_Surface *f1play = NULL;

SDL_Rect offsetBG;
SDL_Rect offsetSPR;
SDL_Rect offsetBALL;
SDL_Rect offsetBRICK[34];
SDL_Rect sprt_lvs[2];
SDL_Rect offsetARC;


bool quit = false;
bool brickVis[34];

bool start = true;
bool fstSCR = true;
bool arc_down = false;
bool lost = false;
bool nxt = false;
bool finish = false;

int xVelSPR = 0;
int Ytmp = 0;
int Xtmp = 0;
int xVelBALL;
int yVelBALL;
int dirc;
int tmp = 0;
int score = 0;
int lives = 3;
int nxtLvl = 0;







int main(int argc,char *argv[]){
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1){
		printf("SDL Cannot Initialize");
	}
	if(argc==2){
		if(argv[1]="-f"){
			screen = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);
		}
	}
	else {
		screen = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_DOUBLEBUF | SDL_HWSURFACE);
	}
	
	SDL_WM_SetCaption("ArcanoidX",NULL);
	bg = IMG_Load("./images/bg.png");
	sprt_lv = IMG_Load("./images/sprite_small.png");
	sprite = IMG_Load("./images/sprite.png");
	sprt_lvs[0].x = 530;
	sprt_lvs[0].y = 370;
	sprt_lvs[0].w = 30;
	sprt_lvs[0].h = 15;
	sprt_lvs[1].x = 570;
	sprt_lvs[1].y = 370;
	sprt_lvs[1].w = 30;
	sprt_lvs[1].h = 15;
	offsetARC.x = 235;
	offsetARC.y = 0;
	offsetARC.w = 170;
	offsetARC.h = 40;
	bl = IMG_Load("./images/bl.png");
	arc = IMG_Load("./images/arc.png");
	cr = IMG_Load("./images/cr.png");
	f1play = IMG_Load("./images/f1play.png");	

	ball = IMG_Load("./images/ball.png");
	brick[0] = IMG_Load("./images/red.png");
	brick[1] = IMG_Load("./images/blue.png");
	brick[2] = IMG_Load("./images/green.png");
	brick[3] = IMG_Load("./images/purple.png");
	gameover = IMG_Load("./images/gameover.png");
	for(int i=0;i<34;i++){
		brickVis[i] = true;
	}

	
	while(fstSCR==true){
			while(SDL_PollEvent(&event)){
				if(event.type==SDL_QUIT){
					quit = true;
					fstSCR = false;
				}
				if(event.type==SDL_KEYDOWN){
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: quit = true;fstSCR = false;break;
						case SDLK_F1: fstSCR = false; break;
					}
				}
				if(arc_down == false){
					SDL_BlitSurface(bl,NULL,screen,&offsetBG);
					for(offsetARC.y=0;offsetARC.y<160;offsetARC.y++){
						SDL_BlitSurface(arc,NULL,screen,&offsetARC);
						SDL_Flip(screen);
						if(offsetARC.y != 159){
							SDL_BlitSurface(bl,&offsetARC,screen,&offsetARC);
						}
					}
					arc_down = true;
					offsetARC.x = 0;
					offsetARC.y = 380;
					offsetARC.w = 100;
					offsetARC.h = 100;
					SDL_BlitSurface(cr,NULL,screen,&offsetARC);
					SDL_Flip(screen);
					
					
				}
				offsetARC.x = 235;
				offsetARC.y = 200;
				offsetARC.w = 170;
				offsetARC.h = 30;
				SDL_BlitSurface(f1play,NULL,screen,&offsetARC);
				SDL_Flip(screen);
			}
	}

	//starting level 1
	if(quit==false){
		levl = IMG_Load("./images/level1.png");
		level("./levels/level1");
		nxt = false;
		nxtLvl = 0;
	}
	//starting level 2
	if(quit==false){
		levl = IMG_Load("./images/level2.png");
		level("./levels/level2");
		nxt = false;
		nxtLvl = 0;
	}
	
	//starting level 3
	if(quit==false){
		levl = IMG_Load("./images/level3.png");
		level("./levels/level3");
		if(lives!=0 && quit==false){
			finish = true;
		}
	}
	
	//Finishing the game
	if(finish == true){
		finished = IMG_Load("./images/finished.png");
		SDL_BlitSurface(finished,NULL,screen,&offsetBG);
		SDL_Flip(screen);
		delay();
	}
	//clearing memory
	SDL_FreeSurface(bg);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(sprite);
	SDL_FreeSurface(ball);
	for(int i=0;i<4;i++){
		SDL_FreeSurface(brick[i]);
	}
	SDL_FreeSurface(sprt_lv);
	SDL_FreeSurface(lose);
	SDL_FreeSurface(gameover);
	SDL_FreeSurface(bl);
	SDL_FreeSurface(levl);
	SDL_FreeSurface(finished);
	SDL_Quit();
	printf("Your Score is:%d\n",score);
	return 0;
}
