#include "Mundo.h"
#include "glut.h"
#include "Interaccion.h"
#include "Barra.h"
#include"Ladrillos.h"
#include"ListaLadrillos.h"
#include"Esfera.h"

void Mundo::Dibuja()
{
	int c=0;
	char nombre[] = "ARKANOID";

	gluLookAt(50.0,50.0,65.0,
			50.0,50.0,0.0,
			0.0,1.0,0.0);
		
		//METER EN UNA CLASE - BACKGROUND 
	
	glDisable(GL_LIGHTING);
	/*
	glColor3ub(0,0,200);
	glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(100, 0);
		glVertex2f(100, 100);
        glVertex2f(0, 100);
    glEnd();
	*/

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
//	esfera.Dibuja();
	disparos.dibuja();
	bordes.Dibuja();
	deslizante.Dibuja();
//	amarillo1.Dibuja();
	player.vidas(player.vida);
	if(player.gameover = true)
		gameover();
	glEnable(GL_LIGHTING);
}

void Mundo::Mover()
{
	disparos.mueve(0.025f);
//	esfera.Mover(0.025f);
	deslizante.Mover(0.025f);
	Interaccion::rebote(disparos, bordes);
	Interaccion::rebote(deslizante, bordes);
	Interaccion::rebote(disparos, deslizante);
	Interaccion::rebote(disparos, ladrillos);

	for(int i=0;i<disparos.numero;i++){				////EL PROBLEMA DE QUE NO SE ROMPAN LOS LADRILLOS EST� AQU� EN LOS �NDICES 
		for(int j=0;j<ladrillos.numero;j++){		////hAY QUE REVISARLO PUES
			if(Interaccion::rebote(*disparos[i], *ladrillos[j]))	ladrillos.eliminar(j);
		}
	}
for(int j=0;j<disparos.numero;j++){
	if(Interaccion::rebote(*disparos[j], bordes.suelo) == true)
	{
		disparos.destruirContenido();
		player.vida-=1;
	}
//	if(player.vida=='0')
//		player.gameover = true;

}
}

void Mundo::Inicializa()
{
/*
	esfera.SetColor(0,255,0);
	esfera.SetPos(50.0f,5.0f);
	esfera.SetRadio(1.0f);
	esfera.setVel(0.0f,40.0f);
*/

	deslizante.SetColor(255,0,0);
	deslizante.SetPos(45.0f,2.0f,55.0f,1.0f);	//Unico, cambio setpos de x e y , no limites
	
	Ladrillos *l1=new Ladrillos(55.0f,5.0f,65.0f,2.0f);
	l1->SetColor(0,0,255);
	ladrillos.agregar(l1); 

	Ladrillos *l2=new Ladrillos(25.0f,9.0f,35.0f,6.0f);
	l2->SetColor(0,255,0);
	ladrillos.agregar(l2); 

	Ladrillos *l3=new Ladrillos(5.0f,16.0f,15.0f,13.0f);
	l3->SetColor(255,0,0);
	ladrillos.agregar(l3); 
/*
	amarillo1.SetColor(0,255,0);
	amarillo1.SetPos(45.0f,7.0f,55.0f,5.0);
*/

	player.vida = '3';
	player.gameover = false;

	fin.SetPos(10.0f,10.0f,90.0f,90.0f);
	fin.SetColor(0,0,255);
}

void Mundo::teclaEspecial(unsigned char key) 
{ 
		switch(key) 
		{  
			case GLUT_KEY_LEFT: 
				deslizante.setVel (-25.0f, 0.0f);
					break;  
			case GLUT_KEY_RIGHT:  
				deslizante.setVel (25.0f, 0.0f);  
					break;	
		}
} 

void Mundo::teclaEspecial2(unsigned char key)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		deslizante.setVel (0,0);
			break;
	case GLUT_KEY_RIGHT:
		deslizante.setVel (0,0);
			break;
	}
}

void Mundo::gameover()
{
//	fin.Dibuja();
}

void Mundo::tecla(unsigned char key)
{
		switch(key)
	{
		case ' ':
			{
 				Esfera* d=new Esfera();
				Vector2D pos=deslizante.GetPos();
				d->SetPos(pos.x,pos.y);
				disparos.agregar(d);

				break;
			}
		case 'r': Inicializa();
					break;
	}

}