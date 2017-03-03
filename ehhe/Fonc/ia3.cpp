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

/*

void PoserJetonn(int colonne, int grille[6][7] ,int joueur); //pose le jeton de la couleur "joueur" sur un tableau

bool Victoire(int grille[6][7], int joueur); //detecte la victoire sur le tableau

bool ColonnePleine(int colonne, int grille[6][7]); //renvoie true si la colonne est pleine

bool ColonnePleineMoins1 (int colonne, int grille[6][7]);

int DetecterLignesLibres(int colonne, int grille[6][7]); // detecte combien de placer il reste sur la colonne envoyee en parametre 

*/

/*

0.0	0.1	0.2	0.3	0.4	0.5	0.6

1.0	1.1	1.2	1.3	1.4	1.5	1.6

2.0	2.1	2.2	2.3	2.4	2.5	2.6

3.0	3.1	3.2	3.3	3.4	3.5	3.6

4.0	4.1	4.2	4.3	4.4	4.5	4.6

5.0	5.1	5.2	5.3	5.4	5.5	5.6



rand_a_b(x,y);   



*/

void CopierContenuTableau(int source[6][7], int cible[6][7]);

void calcul(int grille[6][7], int joueur, int grilleBackup[6][7]);

bool GagneProchainCoup(int grille[6][7], int joueur);

bool VictoireAdverse(int grille[6][7],int joueur);

bool GrillePleine(int grille[6][7]);

void initTableau(Grille *grille,int tableau[6][7]);

int IAJoue3(int joueur, Grille *grille, int *tourNumero,int *posi)
{
	bool gagneSur=false;
	bool victoireTemp=false;
	bool defaite=false;

	int tableau[6][7];
	int tableau2[6][7];
	initTableau(grille, tableau);
	int colonneFinale=-1;
	
	colonneFinale=rand_a_b(0,7);
	
	if(*tourNumero==1)
	{
		colonneFinale=3;
		cout << "premier tour" << endl;
	}
	else if (*tourNumero==2)
	{
		if(colonneFinale%2==0)
			colonneFinale=4;
		else
			colonneFinale=2;
	 }



	while (!gagneSur && !GrillePleine(tableau))
	{
		gagneSur=true;
	}






	while(ColonnePleine(colonneFinale,tableau))
	{
		colonneFinale=rand_a_b(0,7);
	}

	//laisser ces deux lignes
	(*tourNumero)+=1;
	*posi=colonneFinale;	

	return colonneFinale;





}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool GagneProchainCoup(int grille[6][7], int joueur)
{
	int fausseGrille[6][7];
	CopierContenuTableau(grille,fausseGrille);
	bool miniVictoire=false;
	bool victoire=true;
	for(int i=0; i<7; ++i)
	{
		if(!ColonnePleine(i,fausseGrille))
		{
			PoserJetonn(i,fausseGrille, -joueur);
			if(VictoireAdverse(fausseGrille, joueur))
				return false;

			for(int j=0; j<7; ++j)
			{
				if(!ColonnePleine(j,fausseGrille))
				{
					PoserJetonn(j,fausseGrille, joueur);
					if(Victoire(fausseGrille, joueur))
					{
						miniVictoire=true;
					}
				}
			}
			if(!miniVictoire)
			{
				victoire=false;
			}
			miniVictoire=false;
		}
	}
	return victoire;
}


void calcul(int grille[6][7], int joueur, int grilleBackup[6][7])
{
	int grilleModif[6][7];
	CopierContenuTableau(grille,grilleModif);

	if(!VictoireAdverse(grille,joueur) && !GrillePleine(grille))
	{
		for(int i=0; i<7; i++)
		{
			
		}
	}
}


void CopierContenuTableau(int source[6][7], int cible[6][7])
{
	for(int i=0; i<6; i++)
	{
		for (int j=0; j<7; j++)
		{
			cible[i][j]=source[i][j];
		}
	}
}

bool VictoireAdverse(int grille[6][7],int joueur)
{
	return Victoire(grille, -joueur);
}

bool GrillePleine(int grille[6][7])
{
	bool plein=true;
	for(int i=0; i<7; i++)
	{
		if(!ColonnePleine(i,grille))
		{
			plein=false;
		}
	}

	return plein;
}

void initTableau(Grille *grille,int tableau[6][7])
{
	for(int i=0; i<6; i++)
	{
		for (int j=0; j<7; j++)
		{
			tableau[i][j]=grille->RegarderGrille(i,j);
		}
	}

}




