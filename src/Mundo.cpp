#include "Mundo.h"
#include<iostream>
#include <stdlib.h>
#include<time.h>
#include "glut.h"
#include "Interaccion.h"
#include "Barra.h"
#include"Ladrillos.h"
#include"ListaLadrillos.h"
#include"Esfera.h"
#include "Bonus.h"
#include"BonusBarra.h"
#include"BonusVida.h"
#include"BonusDisparo.h"
#include"Bonuses.h"
#include"ListaLadrillos.h"
#include"LadrillosBonus.h"
#include <fstream>
#define MAX 30

using namespace std;
using namespace ETSIDI;


void Mundo::Dibuja()

{
	int c=0;
	char nombre[] = "ARKANOID";


	gluLookAt(50.0,50.0,65.0,
			50.0,50.0,0.0,
			0.0,1.0,0.0);
		
		//METER EN UNA CLASE - BACKGROUND 
	
	glDisable(GL_LIGHTING);

	//Nombre Juego ARKANOID
	glColor3ub(255,255,255);
	for(int i=0;nombre[i]!='\0';i++)
	{
	glRasterPos3i(30+c,100,1);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,nombre[i]);
	c+=5;
	}

	//Dibujar
	ladrillos.dibuja();
	disparos.dibuja();
	bordes.dibuja();
	deslizante.dibuja();
	bonuses.dibuja();

	player.vidas(player.vida);
}

void Mundo::Mover()
{
	bonuses.mueve(0.25f);
	disparos.mueve(0.025f);
	deslizante.Mover(0.025f);
	Interaccion::rebote(disparos, bordes);
	Interaccion::rebote(deslizante, bordes);
	Interaccion::rebote(disparos, deslizante);
	for(int j=0;j<disparos.numero;j++){
	if(Interaccion::rebote(*disparos[j], bordes.getSuelo()) == true)
	{
		disparos.destruirDisparo(j);
		if(player.vida>0)player.vida-=1;
	}

	if(player.vida==0)
		player.gameover=true;
}
	bool k=false;
	if((num=Interaccion::rebote(disparos,ladrillos,k))!=-1)
	{
		if(k==true){
		srand(time(NULL));
		int i=rand()%3;
		Bonus *b1;
		switch (i){
		case 0:	b1=new BonusVida(); break;
		case 1: b1=new BonusDisparo(); break;	
		case 2: b1=new BonusBarra(); break;
		default: break;
	}
//		Bonus *b1=new Bonus();
		b1->SetPos(disparos[num]->posicion.x, disparos[num]->posicion.y);
		bonuses.agregar(b1); 
		}
	}
	for(int i=0;i<bonuses.numero;i++){
		if((Interaccion::rebote(*bonuses[i],deslizante,player,bonuses[i]->getTipo(), disparos) == true)||(Interaccion::rebote(*bonuses[i],bordes.getSuelo())==true))		//FUNCIONES PARA DESTRUIR O RECOGER BONUS
			bonuses.destruirBonus(i);																																	
	}	
	if(nivel==3)end=true;
	if((ladrillos.getNumero()==0)&&(end==false)){
		nivel++;
		if(nivel<3)Inicializa();
	}
}

void Mundo::Inicializa()
{

	ladrillos.inicializa(nivel); 
	disparos.inicializa();
	bonuses.inicializa();
	player.vida=3;
	player.gameover=false;
	end=false;

	deslizante.SetColor(255,150,0);
	deslizante.SetPos(45.0f,2.0f,55.0f,1.0f);	//Unico, cambio setpos de x e y , no limites
	deslizante.setVel(0.0f,0.0f);
}


void Mundo::teclaEspecial(unsigned char key) 
{ 
		switch(key) 
		{  
			case GLUT_KEY_LEFT: 
				deslizante.setVel (-30.0f, 0.0f);
					break;  
			case GLUT_KEY_RIGHT:  
				deslizante.setVel (30.0f, 0.0f);  
					break;	
		}
} 

void Mundo::teclaEspecial2(unsigned char key)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		deslizante.setVel (0.0f,0.0f);
			break;
	case GLUT_KEY_RIGHT:
		deslizante.setVel (0.0f,0.0f);
			break;
	}
}

void Mundo::tecla(unsigned char key)
{
		switch(key)
	{
		case ' ':
			{
 				Esfera* d=new Esfera();
				Vector pos=deslizante.GetPos();
				d->SetPos(pos.x + 1,pos.y + 1);
				disparos.agregar(d);

				break;
			}
		case 'r':
			pasaNivel();
			Inicializa();
			break;

	}
}
