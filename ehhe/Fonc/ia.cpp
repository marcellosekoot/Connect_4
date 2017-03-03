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


//void PoserJetonn(int colonne, int grille[6][7] ,int joueur);
//bool Victoire(int grille[6][7], int joueur);
//bool ColonnePleine(int colonne, int grille[6][7]);
//bool ColonnePleineMoins1 (int colonne, int grille[6][7]);
void Recap (int numero, bool colonnesEviter[7], bool colonnesEviter2[7], bool colonnesViser[7], bool stop, int colonneFinale,bool ColonneViser2[7], bool colonnesEviter3[7]);
//int DetecterLignesLibres(int colonne, int grille[6][7]);


int IAJoue(int joueur, Grille *grille, int *tourNumero,int *posi)
{
	int colonneFinale=-1;
	int nouvelleGrille[6][7];
	bool colonnesAEviter[7];
	for(int i=0; i<7; i++)
	{
		colonnesAEviter[i]=false;
	}
	bool colonnesAEviter2[7];
	for(int i=0; i<7; i++)
	{
		colonnesAEviter2[i]=false;
	}
	bool stop=false;
	int colonnesVictorieuses = 0;
	bool colonnesAViser[7];
	for(int i=0; i<7; i++)
	{
		colonnesAViser[i]=false;
	}
	bool colonnesAViser2[7];
	for(int i=0; i<7; i++)
	{
		colonnesAViser2[i]=false;
	}
	bool colonnesAEviter3[7];
	for(int i=0; i<7; i++)
	{
		colonnesAEviter3[i]=false;
	}



//	sleep(milliseconds(150));

//premiers tours

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


//
//DETECTION
//

	cout << "#############################################################" << endl;



//test pour gagner si 3 alignes
	for (int r=0; r<7; r++)
	{
//reinitiaisation
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
//test pour eviter les erreurs de segmentation
		if(!ColonnePleine(r,nouvelleGrille))
		{
//simulation d'ajout d'un jeton
			PoserJetonn(r, nouvelleGrille, joueur);
//test des colonne pour chercher la victoire
			if(Victoire(nouvelleGrille,joueur))
			{
				colonneFinale=r;
			}
		}
	}

	Recap(1,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//Test pour que l'adversaire ne gagne pas si 3 alignes
	if(colonneFinale<0)
	{
		for (int r=0; r<7; r++)
		{
			for(int i=0; i<6; i++)
			{
				for (int j=0; j<7; j++)
				{
					nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
				}
			}
			if(!ColonnePleine(r,nouvelleGrille))
			{
				PoserJetonn(r, nouvelleGrille, -(joueur));
				if(Victoire(nouvelleGrille,-(joueur)))
				{
					colonneFinale=r;
				}
			}
		}
	}

	Recap(2,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);


//Test pour que l'adversaire ne pas permettre a l'adversaire d'en avoir 3 alignes en rajoutant au dessus
	if(colonneFinale<0)
	{
		for (int r=0; r<7; r++)
		{
			for(int i=0; i<6; i++)
			{
				for (int j=0; j<7; j++)
				{
					nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
				}
			}
			if(!ColonnePleineMoins1(r,nouvelleGrille))
			{
				PoserJetonn(r, nouvelleGrille, joueur);
				PoserJetonn(r, nouvelleGrille, -(joueur));
				if(Victoire(nouvelleGrille,-(joueur)))
				{
					colonnesAEviter[r]=true;
				}
			}
		}
	}



	Recap(3,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//Test pour faire un double coup

	if(colonneFinale<0)
	{
		for (int r=0; r<7; r++)
		{
			for(int ri=0; ri<7; ri++)
			{
				for(int jhum=0; jhum<7; jhum++)
				{
					for(int i=0; i<6; i++)
					{
						for (int j=0; j<7; j++)
						{
							nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
						}
					}

					if(!ColonnePleine(r,nouvelleGrille))
					{
						PoserJetonn(r, nouvelleGrille, joueur);

						if(!ColonnePleine(ri, nouvelleGrille))
						{
							PoserJetonn(ri, nouvelleGrille, -(joueur));

							if(!ColonnePleine(jhum,nouvelleGrille))
							{
								PoserJetonn(jhum,nouvelleGrille,joueur);

								if(Victoire(nouvelleGrille,joueur))
								{
									colonnesVictorieuses++;
								}
							}
						}
					}
				}
				if(colonnesVictorieuses>=2)
					colonnesAViser[r]=true;
				colonnesVictorieuses=0;
			}
		}
	}


	Recap(4,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);



//Test pour eviter de permettre le double victoire adverse au prochain coup

	if(colonneFinale<0)
	{
		for (int r=0; r<7; r++)
		{
			for(int ri=0; ri<7; ri++)
			{
				for(int jhum=0; jhum<7; jhum++)
				{
					for(int i=0; i<6; i++)
					{
						for (int j=0; j<7; j++)
						{
							nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
						}
					}

					if(!ColonnePleine(r,nouvelleGrille))
					{
						PoserJetonn(r, nouvelleGrille, joueur);

						if(!ColonnePleine(ri, nouvelleGrille))
						{
							PoserJetonn(ri, nouvelleGrille, -(joueur));

							if(!ColonnePleine(jhum,nouvelleGrille))
							{
								PoserJetonn(jhum,nouvelleGrille,-(joueur));

								if(Victoire(nouvelleGrille,-(joueur)))
								{
									colonnesVictorieuses++;
								}
							}
						}
					}
				}
				if(colonnesVictorieuses>=2)
					colonnesAEviter2[r]=true;
				colonnesVictorieuses=0;

			}
		}
	}


	Recap(5,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//Test pour ne pas permettre a l'adversaire de bousiller nos 3 alignes
	if(colonneFinale<0)
	{
		for (int r=0; r<7; r++)
		{
			for(int i=0; i<6; i++)
			{
				for (int j=0; j<7; j++)
				{
					nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
				}
			}
			if(!ColonnePleineMoins1(r,nouvelleGrille))
			{
				PoserJetonn(r, nouvelleGrille, -(joueur));
				PoserJetonn(r, nouvelleGrille, joueur);
				if(Victoire(nouvelleGrille,joueur))
				{
					colonnesAEviter3[r]=true;
				}
			}
		}
	}



//Test pour empecher l'adversaire de se faire deux jetons gagnants d'affile sur la meme rangee
	Recap(50,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

	cout << "a " << endl;

	if(colonneFinale<0)
	{
		for (int a=0; a<7; a++)
		{
			if(!ColonnePleine(a,nouvelleGrille))
			{
				int nbVictoires;
				int nbLignesDispo;
				int g;
				for(int b=0; b<7; b++)
				{
					if(!ColonnePleine(b,nouvelleGrille))
					{
//remise des variables a 0
						nbVictoires=0;
						g=0;
						cout << " b" << endl;

//detection lignes dispo sur colonne b
						nbLignesDispo = DetecterLignesLibres(b,nouvelleGrille);

//		sleep(milliseconds(1));
						cout << "bb " << endl;
						if(a==b) nbLignesDispo--;
						cout << "nombrelignesdispo : " << nbLignesDispo << endl;
						while(g<=nbLignesDispo-2)	//LE WHILE ICI
						{
//		sleep(milliseconds(1));
							cout << "c " << endl;
//init grille
							for(int i=0; i<6; i++)
							{
								for (int j=0; j<7; j++)
								{
									nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
								}
							}

//		sleep(milliseconds(1));
							cout << " d" << endl;
//pose du jeton adverse sur colonne a
							PoserJetonn(a,nouvelleGrille,-(joueur));

//		sleep(milliseconds(1));
							cout << "e " << endl;
//pose des x jetons
							for(int h=g; h>1; h--)
							{
								PoserJetonn(b,nouvelleGrille, joueur);
							}
							g++;

//		sleep(milliseconds(1));
							cout << " f" << endl;
//jeton mechant
							PoserJetonn(b,nouvelleGrille,-(joueur));

//		sleep(milliseconds(1));
							cout << "g " << endl;
//testGain
							if(Victoire(nouvelleGrille,-(joueur)))
								nbVictoires++;

//		sleep(milliseconds(1));
							cout << " h" << endl;
//init
							for(int i=0; i<6; i++)
							{
								for (int j=0; j<7; j++)
								{
									nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
								}
							}

//		sleep(milliseconds(1));
							cout << "i " << endl;
//le jeton adverse
							PoserJetonn(a,nouvelleGrille, -(joueur));
//
//		sleep(milliseconds(1));
							cout << " j" << endl;
//les x+1 jetons alies
							for(int h=g; h>1; h--)
							{
								PoserJetonn(b,nouvelleGrille, joueur);
							}

//		sleep(milliseconds(1));
							cout << "k " << endl;
//jeton mechant
							PoserJetonn(b,nouvelleGrille,-(joueur));

//		sleep(milliseconds(1));
							cout << " l" << endl;
//testGain
							if(Victoire(nouvelleGrille,-(joueur)))
								nbVictoires++;

//		sleep(milliseconds(1));
							cout << "m " << endl;
//si 2 gains, viser la colonne a
							if(nbVictoires==2)
								colonnesAViser2[a]=true;

//		sleep(milliseconds(1));
							cout << " n" << endl;
//mise a jour des variables
							nbVictoires=0;
						}
					}
				}
			}
		}
	}



//
//PLACEMENT
//


//1/ eviter de faire gagner l'adversaire directement
//2/ eviter de faire gagner l'adversaire en double coup au tour suivant
//3/ test pour faire un double coup
//4/ test pour eviter que l'adversaire ne se fasse une double triple alignee gagnable sur la meme rangee
//5/ test pour eviter que l'adversaire ne bousille notre triple aligne

//1/ Eviter
//2/ Eviter2
//3/ Viser
//4/ Viser2
//5/ Eviter3


	Recap(12345,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+2+3+4+5
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || colonnesAEviter2[colonneFinale] || !colonnesAViser[colonneFinale] || !colonnesAViser2[colonneFinale] || colonnesAEviter3[colonneFinale]) && !stop);
	}

	Recap(1234,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+2+3+4
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || colonnesAEviter2[colonneFinale] || !colonnesAViser[colonneFinale] || !colonnesAViser2[colonneFinale]) && !stop);
	}

	Recap(1235,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+2+3+5
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || colonnesAEviter2[colonneFinale] || !colonnesAViser[colonneFinale] || colonnesAEviter3[colonneFinale]) && !stop);
	}

	Recap(123,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+2+3
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || colonnesAEviter2[colonneFinale] || !colonnesAViser[colonneFinale]) && !stop);
	}


	Recap(1245,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+2+4+5
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || colonnesAEviter2[colonneFinale] || !colonnesAViser2[colonneFinale] || colonnesAEviter3[colonneFinale]) && !stop);
	}

	Recap(124,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+2+4
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || colonnesAEviter2[colonneFinale] || !colonnesAViser2[colonneFinale]) && !stop);
	}

	Recap(125,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+2+5
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || colonnesAEviter2[colonneFinale] || colonnesAEviter3[colonneFinale]) && !stop);
	}

	Recap(12,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+2
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || colonnesAEviter2[colonneFinale]) && !stop);
	}

	Recap(1345,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+3+4+5
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || !colonnesAViser[colonneFinale] || !colonnesAViser2[colonneFinale] || colonnesAEviter3[colonneFinale]) && !stop);
	}

	Recap(134,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+3+4
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || !colonnesAViser[colonneFinale] || !colonnesAViser2[colonneFinale]) && !stop);
	}

	Recap(135,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+3+5
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || colonnesAEviter2[colonneFinale] || !colonnesAViser[colonneFinale] ) && !stop);
	}

	Recap(13,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+3
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || !colonnesAViser[colonneFinale]) && !stop);
	}

	Recap(145,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+4+5
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || !colonnesAViser2[colonneFinale] || colonnesAEviter3[colonneFinale]) && !stop);
	}

	Recap(14,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+4
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || !colonnesAViser2[colonneFinale]) && !stop);
	}

	Recap(15,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1+5
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille) || colonnesAEviter3[colonneFinale]) && !stop);
	}

	Recap(111,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//1
	if(colonneFinale<0)
	{
		stop=false;
		for(int i=0; i<6; i++)
		{
			for (int j=0; j<7; j++)
			{
				nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
			}
		}
		int compteur=0;
		do
		{
			compteur++;
			if (compteur>3000)
			{
				stop = true;
				colonneFinale=-1;
			}
			else colonneFinale=rand_a_b(0,7);
		}
		while ( (colonnesAEviter[colonneFinale] || ColonnePleine(colonneFinale,nouvelleGrille)) && !stop);
	}

	Recap(101,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

//reinitialisation grille
	for(int i=0; i<6; i++)
	{
		for (int j=0; j<7; j++)
		{
			nouvelleGrille[i][j]=grille->RegarderGrille(i,j);
		}
	}

//placement par defaut
	stop = false;
	if(colonneFinale<0)
	{
		int a=0;
		do
		{
			colonneFinale=rand_a_b(0,7);
			a++;
			if(a>1000) stop=true;
		}
		while(ColonnePleine(colonneFinale,nouvelleGrille)&& !stop);
	}


	Recap(0,colonnesAEviter,colonnesAEviter2,colonnesAViser,stop,colonneFinale,colonnesAViser2,colonnesAEviter3);

		(*tourNumero)+=1;
		*posi=colonneFinale;	
		return colonneFinale;

}

////////////////////////////////////////////////////////////////////////////////




void Recap (int numero, bool colonnesEviter[7], bool colonnesEviter2[7], bool colonnesViser[7], bool stop, int colonneFinale, bool colonnesViser2[7], bool colonnesEviter3[7])
{
	cout << "//////////////////////////////////////////////////////////////////////////" << endl << endl;

	cout << "recap numero " << numero << endl;
	for (int i=0; i<7; i++)
	{
		cout << "Colonne a éviter " << i << "  " <<colonnesEviter[i] << endl;
	}
	for (int i=0; i<7; i++)
	{
		cout << "Colonne a éviter2 " << i << "  " << colonnesEviter2[i] << endl;
	}
	for (int i=0; i<7; i++)
	{
		cout << "Colonne a viser " << i << "  " << colonnesViser[i] << endl;
	}
	for (int i=0; i<7; i++)
	{
		cout << "Colonne a viser2 " << i << "  " << colonnesViser2[i] << endl;
	}
	for (int i=0; i<7; i++)
	{
		cout << "Colonne a éviter3 " << i << "  " << colonnesEviter3[i] << endl;
	}

	cout << "stop : " << stop << endl;
	cout << "colonneFinale = " << colonneFinale << endl ;
}



