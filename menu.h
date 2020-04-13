#ifndef __MENU_H
#define __MENU_H
#include "window.h"

class Menu
{	
	public:
		void AffichageMenu(Window *background);
		void AffichageGagnant(Window *background);
		void AffichagePerdant(Window *background);
		void AffichageAide(Window *background);
		void AffichageInfo(Window *background);

};

#endif
