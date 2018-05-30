#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"
#include <Windows.h>
#include <MMSystem.h>

//Solo para Visual Studio 2015
#if (_MSC_VER == 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

static GLuint ciudad_display_list;	//Display List for the Monito

/*********************keyframes******************/
////Variables de dibujo y manipulacion
float posX = 0, posY = 2.5, posZ = -3.5;
//globo terraqueo
float giroGloboTerraqueo = 0;


////velocidad
#define MAX_FRAMES 9
int i_max_steps = 90;
int i_curr_steps = 0;
////Variables para GUARDAR Key Frames
typedef struct _frame
{
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
}FRAME;

FRAME KeyFrame[MAX_FRAMES];

int FrameIndex = 5;			//introducir datos
bool play = false;
int playIndex = 0;//inicio de frames

				  ////Graba secuencia
int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

int mundo;
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;



CCamera objCamera;	//Create objet Camera
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 
int font = (int)GLUT_BITMAP_HELVETICA_18;

void saveFrame(void)
{
	printf("frameindex %d\n", FrameIndex);
	//guarda la posicion de la animacion
	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;
	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
}

void interpolation(void)
{		//diferencia de la pos f y la pos ini entre la velocidad
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
}


void Sonido() 
{
	PlaySound(TEXT("audio.wav"), NULL, SND_ASYNC);

}
void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex >1)
		{
			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;
	}
}

/*********************animacion*********************/
//float angRot = 0.0;
bool g_fanimacion = false;

/*********************iluminación******************/
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };					// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };					// Ambiental Light Values
GLfloat m_s1[] = { 18 };

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };					// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };					// Ambiental Light Values
GLfloat m_s2[] = { 22 };
/*********************Carga de texturas******************/
CTexture textCielo;
CTexture textPared;
CTexture textPasto;
CTexture textPiso;
CTexture textCobijaBuzz;
CTexture textCobijaPrincesa;
CTexture textCobija;
CTexture textCobija2;
CTexture textCama;
CTexture textBaul;
CTexture textBaulTapa;
CTexture textBuro;
CTexture textBuroCajones;
CTexture textCobre;
CTexture textGloboTer;
CTexture textMueble;
CTexture textEscritorio;
CTexture textEscritorioMadera;
CTexture textCuadro1;
CTexture textCuadro2;
CTexture textCuadro3;
CTexture textCuadro4;
CTexture textPuerta;
CTexture textManija;
CTexture textLadrillo;
CTexture textVentana;
CTexture textVentana2;
CTexture textPuerta2;
CTexture textTecho;
CTexture textLibro1;
CTexture textLibro2;
CTexture textLibro3;
CTexture textLibro4;
CTexture textLibro6;
CTexture textLibro7;
CTexture textLibro8;
CTexture textBarda;
CTexture textPiscina;
CTexture textPiscina2;
CTexture textEscalera;
CTexture textTransparente;
CTexture textVentanal;
CTexture textFachada;
CTexture textSilla;
CTexture textRefri;
CTexture textMetal;
CTexture textMaderaAlacena;
CTexture textAlacena1;
CTexture textAlacena2;
CTexture textHorno1;
CTexture textHorno2;
CTexture textMicrohondas;
CTexture textMaderaPared;
CTexture textAlfombra;
CTexture textPantalla;
CTexture textBocina;
CTexture textCuero;
CTexture textMaderaMesita;
CTexture textParedFina;
CTexture textAzulejo;
CTexture textPisoBaño;
CTexture textAzulejo2;
CTexture textPisoBaño2;
CTexture textParedNubes;
CTexture textParedRosa;
CTexture textParedCochera;
CTexture textPisoCochera;
CTexture textcarpa;
CTexture textmetal;
CTexture textred;
/*********************Carga de Figuras*******************/
CFiguras figSuelo;
CFiguras figPared;
CFiguras figCasa;
CFiguras figExterior;
CFiguras figCama;
CFiguras figBaul;
CFiguras figBuro;
CFiguras figGloboTer;
CFiguras figMueble;
CFiguras figEscritorio;
CFiguras figCuadro;
CFiguras figPuerta;
CFiguras figVentana;
CFiguras figLibro;
CFiguras figVentanal;
CFiguras figMesa;
CFiguras figSilla;
CFiguras figComedor;
CFiguras figSala;
CFiguras fig18;
CFiguras fig19;
/*********************Carga figuras 3D******************/

/*********************Objetos*********************/


void refri(void) {
	glPushMatrix();
		glPushMatrix();
			figComedor.prisma(18,6,10,textMetal.GLindex);
			glPushMatrix();
				glTranslatef(3,0,0);
				figComedor.prisma(18,0.1,10,textRefri.GLindex);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void alacena(void) {
	glPushMatrix();
		//base
		glPushMatrix();
		figComedor.prisma(6,3,25,textMaderaAlacena.GLindex);
			//alacena1
			glPushMatrix();
				glTranslatef(1.5,0,0);
				figComedor.prisma(6, 0.1, 5, textAlacena1.GLindex);
				//alacena2
				glPushMatrix();
					glTranslatef(0,0,5);
					figComedor.prisma(6, 0.1, 5, textAlacena1.GLindex);
				glPopMatrix();
				//alacena3
				glPushMatrix();
					glTranslatef(0,0,-5);
					figComedor.prisma(6, 0.1, 5, textAlacena1.GLindex);
				glPopMatrix();
				//alacena4
				glPushMatrix();
					glTranslatef(0,0,10);
					figComedor.prisma(6, 0.1, 5, textAlacena2.GLindex);
				glPopMatrix();
				//alacena5
				glPushMatrix();
					glTranslatef(0,0,-10);
					figComedor.prisma(6, 0.1, 5, textAlacena2.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void estufa(void) {
	glPushMatrix();
		//base
		glPushMatrix();
			figComedor.prisma(6, 4, 25, textMaderaAlacena.GLindex);
				//horno
				glPushMatrix();
					glTranslatef(2, 0, 0);
					figComedor.prisma(6,0.1,5,textHorno1.GLindex);
					glPushMatrix();
						glTranslatef(-2,3,0);
						figComedor.prisma(0.1,4,5,textHorno2.GLindex);
					glPopMatrix();
				glPopMatrix();
				//alacena1
				glPushMatrix();
					glTranslatef(2, 0, 5);
					figComedor.prisma(6,0.1,5,textAlacena1.GLindex);
				glPopMatrix();
				//alacena2
				glPushMatrix();
					glTranslatef(2, 0, 10);
					figComedor.prisma(6,0.1,5,textAlacena1.GLindex);
				glPopMatrix();
				//alacena3
				glPushMatrix();
					glTranslatef(2, 0, -5);
					figComedor.prisma(6,0.1,5,textAlacena1.GLindex);
				glPopMatrix();
				//alacena4
				glPushMatrix();
					glTranslatef(2, 0, -10);
					figComedor.prisma(6,0.1,5,textAlacena1.GLindex);
				glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void mesa(void) {
	glPushMatrix();
		//tabla	
		glPushMatrix();
			figMesa.prisma(0.5,10,25,textEscritorio.GLindex);
			glPushMatrix();
			glTranslatef(0,-7,0);
				figMesa.cilindro(0.4,7,10,textEscritorio.GLindex);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void silla(void) {
	glPushMatrix();
		//base
		glPushMatrix();
			figSilla.prisma(0.3,2,3,textSilla.GLindex);
			glTranslatef(0,-0.1,0);
			figSilla.prisma(0.1,2,3, textEscritorio.GLindex);
			//respaldo
			glPushMatrix();
				glTranslatef(-1.15,1.25,0);
				figSilla.prisma(3,0.3,3,textEscritorio.GLindex);
			glPopMatrix();
			//patas
			glPushMatrix();
			glTranslatef(-1.15,-6,1.25);
				figSilla.cilindro(0.1,5.75,10,textEscritorio.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-1.15,-6,-1.25);
				figSilla.cilindro(0.1,5.75,10,textEscritorio.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.75,-6,1.25);
				figSilla.cilindro(0.1,6,10,textEscritorio.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.75,-6,-1.25);
				figSilla.cilindro(0.1,6,10,textEscritorio.GLindex);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void baul(void) {
	glPushMatrix();
		glPushMatrix();
			figBaul.prisma(4,10,5,textBaul.GLindex);
			glPushMatrix();
				glTranslatef(4.9,2,0);
				glRotatef(90,0,0,1);
				figBaul.cilindro(2.5,9.8,20,textBaulTapa.GLindex);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();//////////////
}

void buro(void) {
	glPushMatrix();
		glPushMatrix();
			//principal
			figBuro.prisma(13,8,3,textBuro.GLindex);
			/////patas
			glPushMatrix();
				//pata1
				glTranslatef(-3.25,-7,-1);
				figBuro.prisma(1, 1.5, 1, textBuro.GLindex);
			glPopMatrix();
			glPushMatrix();
				//pata2
				glTranslatef(3.25,-7,-1);
				figBuro.prisma(1, 1.5, 1, textBuro.GLindex);
			glPopMatrix();
			glPushMatrix();
				//pata3
				glTranslatef(-3.25,-7,1);
				figBuro.prisma(1, 1.5, 1, textBuro.GLindex);
			glPopMatrix();
			glPushMatrix();
				//pata4
				glTranslatef(3.25,-7,1);
				figBuro.prisma(1, 1.5, 1, textBuro.GLindex);
			glPopMatrix();
			//molduras superior
			glPushMatrix();
				glTranslatef(0,6.5,0);
				figBuro.prisma(0.5, 9, 4, textBuroCajones.GLindex);
			glPopMatrix();
			//molduras inferior
			glPushMatrix();
				glTranslatef(0,-6.5,0);
				figBuro.prisma(0.25, 8.5, 3.5, textBuroCajones.GLindex);
			glPopMatrix();
			//cajon1
			glPushMatrix();
				glTranslatef(0,-5,1.5);
				figBuro.prisma(2, 6, 0.25, textBuroCajones.GLindex);
				//manijas
				glPushMatrix();
					glTranslatef(-2.25, 0, 0.5);
					figBuro.esfera(0.5,10,10,textBuro.GLindex);
					glPushMatrix();
						glTranslatef(4.5, 0, 0);
						figBuro.esfera(0.5, 10, 10, textBuro.GLindex);
					glPopMatrix();
				glPopMatrix();				
			glPopMatrix();
			//cajon2
			glPushMatrix();
				glTranslatef(0,-2,1.5);
				figBuro.prisma(2, 6, 0.25, textBuroCajones.GLindex);
				//manijas
				glPushMatrix();
					glTranslatef(-2.25, 0, 0.5);
					figBuro.esfera(0.5,10,10,textBuro.GLindex);
					glPushMatrix();
						glTranslatef(4.5, 0, 0);
						figBuro.esfera(0.5, 10, 10, textBuro.GLindex);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//cajon3
			glPushMatrix();
				glTranslatef(0,1,1.5);
				figBuro.prisma(2, 6, 0.25, textBuroCajones.GLindex);
				//manijas
				glPushMatrix();
					glTranslatef(-2.25, 0, 0.5);
					figBuro.esfera(0.5,10,10,textBuro.GLindex);
					glPushMatrix();
						glTranslatef(4.5, 0, 0);
						figBuro.esfera(0.5, 10, 10, textBuro.GLindex);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//cajon4
			glPushMatrix();
				glTranslatef(-1.6,4,1.5);
				figBuro.prisma(2, 2.75, 0.25, textBuroCajones.GLindex);
				glPushMatrix();
					glTranslatef(0, 0, 0.5);
					figBuro.esfera(0.5,10,10,textBuro.GLindex);
					
				glPopMatrix();
			glPopMatrix();
			//cajon5
			glPushMatrix();
				glTranslatef(1.6,4,1.5);
				figBuro.prisma(2, 2.75, 0.25, textBuroCajones.GLindex);
				glPushMatrix();
					glTranslatef(0, 0, 0.5);
					figBuro.esfera(0.5,10,10,textBuro.GLindex);
					
				glPopMatrix();
			glPopMatrix();

		glPopMatrix();

	
	glPopMatrix();///////////////////
}

void globoTerraqueo(void) {
	glPushMatrix();
		//base
		glPushMatrix();
			figGloboTer.cono(4,4,10,textCobre.GLindex);
			//barra
			glPushMatrix();
				glTranslatef(0,3,0);
				figGloboTer.cilindro(0.5,17,10,textCobre.GLindex);
				//globo
				glPushMatrix();
					glTranslatef(0, 9, 0);
					glRotatef(giroGloboTerraqueo,0,1,0);
					figGloboTer.esfera(7,20,20,textGloboTer.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();/////////////////
}

void librero(void) {
	glPushMatrix();
		//repisa 1
		glPushMatrix();
			figMueble.prisma(0.09,4,2.5,textMueble.GLindex);
			glPushMatrix();
				//pata 1
				glTranslatef(-1.9,-0.5,1.3);
				figMueble.cilindro(0.1,5,10,textMueble.GLindex);
			glPopMatrix();
			glPushMatrix();
				//pata 2
				glTranslatef(1.9,-0.5,-1.3);
				figMueble.cilindro(0.1,5,10,textMueble.GLindex);
			glPopMatrix();
			glPushMatrix();
				//pata 3
				glTranslatef(-1.9,-0.5,-1.3);
				figMueble.cilindro(0.1,5,10,textMueble.GLindex);
			glPopMatrix();
			glPushMatrix();
				//pata 1
				glTranslatef(1.9,-0.5,1.3);
				figMueble.cilindro(0.1,5,10,textMueble.GLindex);
			glPopMatrix();
			//repisa 2
			glPushMatrix();
				glTranslatef(0,1.5,0);
				figMueble.prisma(0.09, 4, 2.5, textMueble.GLindex);
			glPopMatrix();
			//repisa 3
			glPushMatrix();
				glTranslatef(0,2.75,0);
				figMueble.prisma(0.09, 4, 2.5, textMueble.GLindex);
				//libro 4
				glPushMatrix();
					glTranslatef(0, 0.2, 0);
					glRotatef(90,0,0,1);
					figMueble.prisma(1.4, 0.3, 0.8, textLibro4.GLindex);
				glPopMatrix();
			glPopMatrix();
			//repisa 4
			glPushMatrix();
				glTranslatef(0,4,0);
				figMueble.prisma(0.09, 4, 2.5, textMueble.GLindex);
				//libro 1
				glPushMatrix();
					glTranslatef(0, 0.7, 0);
					figMueble.prisma(1.4, 0.3, 0.8, textLibro3.GLindex);
				glPopMatrix();
				//libro 2
				glPushMatrix();
					glTranslatef(0.4, 0.7, 0);
					figMueble.prisma(1.4, 0.3, 0.8, textLibro2.GLindex);
				glPopMatrix();
				//libro 3
				glPushMatrix();
					glTranslatef(-0.4, 0.7, 0);
					figMueble.prisma(1.4, 0.3, 0.8, textLibro1.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();///////////
}

void escritorio(void) {
	glPushMatrix();
		glPushMatrix();
			//parte 1
			figEscritorio.prisma(1, 12, 5, textEscritorio.GLindex);
			//pata1
			glPushMatrix();
				glTranslatef(-5.8,-9.5,2.3);
				figEscritorio.cilindro(0.2,1,10,textEscritorio.GLindex);
			glPopMatrix();
			//pata2
			glPushMatrix();
				glTranslatef(-5.8,-9.5,-2.3);
				figEscritorio.cilindro(0.2,1,10,textEscritorio.GLindex);
			glPopMatrix();
			//pata3
			glPushMatrix();
				glTranslatef(-2.2,-9.5,2.3);
				figEscritorio.cilindro(0.2,1,10,textEscritorio.GLindex);
			glPopMatrix();
			//pata4
			glPushMatrix();
				glTranslatef(-2.2,-9.5,-2.3);
				figEscritorio.cilindro(0.2,1,10,textEscritorio.GLindex);
			glPopMatrix();
			//pata5
			glPushMatrix();
				glTranslatef(5.8,-9.55,2.3);
				figEscritorio.cilindro(0.2,9,10,textEscritorio.GLindex);
			glPopMatrix();
			//pata6
			glPushMatrix();
				glTranslatef(5.8,-9.55,-2.3);
				figEscritorio.cilindro(0.2,9,10,textEscritorio.GLindex);
			glPopMatrix();

			glPushMatrix();
				//parte 2
				glTranslatef(-4,-4.5,0);
				figEscritorio.prisma(8,4,5,textEscritorio.GLindex);
				//cajon1
				glPushMatrix();
					glTranslatef(0, 3.5, 2.5);
					figEscritorio.prisma(2,3,0.5,textEscritorio.GLindex);
					glPushMatrix();
					//cajon2
						glTranslatef(0, -4, 0);
						figEscritorio.prisma(5, 3, 0.5, textEscritorio.GLindex);
						//manija
						glPushMatrix();
							glTranslatef(0, 2, 0.4);
							figEscritorio.prisma(0.3, 1, 0.2, textEscritorio.GLindex);
						glPopMatrix();
						//manija 2
						glPushMatrix();
							glTranslatef(0, 3.45, 0.35);
							figEscritorio.prisma(0.3, 1, 0.2, textEscritorio.GLindex);
						glPopMatrix();
					glPopMatrix();
					
				glPopMatrix();
			glPopMatrix();
			//tabla trasera
			glPushMatrix();
				glTranslatef(2,-4.5,-2.35);
				figEscritorio.prisma(8, 8, 0.3, textEscritorio.GLindex);
			glPopMatrix();
			//tabla superior
			glPushMatrix();
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
				glTranslatef(0,0.5,0);
				figEscritorio.prisma(0.5, 14, 7, textEscritorioMadera.GLindex);
				//libro 6
				glPushMatrix();
					glTranslatef(-0.2, 0.8, 0);
					glRotatef(90, 0, 0, 1);
					figMueble.prisma(3, 0.8, 2, textLibro6.GLindex);
					//libro 7
					glPushMatrix();
						glTranslatef(1, 1.5, 0);
						glRotatef(60,1,0,0);
						figMueble.prisma(3, 0.8, 2, textLibro7.GLindex);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();
	glPopMatrix();///////////////
}

void sillon(void) {
	glPushMatrix();
		//base
		glPushMatrix();
			figSala.prisma(2,6,18, textCuero.GLindex);
			//respaldo
			glPushMatrix();
				glTranslatef(2.8,3.5,0);
				figSala.prisma(5,0.2,20, textCuero.GLindex);
			glPopMatrix();
			//laterales
			glPushMatrix();
				glTranslatef(0,1.5,-9.5);
				figSala.prisma(5,6,1, textCuero.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,1.5,9.5);
				figSala.prisma(5,6,1, textCuero.GLindex);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void mesita(void) {
	glPushMatrix();
		glPushMatrix();
			figSala.prisma(4,3.5,3.5, textMaderaMesita.GLindex);
			glPushMatrix();
				glTranslatef(0,2,0);
				figSala.prisma(0.2,10,10,textMaderaMesita.GLindex);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void puerta(void) {
	glPushMatrix();
		glPushMatrix();
			//centro
			figPuerta.prisma(60,20,1.3, textEscritorio.GLindex);
			//picaporte1
			glPushMatrix();
				glTranslatef(-7.8,0,-1.2);
				figPuerta.esfera(1.5,20,20,textManija.GLindex);
			glPopMatrix();
			//picaporte2
			glPushMatrix();
				glTranslatef(-7.8,0,1.2);
				figPuerta.esfera(1.5,10,10,textManija.GLindex);
			glPopMatrix();
			//lateral derecho
			glPushMatrix();
				glTranslatef(10.5,0,0);
				figPuerta.prisma(60, 2, 2.5, textEscritorio.GLindex);
			glPopMatrix();
			//lateral derecho
			glPushMatrix();
				glTranslatef(-10.5,0,0);
				figPuerta.prisma(60, 2, 2.5, textEscritorio.GLindex);
			glPopMatrix();
			//superior
			glPushMatrix();
				glTranslatef(0,30,0);
				figPuerta.prisma(2, 23, 2.5, textEscritorio.GLindex);
			glPopMatrix();
			//rectangulo1
			glPushMatrix();
				glTranslatef(0,25,-0);
					figPuerta.prisma(0.3, 12, 1.5, textEscritorio.GLindex);
				glPushMatrix();
					glTranslatef(0, -12, 0);
					figPuerta.prisma(0.3, 12, 1.5, textEscritorio.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 1.5, textEscritorio.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 1.5, textEscritorio.GLindex);
				glPopMatrix();
			glPopMatrix();
			//rectangulo2
			glPushMatrix();
				glTranslatef(0,6.5,-0);
					figPuerta.prisma(0.3, 12, 1.5, textEscritorio.GLindex);
				glPushMatrix();
					glTranslatef(0, -12, 0);
					figPuerta.prisma(0.3, 12, 1.5, textEscritorio.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 1.5, textEscritorio.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 1.5, textEscritorio.GLindex);
				glPopMatrix();
			glPopMatrix();
			//rectangulo3
			glPushMatrix();
				glTranslatef(0,-12,-0);
				figPuerta.prisma(0.3, 12, 1.5, textEscritorio.GLindex);
				glPushMatrix();
					glTranslatef(0, -12, 0);
					figPuerta.prisma(0.3, 12, 1.5, textEscritorio.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 1.5, textEscritorio.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 1.5, textEscritorio.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();////
}

void ventanal(void) {
	glPushMatrix();
	glPushMatrix();
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glTranslatef(0, -1, 0);
			figVentanal.prisma(18,8,0.2,textVentanal.GLindex);
			glDisable(GL_BLEND);
		glPopMatrix();
		glPopMatrix();
	glPopMatrix();//////////////
}

void paredVentanas(void) {
glPushMatrix();
	glPushMatrix();
	//trave
	glPushMatrix();
		glTranslatef(0,9,0);
		figExterior.prisma(2,45.02,0.2,textFachada.GLindex);
	glPopMatrix();
	///////////ventanas
	glPushMatrix();
		//ventana1
		glPushMatrix();		
			ventanal();	
			///////////pílares
			//pilar 1
			glPushMatrix();
				glTranslatef(4.5, -1, 0);
				figExterior.prisma(18, 1, 0.2, textFachada.GLindex);
			glPopMatrix();
			//pilar 2
			glPushMatrix();
				glTranslatef(-4.5, -1, 0);
				figExterior.prisma(18, 1, 0.2, textFachada.GLindex);
			glPopMatrix();
			//pilar3
			glPushMatrix();
				glTranslatef(13.5, -1, 0);
				figExterior.prisma(18, 1, 0.2, textFachada.GLindex);
			glPopMatrix();
			//pilar4
			glPushMatrix();
				glTranslatef(-13.5, -1, 0);
				figExterior.prisma(18, 1, 0.2, textFachada.GLindex);
			glPopMatrix();
			//pilar5
			glPushMatrix();
				glTranslatef(-22.25, -1, 0);
				figExterior.prisma(18, 0.5, 0.2, textFachada.GLindex);
			glPopMatrix();
			//pilar6
			glPushMatrix();
				glTranslatef(22.25, -1, 0);
				figExterior.prisma(18, 0.5, 0.2, textFachada.GLindex);
			glPopMatrix();
			//ventana2
			glPushMatrix();
				glTranslatef(-9,0,0);
				ventanal();
			glPopMatrix();
			//ventana3
			glPushMatrix();
				glTranslatef(-18,0,0);
				ventanal();				
			glPopMatrix();
			//ventana4
			glPushMatrix();
				glTranslatef(9,0,0);
				ventanal();
				glPopMatrix();
			glPopMatrix();
			//ventana5
			glPushMatrix();
				glTranslatef(18,0,0);
				ventanal();				
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
glPopMatrix();
}

void cuarto(void) {
	//paredes
	glPushMatrix();
		//figCasa.prisma(60.0,85.0,85.0,textParedNubes.GLindex);
		figCasa.prismaRep2(61.0, 86.0, 86.0, textLadrillo.GLindex);
		//techo
		glPushMatrix();
			glTranslatef(45,50.1,0);
			glRotatef(90,0,0,1);
			glScalef(2,1,2.8);
			figCasa.cilindro(20,88,3,textTecho.GLindex);
		glPopMatrix();
		//cochera
		glPushMatrix();
			glTranslatef(-60,-15,0);
			figCasa.prismaRep2(30.0, 34.0, 85.0, textLadrillo.GLindex);
			//techo
			glPushMatrix();
				glTranslatef(17,23.5,0);
				glRotatef(90,0,0,1);
				glScalef(1,1,2.8);
				figCasa.cilindro(18,34,3,textTecho.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,-2.5,-42.6);
				figCasa.prisma(25,28,0.1,textTecho.GLindex);
			glPopMatrix();
		glPopMatrix();
		//exterior
		glPushMatrix();		
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			//puerta
			glPushMatrix();	
				glTranslatef(0,-16,-43);
				figVentana.prisma(29,12,0.1,textPuerta2.GLindex);
			glPopMatrix();
			//ventana1
			glPushMatrix();			
				glTranslatef(25,15,-43);
				figVentana.prisma(23,20,0.001,textVentana.GLindex);
			glPopMatrix();
			//ventana2
			glPushMatrix();			
				glTranslatef(-25,15,-43);
				figVentana.prisma(23,20,0.001,textVentana.GLindex);
			glPopMatrix();
			//ventana3
			glPushMatrix();			
				glTranslatef(25,-15,-43);
				figVentana.prisma(23,20,0.001,textVentana.GLindex);
			glPopMatrix();
			//ventana4
			glPushMatrix();			
				glTranslatef(-25,-15,-43);
				figVentana.prisma(23,20,0.001,textVentana.GLindex);
			glPopMatrix();
			//ventana5
			glPushMatrix();			
				glTranslatef(0,17,-43);
				figVentana.prisma(21,15,0.001,textVentana2.GLindex);
			glPopMatrix();		
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();
		//piso
		glPushMatrix();
			glTranslatef(0, -29.5, 0);
			figCasa.prismaRep(1.0, 84.8, 84.8, textPiso.GLindex);
		glPopMatrix();
		//cama
		glPushMatrix();
			glTranslatef(-21, -21.5, 30);			
			glScalef(1.5, 2, 2);
			//cama();
		glPopMatrix();
		//baul
		glPushMatrix();
			glTranslatef(-35, -24, -3);
			glRotatef(90, 0, 1, 0);
			glScalef(2.2, 2.5, 1.8);
			baul();			
		glPopMatrix();
		//buro
		glPushMatrix();
			glTranslatef(37.5, -15.5, 31);
			glRotatef(270, 0, 1, 0);
			glScalef(2, 1.8, 1.5);
			buro();
			//globo terraqueo
			glPushMatrix();
				glTranslatef(0, 6.5, 0);
				glScalef(0.4, 0.4, 0.4);
				globoTerraqueo();
			glPopMatrix();
		glPopMatrix();
		//escritorio
		glPushMatrix();
			glTranslatef(0,-10,-35);
			glScalef(2.5,2,2);
			escritorio();
		glPopMatrix();
		//librero
		glPushMatrix();
			glTranslatef(37,-27,-25);
			glRotatef(90,0,1,0);
			glScalef(5,5,3);
			librero();
		glPopMatrix();
		//cuadro 1
		glPushMatrix();
			glTranslatef(-42.3, 5 ,29.8);
			figCuadro.prisma(25,0.1,15,textCuadro1.GLindex);
		glPopMatrix();
		//cuadro2
		glPushMatrix();
			glTranslatef(-18, 0, 42.3);
			glRotatef(90, 0, 1, 0);
			figCuadro.prisma(20, 0.1, 12, textCuadro2.GLindex);
		glPopMatrix();
		//puerta 1
		glPushMatrix();
			glTranslatef(18,-3,41.5);
			glScalef(1,0.9,1);
			puerta();
		glPopMatrix();
		//puerta 1
		glPushMatrix();
			glTranslatef(41,-3,3);
			glRotatef(90,0,1,0);
			glScalef(1,0.9,1);
			puerta();
		glPopMatrix();
	glPopMatrix();////////////////////	
}

void piscina(void) {
glPushMatrix();
	//piso
	glPushMatrix();
		figExterior.prisma(0.1,50,30,textPiscina.GLindex);
		//barda norte
		glPushMatrix();
			glTranslatef(0,3,-15);	
			figExterior.prisma(7, 50, 0.5, textPiscina2.GLindex);
			glPushMatrix();
				//lateral derecho
				glTranslatef(24.75, 0, 15);
				figExterior.prisma(7, 0.5, 30, textPiscina2.GLindex);
			glPopMatrix();
			glPushMatrix();
				//lateral derecho
				glTranslatef(-24.75, 0, 15);
				figExterior.prisma(7, 0.5, 30, textPiscina2.GLindex);
			glPopMatrix();
		glPopMatrix();
		//barda sur
		glPushMatrix();
			glTranslatef(0,3,14.75);	
			figExterior.prisma(6, 49, 0.5, textPiscina2.GLindex);
			//escalones
			glPushMatrix();
				glTranslatef(0,-1,0.5);
				figExterior.prisma(4,20,1,textEscalera.GLindex);
				glPushMatrix();
					glTranslatef(0, -0.5, 1);
					figExterior.prisma(3, 15, 1, textEscalera.GLindex);
						glPushMatrix();
							glTranslatef(0, -0.5, 1);
							figExterior.prisma(2, 10, 1, textEscalera.GLindex);
						glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
glPopMatrix();
}

void camaNino(void) {
	//glPushMatrix();
		//colchon
		glPushMatrix();
			figCama.prisma(6, 24, 11, textCobija.GLindex, textCobijaBuzz.GLindex);
			//patas cabecera
			//1
			glPushMatrix();
				glTranslatef(-12.5, 1, 5);
				figCama.prisma(9.5, 1, 1, textCama.GLindex);
				glPushMatrix();
					glTranslatef(0, 4.5, 0);
					figCama.cono(3,0.5,10,textCama.GLindex);
					glPushMatrix();
						glTranslatef(0, 2.5, 0);
						figCama.esfera(0.7,10,10,textCama.GLindex);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//2
			glPushMatrix();
				glTranslatef(-12.5, 1, -5);
				figCama.prisma(9.5, 1, 1, textCama.GLindex);
					glPushMatrix();
						glTranslatef(0, 4.5, 0);
						figCama.cono(3,0.5,10,textCama.GLindex);
						glPushMatrix();
							glTranslatef(0, 2.5, 0);
							figCama.esfera(0.7,10,10,textCama.GLindex);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPushMatrix();
			//3 
			glPushMatrix();
				glTranslatef(12.5, 0, 5);
				figCama.prisma(7.5, 1, 1, textCama.GLindex);
				glPushMatrix();
					glTranslatef(0, 3.5, 0);
					figCama.cono(3, 0.5, 10, textCama.GLindex);
					glPushMatrix();
						glTranslatef(0, 2.5, 0);
						figCama.esfera(0.7, 10, 10, textCama.GLindex);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//4
			glPushMatrix();
				glTranslatef(12.5, 0, -5);
				figCama.prisma(7.5, 1, 1, textCama.GLindex);
				glPushMatrix();
					glTranslatef(0, 3.5, 0);
					figCama.cono(3, 0.5, 10, textCama.GLindex);
					glPushMatrix();
						glTranslatef(0, 2.5, 0);
						figCama.esfera(0.7, 10, 10, textCama.GLindex);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//tranvaersal 1
			glPushMatrix();
				glTranslatef(-12.5, 0, 0);
				figCama.prisma(6, 1, 9, textCama.GLindex);
				glPushMatrix();
					glTranslatef(0, 5.5, 0);
					figCama.prisma(0.5, 0.5, 9, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 4, 0);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 4, -3.25);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 4, -1.75);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 4, 3.25);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 4, 1.75);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
			glPopMatrix();
			//transversal2
			glPushMatrix();
				glTranslatef(12.5, -1, 0);
				figCama.prisma(4,1,9, textCama.GLindex);
				glPushMatrix();
					glTranslatef(0, 4.5, 0);
					figCama.prisma(0.5, 0.5, 9, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 3, 0);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 3, -3.25);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 3, -1.75);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 3, 3.25);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 3, 1.75);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void camaNina(void) {
	//glPushMatrix();
		//colchon
		glPushMatrix();
			figCama.prisma(6, 24, 11, textCobija2.GLindex, textCobijaPrincesa.GLindex);
			//patas cabecera
			//1
			glPushMatrix();
				glTranslatef(-12.5, 1, 5);
				figCama.prisma(9.5, 1, 1, textCama.GLindex);
				glPushMatrix();
					glTranslatef(0, 4.5, 0);
					figCama.cono(3,0.5,10,textCama.GLindex);
					glPushMatrix();
						glTranslatef(0, 2.5, 0);
						figCama.esfera(0.7,10,10,textCama.GLindex);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//2
			glPushMatrix();
				glTranslatef(-12.5, 1, -5);
				figCama.prisma(9.5, 1, 1, textCama.GLindex);
					glPushMatrix();
						glTranslatef(0, 4.5, 0);
						figCama.cono(3,0.5,10,textCama.GLindex);
						glPushMatrix();
							glTranslatef(0, 2.5, 0);
							figCama.esfera(0.7,10,10,textCama.GLindex);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPushMatrix();
			//3 
			glPushMatrix();
				glTranslatef(12.5, 0, 5);
				figCama.prisma(7.5, 1, 1, textCama.GLindex);
				glPushMatrix();
					glTranslatef(0, 3.5, 0);
					figCama.cono(3, 0.5, 10, textCama.GLindex);
					glPushMatrix();
						glTranslatef(0, 2.5, 0);
						figCama.esfera(0.7, 10, 10, textCama.GLindex);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//4
			glPushMatrix();
				glTranslatef(12.5, 0, -5);
				figCama.prisma(7.5, 1, 1, textCama.GLindex);
				glPushMatrix();
					glTranslatef(0, 3.5, 0);
					figCama.cono(3, 0.5, 10, textCama.GLindex);
					glPushMatrix();
						glTranslatef(0, 2.5, 0);
						figCama.esfera(0.7, 10, 10, textCama.GLindex);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//tranvaersal 1
			glPushMatrix();
				glTranslatef(-12.5, 0, 0);
				figCama.prisma(6, 1, 9, textCama.GLindex);
				glPushMatrix();
					glTranslatef(0, 5.5, 0);
					figCama.prisma(0.5, 0.5, 9, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 4, 0);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 4, -3.25);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 4, -1.75);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 4, 3.25);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 4, 1.75);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
			glPopMatrix();
			//transversal2
			glPushMatrix();
				glTranslatef(12.5, -1, 0);
				figCama.prisma(4,1,9, textCama.GLindex);
				glPushMatrix();
					glTranslatef(0, 4.5, 0);
					figCama.prisma(0.5, 0.5, 9, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 3, 0);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 3, -3.25);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 3, -1.75);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 3, 3.25);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 3, 1.75);
					figCama.prisma(2.5, 0.4, 0.4, textCama.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void cuartoNinos(void) {
	//Piso
	glPushMatrix();
		figSuelo.prisma(0.2,40,70,textPiso.GLindex);	
		//Paredes
		//sur
		glPushMatrix();
			glTranslatef(0, 10, 34.9);
			figPared.prisma(20, 40, 0.2, textParedNubes.GLindex);
			glPushMatrix();
				glTranslatef(0, 0, 0.1);
				figPared.prisma(20.1, 40, 0.1, textFachada.GLindex);
			glPopMatrix();
		glPopMatrix();
		//oeste
		glPushMatrix();
			glTranslatef(20, 10, 5);
			figPared.prisma(20, 0.2, 60, textAzulejo.GLindex);
		glPopMatrix();
		//este
		glPushMatrix();
			glTranslatef(-19.9, 10, 5);
			figPared.prisma(20, 0.2, 60, textCuadro1.GLindex);
			//madera
			glPushMatrix();
				glTranslatef(-0.15, 0, 0);
				figPared.prisma(20, 0.1, 60, textMaderaPared.GLindex);
			glPopMatrix();
		glPopMatrix();
		//norte
		glPushMatrix();
			glTranslatef(0, 10, -24.9);
			figPared.prisma(20, 40, 0.2, textParedRosa.GLindex);
			
			//intermedia
			glPushMatrix();
				glTranslatef(0, 0,30.9);
				figPared.prisma(20, 39.9, 0.1, textParedNubes.GLindex);
				//cuadro 1
				glPushMatrix();
					glTranslatef(14,0,0.1);
					glRotatef(90, 0, 1, 0);
					figCuadro.prisma(12 ,0.1, 6, textCuadro1.GLindex);
				glPopMatrix();
				//cuadro 2
				glPushMatrix();
					glTranslatef(-14,0,0.1);
					glRotatef(90, 0, 1, 0);
					figCuadro.prisma(12 ,0.1, 6, textCuadro2.GLindex);
				glPopMatrix();
				//cuadro 3
				glPushMatrix();
					glTranslatef(0,0,0.1);
					glRotatef(90, 0, 1, 0);
					figCuadro.prisma(12 ,0.1, 6, textCuadro3.GLindex);
				glPopMatrix();
				//cuadro 4
				glPushMatrix();
					glTranslatef(0,0,-0.2);
					glRotatef(90, 0, 1, 0);
					figCuadro.prisma(12 ,0.1, 20, textCuadro4.GLindex);
				glPopMatrix();
				//lateral1
				glPushMatrix();
					glTranslatef(19.9, 0, 14.5);
					figPared.prisma(20, 0.1, 29, textParedNubes.GLindex);
					//puertabaño1
					glPushMatrix();
						glTranslatef(0,-1,-9);
						glScalef(0.35,0.3,0.3);
						glRotatef(90, 0, 1, 0);
						puerta();
					glPopMatrix();
				glPopMatrix();
				//lateral2
				glPushMatrix();
					glTranslatef(-19.8, 0, 14.5);
					figPared.prisma(20, 0.1, 29, textParedNubes.GLindex);
					//puerta pasillo1
					glPushMatrix();
						glTranslatef(-0.1,-1,-9);
						glScalef(0.35,0.3,0.3);
						glRotatef(90, 0, 1, 0);
						puerta();
					glPopMatrix();
				glPopMatrix();
				//lateral3
				glPushMatrix();
					glTranslatef(19.9, 0, -15.5);
					figPared.prisma(20, 0.1, 31, textParedRosa.GLindex);
					//puertabaño2
					glPushMatrix();
						glTranslatef(0,-1,9);
						glScalef(0.35,0.3,0.3);
						glRotatef(270, 0, 1, 0);
						puerta();
					glPopMatrix();
				glPopMatrix();
				//lateral4
				glPushMatrix();
					glTranslatef(-19.8, 0, -15.5);
					figPared.prisma(20, 0.1, 31, textParedRosa.GLindex);
					//puerta pasillo 2
					glPushMatrix();
						glTranslatef(-0.1,-1,9);
						glScalef(0.35,0.3,0.3);
						glRotatef(270, 0, 1, 0);
						puerta();
					glPopMatrix();
				glPopMatrix();
				//sur
				glTranslatef(0, 0, -0.1);
				figPared.prisma(20, 39.9, 0.1, textParedRosa.GLindex);
			glPopMatrix();
		glPopMatrix();
		////////////objetos
		//cama1
		glPushMatrix();
			glTranslatef(-11, 3, 28);
			glScalef(0.6, 0.8, 1);
			camaNino();
		glPopMatrix();
		//cama 2
		glPushMatrix();
			glTranslatef(-11, 3, -18);
			glScalef(0.6, 0.8, 1);
			camaNina();
		glPopMatrix();
		//escritorio
		glPushMatrix();
			glTranslatef(6, 7.5, -22);
			glScalef(1, 0.8, 0.7);
			escritorio();
		glPopMatrix();
		//buro 1
		glPushMatrix();
			glTranslatef(18, 5, -12);
			glScalef(0.8, 0.7, 1);
			glRotatef(270,0,1,0);
			buro();
			//globo terraqueo
			glPushMatrix();
				glTranslatef(0, 6.5, 0);
				glScalef(0.4, 0.4, 0.4);
				globoTerraqueo();
			glPopMatrix();
		glPopMatrix();
		//baul
		glPushMatrix();
			glTranslatef(1, 2, 28);
			glScalef(1, 1, 1);
			glRotatef(90,0,1,0);
			baul();
		glPopMatrix();
		//buro 2
		glPushMatrix();
			glTranslatef(9, 5, 32);
			glScalef(0.8, 0.7, 1);
			glRotatef(180,0,1,0);
			buro();
		glPopMatrix();
		//librero
		glPushMatrix();
			glTranslatef(17, 1, 28);
			glScalef(1.5, 2, 1.8);
			glRotatef(90,0,1,0);
			librero();
		glPopMatrix();

	glPopMatrix();		

}

void banoNinos(void) {
	glPushMatrix();
		glPushMatrix();
			figSuelo.prismaRep3(0.2, 25, 60, textPisoBaño.GLindex);
			//limites
			//sur
			glPushMatrix();
				glTranslatef(0,10,30);
				figExterior.prisma(20,25,0.1,textAzulejo.GLindex);
				//fachada
				glPushMatrix();
					glTranslatef(0, 0, 0.1);
					figExterior.prisma(20, 25, 0.1, textFachada.GLindex);
				glPopMatrix();
			glPopMatrix();
			//norte
			glPushMatrix();
				glTranslatef(0,10,-30);
				figExterior.prisma(20,25,0.1,textAzulejo.GLindex);
				//fachada
				glPushMatrix();
					glTranslatef(0, 0, -0.1);
					figExterior.prisma(20, 25, 0.1, textFachada.GLindex);
				glPopMatrix();
			glPopMatrix();
			//este
			glPushMatrix();
				glTranslatef(12.4,9.9,0);
				figExterior.prisma(20,0.1,60, textAzulejo.GLindex);
				//fachada
				glPushMatrix();
					glTranslatef(0.1, 0, 0);
					figExterior.prisma(20, 0.1, 60.3, textFachada.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void cuartoPrincipal(void) {
	//Piso
	glPushMatrix();
		figSuelo.prisma(0.2,40,50, textPiso.GLindex);
		//suelo azulejo
		glPushMatrix();
			glTranslatef(0,0.1,17.5);
			figExterior.prismaRep3(0.1, 40, 15, textPisoBaño2.GLindex);
		glPopMatrix();
		//Paredes
		//sur
		glPushMatrix();
			glTranslatef(0, 10, 24.9);
			figPared.prisma(20, 40, 0.2, textParedFina.GLindex);
			//pared baño sur
			glPushMatrix();
				glTranslatef(0, 0, -0.1);
				figPared.prisma(20, 40, 0.1, textAzulejo2.GLindex);
			glPopMatrix();
			//pared baño este
			glPushMatrix();
				glTranslatef(19.8, 0, -7.5);
				figPared.prisma(20, 0.1, 15, textAzulejo2.GLindex);
			glPopMatrix();
			//pared baño este
			glPushMatrix();
				glTranslatef(-19.8, 0, -7.5);
				figPared.prisma(20, 0.1, 15, textAzulejo2.GLindex);
			glPopMatrix();
			//puerta1
			glPushMatrix();
				glTranslatef(15,-1,-15);
				glScalef(0.35,0.3,0.3);
				puerta();
			glPopMatrix();
			glPushMatrix();
				//pared intemedia;
				glTranslatef(-0.1, 0, -15);
				figPared.prisma(20, 40, 0.1, textParedFina.GLindex);
				//pared baño norte
				glPushMatrix();
					glTranslatef(0, 0, 0.1);
					figPared.prismaRep3(19.8, 40, 0.1, textAzulejo2.GLindex);
				glPopMatrix();
			glPopMatrix();			
		glPopMatrix();
		//este
		glPushMatrix();
			glTranslatef(19.9, 10, 0);
			figPared.prisma(20, 0.2, 50, textParedFina.GLindex);
			//fachada
			glPushMatrix();
				glTranslatef(0.1, 0, 0);
				figPared.prisma(20, 0.2, 50, textFachada.GLindex);
			glPopMatrix();
		glPopMatrix();
		//oeste
		glPushMatrix();
			glTranslatef(-19.9, 10, 0);
			figPared.prisma(20, 0.2, 50, textParedFina.GLindex);
			//puerta5
			glPushMatrix();
				glTranslatef(-0.1,-1.5,0);
				glScalef(0.45,0.28,0.3);
				glRotatef(90,0,1,0);
				puerta();
			glPopMatrix();
		glPopMatrix();
		//norte
		glPushMatrix();
			glTranslatef(0, 10, -24.9);
			figPared.prisma(20, 40, 0.2, textParedFina.GLindex);
			glPushMatrix();
				glTranslatef(0, 0,-0.1);
				figPared.prisma(20, 40, 0.1, textFachada.GLindex);
			glPopMatrix();
			//puerta3
			glPushMatrix();
				glTranslatef(5.1,-1.5,0);
				glScalef(0.45,0.28,0.3);
				glRotatef(0,0,1,0);
				puerta();
			glPopMatrix();
			//puerta4
			glPushMatrix();
				glTranslatef(-5.1,-1.5,0);
				glScalef(0.45,0.28,0.3);
				glRotatef(180,0,1,0);
				puerta();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();	
}

void comedor(void) {
	//Piso
	glPushMatrix();		
		figSuelo.prisma(0.2,45,90, textPiso.GLindex);
		//////////Objetos
		glPushMatrix();
			//mesa
			glPushMatrix();
				glTranslatef(0, 7.5, -0);
				mesa();
				//silla1
				glPushMatrix();
					glTranslatef(-7,-1,0);
					silla();
				glPopMatrix();
				//silla2
				glPushMatrix();
					glTranslatef(-7,-1,7.5);
					silla();
				glPopMatrix();
				//silla3
				glPushMatrix();
					glTranslatef(-7, -1, -7.5);
					silla();
				glPopMatrix();
				//silla4
				glPushMatrix();
					glTranslatef(7,-1,0);
					glRotatef(180,0,1,0);
					silla();
				glPopMatrix();
				//silla5
				glPushMatrix();
					glTranslatef(7,-1,7.5);
					glRotatef(180, 0, 1, 0);
					silla();
				glPopMatrix();
				//silla6
				glPushMatrix();
					glTranslatef(7,-1,-7.5);
					glRotatef(180, 0, 1, 0);
					silla();
				glPopMatrix();
				//silla7
				glPushMatrix();
					glTranslatef(0,-1,-14);
					glRotatef(270, 0, 1, 0);
					silla();
				glPopMatrix();
				//silla8
				glPushMatrix();
					glTranslatef(0,-1,14);
					glRotatef(90, 0, 1, 0);
					silla();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//Refri
		glPushMatrix();
			glTranslatef(-19.4, 9.5, 25);
			refri();
		glPopMatrix();
		//alacena
		glPushMatrix();
			glTranslatef(-20.9,15.5,0);
			alacena();
			glPushMatrix();
				glTranslatef(0.5,-12.5,0);
				estufa();
			glPopMatrix();
		glPopMatrix();
		//puerta1
		glPushMatrix();
			glTranslatef(22.5,8.5,31.2);
			glScalef(0.4,0.28,0.3);
			glRotatef(90,0,1,0);
			puerta();
		glPopMatrix();
		//puerta2
		glPushMatrix();
			glTranslatef(22.5,8.5,38);
			glScalef(0.4,0.28,0.3);
			glRotatef(270,0,1,0);
			puerta();
		glPopMatrix();
		//puerta3
		glPushMatrix();
			glTranslatef(22.5, 8.5, -35);
			glScalef(0.4, 0.28, 0.3);
			glRotatef(90, 0, 1, 0);
			puerta();
		glPopMatrix();
		//puerta4
		glPushMatrix();
			glTranslatef(22.5, 8.5, -28.2);
			glScalef(0.4, 0.28, 0.3);
			glRotatef(270, 0, 1, 0);
			puerta();
		glPopMatrix();
		/******Paredes*****/
		//oeste
		glPushMatrix();
			glTranslatef(-22.3, 10, 0);
			figPared.prismaRep3(20, 0.2, 90, textMaderaPared.GLindex);
			glTranslatef(-0.1,0,0);
			figPared.prismaRep3(20.1, 0.2, 90, textFachada.GLindex);
		glPopMatrix();
		//este
		glPushMatrix();
			glTranslatef(22.4, 10, 0);
			figPared.prisma(20.2, 0.2, 90, textMaderaPared.GLindex);
			//fachada
			glPushMatrix();
				glTranslatef(0.1,0, 0);
				figPared.prisma(20.2, 0.3, 90, textFachada.GLindex);

			glPopMatrix();
		glPopMatrix();
		//sur
		glPushMatrix();
			//ventanas
			glTranslatef(0, 10, 44.9);
			paredVentanas();
		glPopMatrix();
		//norte
		glPushMatrix();
			//ventanas
			glTranslatef(0, 10, -44.9);
			glPushMatrix();
				paredVentanas();
			glPopMatrix();			
		glPopMatrix();
		//Entrada principal
		glPushMatrix();
			glTranslatef(-7,0,60);
//			figSuelo.prisma(0.2,59,20,textEscritorioMadera.GLindex);
		glPopMatrix();
		

	glPopMatrix();
		
}

void sala(void) {
	//Piso
	glPushMatrix();
		
		figSuelo.prisma(0.2,45,50, textPiso.GLindex);
		////////Objetos
		//Alfombra
		glPushMatrix();
			glTranslatef(-8,0.5,0);
			figSala.prisma(0.1,20,20,textAlfombra.GLindex);
			//mesita
			glPushMatrix();
				glTranslatef(0,2,0);
				mesita();
			glPopMatrix();
		glPopMatrix();
		//pantalla
		glPushMatrix();
			glTranslatef(-22.3,12,0);
			figSala.prisma(12,0.05,15,textPantalla.GLindex);
		glPopMatrix();
		//bocina1
		glPushMatrix();
			glTranslatef(-21,6,10);
			figSala.prisma(12,0.7,0.7,textBocina.GLindex);
		glPopMatrix();
		//bocina2
		glPushMatrix();
			glTranslatef(-21,6,-10);
			figSala.prisma(12,0.7,0.7,textBocina.GLindex);
		glPopMatrix();
		//bocina3
		glPushMatrix();
			glTranslatef(6,6,13.5);
			figSala.prisma(12,0.7,0.7,textBocina.GLindex);
		glPopMatrix();
		//bocina4
		glPushMatrix();
			glTranslatef(6,6,-13.5);
			figSala.prisma(12,0.7,0.7,textBocina.GLindex);
		glPopMatrix();
		//sillon
		glPushMatrix();
			glTranslatef(6,1,0);
			sillon();
		glPopMatrix();
		//puertas
		//puerta1
		glPushMatrix();
			glTranslatef(22.5,8.5,-3.4);
			glScalef(0.4,0.28,0.3);
			glRotatef(90,0,1,0);
			puerta();
		glPopMatrix();
		//puerta2
		glPushMatrix();
			glTranslatef(22.5,8.5,3.4);
			glScalef(0.4,0.28,0.3);
			glRotatef(270,0,1,0);
			puerta();
		glPopMatrix();
		///////Paredes
		glPushMatrix();
			glTranslatef(-22.4, 10, 0);
			figPared.prisma(20, 0.2, 50, textMaderaPared.GLindex);
			glTranslatef(-0.1, 0, 0);
			figPared.prisma(20.1, 0.1, 50, textFachada.GLindex);

		glPopMatrix();
		glPushMatrix();
			glTranslatef(22.4, 10, 0);
			figPared.prisma(20, 0.2, 50, textMaderaPared.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 10, 24.9);
			paredVentanas();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 10, -24.9);
			paredVentanas();
		glPopMatrix();
	glPopMatrix();
}

void pasilloLargo(void) {
	glPushMatrix();
		glPushMatrix();
			figSuelo.prisma(0.2,16,110, textPiso.GLindex);
			//paredess
			//este
			glPushMatrix();
				glTranslatef(7.9, 10, -24.8);
				figPared.prisma(20, 0.2, 60.5, textMaderaPared.GLindex);
				//fachada
				glPushMatrix();
					glTranslatef(0.1, 0, 0);
					figPared.prisma(20, 0.1, 60.5, textFachada.GLindex);
				glPopMatrix();
			glPopMatrix();
			//oeste
			glPushMatrix();
				glTranslatef(-7.9, 10, 0);
				figPared.prisma(20, 0.2, 110, textMaderaPared.GLindex);
				//fachada
				glPushMatrix();
					glTranslatef(-0.1,0,0);
					figPared.prisma(20, 0.1, 110, textFachada.GLindex);
				glPopMatrix();
			glPopMatrix();
			//sur
			glPushMatrix();
				glTranslatef(0, 10, 54.9);
				figPared.prisma(20, 16, 0.2, textMaderaPared.GLindex);
				//fachada
				glTranslatef(-0.2, 0, 0.2);
				figPared.prisma(20, 16.2, 0., textFachada.GLindex);
				//puerta
				glPushMatrix();
					glTranslatef(0, -2, -0.1);
					glScalef(0.25, 0.28, 0.4);
					puerta();
				glPopMatrix();
			glPopMatrix();
			//norte
			glPushMatrix();
				glTranslatef(0, 10, -54.9);
				figPared.prisma(20, 16, 0.2, textMaderaPared.GLindex);
				//fachada
				glPushMatrix();
					glTranslatef(0,0,-0.15);
					figPared.prisma(20.2, 16, 0.1, textFachada.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void carrusel(void)
{
	glTranslatef(16, 0, 26);
	/*glPushMatrix();
	glTranslatef(8, 0.1, 20);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig18.prisma2(0, 0); //textura carrusel piso
	glEnable(GL_LIGHTING);
	glPopMatrix();*/

	//techo


	glPushMatrix();
	glTranslatef(10, 6, 22);
	glRotatef(mundo, 0, 1, 0);
	fig18.cono(2, 7, 100, textcarpa.GLindex);
	glPopMatrix();
	//piso
	glPushMatrix();
	glTranslatef(10, 0.2, 22);
	//glRotatef(180, 1, 0, 0);
	glRotatef(mundo, 0, 1, 0);
	fig19.cono(0.1, 7, 100, textmetal.GLindex);
	glPopMatrix();

	//postes 
	glPushMatrix();
	glTranslatef(10, 0.1, 22);
	//glRotatef(180, 1, 0, 0);
	fig18.cilindro(0.3, 6, 100, textred.GLindex);
	//sillacarrusel();
	glRotatef(mundo, 0, 1, 0);

	glTranslatef(4, 0.1, -5);
	fig18.cilindro(0.1, 6, 100, 0);
	glTranslatef(-5, 0.1, -1);
	fig18.cilindro(0.1, 6, 100, 0);
	glTranslatef(-3, 0, 1);
	fig18.cilindro(0.1, 6, 100, 0);
	glTranslatef(-2, 0, 4);
	fig18.cilindro(0.1, 6, 100, 0);
	glTranslatef(1, 0, 5);
	fig18.cilindro(0.1, 6, 100, 0);
	glTranslatef(3, 0, 2);
	fig18.cilindro(0.1, 6, 100, 0);
	glTranslatef(4, 0, 0);
	fig18.cilindro(0.1, 6, 100, 0);
	glTranslatef(4, 0, -4);
	fig18.cilindro(0.1, 6, 100, 0);


	glPopMatrix();

}

void sillacarrusel(void) {

	glPushMatrix();
	glTranslatef(0, .015, 0);
	glScalef(1, .01, 1);
	fig19.prisma2(0, 0);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -.4);
	glRotatef(90, 1, 0, 0);
	glScalef(1, .01, .07);
	fig19.prisma2(0, 0);
	glPopMatrix();



}

void cochera(void) {
	//Piso
	glPushMatrix();
		figSuelo.prisma(0.2,70,50, textPisoCochera.GLindex);
		//Paredes
		//sur
		glPushMatrix();
			glTranslatef(0, 10, 25);
			figPared.prisma(20, 70, 0.1, textParedCochera.GLindex);
			//fachada
			glPushMatrix();
				glTranslatef(0, 0, 0.1);
				figPared.prisma(20, 70.2, 0.1, textFachada.GLindex);
			glPopMatrix();
		glPopMatrix();
		//norte
		glPushMatrix();
			glTranslatef(0, 10, -25);
			figPared.prisma(20, 70, 0.1, textParedCochera.GLindex);
			//fachada
			glPushMatrix();
				glTranslatef(0, 0, -0.1);
				figPared.prisma(20, 70.2, 0.1, textFachada.GLindex);
			glPopMatrix();
		glPopMatrix();
		//este
		glPushMatrix();
			glTranslatef(34.9, 10, 0);
			figPared.prisma(20, 0.1, 50, textParedCochera.GLindex);
			//fachada
			glPushMatrix();
				glTranslatef(0.1, 0, 0);
				figPared.prisma(20.3, 0.1, 50, textFachada.GLindex);
			glPopMatrix();
		glPopMatrix();
		/*
		glPushMatrix();
			glTranslatef(19.9, 10, 0);
			figPared.prisma(20, 0.2, 60, textCuadro2.GLindex);
		glPopMatrix();*/
	glPopMatrix();
}

/*********************Funciones main*********************/
void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	//Inicializacion texturas
	//exterior
	textCielo.LoadBMP("Texturas/exterior/01.bmp");
	textCielo.BuildGLTexture();
	textCielo.ReleaseImage();

	textPasto.LoadTGA("Texturas/exterior/verde.tga");
	textPasto.BuildGLTexture();
	textPasto.ReleaseImage();

	textTransparente.LoadTGA("Texturas/cuarto/transparente.tga");
	textTransparente.BuildGLTexture();
	textTransparente.ReleaseImage();

	textVentanal.LoadTGA("Texturas/cuarto/glass.tga");
	textVentanal.BuildGLTexture();
	textVentanal.ReleaseImage();

	textFachada.LoadTGA("Texturas/exterior/fachada.tga");
	textFachada.BuildGLTexture();
	textFachada.ReleaseImage();

	//cuarto
	textPiso.LoadTGA("Texturas/cuarto/piso.tga");
	textPiso.BuildGLTexture();
	textPiso.ReleaseImage();

	//cama
	textCobijaBuzz.LoadTGA("Texturas/cuarto/buzz.tga");
	textCobijaBuzz.BuildGLTexture();
	textCobijaBuzz.ReleaseImage();

	textCobija.LoadTGA("Texturas/cuarto/cobija.tga");
	textCobija.BuildGLTexture();
	textCobija.ReleaseImage();

	textCobijaPrincesa.LoadTGA("Texturas/cuarto/princesa.tga");
	textCobijaPrincesa.BuildGLTexture();
	textCobijaPrincesa.ReleaseImage();

	textCobija2.LoadTGA("Texturas/cuarto/rosa.tga");
	textCobija2.BuildGLTexture();
	textCobija2.ReleaseImage();

	textCama.LoadTGA("Texturas/cuarto/wood.tga");
	textCama.BuildGLTexture();
	textCama.ReleaseImage();

	//baul
	textBaul.LoadTGA("Texturas/cuarto/baulLateral.tga");
	textBaul.BuildGLTexture();
	textBaul.ReleaseImage();

	textBaulTapa.LoadTGA("Texturas/cuarto/baulTapa.tga");
	textBaulTapa.BuildGLTexture();
	textBaulTapa.ReleaseImage();

	//buro
	textBuro.LoadTGA("Texturas/cuarto/wood2.tga");
	textBuro.BuildGLTexture();
	textBuro.ReleaseImage();

	textBuroCajones.LoadTGA("Texturas/cuarto/wood3.tga");
	textBuroCajones.BuildGLTexture();
	textBuroCajones.ReleaseImage();

	//globo terraqueo
	textCobre.LoadTGA("Texturas/cuarto/cobre.tga");
	textCobre.BuildGLTexture();
	textCobre.ReleaseImage();

	textGloboTer.LoadTGA("Texturas/cuarto/tierra.tga");
	textGloboTer.BuildGLTexture();
	textGloboTer.ReleaseImage();

	textMueble.LoadTGA("Texturas/cuarto/wood4.tga");
	textMueble.BuildGLTexture();
	textMueble.ReleaseImage();

	//escritorio
	textEscritorio.LoadTGA("Texturas/cuarto/desktop.tga");
	textEscritorio.BuildGLTexture();
	textEscritorio.ReleaseImage();

	textEscritorioMadera.LoadTGA("Texturas/cuarto/wood5.tga");
	textEscritorioMadera.BuildGLTexture();
	textEscritorioMadera.ReleaseImage();

	//cuadros
	textCuadro1.LoadTGA("Texturas/cuarto/cuadro1.tga");
	textCuadro1.BuildGLTexture();
	textCuadro1.ReleaseImage();

	textCuadro2.LoadTGA("Texturas/cuarto/cuadro2.tga");
	textCuadro2.BuildGLTexture();
	textCuadro2.ReleaseImage();

	textCuadro3.LoadTGA("Texturas/cuarto/cuadro3.tga");
	textCuadro3.BuildGLTexture();
	textCuadro3.ReleaseImage();

	textCuadro4.LoadTGA("Texturas/cuarto/cuadro4.tga");
	textCuadro4.BuildGLTexture();
	textCuadro4.ReleaseImage();

	//puerta
	textPuerta.LoadTGA("Texturas/cuarto/white.tga");
	textPuerta.BuildGLTexture();
	textPuerta.ReleaseImage();

	textManija.LoadTGA("Texturas/cuarto/oro.tga");
	textManija.BuildGLTexture();
	textManija.ReleaseImage();

	//pared externa
	textLadrillo.LoadTGA("Texturas/cuarto/ladrillos1.tga");
	textLadrillo.BuildGLTexture();
	textLadrillo.ReleaseImage();

	//ventana
	textVentana.LoadTGA("Texturas/exterior/ventana.tga");
	textVentana.BuildGLTexture();
	textVentana.ReleaseImage();

	//ventana2
	textVentana2.LoadTGA("Texturas/exterior/ventana2.tga");
	textVentana2.BuildGLTexture();
	textVentana2.ReleaseImage();

	//puerta
	textPuerta2.LoadTGA("Texturas/exterior/puerta.tga");
	textPuerta2.BuildGLTexture();
	textPuerta2.ReleaseImage();

	//techo
	textTecho.LoadTGA("Texturas/exterior/techo.tga");
	textTecho.BuildGLTexture();
	textTecho.ReleaseImage();

	//libros
	textLibro1.LoadTGA("Texturas/cuarto/libro1.tga");
	textLibro1.BuildGLTexture();
	textLibro1.ReleaseImage();

	textLibro2.LoadTGA("Texturas/cuarto/libro2.tga");
	textLibro2.BuildGLTexture();
	textLibro2.ReleaseImage();

	textLibro3.LoadTGA("Texturas/cuarto/libro3.tga");
	textLibro3.BuildGLTexture();
	textLibro3.ReleaseImage();

	textLibro4.LoadTGA("Texturas/cuarto/libro4.tga");
	textLibro4.BuildGLTexture();
	textLibro4.ReleaseImage();

	textLibro6.LoadTGA("Texturas/cuarto/libro6.tga");
	textLibro6.BuildGLTexture();
	textLibro6.ReleaseImage();

	textLibro7.LoadTGA("Texturas/cuarto/libro7.tga");
	textLibro7.BuildGLTexture();
	textLibro7.ReleaseImage();

	textLibro8.LoadTGA("Texturas/cuarto/libro8.tga");
	textLibro8.BuildGLTexture();
	textLibro8.ReleaseImage();

	//Barda
	textBarda.LoadTGA("Texturas/exterior/barda.tga");
	textBarda.BuildGLTexture();
	textBarda.ReleaseImage();

	//Piscina
	textPiscina.LoadTGA("Texturas/Exterior/pool.tga");
	textPiscina.BuildGLTexture();
	textPiscina.ReleaseImage();

	textPiscina2.LoadTGA("Texturas/Exterior/piscina.tga");
	textPiscina2.BuildGLTexture();
	textPiscina2.ReleaseImage();

	textEscalera.LoadTGA("Texturas/Exterior/escalera.tga");
	textEscalera.BuildGLTexture();
	textEscalera.ReleaseImage();

	//silla
	textSilla.LoadTGA("Texturas/Cuarto/silla.tga");
	textSilla.BuildGLTexture();
	textSilla.ReleaseImage();

	//refrigerador
	textRefri.LoadTGA("Texturas/Cuarto/refri.tga");
	textRefri.BuildGLTexture();
	textRefri.ReleaseImage();

	textMetal.LoadTGA("Texturas/Cuarto/metal.tga");
	textMetal.BuildGLTexture();
	textMetal.ReleaseImage();

	//alacena
	textMaderaAlacena.LoadTGA("Texturas/Cuarto/maderaAlacena.tga");
	textMaderaAlacena.BuildGLTexture();
	textMaderaAlacena.ReleaseImage();

	textAlacena1.LoadTGA("Texturas/Cuarto/alacena1.tga");
	textAlacena1.BuildGLTexture();
	textAlacena1.ReleaseImage();

	textAlacena2.LoadTGA("Texturas/Cuarto/alacena2.tga");
	textAlacena2.BuildGLTexture();
	textAlacena2.ReleaseImage();

	//horno
	textHorno1.LoadTGA("Texturas/Cuarto/horno.tga");
	textHorno1.BuildGLTexture();
	textHorno1.ReleaseImage();
	
	textHorno2.LoadTGA("Texturas/Cuarto/horno2.tga");
	textHorno2.BuildGLTexture();
	textHorno2.ReleaseImage();

	//microhondas
	textMicrohondas.LoadTGA("Texturas/Cuarto/microhondas.tga");
	textMicrohondas.BuildGLTexture();
	textMicrohondas.ReleaseImage();

	//pared interna
	textMaderaPared.LoadTGA("Texturas/Cuarto/maderaPared.tga");
	textMaderaPared.BuildGLTexture();
	textMaderaPared.ReleaseImage();

	//alfombra
	textAlfombra.LoadTGA("Texturas/Cuarto/alfombra.tga");
	textAlfombra.BuildGLTexture();
	textAlfombra.ReleaseImage();

	//pantalla
	textPantalla.LoadTGA("Texturas/Cuarto/pantalla.tga");
	textPantalla.BuildGLTexture();
	textPantalla.ReleaseImage();

	//bocina
	textBocina.LoadTGA("Texturas/Cuarto/bocina.tga");
	textBocina.BuildGLTexture();
	textBocina.ReleaseImage();

	//sillon
	textCuero.LoadTGA("Texturas/Cuarto/cuero.tga");
	textCuero.BuildGLTexture();
	textCuero.ReleaseImage();

	//mesita
	textMaderaMesita.LoadTGA("Texturas/Cuarto/maderaMesita.tga");
	textMaderaMesita.BuildGLTexture();
	textMaderaMesita.ReleaseImage();

	//cuarto principal
	textParedFina.LoadTGA("Texturas/Cuarto/paredFina.tga");
	textParedFina.BuildGLTexture();
	textParedFina.ReleaseImage();

	//baño 1
	textAzulejo.LoadTGA("Texturas/Cuarto/azulejo.tga");
	textAzulejo.BuildGLTexture();
	textAzulejo.ReleaseImage();

	textPisoBaño.LoadTGA("Texturas/Cuarto/pisoBano.tga");
	textPisoBaño.BuildGLTexture();
	textPisoBaño.ReleaseImage();

	//cuarto niños
	textParedNubes.LoadTGA("Texturas/Cuarto/nubespared2.tga");
	textParedNubes.BuildGLTexture();
	textParedNubes.ReleaseImage();

	//baño 2
	textAzulejo2.LoadTGA("Texturas/Cuarto/azulejo2.tga");
	textAzulejo2.BuildGLTexture();
	textAzulejo2.ReleaseImage();

	textPisoBaño2.LoadTGA("Texturas/Cuarto/pisoBano2.tga");
	textPisoBaño2.BuildGLTexture();
	textPisoBaño2.ReleaseImage();

	//cuarto niños
	textParedNubes.LoadTGA("Texturas/Cuarto/nubespared2.tga");
	textParedNubes.BuildGLTexture();
	textParedNubes.ReleaseImage();

	textParedRosa.LoadTGA("Texturas/Cuarto/paredRosa.tga");
	textParedRosa.BuildGLTexture();
	textParedRosa.ReleaseImage();

	//chochera
	textPisoCochera.LoadTGA("Texturas/Exterior/pisoCochera.tga");
	textPisoCochera.BuildGLTexture();
	textPisoCochera.ReleaseImage();

	textParedCochera.LoadTGA("Texturas/Exterior/cochera.tga");
	textParedCochera.BuildGLTexture();
	textParedCochera.ReleaseImage();
	
	textcarpa.LoadTGA("carpa.tga");
	textcarpa.BuildGLTexture();
	textcarpa.ReleaseImage();

	textmetal.LoadTGA("metal.tga");
	textmetal.BuildGLTexture();
	textmetal.ReleaseImage();

	textred.LoadTGA("red.tga");
	textred.BuildGLTexture();
	textred.ReleaseImage();



	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);
	//NEW Iniciar variables de KeyFrames
	for (int i = 0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;

	}
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glRotatef(g_lookupdown, 1.0f, 0, 0);
	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
	////////////////////// Dibujo de figuras ////////////////////////
	glPushMatrix();
		//cielo
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(-25, 20, 10);
			figExterior.skybox(160.0, 80.0, 320.0, textCielo.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		/****************pasto y exterior******************/
		glDisable(GL_LIGHTING);
		//Pastor
		glPushMatrix();
			//pasto
			glTranslatef(-25,-20, 20);
			figExterior.prismaRep3(0.1, 160.0, 300.0, textPasto.GLindex);
			//Barda Norte
			glPushMatrix();
				glTranslatef(0,5,-140);
				glRotatef(90,0,1,0);
				figExterior.prismaRep2(10, 2, 140, textBarda.GLindex);
				//Barda oeste 
				glPushMatrix();	
				glPushMatrix();
					glRotatef(90, 0, 1, 0);
					glTranslatef(69.1,0,-54.5);
					figExterior.prismaRep2(10, 2, 110.9, textBarda.GLindex);
				glPopMatrix();
				glPopMatrix();
				//Barda este
				glPushMatrix();
					glTranslatef(-128,0,71);
					glRotatef(90, 0, 1, 0);
					figExterior.prismaRep2(10, 2, 258, textBarda.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//Piscina
		glPushMatrix();
			glTranslatef(15, -19.9, -90);
			piscina();		
		glPopMatrix();
		//Sala
		glPushMatrix();
			glTranslatef(-58.5, -20, 50);
			sala();
		glPopMatrix();
		
		//Cuarto 2
		glPushMatrix();
			glTranslatef(0, -20, 0);
			cuartoPrincipal();
		glPopMatrix();
		//Cocina, comedor
		glPushMatrix();
			glTranslatef(-58.5, -20, -40);
			glScalef(1,1,0.7);
			comedor();
		glPopMatrix();
		//Pasillo largo
		glPushMatrix();
			glTranslatef(-28, -20, 20);
			pasilloLargo();
		glPopMatrix();
		//Cochera
		glPushMatrix();
			glTranslatef(9, -20, 130);
			cochera();
		glPopMatrix();
		//Carrusel
		glPushMatrix();
		glTranslatef(-120, -20, -220);
		glScalef(2.5,2.5,2.5);
		sillacarrusel();
		carrusel();
		glPopMatrix();


		//baño niños
		glPushMatrix();
			glTranslatef(32.5, -20, 55);
			banoNinos();
		glPopMatrix();

		//carrusel();
		
		/*****************Pasillo Corto******************/
		glPushMatrix();
			glTranslatef(-2.5,-20,-30);
			figSuelo.prisma(0.2,35,10, textBaulTapa.GLindex);
			glPushMatrix();
				glTranslatef(17.4,10,0);
				figPared.prisma(20,0.2,10,textFachada.GLindex);
			glPopMatrix();
		glPopMatrix();	

		//Cuarto 1
		glPushMatrix();
			glTranslatef(0, -20, 50);
			cuartoNinos();
		glPopMatrix();

	
		glEnable(GL_LIGHTING);
	glPopMatrix();
	
	glutSwapBuffers();

} //pendiente

void animacion()
{
	dwCurrentTime = GetTickCount();
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;
	if (g_fanimacion)
	{
		//Globo terraqueo
		giroGloboTerraqueo += 1.0;		

	}

	if (dwElapsedTime >= 30)
	{
		mundo = (mundo - 10) % 360;
		dwLastUpdateTime = dwCurrentTime;



	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.4);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'k':		//
	case 'K':
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}

		break;
	case 'P':
	case 'p':
		Sonido();
		break;

	case 'O':		//  
	case 'o':
		g_fanimacion ^= true; //Activamos/desactivamos la animacíon
							  //circuito = false;
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;

	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
} //pendiente

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void menu(int id)
{

}

int main(int argc, char** argv)   // Main Function
{
	int submenu;
	glutInit(&argc, argv);					// Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(1080, 1080);			// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);			//Posicion de la Ventana
	glutCreateWindow("Proyecto final");		// Nombre de la Ventana
											//glutFullScreen();					    // Full Screen
	InitGL();								// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);				//Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);				//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);				//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);			//Otras
	glutIdleFunc(animacion);

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito", submenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}