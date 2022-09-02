#include<allegro.h>
#include<stdio.h>
#include<stdlib.h>
#define maxfilas 30
#define maxcolumnas 20
BITMAP *buffer;
BITMAP *bufbmp;
BITMAP *ladrillo;
BITMAP  *escalera;
BITMAP *burbuja;
BITMAP *burbujabmp;

BITMAP *persobmp;
BITMAP *perso;
BITMAP *disparobmp;
BITMAP *dispa;
BITMAP *trampabmp;

int fil,col,i,j,z;	
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


typedef struct {

int direccion=1;
int posx;
int posy;
	
}burbujas;


personaje JJ;
personaje BA;
burbujas  BU[5];


	
	
void cargarmapaarchivo(){


FILE * mapa = fopen ("mapa.txt" , "r");
if(mapa==NULL){
	printf("error al abrir el archivo");
	return;
	
}

i=0;
j=0;
z=0;

while(!feof (mapa) ){
 		 
		 leido = fgetc(mapa);
		 if(leido=='b'){
		 BU[z].posx=i*30;
		 BU[z].posy=j*30;
		 z++;
		 printf("el valor de z es :%d",z);
		  }
		 
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

	
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT,900,570,0,0);
	


	buffer = create_bitmap(900,570);
	ladrillo = load_bitmap("IMG/ladrillo.bmp",NULL);
	escalera = load_bitmap("IMG/escalera.bmp",NULL);
	persobmp= load_bitmap("IMG/personajes.bmp",NULL);
	bufbmp= load_bitmap("IMG/fondo.bmp",NULL);
	disparobmp= load_bitmap("IMG/disparo2.bmp",NULL);
	dispa = create_bitmap(30,30);
	perso = create_bitmap(30,30);
	burbuja = create_bitmap(30,30);
	burbujabmp= load_bitmap("IMG/burbuja.bmp",NULL);
	trampabmp= load_bitmap("IMG/trampa.bmp",NULL);
	
	 cargarmapaarchivo();
BA.posx=50*25;
BA.posy=51*10;
//BU.direccion=1;
//BU.posx=30*10;
//BU.posy=30*10;
 int vidas=5;
	
	while(!key[KEY_ESC]&&vidas!=0){
			if(key[KEY_RIGHT]) direccion = 0;
				else if(key[KEY_LEFT]) direccion = 1;
		 		else if(key[KEY_SPACE]){
		 		 BA.posx=JJ.posx;
		 		 BA.posy=JJ.posy-30;
				  direccion = 2;		
				// mapa[JJ.posx][JJ.posy-30]='a';
				 } 	
		 		else if(key[KEY_UP]) direccion = 3;
		 		else if(key[KEY_DOWN]) direccion = 4;
		 	
		 	
		 	if(direccion==1&&key[KEY_LEFT]){
			 if(mapa1[(JJ.posx/30)-1][JJ.posy/30] == 'x')
			  direccion = 6;
			  else JJ.posx -= 30  ;
			  }
			  printf(" pos de x %d",JJ.posx);
			  
			if(direccion==0&&key[KEY_RIGHT]){
			if(mapa1[(JJ.posx/30)+1][JJ.posy/30] == 'x')
			  direccion = 6;
			 else JJ.posx += 30  ;
			 }
			 
			 if(direccion==3&&key[KEY_UP]&&mapa1[JJ.posx/30][JJ.posy/30]=='e'){
			 if(mapa1[JJ.posx][JJ.posy-30/30] == 'e')
			  direccion = 6;
			  else JJ.posy -= 30  ;
			  }
			  
			  if(direccion==4&&key[KEY_DOWN]&&mapa1[JJ.posx/30][(JJ.posy/30)+1]=='e'){
			 if(mapa1[JJ.posx/30][JJ.posy+30/30] == 'x')
			  direccion = 6;
			  else JJ.posy += 30  ;
			  }
			  
			  if(mapa1[JJ.posx/30][JJ.posy/30]=='o'&& mapa1[JJ.posx/30][(JJ.posy/30)+1]=='o'){
			  JJ.posy = JJ.posy+30;
			  }
			  printf(" pos de x %d",JJ.posx);
			 
			if(BA.posy+30!='x'){
				BA.posy+30;
			}
			else if(BA.posy+30=='x'){
			}
			
			if(BA.posy/30 == BU[z].posy/30 && BA.posx/30 == BU[z].posx/30){
		
				BA.posx=30*30;
				BU[z].posy=30*30;
				}	
			 if(mapa1[JJ.posx/30][(JJ.posy/30)]=='t'&&key[KEY_RIGHT]){
			  JJ.posx = JJ.posx-60;
			  vidas=vidas-1;
			  }	
 			if(mapa1[JJ.posx/30][(JJ.posy/30)]=='t'&&key[KEY_LEFT]){
			  JJ.posx = JJ.posx+60;
			  vidas=vidas-1;
			  }	
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
				
		if (mapa1[i][j] == 'e'){
				draw_sprite(buffer,escalera,i*30,j*30);
							}
							
		if (mapa1[i][j] == 't'){
				draw_sprite(buffer,trampabmp,i*30,j*30);
							}	
		}
		
	}
}

void pantalla(){
blit(buffer,screen,0,0,0,0,900,570);}

void dibujarpersonaje(){
	
	blit(persobmp,perso,direccion*30,0,0,0,30,32);

	draw_sprite(buffer,perso,JJ.posx,JJ.posy);
}

void dibujarbala(){

BA.posy=BA.posy-30;

if(mapa1[BA.posx/30][BA.posy/30] == 'x')
BA.posx=30*30;

	blit(disparobmp,dispa,direccion*30,0,0,0,30,32);
	draw_sprite(buffer,dispa,BA.posx,BA.posy);
}

void dibujarburbuja(){
for(z=0,z<5,z++;){

	if(BU[z].direccion==1){
	
	if(mapa1[(BU[z].posx/30)+1][BU[z].posy/30]=='x')
	BU[z].direccion=2;
	else BU[z].posx=BU[z].posx+30;
	}
	
	if(BU[z].direccion==2){
	
	if(mapa1[(BU[z].posx/30)-1][BU[z].posy/30]=='x')
	BU[z].direccion=1;
	else BU[z].posx=BU[z].posx-30;
	}

		blit(burbujabmp,burbuja,0,0,0,0,30,32);
	draw_sprite(buffer,burbuja,BU[z].posx,BU[z].posy);
	}	

}
