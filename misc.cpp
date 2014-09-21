#include<stdio.h>
#include<stdlib.h>


extern int nxtLvl;

bool nxtLevel(int brck){
	if(nxtLvl==brck){
		return true;
	}else return false;
}

void delay(void){
	for(int i = 0; i<100000;i++){
				for(int j = 0; j<8899;j++){
				}
			}
}


int Load(char arg[],int line){
	FILE *fhandler;
	int x,buff[3],count=0,sum=0,lincnt=1;	

	fhandler = fopen(arg,"r");
	if(fhandler==NULL)
		printf("File Not Found\n");
	while((x=fgetc(fhandler))!=EOF){
		count=0;	
		while(x!=10){
			switch(x){
				case 48:x=0;break;
				case 49:x=1;break;
				case 50:x=2;break;
				case 51:x=3;break;
				case 52:x=4;break;
				case 53:x=5;break;
				case 54:x=6;break;
				case 55:x=7;break;
				case 56:x=8;break;
				case 57:x=9;break;
			}

			buff[count]=x;
			count++;
			x=fgetc(fhandler);
		}
		if(lincnt==line){
			if(count==1){
				sum = buff[0];
			}else if(count==2){
				buff[0]=buff[0]*10;
				sum=buff[0]+buff[1];
			}
			else if(count==3){
				buff[0]=buff[0]*100;
				buff[1]=buff[1]*10;
				sum=buff[0]+buff[1]+buff[2];
			}				
		}
		lincnt++;
				
	}
	fclose(fhandler);
	return sum;
}

