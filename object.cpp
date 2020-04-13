#include "object.h"


int Object::getWidth()
{
	return width;
}
int Object::getLength()
{
	return length;
}
int Object::getResistance()
{
	return resistance;
}
Color Object::getColor()
{
	return color;
}
float Object::getX()
{
	return x;
}
float Object::getY()
{
	return y;
}

void Object::setWidth(int width)
{
	this->width = width;
}
	
void Object::setLength(int length)
{
	this->length = length;
}
void Object::setResistance(int resistance)
{
	this->resistance = resistance;
}
void Object::setColor(Color color)
{
	this->color = color;
}
void Object::setX(float x)
{
	this->x = x;
}
void Object::setY(float y)
{
	this->y = y;
}
void Object::setXY(float x, float y)
{
	setX(x); setY(y); 
} 

Object::Object()
{

}

float Object::getVelX()
{
	return this->velX;
}
float Object::getVelY()
{
	return this->velY;
}
void Object::setVelXY(float x, float y)
{
	this->velX = x;
	this->velY = y;
}