#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"misc.h"
#include"collide.h"

extern SDL_Event event;

extern SDL_Surface *screen;
extern SDL_Surface *bg;
extern SDL_Surface *sprite;
extern SDL_Surface *ball;
extern SDL_Surface *brick[];
extern SDL_Surface *lose;
extern SDL_Surface *fscreen;
extern SDL_Surface *gameover;
extern SDL_Surface *levl;
extern SDL_Surface *sprt_lv;

extern SDL_Rect offsetBG;
extern SDL_Rect offsetSPR;
extern SDL_Rect offsetBALL;
extern SDL_Rect offsetBRICK[];
extern SDL_Rect sprt_lvs[];


extern bool quit;
extern bool brickVis[];

extern bool start;
extern bool fstSCR;
extern bool lost;
extern bool nxt;


extern int xVelSPR;
extern int Ytmp;
extern int Xtmp;
extern int xVelBALL;
extern int yVelBALL;
extern int dirc;
extern int tmp;
extern int score;
extern int lives;
extern int nxtLvl;



void level(char flvl[]){
		int x,i;
	
		offsetBG.x = 0;
		offsetBG.y = 0;
		offsetBG.w = 640;
		offsetBG.h = 480;
		offsetSPR.x = 251;
		offsetSPR.y = 401;
		offsetSPR.w = 60;
		offsetSPR.h = 20;
		offsetBALL.x = 275;
		offsetBALL.y = 385;
		offsetBALL.w = 15;
		offsetBALL.h = 15;
		i=0;
		//Bricks initialization
		for(x=0;x<34;x++){
			i=i+1;
			offsetBRICK[x].x = Load(flvl,i);
			i=i+1;
			offsetBRICK[x].y = Load(flvl,i);
			offsetBRICK[x].w = 10;
			offsetBRICK[x].h = 10;
		}
		
		//starting screen of level 
		SDL_BlitSurface(levl,NULL,screen,&offsetBG);
		SDL_Flip(screen);
		delay();

		//drawing the background picture	
		SDL_BlitSurface(bg,NULL,screen,&offsetBG);

		SDL_BlitSurface(sprite,NULL,screen,&offsetSPR);
		SDL_SetColorKey(ball,SDL_RLEACCEL | SDL_SRCCOLORKEY,SDL_MapRGB(ball->format,0,0xff,0xff));
		
		SDL_BlitSurface(bg,NULL,screen,&offsetBG);
		//drawing the lives
		switch(lives){
			case 3:{
				SDL_BlitSurface(sprt_lv,NULL,screen,&sprt_lvs[0]);
				SDL_BlitSurface(sprt_lv,NULL,screen,&sprt_lvs[1]);
				break;
				}
			case 2:{
				SDL_BlitSurface(bg,&sprt_lvs[0],screen,&sprt_lvs[0]);
				SDL_BlitSurface(sprt_lv,NULL,screen,&sprt_lvs[1]);
				break;
				}
			case 1:{
				SDL_BlitSurface(bg,&sprt_lvs[0],screen,&sprt_lvs[0]);
				SDL_BlitSurface(bg,&sprt_lvs[1],screen,&sprt_lvs[1]);
				break;
				}
		}
				

		SDL_BlitSurface(sprite,NULL,screen,&offsetSPR);
		SDL_BlitSurface(ball,NULL,screen,&offsetBALL);
		i=0;
		for(x=0;x<34;x++){
			if(i==4){
				i=0;
			}
			SDL_BlitSurface(brick[i],NULL,screen,&offsetBRICK[x]);
			i=i+1;			
			
		}
	
		SDL_Flip(screen);
	
		while(quit==false && nxt==false ){
			nxt=nxtLevel(34);
	
			if(lost==true){
				nxtLvl = 0;
				offsetBALL.x = 275;
				offsetBALL.y = 385;
			
				for(i=0;i<34;i++){
					brickVis[i] = true;
				}
			
				offsetBG.x = 0;
				offsetBG.y = 0;
				offsetSPR.x = 251;
				offsetSPR.y = 401;
				offsetBALL.x = 275;
				offsetBALL.y = 385;
				
				i=0;	
				for(x=0;x<34;x++){
					i=i+1;
					offsetBRICK[x].x = Load(flvl,i);
					i=i+1;
					offsetBRICK[x].y = Load(flvl,i);
				}



				SDL_BlitSurface(bg,NULL,screen,&offsetBG);
				//drawing the lives
				if(lives==2){
					SDL_BlitSurface(bg,&sprt_lvs[0],screen,&sprt_lvs[0]);
					SDL_BlitSurface(sprt_lv,NULL,screen,&sprt_lvs[1]);
				}else if(lives==1){
					SDL_BlitSurface(bg,&sprt_lvs[0],screen,&sprt_lvs[0]);
					SDL_BlitSurface(bg,&sprt_lvs[1],screen,&sprt_lvs[1]);
				}
				
				SDL_BlitSurface(sprite,NULL,screen,&offsetSPR);
				SDL_BlitSurface(ball,NULL,screen,&offsetBALL);
				
				i=0;
				for(x=0;x<34;x++){
					if(i==4){
						i=0;
					}
					SDL_BlitSurface(brick[i],NULL,screen,&offsetBRICK[x]);
					i=i+1;					
				}
	
				SDL_Flip(screen);
				lost = false;
		}
		while(SDL_PollEvent(&event)){
			if(event.type==SDL_QUIT){
				quit = true;
			}
			if(event.type==SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:quit = true;break;
					case SDLK_RIGHT: xVelSPR++;break;
					case SDLK_LEFT: xVelSPR-- ;break;
				}
			}
			else if(event.type==SDL_KEYUP){
				switch(event.key.keysym.sym){
					case SDLK_RIGHT: xVelSPR--;break;
					case SDLK_LEFT: xVelSPR++;break;
				}
			}
		}
				
		SDL_BlitSurface(bg,&offsetSPR,screen,&offsetSPR);
		SDL_BlitSurface(bg,&offsetBALL,screen,&offsetBALL);
		Ytmp = offsetBALL.y - yVelBALL;
		Xtmp = offsetBALL.x - xVelBALL;
		offsetSPR.x = offsetSPR.x + xVelSPR;
		if(offsetSPR.x + 100>=542){
			offsetSPR.x = offsetSPR.x -xVelSPR;
		}
		//Ball Movement and Collitions
		if(start==true){
			xVelBALL = -1;
			yVelBALL = -1;
			start=false;
		}
		//Ball collision with the upper wall
		if(offsetBALL.y==0 ){
			if((xVelBALL==1) && (yVelBALL==-1)){
				xVelBALL = 1;
				yVelBALL = 1;
			}else if((xVelBALL == -1) && (yVelBALL == -1)){
				xVelBALL = -1;
				yVelBALL = 1;	
			}
		}
		//Ball Collision with left wall
		if(offsetBALL.x==0){
			if((xVelBALL ==-1) && (yVelBALL==-1)){
				xVelBALL = 1;
				yVelBALL = -1;
			}else if((xVelBALL == -1) && (yVelBALL == 1)){
				xVelBALL = 1;
				yVelBALL = 1;
			}
		}
		//Ball Collision with right wall		
		if(offsetBALL.x==482){
			if((xVelBALL == 1) && (yVelBALL == -1)){
				xVelBALL = -1;
				yVelBALL = -1;
			}else if((xVelBALL == 1) && (yVelBALL == 1)){
				xVelBALL = -1;
				yVelBALL = 1;
			}
		}
		dirc=collide(offsetBALL.x,offsetBALL.y,offsetBALL.w,offsetBALL.h,offsetSPR.x,offsetSPR.y,offsetSPR.w,offsetSPR.h);
		for(x=0;x<34;x++){
			if(brickVis[x] == true){
				if(dirc==0){
					dirc=collide(offsetBALL.x,offsetBALL.y,offsetBALL.w,offsetBALL.h,offsetBRICK[x].x,offsetBRICK[x].y,offsetBRICK[x].w,offsetBRICK[x].h);
					if(dirc!=0){
						SDL_BlitSurface(bg,&offsetBRICK[x],screen,&offsetBRICK[x]);
						score = score + 100;
						nxtLvl = nxtLvl + 1;
						brickVis[x] = false;
					}
				}
			}
		}
	
		switch(dirc){
			case 1:
				if((xVelBALL == -1) && (yVelBALL == -1)){
					xVelBALL = -1;
					yVelBALL =  1;
				}
				else{
					xVelBALL = 1;
					yVelBALL = 1;
				}
				break;
			case -1:
				if((xVelBALL ==-1) && (yVelBALL == -1)){
					xVelBALL = -1;
					yVelBALL =  1;
				}
				else{
					xVelBALL = 1;
					yVelBALL = 1;
				}
				break;
			case 2:
				if((xVelBALL == 1) && (yVelBALL ==1)){
					xVelBALL = -1;
					yVelBALL = 1;
				}
					else{
					xVelBALL = -1;
					yVelBALL = -1;
				}
				break;
			case -2:
				if((xVelBALL == -1) && (yVelBALL == 1)){
					xVelBALL = 1;
					yVelBALL = 1;
				}
				else{
					xVelBALL = 1;
					yVelBALL = -1;
				}
			case 3:
				if((xVelBALL == -1) && (yVelBALL == 1)){
					xVelBALL = -1;
					yVelBALL = -1;
				}
				else{
					xVelBALL =  1;
					yVelBALL = -1;
				}
				break;
			case -3:
				if((xVelBALL ==-1) && (yVelBALL ==1)){
					xVelBALL = -1;
					yVelBALL = -1;
				}
				else{
					xVelBALL =  1;
					yVelBALL = -1;
				}
				break;
			case 0:
				break;
			
		}	
		offsetBALL.x+=xVelBALL;
		offsetBALL.y+=yVelBALL;
		SDL_BlitSurface(ball,NULL,screen,&offsetBALL);	
		SDL_BlitSurface(sprite,NULL,screen,&offsetSPR);
		SDL_Flip(screen);
		//when you lose the ball
		if(offsetBALL.y == 480){
			if(lives != 1){
				lose=IMG_Load("./images/lose.png");
				SDL_BlitSurface(lose,NULL,screen,&offsetBG);
				SDL_Flip(screen);
				delay();
			}	
			lost = true;
			lives = lives -1;
			//quit = true;
		
			
		}
		if(lives == 0){
			SDL_BlitSurface(gameover,NULL,screen,&offsetBG);
			SDL_Flip(screen);
			delay();
			quit = true;
		}		
	}
	
}
	
	
