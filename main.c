#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 4 // taille de la grille 4*4 par deefault

int ** initTab2D(int taille)
{
	int ** tab = NULL;
	tab = malloc(taille*sizeof(int *));
	if(tab == NULL)
	{
		return NULL;
	}

	int i = 0; int j =0;
	for(i=0; i<taille; i++)
	{
		tab[i] = (int *) calloc(taille,sizeof(int));
		if(tab[i] == NULL)
		{
			for(j=0; j<i; j++)
			{
				free(tab[j]);
			}
			return NULL;
		}
	}
	return tab;
}

void afficheGrille(int ** tab, int taille)
{
	int i = 0 ; int j = 0;

	for(i=0; i<taille; i++)
	{
		for(j=0; j<taille; j++)
		{
			printf("|%8d  ", tab[i][j]);
		}
		printf("|\n");
	}
	printf("\n");
}

void remplieAleatoirement(int ** tab, int taille)
{
	int i = 0; int j = 0; int reussi = 0; int val = 0;

	while( !(reussi) )
	{
		i = rand()%taille;
		j = rand()%taille;
		if (tab[i][j] == 0)
		{
			val = rand()%2;
			if(val == 0)
			{
				val = 2; 
			}
			else
			{
				val = 4;
			}
			tab[i][j] = val;
			reussi = 1;
		}
	}
}

void copieGrille(int ** tabDep , int ** tabArr, int taille)
{
	int i=0; int j =0;
	for(i=0; i<taille; i++)
	{
		for(j=0; j<taille; j++)
		{
			tabArr[i][j] = tabDep[i][j];
		}
	}
}


void deplacementDroitCaseVide(int ** tab, int taille) //intermediare
{
	int i =0; int j =0; int deplacement = 0;
	while(!(deplacement))
	{
		deplacement = 1;
		for(i=0; i<taille; i++)
		{
			for(j=0; j<taille-1; j++) // -1 car dernière colonne pas de deplacement à droite
			{
				if(tab[i][j] != 0 && tab[i][j+1] == 0)
				{
					tab[i][j+1] = tab[i][j];
					tab[i][j] = 0;
					deplacement = 0;
				}
			}
		}
	}
}

int deplacementDroit(int ** tab, int taille) // fonction finale de deplacement
{
	// gere les cases vides
	deplacementDroitCaseVide(tab, taille);

	int i =0; int j =0; int score = 0;
	// même case cote à cote
	for(i=0; i<taille; i++)
	{
		for(j=taille-1; j>=0 ; j--)
		{
			if(tab[i][j] == tab[i][j-1])
			{
				tab[i][j] *= 2;
				score += tab[i][j];
				tab[i][j-1] = 0;
			}
		}
	}
	//re-decalle les nouvelles cases vides
	deplacementDroitCaseVide(tab, taille);
	return score;
}


int partieFinie(int ** tab, int taille) // retourn 1 si fini sinon 0
{
	int i = 0 ; int j = 0 ;

	for(i=0; i<taille; i++)
	{
		for(j=0; j<taille; j++)
		{
			if(tab[i][j]==2048)
			{
				return 1;
			}
		}
	}
	return 0;
}

void freeTab2D(int ** tab , int taille)
{
	if (tab != NULL)
	{
		int i = 0;
		for(i=0; i<taille; i++)
		{
			if(tab[i] != NULL)
			{
				free(tab[i]);
				tab[i] = NULL;
			}
		}
		free(tab); tab = NULL;
	}
}

void rotaD(int ** tab, int taille) // rota de 90° vers la droite
{
	int ** sauv = NULL;
	sauv = initTab2D(taille);

	if(sauv == NULL)
	{
		perror("Probleme rotation, le jeu peu planter suite à un probleme d'allocation mémoire (plus de place certainement) ... Veuillez relancez le jeu s'il vous plaît \n");
	}

	copieGrille(tab, sauv, taille);

	int i = 0; int j = 0;
	for (i = 0; i < taille; i++) 
	{
    	for (j = 0; j < taille; j++) 
    	{
      		tab[i][j] = sauv[j][i];
    	}
  	}

  	int sauvInt = 0;

  	for (i = 0; i < taille; ++i) 
  	{
    	for (j = 0; j < taille/2; ++j) 
    	{
    		sauvInt = tab[i][j];
    		tab[i][j] = tab[i][taille-1-j];
    		tab[i][taille-1-j] = sauvInt;
	  	}
  	}

	freeTab2D(sauv, taille);
}


int main(int argc, char ** argv)
{
	srand(time(NULL));

	int ** grilleJeu = NULL; int ** grilleJeuPrec = NULL;
	grilleJeu = initTab2D(N); grilleJeuPrec = initTab2D(N);
	if (grilleJeu == NULL || grilleJeuPrec == NULL)
	{
		perror("Erreur de l'initialisation du tableau, pointeur == NULL");
		exit(EXIT_FAILURE);
	}



	grilleJeu[1][1] = 2;
	grilleJeu[1][2] = 2;
	grilleJeu[1][3] = 4;
	grilleJeu[0][1] = 4;
	grilleJeu[0][2] = 4;
	grilleJeu[2][0] = 4;
	grilleJeu[2][1] = 4;
	grilleJeu[2][2] = 4;
	grilleJeu[2][3] = 4;
	int score = 0;
	afficheGrille(grilleJeu, N);
	score += deplacementDroit(grilleJeu, N);
	afficheGrille(grilleJeu, N);
	score += deplacementDroit(grilleJeu, N);
	afficheGrille(grilleJeu, N);
	printf("Score = %d\n", score);

	rotaD(grilleJeu , N);
	afficheGrille(grilleJeu, N);



	freeTab2D(grilleJeu, N); freeTab2D(grilleJeuPrec, N);
	return EXIT_SUCCESS; 
}