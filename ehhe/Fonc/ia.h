#ifndef H_GL_IA
#define H_GL_IA


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "fonctions.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

void PoserJetonn(int colonne, int grille[6][7] ,int joueur); //pose le jeton de la couleur "joueur" sur un tableau
bool Victoire(int grille[6][7], int joueur); //detecte la victoire sur le tableau
bool ColonnePleine(int colonne, int grille[6][7]); //renvoie true si la colonne est pleine
bool ColonnePleineMoins1 (int colonne, int grille[6][7]);
int DetecterLignesLibres(int colonne, int grille[6][7]); // detecte combien de placer il reste sur la colonne envoyee en parametre 





int DetecterLignesLibres(int colonne, int grille[6][7])
{
        int nb=0;
        int x=0;

        while( x<5 && grille[x][colonne]==0)
        {
                x++;
                nb++;
        }

        return nb;
}



bool ColonnePleine(int colonne, int grille[6][7])
{
        return (grille[0][colonne]!=0);
}

bool ColonnePleineMoins1 (int colonne, int grille[6][7])
{
        bool var=false;
        if (grille[1][colonne]!=0) var = true;
        return var;
}

void PoserJetonn(int colonne, int grille[6][7] ,int joueur)
{
        bool pose=false;
        int ligne = 5;
        while (pose == false)
        {
                if(grille[ligne][colonne] == 0)
                {
                        grille[ligne][colonne] = joueur;
                        pose=true;
                }
                else
                {
                        ligne--;
                }
        }

}


bool Victoire(int grille[6][7], int joueur)
{

        bool alignes=false;
        int nbAlignes=0;

        //verification horizontale
for (int i=0; i<=5; i++)
        {
                for (int j=0; j<=6; j++)
                {
                        if(grille[i][j] == joueur)
                        {
                                nbAlignes++;
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
                        if(grille[j][i] == joueur)
                        {
                                nbAlignes++;
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
                        if(grille[ii][iibase-ii] == joueur)
                        {
                                nbAlignes++;
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
                        if(grille[ii+iibase][6-ii] == joueur)
                        {
                                nbAlignes++;
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
                        if(grille[ii][ii+iibase] == joueur)
                        {
                                nbAlignes++;
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
                        if(grille[5-ii][iibase-ii] == joueur)
                        {
                                nbAlignes++;
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


        return alignes;
}




#endif











