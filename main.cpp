#include "freeglut.h"
#include "CoordinadorAjedrez.h"

coordinador juego;

void OnDraw(void); //Esta funcion sera llamada para dibujar
void OnTimer(int value); //Esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //Cuando se pulse una tecla	
void OnMouseClick(int button, int state, int x, int y); //Control del ratón


int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("DeleteSys32(es broma)");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0, 800.0f / 600.0f, 0.1, 150);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick); //Callback del raton

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}

void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//funciones de dibujo
	juego.dibuja();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	juego.tecla(key);

	glutPostRedisplay();
}

void OnTimer(int value)
{
	// Música de fondo 
	ETSIDI::play("sonidos/MusicaFondo.wav");

	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}


void OnMouseClick(int b, int state, int x, int y)
{
	bool down = (state == GLUT_DOWN);

	int specialKey = glutGetModifiers();
	bool ctrlKey = (specialKey & GLUT_ACTIVE_CTRL) ? true : false;
	bool sKey = specialKey & GLUT_ACTIVE_SHIFT;

	juego.Boton_Raton(juego.Get_mundo().get_opon(), x, y, b, down, sKey, ctrlKey);

	glutPostRedisplay();
}
