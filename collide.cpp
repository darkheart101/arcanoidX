#include<SDL/SDL.h>



int collide(int ax,int ay,int aw,int ah,int bx,int by,int bw,int bh){
	//At first we have the collision when a is over b
	//           *---*
	//	     | a |
	//	     *---*
	//           *---*
	//           | b |
	//           *---*
	if(((ay + ah) == by) && ((ax +aw) >= bx ) && ((ax + aw) <= (bx + bw))){
		if((ax + aw)>bx + (bw/2)){
			return 3;//It returns 1 when a hits the first half of bw
		}
		else 
			return -3;//It returns -1 when a hits the other half of bw
	}
	else if(((ay + ah) == by) && (ax>= bx) && (ax <= bx + bw)){
		if((ax+aw)>bx + (bw/2)){
			return 3;
		}
		else
			return -3;
	}
	//when b is over a
	//    *---*
	//    | b |
	//    *---*
	//    *---*
	//    | a |
	//    *---*
	else if((ay == (by + bh)) && ((ax + aw) > bx) && ((ax + aw)<(bx + bw))){
		if((ax + aw)>(bx + (bw/2))){
			return 1;
		}
		else
			return -1;				 
	}
	else if((ay==(by+bh)) && (ax >= bx) && (ax<=(bx+bw))){
		if((ax+aw>(bx+bw/2))){
			return 1;
		}
		else
			return -1;
	}
	// when a is left of b
	//  *---* *---*
	//  | a | | b |
	//  *---* *---* 
	else if((ay <= (by + bh))  && ((ax + aw)== bx) && ((ay + ah)>by)){
			return 2;
	}

	//when a is right of b
	// *---* *---*
	// | b | | a |
	// *---* *---*
	else if((ay <= (by+bh))  &&(ax == (bx+bw)) && ((ay +ah) > by)){
			return -2;
	}
	else
		return 0;
}



