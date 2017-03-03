#ifndef H_GL_FONCTIONS
#define H_GL_FONCTIONS

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Color.hpp>
#include <time.h>
#include <vector>
#include <cstring>

using namespace sf;

int rand_a_b(int a, int b);

class Touches
{
public :
	bool left_down,right_down,up_down,down_down,validation_down,validation_up,left_up,right_up,down_up,up_up,pause_down,pause_up,g_down,g_up;
	Touches();
	void Zero();
};

void AppuiTouches(Event event, Touches *touche, bool *stop, bool *rejouer,bool *menu);
bool AttenteTouche(Event event, Touches *touche, bool *stop, bool *rejouuuerr);

class textures
{
public :
	Texture grillee,jaunee,rougee,flecheeJ,flecheeR,ringg,menuuu;
	Sprite grille,jaune,rouge,flecheJ,flecheR,ring,menuu;
	Font font;
	Text victoire,play,quit,player1,p1o,player2,p2o,egalite,nbVictoires1,nbVictoires2;
	textures();
};


void AfficherVictoire(int anneaux [4][2], textures *texture, RenderWindow *window,int joueur);



class Grille
{
private :
	int grilleJeu [6][7];
public :
	Grille();
	bool Plein();
	bool ColonnePrise(int i);
	int RegarderGrille(int i, int j);
	void PlacerJeton (int i, int j, int *joueur);
	void Afficher(textures *texture, RenderWindow *window, int posi,int joueur, int nbVictoires[2]);
	bool Victoire (int joueur,int anneau[4][2]);
	void Clear();
	void VerifierPlein(textures *texture, RenderWindow *window, bool *egalite);
};



void PoserJeton(int colonne, Grille *grille,int *joueur);


class Hand
{
private :
	int horizontal;
public :
	Hand();
	void Replacer();
	void Right();
	void Left();
	int j();
	void DefJ(int a);
	void Deplacement(Touches *touches, Grille *grille, int *joueur, int *aJoue);
};


class Menu
{
private :
	bool joueur1,joueur2;
	int position;
	bool gauche;
	int choixIA;
	int choixIA2;
public :
	Menu();
	int ChoixIAIs();
	int ChoixIA2Is();
	bool Joueur1Is();
	bool Joueur2Is();
	void Afficher(textures *texture, RenderWindow *window);
	void Gerer(Touches *touche, bool *menuu,bool *rejouer, bool *stop);
};


void SwitchAuto (Touches *touche, bool *automatique, bool *stop, bool*rejouer);

#endif


