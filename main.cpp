#include<allegro.h>
#include<stdio.h>
#include<stdlib.h>
#define maxfilas 30
#define maxcolumnas 20
#define maxburbujas 2
#define maxniveles 3
#define maxrank 5

BITMAP *buffer;
BITMAP *bufbmp;
BITMAP *ladrillo;
BITMAP  *escalera;
BITMAP *burbuja;
BITMAP *burbujabmp;

int fil,col,i,j,z;	
int direccion=0;
//	int nivel=0;
//	int impacto=0;
int puntaje = 0;
int vidas=5;
int bandera = 1;
	
BITMAP *persobmp;
BITMAP *perso;
BITMAP *disparobmp;
BITMAP *dispa;
BITMAP *trampabmp;

void cargarmapaarchivo(int nivel);
void dibujarpersonaje();
void dibujamapa();
void pantalla();
void dibujarbala();
void dibujarburbuja();
void general();
void colision(int nivel);
void imprank();
int verificacambionivel(int nivel);

 
char leido;
char mapa1[maxfilas][maxcolumnas];

typedef struct
{

	int direccion;
	int posx;
	int posy;
		
}personaje;


typedef struct 
{

	int direccion;
	int posx;
	int posy;
	int activado;
	
}burbujas;

typedef struct {
	char nombre;
	int puntos;
}ranking;

personaje JJ; /*={1,30*10,51*10};*/
personaje BA;
burbujas  BU[maxburbujas];
ranking RK[maxrank];

int main()
{

	int opcion=0;
    int nivel=2;
	
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT,900,570,0,0);
	
	if(install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL)!=0){
		allegro_message("error: iniciando el sonido \n \n",allegro_error);
		return 1;
	}
	set_volume(70,70);
	
	MIDI *musica = load_midi("IMG/musicafondo.mid");
	MIDI *musica2 = load_midi("IMG/river.mid");
	MIDI *musicamenu = load_midi("IMG/musicamenu.mid");
	SAMPLE *shot = load_wav("IMG/diparo.wav");
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
	BITMAP  *menu =  load_bitmap("IMG/menu.bmp",NULL);
	
	while(opcion!=3)
	{
		
		opcion = 0;
		vidas = 5;
		puntaje = 0;
		nivel = 2;
		play_midi(musicamenu,1);
		
		while(opcion==0)
		{
			blit(menu,buffer,0,0,0,0,900,570);
			blit(buffer,screen,0,0,0,0,900,570);
		
			if(key[KEY_1]) 
				opcion = 1;
		
			if(key[KEY_2]) 
				opcion = 2;
		
			if(key[KEY_3]) 
				opcion = 3;
		}
	
		if(opcion==2)
		{
			imprank();
		}
	
		/* ACA DEBERIAS PONER UN WHILE GENERAL PARA EJECUTAR LOS NIVELES*/
		while(nivel<maxniveles&&opcion==1)
		{
		
		 	BA.posx=50*25;
		 	BA.posy=51*10;
		 	cargarmapaarchivo(nivel); /* deberias llamar a cargamapaarchivo con el parametro nivel*/
		 
		 	play_midi(musica,1);
			int bandera=1;
			
			while(!key[KEY_ESC]&&vidas!=0&&nivel<maxniveles) // pasar el && opcion al while con max niveles
			{
			
				general();
				colision(2);
			
				if (verificacambionivel(nivel)==1)
				{
					nivel++;
					if(nivel<maxniveles)
						cargarmapaarchivo(nivel);
				}  
			 // printf("nivel es %d", nivel);
		    }
		 	opcion = 0;		
			printf("\nnivel:%d opcion:%d\n",nivel,opcion);	
			
		}
		
	}
	allegro_exit();
	
	
	return 0;
}

END_OF_MAIN();	


void general(){

	if(key[KEY_RIGHT]) 
		direccion = 0;
	else if(key[KEY_LEFT]) 
		direccion = 1;
		
 	else if(key[KEY_SPACE ] && bandera==1)
	{
 		BA.posx=JJ.posx;
 		BA.posy=JJ.posy;
 		bandera = 0;
 		printf("bandera :%d\n",bandera);
		direccion = 2;	
		  
		// mapa[JJ.posx][JJ.posy-30]='a';
	}
 	else if(key[KEY_UP]) 
		direccion = 3;
 	else if(key[KEY_DOWN])
	 	direccion = 4;
 	
 	if(direccion==1&&key[KEY_LEFT])
	  {
		if(mapa1[(JJ.posx/30)-1][JJ.posy/30] == 'x')
	  		direccion = 6;
	  
	  	else JJ.posx -= 30;
	  }
	  
	if(direccion==0&&key[KEY_RIGHT]){
		if(mapa1[(JJ.posx/30)+1][JJ.posy/30] == 'x')
		  	direccion = 6;
		else JJ.posx += 30;
	 }
	 
	 if(direccion==3&&key[KEY_UP]&&mapa1[JJ.posx/30][JJ.posy/30]=='e')
	 {
		if(mapa1[JJ.posx][JJ.posy-30/30] == 'e')
		  	direccion = 6;
		else JJ.posy -= 30;
	  }
	  
	  if(direccion==4&&key[KEY_DOWN]&&mapa1[JJ.posx/30][(JJ.posy/30)+1]=='e')
	  {
	   	if(mapa1[JJ.posx/30][JJ.posy+30/30] == 'x')
		 	 direccion = 6;
		 else JJ.posy += 30;
	  }
	  
	if(mapa1[JJ.posx/30][JJ.posy/30]=='o'&& mapa1[JJ.posx/30][(JJ.posy/30)+1]=='o')
	{
		JJ.posy = JJ.posy+30;
	}

	if(BA.posy+30!='x')
	{
		BA.posy+30;
	}
	else if(BA.posy+30=='x'){
	}
	
	if(mapa1[JJ.posx/30][(JJ.posy/30)+1]=='t')
	{
		JJ.posx = JJ.posx-60;
		vidas=vidas-1;
	}	
		
	if(mapa1[JJ.posx/30][(JJ.posy/30)]=='t'&&key[KEY_RIGHT])
	{
		JJ.posx = JJ.posx-60;
		vidas=vidas-1;
	}	
	if(mapa1[JJ.posx/30][(JJ.posy/30)]=='t'&&key[KEY_LEFT])
	 {
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

void dibujamapa(){
	
	blit(bufbmp,buffer,0,0,0,0,30,32);
	draw_sprite(buffer,bufbmp,0,0);
	
	for(i=0;i<maxfilas;i++){
		for(j=0;j<maxcolumnas;j++){
			
		//	textout(screen,font,"hola mundo",100,100,-1);
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
		textprintf_ex(buffer,font,10,10,0xff0000,0x808080,"VIDAS : %d", vidas);
		textprintf_ex(buffer,font,10,30,0xff0000,0x808080,"PUNTAJE : %d", puntaje);
	}
}

void pantalla()
{
	blit(buffer,screen,0,0,0,0,900,570);
}

void dibujarpersonaje()
{
	blit(persobmp,perso,direccion*30,0,0,0,30,32);
	draw_sprite(buffer,perso,JJ.posx,JJ.posy);
}

void dibujarbala()
{
	BA.posy=BA.posy-30;
	
	if(mapa1[BA.posx/30][BA.posy/30] == 'x'){
		BA.posx=30*30;
		bandera =1;
	}
	blit(disparobmp,dispa,direccion*30,0,0,0,30,32);
	draw_sprite(buffer,dispa,BA.posx,BA.posy);
}

void dibujarburbuja()
{
	
	for(z=0;z<maxburbujas;z++){
	
		if(BU[z].direccion==1){
		
			if (mapa1[(BU[z].posx/30)+1][BU[z].posy/30]=='x')
			   BU[z].direccion=2;
			else BU[z].posx=BU[z].posx+30;
		}
		
		if (BU[z].direccion==2){
		
		   if (mapa1[(BU[z].posx/30)-1][BU[z].posy/30]=='x')
		      BU[z].direccion=1;
		   else 
		      BU[z].posx=BU[z].posx-30;
		}
	
		blit(burbujabmp,burbuja,0,0,0,0,30,32);
		draw_sprite(buffer,burbuja,BU[z].posx,BU[z].posy);
	}
}


void cargarmapaarchivo(int nivel)
{
 
FILE * mapa;

	if (nivel==0)
	  mapa = fopen ("mapa.txt" , "r");
	else if (nivel==1)
	     mapa = fopen ("mapa2.txt" , "r");
	else if (nivel==2)
		mapa = fopen ("mapa3.txt" , "r");
	  
	if(mapa==NULL){
	  printf("error al abrir el archivo");
	  return;
	}

	i=0;
	j=0;
	z=0;

	while(!feof (mapa) )
	{
	 		 
		leido = fgetc(mapa);
		if(leido=='b'){
			BU[z].posx=i*30;
			BU[z].posy=j*30;
			BU[z].direccion=1;
			BU[z].activado=0;
			z++;
		}
		  
		if(leido=='p')
		{
			JJ.posx=i*30;
			JJ.posy=j*30;
		}
		 
		if(leido=='\n')
		{
		   i++;
		   j=0;
		}
		else
		{
			mapa1[i][j]=leido;
			j++;
		}
	
	}
 
	fclose;
}
	
int verificacambionivel(int nivel)
{
	int impacto=0;
	int z=0;
//	printf("el nivel es %d", nivel);

	for(z=0;z<maxburbujas;z++)
        if (BU[z].activado==1){
	   		impacto++;
        	printf("%d, impacto: %d",z,impacto);
        } 
   
	if (impacto==maxburbujas){
	   return 1;				  
	}
	else
	return 0;
}

void colision(int nivel)
{
	int z;
	for(z=0;z<maxburbujas;z++)
	{
		if(BA.posy/30 == BU[z].posy/30 && BA.posx/30 == BU[z].posx/30)
		{
			puntaje = puntaje + 100 * vidas;
			printf(" puntaje %d",puntaje);
			BA.posx=30*30;
			bandera = 1;
			BU[z].posy=30*30;
		//	printf("el nivel es [%d - %d]", nivel);
			BU[z].activado=1;
		}
		
	}
}

void imprank()
{
	
	FILE* franking = fopen("ranking.txt","r");
	int i;
	
	for(i=0; i <maxrank; i++)
	{
		fscanf(franking, "%s", RK[i].nombre);
		fscanf(franking, "%d", &RK[i].puntos);
	}
	fclose(franking);
	
	for(i=0; i <maxrank; i++)
	{
		printf( "%s", RK[i].nombre);
		printf("	%d/n", &RK[i].puntos);
	}
	
}

