#include "window.h"
#include "object.h"
#include "cell.h"
#include "player.h"
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <fstream>

using namespace std;


void DebutJeu(Window *background, bool LDonnee);
//void AffichageMeilleurScore(Window *background);



char* convertion(const char* categorie, int donnee)
{
 	char buff[10];
	char* info = new char[50];
	strcpy(info, categorie);
	sprintf(buff, "%d", donnee);
	strcat(info, buff);
	return info;
}
void AffichageInfoJeu(Window *background, int level, int score, int balls)
{
  
	char* info;
	info = convertion("Niveau: ", level);
	background->print(3, 26, info);
	info = convertion("Le score: ", score);
	background->print(15, 26, info);
	info = convertion("Balles: ", balls);
	background->print(33, 26, info);
	background->print(60, 26, "Appuyez sur H pour de l'aide.");
}
void CasseBrique(int opt)
{
	Menu menu;
	Window *background = new Window(27, 90, 0, 0);
	background->setCouleurBordure(WBLUE);
    background->setCouleurFenetre(WBLACK);
    menu.AffichageMenu(background);

    switch(opt)
    {
    	case 1:
    		menu.AffichageInfo(background);
    		menu.AffichageMenu(background);
    		break;
    	case 2:
    		menu.AffichageAide(background);
    		menu.AffichageMenu(background);
    	default:
    		break;
    } 

    char ch;
    while((ch = getch()) != 'q')
    {
    	switch(ch)
    	{
    		case 's':    		
    			DebutJeu(background, false);
    			menu.AffichageMenu(background);
    			break;   
    		case 'h':
    			background->clear();
    			//AffichageMeilleurScore(background);
    			menu.AffichageMenu(background);	
    			break;	
    		case 'l':
    			DebutJeu(background, true);
    			menu.AffichageMenu(background);	
    			break;
    		case 'c':
    			background->clear();
    			menu.AffichageInfo(background);
    			menu.AffichageMenu(background);	
    			break;
    	}
    	

    }
}
float magnitude(float x, float y)
{
	x = x*x;
	y = y*y;
	return sqrt(x+y);
}
void AffichageCadre(Window *background, Cell ecranPreced[][26], Cell ecranActu[][26])
{
	for(int i=0; i<90; i++)
	{
		for(int j=0; j<26; j++)
		{
			if( ecranActu[i][j].getColor() != ecranPreced[i][j].getColor())
			{
				background->print(i, j,  ecranActu[i][j].getCharacter(),  ecranActu[i][j].getColor());
			}
		}
	}
}
void AjoutObjetAlecran(Object &object, Cell  ecranActu[][26])
{
	for(int i=(int)object.getX(); i<(int)object.getX()+object.getWidth(); i++)
	{
		for(int j=(int)object.getY(); j<(int)object.getY()+object.getLength(); j++)
		{
			 ecranActu[i-1][j-1].setColor(object.getColor());
			 ecranActu[i-1][j-1].setCharacter(' ');
		}
	}
}
void RenitialiserEcran(Cell ecran[][26])
{
	for(int i=0; i<90; i++)
	{
		for(int j=0; j<26; j++)
		{
			ecran[i][j].setColor(WBLACK);	
			ecran[i][j].setCharacter(' ');
		}

	}
}
void AffichageLog(string log)
{
	fstream f;
	f.open("log.txt", ios::out);
	f<<log;
	f.close();
}
bool CollisionObjet(Object obj1, Object obj2)
{

	if(obj1.getX() + obj1.getWidth() <= obj2.getX()) return false;
	if(obj1.getX() >= obj2.getWidth() + obj2.getX()) return false;
	if(obj1.getY() + obj1.getLength() <= obj2.getY()) return false;
	if(obj1.getY() >= obj2.getLength() + obj2.getY()+1) return false;
	return true;
}
void generationBrique(Object briq[20], int &nombre)
{

	fstream f;
	f.open("config.txt", ios::in);

	if(f.is_open()){
		int x, y, l, w, r;
		f>>nombre;

		for(int i = 0; i<nombre; i++)
		{
			f>>x>>y>>l>>w>>r;
			briq[i].setXY(x, y);
			briq[i].setLength(l);
			briq[i].setWidth(w);
			briq[i].setResistance(r);
			if(r == 1) briq[i].setColor(WMAGENTA);
			else briq[i].setColor(WRED);
		}
	}
	else
	{
		int y = 2;
		int x = 4;
		for(int i=0; i<nombre; i++)
		{
			briq[i].setXY(x, y);
			briq[i].setLength(2);
			briq[i].setWidth(10);
			briq[i].setColor(WRED);
			briq[i].setResistance(2);
			x+= briq[i].getWidth() + 5;
			if(x > 85)
			{
				x = 4;
				y += 3;
			}
		}
	}
}
bool Niveau(Object briq[20], int nombre)
{
	for(int i=0; i<nombre; i++)
	{
		if(briq[i].getResistance() > 0)
		{
			return false;
		}
	}
	return true;
}

void MeilleurScore(int score)
{
	if(score == 0)return;

	fstream f;
	f.open("lesscores.txt", ios::in);

	int scores[6];
	int NbScore=0;

	scores[0] = score;

	for(int i=0; i<5; i++)
	{
		
		f>>score;
		if(f.eof())
		{
			break;
		}
		NbScore++;
		scores[NbScore] = score;
		
	}
	for(int i=0; i<=NbScore; i++)
	{
		for(int j=0; j<=NbScore; j++)
		{
			if(scores[i] > scores[j])
			{
				int temp = scores[i];
				scores[i] = scores[j];
				scores[j] = temp;
			}
		}
	}

	f.close();
	f.open("lesscores.txt", ios::out);
	for(int i=0; i<=NbScore; i++)
	{
		if( i == 5) break;
		f<<scores[i]<<endl;
	}
	
	f.close();
}

void MeilleurScores(Window *background)
{
	char ch;
	int score;
	background->clear();
	background->print(41, 9, "Les scores", BRED);

	fstream f;
	f.open("lesscores.txt", ios::in);

	for(int i=0; i<5; i++)
	{
		
		f>>score;
		if(f.eof())
		{
			break;
		}
		if(score != 0)
		{
			background->print(43, 11+i*2, convertion("", score));
		}
	}


	while((ch = getch()) != 'q') {}
}


void DebutJeu(Window *background, bool LDonnee)
{
	Menu menu;
	int FR = 60;

      
	Cell ecranActu[90][26];
	Cell ecranPreced[90][26];

	Object briq[40];
	Object ball;
	Object platform;

	Player player;

	bool mouvement = false;
	float vitesseJeu = 0.5f;
	int nombreBrique = 24;
	bool niveauFait = false;
	player.setLevel(1), player.setScore(0), player.setBalls(5);
	generationBrique(briq, nombreBrique);
	platform.setXY(34, 26);

	string log = "";

	if(LDonnee == true)
	{
		int level, score, balls;
		float px, py; // coordonnee plateforme
		float bx, by; // coordonnee ball
		float vx, vy;
		//Nous remplaçons les donnees precedentes avec les donnees lues a partir du fichier 
		fstream f;
		f.open("enregistre.txt", ios::in);
		int mov;
		f>>mov; 
		if(mov == 1)  mouvement= true;
		else  mouvement= false;
		f>>level; player.setLevel(level);
		f>>score; player.setScore(score);
		f>>balls; player.setBalls(balls);
		f>>niveauFait;
		f>>px>>py; platform.setXY(px, py);
		f>>bx>>by; ball.setXY(bx, by);
		f>>vx>>vy; ball.setVelXY(vx, vy);
		f>>vitesseJeu;
		f>>nombreBrique;
		for(int i=0; i<nombreBrique; i++)
		{
			int x, y, l, w, r;
			f>>x>>y>>l>>w>>r;
			briq[i].setXY(x, y);
			briq[i].setLength(l);
			briq[i].setWidth(w);
			briq[i].setResistance(r);
			if(r == 1) briq[i].setColor(WMAGENTA);
			else briq[i].setColor(WRED);
		}
		f.close();
	}


	//Debut de configuration
	RenitialiserEcran(ecranPreced);
	RenitialiserEcran(ecranActu);
	platform.setWidth(20); // axe OX
	platform.setLength(1); // axe OY

	platform.setColor(WGREEN);


	ball.setColor(WBLUE);
	ball.setWidth(1);
	ball.setLength(1);


	background->clear();
	short int ch;
	while((ch = getch()) != 'q')
	{
		usleep(1000000 / FR);
		//Modifier les objets du jeu
		switch(ch)
		{
			case KEY_LEFT:
			{
				if(platform.getX()-1 > 0)
					platform.setX(platform.getX()-3);
				break;
			}
			case KEY_RIGHT:
			{
				if(platform.getX()+20 < 91)
					platform.setX(platform.getX()+3);
				break;
			}
			case 's':
			{
				if((player.getBalls() > 0) && niveauFait == false)
				{
					mouvement = true;
					ball.setVelXY(0, -1);
				}
				break;
			}	
			case 'h':
			{
				menu.AffichageAide(background);
				background->clear();
				RenitialiserEcran(ecranPreced);

			}
			case 'c':
			{
				if(player.getBalls()  == 0) return;
				else
				{
					if(niveauFait == true)
					{
						background->clear();
						niveauFait = false;
						generationBrique(briq, nombreBrique);
						player.setLevel(player.getLevel()+1);
						vitesseJeu *= 1.25;
						RenitialiserEcran(ecranPreced);
					}
				}
			}
			case '0':
			{
				fstream f;
				f.open("enregistre.txt", ios::out);
				if(mouvement == true) f<<"1\n";
				else f<<"0\n";

				f<<player.getLevel()<<"\n";
				f<<player.getScore()<<"\n";
				f<<player.getBalls()<<"\n";
				f<<niveauFait<<"\n";
				f<<platform.getX()<<" "<<platform.getY()<<"\n";
				f<<ball.getX()<<" "<<ball.getY()<<"\n";
				f<<ball.getVelX()<<" "<<ball.getVelY()<<"\n";
				f<<vitesseJeu<<"\n";
				f<<nombreBrique<<"\n";
				for(int i=0; i<nombreBrique; i++)
				{
					int x, y;
					x = briq[i].getX();
					y = briq[i].getY();
					f<<x<<" "<<y<<" ";
					f<<briq[i].getLength()<<" ";
					f<<briq[i].getWidth()<<" ";
					f<<briq[i].getResistance()<<"\n";
				}				
				f.close();
				break;
			}
			default:
				break;
		}	

		if(mouvement == false)
		{
			ball.setXY(platform.getX()+platform.getWidth()/2-1, platform.getY()-1);

		}
		else
		{
			ball.setX(ball.getX() + ball.getVelX() * vitesseJeu);
			ball.setY(ball.getY() + ball.getVelY() * vitesseJeu);
			if(ball.getY() < 0) ball.setY(0);


			if(CollisionObjet(ball, platform) && ball.getY() >25.5f)
			{
				log += "Objet frappé\n";
				if(ball.getX() < platform.getX()+7)
				{
					float pozx = ball.getX() - abs((platform.getX()+10-ball.getX()));
					float pozy = ball.getY()-4;
					pozx -= ball.getX();
					pozy -= ball.getY();
					float mag = magnitude(pozx, pozy);
					ball.setVelXY(pozx / mag, pozy / mag);
				}
				else
				{
					if(ball.getX() > platform.getX()+13)
					{							
						float pozx = ball.getX() + abs((platform.getX()+10-ball.getX()));
						float pozy = ball.getY()-8;
						pozx -= ball.getX();
						pozy -= ball.getY();
						float mag = magnitude(pozx, pozy);
						ball.setVelXY(pozx / mag, pozy / mag);
					}
					else
					{
						ball.setVelXY(0, -1);
					}
				}
			}
			else
			{
							
				if( ball.getY() > 26) 
				{
					mouvement = false;
					player.setBalls(player.getBalls() -1);
					log+= "Vie perdue\n";
					if(player.getBalls() == 0)
					{
						AffichageLog(log);
						 MeilleurScore(player.getScore());
						menu.AffichagePerdant(background);
					}
				}
				if( ball.getX() < 1) ball.setVelXY(-ball.getVelX(), ball.getVelY());
				if( ball.getX() > 90) ball.setVelXY(-ball.getVelX(), ball.getVelY());
				if( ball.getY() < 1) ball.setVelXY(ball.getVelX(), -ball.getVelY());

		        
				for(int i=0; i<nombreBrique; i++)
				{
					if((briq[i].getResistance() > 0) && CollisionObjet(ball, briq[i]))
					{
						player.setScore(player.getScore() + 10 * player.getLevel());
						briq[i].setResistance(briq[i].getResistance()-1);
						if(briq[i].getResistance() == 1) briq[i].setColor(WMAGENTA);
						if(ball.getX() < briq[i].getX() + 0.5)
						{
							ball.setVelXY(-ball.getVelX(), ball.getVelY());			
						}
						else
						{
							if(ball.getX() > briq[i].getX() +briq[i].getWidth() -0.5)
							{
								ball.setVelXY(-ball.getVelX(), ball.getVelY());
							}
							else
							{
								ball.setVelXY(ball.getVelX(), -ball.getVelY());
							} 
						}
					}
				}
			}

		}

	        
		AjoutObjetAlecran(platform, ecranActu);
         	AjoutObjetAlecran(ball, ecranActu);
		AffichageInfoJeu(background, player.getLevel(), player.getScore(), player.getBalls());
		for(int i=0; i<nombreBrique; i++)
		{
			if(briq[i].getResistance() > 0)
				AjoutObjetAlecran(briq[i], ecranActu);
		}

		AffichageCadre(background, ecranPreced, ecranActu);
		for(int i=0; i<90; i++)
		{
			for(int j=0; j<26; j++)
			{
				ecranPreced[i][j].setColor(ecranActu[i][j].getColor());
			}

		}
		RenitialiserEcran(ecranActu);

		if(Niveau(briq, nombreBrique) == true)
		{			
			niveauFait = true;
			mouvement = false;
			menu.AffichageGagnant(background);
			AffichageLog(log);
		}
	}	
}



int main(int argc, char** argv){


   int opt;
   if(argc > 1)
   {
	   if(argv[1][1] == 'c')
	  	    opt = 1;
	   if(argv[1][1] == 'h')
	  	    opt = 2;
	}


	startProgramX();
	CasseBrique(opt);
	stopProgramX();
	return 0;
}
