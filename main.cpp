#include "freeglut.h"
#include "CoordinadorAjedrez.h"

CoordinadorAjedrez controlador;

void OnDraw(void); //esta funcion sera llamada para dibujar

void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion

void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla
void onSpecialKeyboardDown(int key, int x, int y);
void OnMouseClick(int button, int state, int x, int y);


int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutSpecialFunc(onSpecialKeyboardDown);


	glutMouseFunc(OnMouseClick); // Registrar callback
	
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

	controlador.dibuja();

	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	controlador.tecla(key);

	glutPostRedisplay();
}

void OnTimer(int value)
{
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}

void onSpecialKeyboardDown(int key, int x, int y)
{
	controlador.tecla(key);
}

void OnMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		controlador.mouse(x, y); // Delegar en el controlador
		glutPostRedisplay(); // Redibujar
	}
}
