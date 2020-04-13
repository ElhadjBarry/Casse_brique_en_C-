#ifndef __OBJECT_H
#define __OBJECT_H

#include "window.h"

class Object
{
	//top-left coordinate
	float x, y;
	int width, length;
	int resistance;
	Color color;
	float velX, velY;
	public:
		Object();

		int getWidth();
		int getLength();
		int getResistance();
		Color getColor();
		float getX();
		float getY();
		float getVelX();
		float getVelY();

		void setWidth(int width);
		void setLength(int lenth);
		void setResistance(int resistance);
		void setColor(Color color);
		void setXY(float x, float y);
		void setX(float x);
		void setY(float y);

		void setVelXY(float x, float y);

};

/*class Brick : public Object
{
	public:
		Brick()
		{

		}
};

class Ball : public Object
{
	
	public:
		float getVelX();
		float getVelY();
		void setVelXY(float x, float y);
};

class Platform : public Object
{

};*/
#endif
