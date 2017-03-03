#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "fonctions.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>


using namespace sf;
using namespace std;

int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}

void AfficherVictoire(int anneaux [4][2], textures *texture, RenderWindow *window,int joueur)
{
	for(int i=0; i<4; i++)
	{
		texture->ring.setPosition(7+96*anneaux[i][1] , 102+97*anneaux[i][0]);
		window->draw(texture->ring);
	}
	if(joueur!=1)
		texture->victoire.setString("Victoire aux Rouges");
	else
		texture->victoire.setString("Victoire aux Jaunes");

	window->draw(texture->victoire);
	window->display();

}



void PoserJeton(int colonne, Grille *grille,int *joueur)
{
	if (colonne>=0)
	{
		bool pose=false;
		int ligne = 5;
		while (pose == false)
		{
			if(grille->RegarderGrille(ligne,colonne) == 0)
			{
				grille->PlacerJeton(ligne,colonne,joueur);
				pose=true;
				*joueur=-*joueur;
			}
			else
			{
				ligne--;
			}

		}

	}
}


void AppuiTouches(Event event, Touches *touche,bool *stop,bool *rejouer, bool *menu)
{
	switch (event.type)
	{
	case Event::Closed :
		*stop = true;
		*rejouer = false;
		*menu=false;
		break;
	case Event::KeyPressed :
		switch(event.key.code)
		{
		case Keyboard::Space :
			touche->validation_down=true;
			break;
		case Keyboard::Return :
			touche->validation_down=true;
			break;
		case Keyboard::Right :
			touche->right_down=true;
			break;
		case Keyboard::Left :
			touche->left_down=true;
			break;
		case Keyboard::Up :
			touche->up_down=true;
			break;
		case Keyboard::G :
			touche->g_down=true;
			break;
		case Keyboard::Down :
			touche->down_down=true;
			break;
		case Keyboard::P :
			touche->pause_down=true;
			break;
		default :
			break;
		}
		break;
	case Event::KeyReleased :
		switch(event.key.code)
		{
		case Keyboard::Space :
			touche->validation_down=false;
			touche->validation_up=true;
			break;
		case Keyboard::Return :
			touche->validation_down=false;
			touche->validation_up=true;
			break;
		case Keyboard::Right :
			touche->right_down=false;
			touche->right_up=true;
			break;
		case Keyboard::G :
			touche->g_down=false;
			touche->g_up=true;
			break;
		case Keyboard::Left :
			touche->left_down=false;
			touche->left_up=true;
			break;
		case Keyboard::Up :
			touche->up_down=false;
			touche->up_up=true;
			break;
		case Keyboard::Down :
			touche->down_down=false;
			touche->down_up=true;
			break;
		case Keyboard::P :
			touche->pause_down = false;
			touche->pause_up=true;
			break;
		default :
			break;
		}
		break;
	default :
		break;
	}

}


bool AttenteTouche(Event event, Touches *touche, bool *stop, bool *rejouer)
{
	bool onPart=false;
	switch (event.type)
	{
	case Event::Closed :
		*stop = true;
		*rejouer = false;
		onPart=true;
		break;
	case Event::KeyPressed :
		switch(event.key.code)
		{
		case Keyboard::Return :
			onPart=true;
			break;
		case Keyboard::Space :
			onPart=true;
			break;
		default :
			break;
		}
	default :
		break;
	}
	return onPart;
}


//emplementation classe Touches

Touches::Touches()
{
	left_down=right_down=up_down=down_down=validation_down=pause_down=g_down=false;
	validation_up=left_up=right_up=down_up=up_up=pause_up=g_up = true;
}
void Touches::Zero()
{
	left_down=right_down=up_down=down_down=validation_down=pause_down=g_down=false;
	validation_up=left_up=right_up=down_up=up_up=pause_up=g_up = true;
}




//implementation methodes textures
textures::textures()
{
	menuuu.loadFromFile("images/connectfuhrer.png");
	ringg.loadFromFile("images/ring.png");
	flecheeR.loadFromFile("images/flecheRouge.png");
	flecheeJ.loadFromFile("images/flecheJaune.png");
	grillee.loadFromFile("images/Grille.png");
	jaunee.loadFromFile("images/jaune.png");
	rougee.loadFromFile("images/rouge.png");
	menuu.setTexture(menuuu);
	grille.setTexture(grillee);
	rouge.setTexture(rougee);
	jaune.setTexture(jaunee);
	jaune.setScale(0.93,0.93);
	rouge.setScale(0.93,0.93);
	grille.setPosition(0,100);
	flecheJ.setTexture(flecheeJ);
	flecheR.setTexture(flecheeR);
	flecheJ.setScale(0.25,0.25);
	flecheJ.setPosition(315,10);
	flecheR.setScale(0.25,0.25);
	flecheR.setPosition(315,10);
	ring.setTexture(ringg);
	ring.setScale(0.14,0.14);
	font.loadFromFile("font/cicle.ttf");
	victoire.setFont(font);
	play.setFont(font);
	quit.setFont(font);
	player1.setFont(font);
	p1o.setFont(font);
	player2.setFont(font);
	p2o.setFont(font);
	menuu.setScale(1.6,1.6);
	play.setCharacterSize(70);
	quit.setCharacterSize(70);
	player1.setCharacterSize(35);
	p1o.setCharacterSize(30);
	player2.setCharacterSize(35);
	p2o.setCharacterSize(30);
	play.setStyle(Text::Bold );
	quit.setStyle(Text::Bold );
	player1.setStyle(Text::Bold );
	p1o.setStyle(Text::Bold );
	player2.setStyle(Text::Bold );
	p2o.setStyle(Text::Bold );
	play.setPosition(300,30);
	quit.setPosition(300,500);
	player1.setPosition(120,200);
	p1o.setPosition(120,230);
	player2.setPosition(440,200);
	p2o.setPosition(440,230);
	play.setString("Play");
	quit.setString("Exit");
	player1.setString("Joueur rouge");
	p1o.setString("Humain");
	player2.setString("Joueur Jaune");
	p2o.setString("Humain");
	victoire.setCharacterSize(50);
	victoire.setColor(Color::Green);
	victoire.setStyle(Text::Bold );
	victoire.setString("Victoire joueur victorieux !");
	victoire.setPosition(120,15);
	egalite.setFont(font);
	egalite.setPosition(220,15);
	egalite.setString("Egalite");
	egalite.setStyle(Text::Bold);
	egalite.setCharacterSize(80);
	nbVictoires1.setFont(font);
	nbVictoires1.setPosition(15,15);
	nbVictoires1.setStyle(Text::Bold);
	nbVictoires1.setCharacterSize(30);
	nbVictoires2.setFont(font);
	nbVictoires2.setPosition(640,15);
	nbVictoires2.setStyle(Text::Bold);
	nbVictoires2.setCharacterSize(30);
}






//implementation methodes Grille

Grille::Grille()
{
	for (int i=0; i<=5; i++)
	{
		for (int j=0; j<=6; j++)
		{
			this->grilleJeu[i][j] = 0;
		}
	}
}
bool Grille::Plein()
{
	bool plein= true;
	for (int i=0; i<7; i++)
	{
		if(this->RegarderGrille(0,i)==0) plein = false;
	}
	return plein;
}
bool Grille::ColonnePrise(int i)
{
	return (this->grilleJeu[0][i]!=0);
}
int Grille::RegarderGrille(int i, int j)
{
	return this->grilleJeu[i][j];
}
void Grille::PlacerJeton (int i, int j, int *joueur)
{
	this->grilleJeu[i][j] = *joueur;
}

void Grille::Afficher(textures *texture, RenderWindow *window, int posi,int joueur,int nbVictoires[2])
{
	window->clear();
	window->draw(texture->grille);

	stringstream ss;
	ss << nbVictoires[0];
	string str = ss.str();
	texture->nbVictoires1.setString(str);
	ss.str("");
	ss << nbVictoires[1];
	str = ss.str();
	texture->nbVictoires2.setString(str);

	window->draw(texture->nbVictoires1);
	window->draw(texture->nbVictoires2);

	if(joueur==1)
	{
		texture->flecheR.setPosition(27 + posi * 96,10);
		window->draw(texture->flecheR);
	}
	else
	{
		texture->flecheJ.setPosition(27 + posi * 96,10);
		window->draw(texture->flecheJ);
	}
	for (int i=0; i<=5; i++)
	{
		for (int j=0; j<=6; j++)
		{
			if(this->grilleJeu[i][j] == 1)
			{
				texture->rouge.setPosition(17 + 96*j , 112 + 97*i);
				window->draw(texture->rouge);
			}

			if(this->grilleJeu[i][j] == -1)
			{
				texture->jaune.setPosition(17 + 96*j , 112 + 97*i);
				window->draw(texture->jaune);
			}

		}

	}

}

bool Grille::Victoire (int joueur,int anneau[4][2])
{
	anneau[2][2]=4;
	int anos[4][2];
	bool alignes=false;
	int nbAlignes=0;

	//verification horizontale
	for (int i=0; i<=5; i++)
	{
		for (int j=0; j<=6; j++)
		{
			if(this->grilleJeu[i][j] == joueur)
			{
				nbAlignes++;
				if(alignes==false)
				{
					anos[j%4][0]=i;
					anos[j%4][1]=j;
				}
			}
			else
			{
				nbAlignes=0;
			}

			if(nbAlignes==4)
			{
				alignes=true;
			}

		}
		nbAlignes=0;

	}
	//verification verticale
	for (int i=0; i<=6; i++)
	{
		for (int j=0; j<=5; j++)
		{
			if(this->grilleJeu[j][i] == joueur)
			{
				nbAlignes++;
				if(alignes==false)
				{
					anos[j%4][0]=j;
					anos[j%4][1]=i;
				}
			}
			else
			{
				nbAlignes=0;
			}

			if(nbAlignes==4)
			{
				alignes=true;
			}

		}
		nbAlignes=0;

	}


	//Gestion diagonale

	//en montant de gauche a droite, pour les rangées començant a droite
	for (int i=3; i<=5; i++)
	{
		int ii=i;
		int iibase=i;
		for(ii; ii>=0; ii--)
		{
			if(this->grilleJeu[ii][iibase-ii] == joueur)
			{
				nbAlignes++;
				if(alignes==false)
				{
					anos[ii%4][0]=ii;
					anos[ii%4][1]=iibase-ii;
				}
			}
			else
			{
				nbAlignes=0;
			}
			if(nbAlignes==4)
			{
				alignes=true;
			}
		}
		nbAlignes=0;
	}

	//en montant de gauche a droite, pour les rangées començant a gauche
	for (int i=0; i<=2; i++)
	{
		int ii;
		int iibase=i;
		for(ii=0; ii<=5-iibase; ii++)
		{
			if(this->grilleJeu[ii+iibase][6-ii] == joueur)
			{
				nbAlignes++;
				if(alignes==false)
				{
					anos[ii%4][0]=ii+iibase;
					anos[ii%4][1]=6-ii;
				}
			}
			else
			{
				nbAlignes=0;
			}
			if(nbAlignes==4)
			{
				alignes=true;
			}
		}
		nbAlignes=0;
	}


	//en descendant de gauche a droite, pour les rangées commençant en haut
	for (int i=1; i<=3; i++)
	{
		int ii;
		int iibase=i;
		for(ii=0; ii<=6-iibase; ii++)
		{
			if(this->grilleJeu[ii][ii+iibase] == joueur)
			{
				nbAlignes++;
				if(alignes==false)
				{
					anos[ii%4][0]=ii;
					anos[ii%4][1]=ii+iibase;
				}
			}
			else
			{
				nbAlignes=0;
			}
			if(nbAlignes==4)
			{
				alignes=true;
			}
		}
		nbAlignes=0;
	}

	//en montant de droite a gauche, pour les rangées commençant en bas
	for (int i=3; i<=5; i++)
	{
		int ii;
		int iibase=i;
		for(ii=0; ii<=iibase; ii++)
		{
			if(this->grilleJeu[5-ii][iibase-ii] == joueur)
			{
				nbAlignes++;
				if(alignes==false)
				{
					anos[ii%4][0]=5-ii;
					anos[ii%4][1]=iibase-ii;
				}
			}
			else
			{
				nbAlignes=0;
			}
			if(nbAlignes==4)
			{
				alignes=true;
			}
		}
		nbAlignes=0;
	}


	if(alignes)
	{
		for(int l=0; l<4; l++)
		{
			anneau[l][0]=anos[l][0];
			anneau[l][1]=anos[l][1];
		}
	}

	return alignes;
}


void Grille::Clear()
{
	for (int i=0; i<=5; i++)
	{
		for (int j=0; j<=6; j++)
		{
			this->grilleJeu[i][j]=0;
		}
	}
}

void Grille::VerifierPlein(textures *texture, RenderWindow *window, bool *egalite)
{
	*egalite = true;
	for(int i=0; i<7; i++)
	{
		if(this->RegarderGrille(0,i)==0) *egalite = false;
	}
	if(*egalite)
		window->draw(texture->egalite);
}







//implémentation methodes Hand

Hand::Hand()
{
	horizontal = 3;
}

void Hand::Replacer()
{
	if (this->horizontal < 0)
	{
		this->horizontal = 0;
	}
	if (this->horizontal > 6)
	{
		this->horizontal = 6;
	}
}

void Hand::Right()
{
	this->horizontal++;
	this->Replacer();
}
void Hand::Left()
{
	this->horizontal--;
	this->Replacer();
}

int Hand::j()
{
	return this->horizontal;
}

void Hand::DefJ(int a)
{
	this->horizontal=a;
}

void Hand::Deplacement(Touches *touches, Grille *grille, int *joueur, int *aJoue)
{
	if(touches->left_down && touches->left_up)
	{
		touches->left_up = false;
		this->Left();
	}
	if(touches->right_down && touches->right_up)
	{
		touches->right_up = false;
		this->Right();;
	}
	if(touches->validation_down && touches->validation_up)
	{
		if(grille->RegarderGrille(0,this->horizontal)==0)
		{
			touches->validation_up = false;
			PoserJeton(this->horizontal,grille,joueur);
			*aJoue+=1;
		}
	}
}






//implementation methodes Menu
Menu::Menu()
{
	joueur1=joueur2=true;
	position = 1;
	gauche = true;
	choixIA=0;
	choixIA2=0;
}
int Menu::ChoixIA2Is()
{
	return choixIA2;
}

int Menu::ChoixIAIs()
{
	return choixIA;
}


bool Menu::Joueur2Is()
{
	return joueur2;
}

bool Menu::Joueur1Is()
{
	return joueur1;
}

void Menu::Afficher(textures *texture, RenderWindow *window)
{
	if(joueur1)
	{
		texture->p1o.setString("Human");
	}
	else if (this->choixIA==0)
	{
		texture->p1o.setString("Machine1");
	}
	else if (this->choixIA==1)
	{
		texture->p1o.setString("Machine2");
	}
	else
	{
		texture->p1o.setString("Machine3");
	}
	if(joueur2)
	{
		texture->p2o.setString("Human");
	}
	else if (this->choixIA2==0)
	{
		texture->p2o.setString("Machine1");
	}
	else if (this->choixIA2==1)
	{
		texture->p2o.setString("Machine2");
	}
	else
	{
		texture->p2o.setString("Machine3");
	}

	switch(this->position)
	{
	case 1 :
		texture->play.setColor(Color::Red);
		texture->p1o.setColor(Color::White);
		texture->p2o.setColor(Color::White);
		break;
	case 2 :
		texture->play.setColor(Color::White);
		texture->quit.setColor(Color::White);
		if (this->gauche)
		{
			texture->p1o.setColor(Color::Red);
			texture->p2o.setColor(Color::White);
		}
		else
		{
			texture->p2o.setColor(Color::Red);
			texture->p1o.setColor(Color::White);
		}
		break;
	case 3 :
		texture->p1o.setColor(Color::White);
		texture->p2o.setColor(Color::White);
		texture->quit.setColor(Color::Red);
		break;
	default :
		break;
	}

	window->clear();
	//window->draw(texture->menuu);
	window->draw(texture->play);
	window->draw(texture->quit);
	window->draw(texture->player1);
	window->draw(texture->p1o);
	window->draw(texture->player2);
	window->draw(texture->p2o);
	window->display();
}


void Menu::Gerer(Touches *touche, bool *menuu,bool *rejouer, bool *stop)
{
	if(touche->down_down && touche->down_up)
	{
		touche->down_up = false;
		this->position++;
	}

	if(touche->up_down && touche->up_up)
	{
		touche->up_up = false;
		this->position--;
	}

	if(touche->left_down && touche->left_up)
	{
		touche->left_up = false;
		this->gauche=true;
	}

	if(touche->right_down && touche->right_up)
	{
		touche->right_up = false;
		this->gauche=false;
	}
	if (this->position < 1) this->position = 1;
	if (this->position > 3) this->position = 3;
	if(touche->validation_down && touche->validation_up)
	{
		touche->validation_up=false;
		switch(this->position)
		{
		case 1 :
			*menuu=false;
			break;
		case 2 :
			if(gauche)
			{
				if(joueur1)joueur1=false;
				else if (choixIA==0) 
				{
					choixIA=1;
					joueur1=false;
				}
				else if (choixIA==1)
				{
					choixIA=2;
				}
				else 
				{
					choixIA=0;
					joueur1=true;
				}
			}
			if(!gauche)
			{
				if(joueur2)joueur2=false;
				else if (choixIA2==0) 
				{
					choixIA2=1;
					joueur2=false;
				}
				else if (choixIA2==1)
				{
					choixIA2=2;
				}
				else 
				{
					choixIA2=0;
					joueur2=true;
				}
			}
			break;
		case 3 :
			*menuu=false;
			*rejouer=false;
			*stop=true;
			break;
		default :
			break;

		}
	}

}


void SwitchAuto(Touches *touche, bool *automatique, bool *stop, bool *rejouer)
{
        if(touche->g_down && touche->g_up)
        {
                touche->g_up = false;
        	if(*automatique) *automatique = false;
		else		 *automatique = true;        
        }
	

	

	
}


