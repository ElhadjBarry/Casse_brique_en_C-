#ifndef __PLAYER_H
#define __PLAYER_H
#include "window.h"

class Player
{
	int level;
	int score; 
	int balls;
	
	public:
		int getLevel();
		int getScore();
		int getBalls();

		void setLevel(int level);
		void setScore(int score);
		void setBalls(int balls);
};

#endif