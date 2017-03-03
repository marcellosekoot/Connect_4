#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string.h>
#include "Fonc/fonctions.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <ctime>
#include "Fonc/ia.cpp"
#include "Fonc/ia2.cpp"
#include "Fonc/ia3.cpp"

using namespace sf;
using namespace std;

const int LARGEUR_ECRAN = 700;
const int HAUTEUR_ECRAN = 700;


int main()
{
//définition d'ecran
	RenderWindow window(VideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN), "Ceci est un puissance 4");
	window.setPosition(Vector2i(50, 50));
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	Color couleur(255,255,255,255);

//Definition de variables
	Grille *grille = new Grille();
	textures *texture = new textures();
	Touches *touche = new Touches();
	int joueur = 1;
	Clock hey;
	Time maintenant,avant;
	bool stop=false;
	Event event;
	Hand *hand = new Hand();
	int anneaux [4][2];
	bool menuu = true;
	bool rejouer=true;
	Menu *menu = new Menu();
	bool egalite=false;
	srand(time(NULL)); // initialisation de rand
	int position=0;
	int nbVictoires[2];
	int colonneActuelle=3;
	nbVictoires[0]=nbVictoires[1]=0;
	bool victoire=false;
	bool automatique=false;
//boucle globale
	while (rejouer)
	{


//menu
		while(menuu && !automatique)
		{	
			sleep(milliseconds(10));
			window.pollEvent(event);
			AppuiTouches(event,touche,&stop,&rejouer, &menuu);
			menu->Gerer(touche, &menuu, &rejouer, &stop);
			menu->Afficher(texture, &window);
		}
		menuu=true;


		int tourNumero=1;
//jeu central
		while (!victoire && !stop && !egalite)
		{
			sleep(milliseconds(10));
			if( (joueur==1 && menu->Joueur1Is()) || (joueur==-1 && menu->Joueur2Is()))
			{
				window.pollEvent(event);
				AppuiTouches(event, touche, &stop, &rejouer, &menuu);
				hand->Deplacement(touche,grille,&joueur, &tourNumero);
				position=hand->j();
			}
			else if (joueur==1)
			{
				if(menu->ChoixIAIs()==0)
				{		
					PoserJeton(IAJoue(joueur, grille, &tourNumero,&position),grille,&joueur);
				}
				else if (menu->ChoixIAIs()==1)
					PoserJeton(IAJoue2(joueur, grille, &tourNumero,&position),grille,&joueur);
				else
					PoserJeton(IAJoue3(joueur, grille, &tourNumero,&position),grille,&joueur);

				if(!menu->Joueur2Is())
				{
					hand->DefJ(position);
				}
			}
			else
			{
				if(menu->ChoixIA2Is()==0)
				{		
					PoserJeton(IAJoue(joueur, grille, &tourNumero,&position),grille,&joueur);
				}
				else if (menu->ChoixIA2Is()==1)
					PoserJeton(IAJoue2(joueur, grille, &tourNumero,&position),grille,&joueur);
				else
					PoserJeton(IAJoue3(joueur, grille, &tourNumero,&position),grille,&joueur);
				
				if(!menu->Joueur1Is())
				{
					hand->DefJ(position);
				}
			}

			window.pollEvent(event);
			AppuiTouches(event, touche, &stop, &rejouer, &menuu);
			SwitchAuto(touche,&automatique, &stop, &rejouer);
			victoire = grille->Victoire(-joueur,anneaux); 
			grille->Afficher(texture, &window,position,joueur,nbVictoires);
			if(!victoire)	
				grille->VerifierPlein(texture, &window, &egalite);
			window.display();

		}
//fin de boucle jeu central


		if (!stop && !egalite)
		{
			AfficherVictoire(anneaux,texture,&window,joueur);
			if(joueur==1)
				nbVictoires[1]++;
			else
				nbVictoires[0]++;
		}
		if (!stop && !automatique)
		{
			touche->Zero();
			event.key.code=Keyboard::Q;
			while(!AttenteTouche(event,touche,&stop,&rejouer))
				window.pollEvent(event);
			sleep(milliseconds(15));
		}

		tourNumero=1;
		egalite=false;
		victoire=false;
		grille->Clear();
		position=3;
		hand->DefJ(position);


	} //fin de boucle globale

	window.close();
	return 0;
}


//vertical :
// 12 + 97 * x

//horizontal :
// 17 + 96 * x

