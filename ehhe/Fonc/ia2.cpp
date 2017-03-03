#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "fonctions.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ia.h"

using namespace sf;
using namespace std;

//liste des fonctions deja presentes :
/*

void PoserJetonn(int colonne, int grille[6][7] ,int joueur); //pose le jeton de la couleur "joueur" sur un tableau

bool Victoire(int grille[6][7], int joueur); //detecte la victoire sur le tableau

bool ColonnePleine(int colonne, int grille[6][7]); //renvoie true si la colonne est pleine

bool ColonnePleineMoins1 (int colonne, int grille[6][7]);

int DetecterLignesLibres(int colonne, int grille[6][7]); // detecte combien de placer il reste sur la colonne envoyee en parametre 

*/

//aide :

/*
Le joueur rouge est représenté par la valeur "1" dans la variable joueur
Le joueur jaune est représenté par la valeur "-1" dans la variable joueur
donc pour passer de joueur rouge a jaune ou inversement, on change le signe de "joueur"

La tableau est utilise comme :

0.0	0.1	0.2	0.3	0.4	0.5	0.6

1.0	1.1	1.2	1.3	1.4	1.5	1.6

2.0	2.1	2.2	2.3	2.4	2.5	2.6

3.0	3.1	3.2	3.3	3.4	3.5	3.6

4.0	4.1	4.2	4.3	4.4	4.5	4.6

5.0	5.1	5.2	5.3	5.4	5.5	5.6



pour initialiser les valeurs du tableau servant a faire les essais avec les valeurs de la grille actuelle on utilise :

		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				notreTableau[i][j]=grille->RegarderGrille(i,j);
			}
		}


la fonction aléatoire :
retourne un entier entre "x" compris et "y" exclus

rand_a_b(x,y);   



*/


int IAJoue2(int joueur, Grille *grille, int *tourNumero,int *posi)
{
	int notreTableau[6][7];
	for(int i=0; i<6; i++)
	{
		for (int j=0; j<7; j++)
		{
			notreTableau[i][j]=grille->RegarderGrille(i,j);
		}
	}
	int colonneFinale=-1;
	
	colonneFinale=rand_a_b(0,7);


//faire attention a ne pas retourner un colonneFinale sur une colonne pleine pour éviter un core dumped. la grille reçue en parametre ne sera jamais pleine.


	while(ColonnePleine(colonneFinale,notreTableau))
	{
		colonneFinale=rand_a_b(0,7);
	}

	//laisser ces deux lignes
	(*tourNumero)+=1;
	*posi=colonneFinale;	

	return colonneFinale;

}

////////////////////////////////////////////////////////////////////////////////


