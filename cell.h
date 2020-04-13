#ifndef __FRAMECELL_H
#define __FRANECELL_H
#include "window.h"

class Cell
{
	char character;
	Color color;
	
	public:
		int getCharacter();
		void setCharacter(char character);	

		Color getColor();
		void setColor(Color color);

		//set all
		void set(char character, Color color);
};

#endif