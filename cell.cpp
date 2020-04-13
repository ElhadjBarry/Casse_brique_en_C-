#include "cell.h"

Color Cell::getColor()
{
	return color;
}
void Cell::setColor(Color color)
{
	this->color = color;
}


int Cell::getCharacter()
{
	return character;
}
void Cell::setCharacter(char character){
	this->character = character;
}


void Cell::set(char character, Color color)
{
	setCharacter(character);
	setColor(color);
}
