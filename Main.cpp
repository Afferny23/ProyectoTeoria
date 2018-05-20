#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"

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
CTexture textCobija;
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
/*********************Carga figuras 3D******************/

/*********************Objetos*********************/
void cama(void) {
	glPushMatrix();
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
						glPushMatrix();
							//manija 1
							glTranslatef(0, 2, 0.4);
							figEscritorio.prisma(0.3, 1, 0.2, textEscritorio.GLindex);
						glPopMatrix();
					glPopMatrix();
					//manija 2
					glPushMatrix();
						glTranslatef(0, 3.45, 2.8);
						figEscritorio.prisma(0.3, 1, 0.2, textEscritorio.GLindex);
					glPopMatrix();
				glPopMatrix();
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

void puerta(void) {
	glPushMatrix();
		glPushMatrix();
			//centro
			figPuerta.prisma(60,20,0.6, textPuerta.GLindex);
			//picaporte
			glPushMatrix();
				glTranslatef(-7.8,0,-1.2);
				figPuerta.esfera(1.5,10,10,textManija.GLindex);
			glPopMatrix();
			//lateral derecho
			glPushMatrix();
				glTranslatef(10.5,0,0);
				figPuerta.prisma(60, 2, 2, textPuerta.GLindex);
			glPopMatrix();
			//lateral derecho
			glPushMatrix();
				glTranslatef(-10.5,0,0);
				figPuerta.prisma(60, 2, 2, textPuerta.GLindex);
			glPopMatrix();
			//superior
			glPushMatrix();
				glTranslatef(0,30,0);
				figPuerta.prisma(2, 23, 2, textPuerta.GLindex);
			glPopMatrix();
			//rectangulo1
			glPushMatrix();
				glTranslatef(0,25,-0.5);
					figPuerta.prisma(0.3, 12, 0, textPuerta.GLindex);
				glPushMatrix();
					glTranslatef(0, -12, 0);
					figPuerta.prisma(0.3, 12, 0.3, textPuerta.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 0.3, textPuerta.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 0.3, textPuerta.GLindex);
				glPopMatrix();
			glPopMatrix();
			//rectangulo2
			glPushMatrix();
				glTranslatef(0,6.5,-0.5);
					figPuerta.prisma(0.3, 12, 0.3, textPuerta.GLindex);
				glPushMatrix();
					glTranslatef(0, -12, 0);
					figPuerta.prisma(0.3, 12, 0.3, textPuerta.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 0.3, textPuerta.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 0.3, textPuerta.GLindex);
				glPopMatrix();
			glPopMatrix();
			//rectangulo3
			glPushMatrix();
				glTranslatef(0,-12,-0.5);
				figPuerta.prisma(0.3, 12, 0.3, textPuerta.GLindex);
				glPushMatrix();
					glTranslatef(0, -12, 0);
					figPuerta.prisma(0.3, 12, 0.3, textPuerta.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 0.3, textPuerta.GLindex);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-6, -6, 0);
					figPuerta.prisma(12.3, 0.3, 0.3, textPuerta.GLindex);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();////
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
			cama();
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

	textPasto.LoadTGA("Texturas/exterior/grass.tga");
	textPasto.BuildGLTexture();
	textPasto.ReleaseImage();
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
			figExterior.skybox(160.0, 80.0, 280.0, textCielo.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		//pasto
		glDisable(GL_LIGHTING);
		glPushMatrix();
			glTranslatef(-25,-20, 10);
			figExterior.prismaRep(0.1,140.0,260.0,textPasto.GLindex);
		glPopMatrix();
		
		/*******************Cuarto 1********************/
		//Piso
		glPushMatrix();
			glTranslatef(0,-20,0);
			figSuelo.prisma(0.2,40,50, textPiso.GLindex);
			//Paredes
			glPushMatrix();
				glTranslatef(0, 10, 24.9);
				figPared.prisma(20, 40, 0.2, textBaul.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(19.9, -10, 0);
				figPared.prisma(20, 0.2, 50, textBaul.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-19.9, -10, 0);
				figPared.prisma(20, 0.2, 50, textBaul.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, -10, -24.9);
				figPared.prisma(20, 40, 0.2, textBaul.GLindex);
			glPopMatrix();
		glPopMatrix();	

		/*******************Cuarto 2********************/
		//Piso
		glPushMatrix();
			glTranslatef(0,-20,50);
			figSuelo.prisma(0.2,40,50,textBaulTapa.GLindex);	
			//Paredes
			glPushMatrix();
				glTranslatef(0, 10, 24.9);
				figPared.prisma(20, 40, 0.2, textCuadro1.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(19.9, 10, 0);
				figPared.prisma(20, 0.2, 50, textCuadro1.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-19.9, 10, 0);
				figPared.prisma(20, 0.2, 50, textCuadro1.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 10, -24.9);
				figPared.prisma(20, 40, 0.2, textCuadro1.GLindex);
			glPopMatrix();
			
		glPopMatrix();		

		/*******************Cochera********************/
		//Piso
		glPushMatrix();
			glTranslatef(0,-20,105);
			figSuelo.prisma(0.2,40,60, textCobijaBuzz.GLindex);
			//Paredes
			glPushMatrix();
				glTranslatef(0, 10, 29.9);
				figPared.prisma(20, 40, 0.2, textCuadro2.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 10, -29.9);
				figPared.prisma(20, 40, 0.2, textCuadro2.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-19.9, 10, 0);
				figPared.prisma(20, 0.2, 60, textCuadro2.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(19.9, 10, 0);
				figPared.prisma(20, 0.2, 60, textCuadro2.GLindex);
			glPopMatrix();
		glPopMatrix();

		/***************Cocina, comedor****************/
		//Piso
		glPushMatrix();
			glTranslatef(-52.5,-20,-50);
			figSuelo.prisma(0.2,45,90, textBuro.GLindex);
			//Paredes
			glPushMatrix();
				glTranslatef(-22.4, 10, 0);
				figPared.prisma(20, 0.2, 90, textEscritorio.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(22.4, 10, 0);
				figPared.prisma(20, 0.2, 90, textEscritorio.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 10, 44.9);
				figPared.prisma(20, 45, 0.2, textEscritorio.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 10, -44.9);
				figPared.prisma(20, 45, 0.2, textEscritorio.GLindex);
			glPopMatrix();
		glPopMatrix();
		/********************Sala*********************/
		//Piso
		glPushMatrix();
			glTranslatef(-52.5,-20,50);
			figSuelo.prisma(0.2,45,50, textBuro.GLindex);
			glPushMatrix();
				glTranslatef(-22.4, 10, 0);
				figPared.prisma(20, 0.2, 50, textEscritorioMadera.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(22.4, 10, 0);
				figPared.prisma(20, 0.2, 50, textEscritorioMadera.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 10, 24.9);
				figPared.prisma(20, 45, 0.2, textEscritorioMadera.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 10, -24.9);
				figPared.prisma(20, 45, 0.2, textEscritorioMadera.GLindex);
			glPopMatrix();
		glPopMatrix();





		//Patio
		glPushMatrix();
			glTranslatef(32.5, -20, 52.5);
			figSuelo.prisma(0.2, 25, 55, textCobre.GLindex);
		glPopMatrix();

		//Pasillo largo
		glPushMatrix();
			glTranslatef(-25,-20,20);
			figSuelo.prisma(0.2,10,110, textCama.GLindex);
			//paredes
			glPushMatrix();
				glTranslatef(4.9, 10, 0);
				figPared.prisma(20, 0.2, 110, textGloboTer.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-4.9, 10, 0);
				figPared.prisma(20, 0.2, 110, textGloboTer.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-4.9, 10, 0);
				figPared.prisma(20, 0.2, 110, textGloboTer.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 10, 54.9);
				figPared.prisma(20, 10, 0.2, textGloboTer.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 10, -54.9);
				figPared.prisma(20, 10, 0.2, textGloboTer.GLindex);
			glPopMatrix();
		glPopMatrix();
		//Pasillo Corto
		glPushMatrix();
			glTranslatef(-2.5,-20,-30);
			figSuelo.prisma(0.2,35,10, textBaulTapa.GLindex);
		glPopMatrix();
			
			
			
		glEnable(GL_LIGHTING);
		/*//pasto
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(0, -20, 0);
			figExterior.prismaRep(1.0, 60.0, 60.0, textPasto.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		//cuarto
		glPushMatrix();
		//glScalef(1.0, 0.5, 1.0);
			glTranslatef(-10, -10.5, 0);
			glRotatef(180, 0, 1, 0);
			glDisable(GL_LIGHTING);
			glScalef(0.3, 0.3, 0.3);
			cuarto();
			glEnable(GL_LIGHTING);
		glPopMatrix();
		*/
	glPopMatrix();
	glutSwapBuffers();

} //pendiente

void animacion()
{
	if (g_fanimacion)
	{
		//Globo terraqueo
		giroGloboTerraqueo += 1.0;		

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