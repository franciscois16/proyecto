#include<allegro.h>
#include<stdio.h>
#include<stdlib.h>
#define maxfilas 30
#define maxcolumnas 20
BITMAP *buffer;
BITMAP *bufbmp;
BITMAP *ladrillo;
BITMAP *burbuja;
BITMAP *burbujabmp;

BITMAP *persobmp;
BITMAP *perso;
BITMAP *disparobmp;
BITMAP *dispa;

int fil,col,i,j;	
int direccion=0;

char leido;
char mapa1[maxfilas][maxcolumnas];


void dibujarpersonaje();
void dibujamapa();
void pantalla();
void dibujarbala();
void dibujarburbuja();
//char leido[600];

/*
char mapa[maxfilas][maxcolumnas]{
"xxxxxxxxxxxxxxxxxxx",
"xxxx              x",
"xxx               x",
"xx                x",
"x                 x",		
"x                 x",
"x                 x",
"x                 x",
"x                 x",	
"x                 x",
"x                 x",		
"x       x         x",
"x       x         x",
"xx      x         x",
"xxx     x         x",
"xx      x         x",
"x       x         x",
"x       x         x",
"x                 x",
"x                 x",
"x                 x",		
"x                 x",		
"x                 x",		
"x                 x",		
"x                 x",							
"x                 x",		
"xx                x",
"xxx               x",
"xxxx              x",
"xxxxxxxxxxxxxxxxxxx",};
*/
typedef struct{

int direccion;
int posx=30*10;
int posy=51*10;
	
}personaje;


typedef struct{

int direccion=1;
int posx;
int posy;
	
}burbujas;


personaje JJ;
personaje BA;
burbujas BU;


	
	
void cargarmapaarchivo(){


FILE * mapa = fopen ("mapa.txt" , "r");
if(mapa==NULL){
	printf("error al abrir el archivo");
	return;
	
}

i=0;
j=0;

while(!feof (mapa) ){
 		 
		 leido = fgetc(mapa);
		 if(leido=='\n'){
		 i++;
		 j=0;
		  }
		else{
			mapa1[i][j]=leido;
			j++;
		}
	
 	
 }
	fclose;
}
	
	

	




main()
{

	
//	fclose(mapa);
	
	
	
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT,900,570,0,0);


	buffer = create_bitmap(900,570);
	ladrillo = load_bitmap("ladrillo.bmp",NULL);
	persobmp= load_bitmap("personajes.bmp",NULL);
	bufbmp= load_bitmap("fondo.bmp",NULL);
	disparobmp= load_bitmap("disparo2.bmp",NULL);
	dispa = create_bitmap(30,32);
	perso = create_bitmap(30,32);
	burbuja = create_bitmap(30,32);
	burbujabmp= load_bitmap("burbuja.bmp",NULL);
	
	 cargarmapaarchivo();
BA.posx=50*25;
BA.posy=51*10;
BU.direccion=1;
BU.posx=30*10;
BU.posy=30*10;
	
	while(!key[KEY_ESC]){
			if(key[KEY_RIGHT]) direccion = 0;
				else if(key[KEY_LEFT]) direccion = 1;
		 		else if(key[KEY_SPACE]){
		 		 BA.posx=JJ.posx;
		 		 BA.posy=JJ.posy-30;
				  direccion = 2;		
				// mapa[JJ.posx][JJ.posy-30]='a';
				 } 	
		 	
		 	
		 	
		 	if(direccion==1&&key[KEY_LEFT]){
			 if(mapa1[JJ.posx-30/30][JJ.posy/30] == 'x')
			  direccion = 4;
			  else JJ.posx -= 30  ;
			  }
			  printf(" pos de x %d",JJ.posx);
			  
			if(direccion==0&&key[KEY_RIGHT]){
			if(mapa1[(JJ.posx+30)/30][JJ.posy/30] == 'x')
			  direccion = 4;
			 else JJ.posx += 30  ;
			 }
			 
			if(BA.posy+30!='x'){
				BA.posy+30;
			}
			else if(BA.posy+30=='x')
 		
		 clear(buffer);		
		
		dibujamapa();
		dibujarpersonaje();
		dibujarbala();
		dibujarburbuja();
		pantalla();
		
rest(150);
}
	allegro_exit();
	
	
	
	
	return 0;
}

END_OF_MAIN();	




void dibujamapa(){
	
	blit(bufbmp,buffer,0,0,0,0,30,32);
	draw_sprite(buffer,bufbmp,0,0);
	
	for(i=0;i<maxfilas;i++){
		for(j=0;j<maxcolumnas;j++){
		if (mapa1[i][j] == 'x'){
				draw_sprite(buffer,ladrillo,i*30,j*30);
				}
				
			
		}
		
		
	}
}

void pantalla(){
blit(buffer,screen,0,0,0,0,900,570);}

void dibujarpersonaje(){
	
	blit(persobmp,perso,direccion*30,0,0,0,30,32);
	//	JJ.posx=30*10;
//	JJ.posy=30*10;
	draw_sprite(buffer,perso,JJ.posx,JJ.posy);
}

void dibujarbala(){

BA.posy=BA.posy-30;

if(mapa1[BA.posx/30][BA.posy/30] == 'x' )
BA.posx=30*30;


	blit(disparobmp,dispa,direccion*30,0,0,0,30,32);
	//	JJ.posx=30*10
	draw_sprite(buffer,dispa,BA.posx,BA.posy);
}

void dibujarburbuja(){
	
	
	
	if(mapa1[BU.posx/30][BU.posy/30]=='x')
	BU.direccion*-1;

	if(BU.direccion==1)
	BU.posx=BU.posx+30;
	else if(BU.direccion==-1)
	BU.posx=BU.posx-30;
	
		blit(burbujabmp,burbuja,0,0,0,0,30,32);
	//	JJ.posx=30*10
	draw_sprite(buffer,burbuja,BU.posx,BU.posy);
	
}




















	
	/*	blit(fondo,screen,0,0,0,0,720,480);
		rectfill(fondo,x1,y1,x2,y2,persod);
		
		switch(pos)
		{
			case 1:
				blit(persod,screen,x1,y1,x2,y2,30,32);
				rest(10); 
		
				break;
				
			case 2:
				blit(persoi,screen,x1,y1,x2,y2,30,32);
				rest(10); 
				
				break;
						
					
			
		}
			if(key[KEY_RIGHT])
		{
			
			x1+=6;
			x2+=6;
			pos=1;
		}
		
			if(key[KEY_LEFT])
		{
			
			x1-=6;
			x2-=6;
			pos=2;
		}
		
		rest(10);
	
	}
	while(!key[KEY_ESC]){
		clear_to_color(buffer,0xFF6400);
	
		blit(persod,screen,0,0,0,0,30,32);





		if(key[KEY_RIGHT])
		{
			x1+=6;
			x2+=6;
		}
		
		if(key[KEY_LEFT])
		{
			x1-=6;
			x2-=6;
		}
		rest(10);
		
	}
	*/
	
	
