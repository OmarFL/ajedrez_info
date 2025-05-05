#pragma once

class Vector
{
private:
	//Se crean los parametros de vector
	float x;
	float y;
public:
	//Metodos
	Vector(float _x=0.0f, float _y=0.0f);
	virtual ~Vector(){}
	Vector conversor(int _f, int _c);
	float getX() {	return x;}
	float getY() { return y; }
	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }
};