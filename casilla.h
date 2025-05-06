#pragma once

//Creación de la clase Casilla
class Casilla
{
private:
	int fila, columna;
	unsigned char rojo; //R
	unsigned char verde;  //G
	unsigned char azul;  //B
	
public:
	Casilla();
	void setCasillas(int f, int c);
	void setColor(unsigned char r, unsigned char v, unsigned char a);
	void cuadrado(float _x, float _y, float tamanio);

	int getF() { return fila; }
	int getC() { return columna; }
	
	
};
