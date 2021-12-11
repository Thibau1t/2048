#include"prototype.h"
#include"fonction.c"


int jeu(int ** grilleJeu, int ** grilleJeuPrec) //renvoi le score à la fin de la partie
{
	int continuer = 1; int coupTotal = 0; char lettre = ' '; unsigned long int score = 0; int coupJouer = 0;

	int ** sauv = NULL;
	sauv = initTab2D();
	if(sauv == NULL)
	{
		perror("Probleme allocation mémoire, veuillez relancer le jeu, je ne garantie pas sons bon fonctionnement\n");
		exit(EXIT_FAILURE);
	}

	while(continuer)
	{

		remplieAleatoirement(grilleJeu);
		copieGrille(grilleJeu, sauv);
		coupJouer = 0;
		while(!coupJouer)
		{
			if(contient2048(grilleJeu) == 1)
			{
				printf("\n\nFélicitations vous avez gagné ᕦ( ⊡ 益 ⊡ )ᕤ\n\n");
				goto stop;
			}
			if(coupTotal >= N*N)
			{
				if(bloquer(grilleJeu) == 1)
				{
					printf("\n\nVous avez perdu, peut-être une prochaine fois (｡ŏ﹏ŏ) \n\n");
					goto stop;
				}
			}

			afficheGrille(grilleJeu);
			printf("Voici le coup numéro %d et le score actuel est %ld. \n\nVeuillez saisir votre déplacement ['d','g','h','b','r'] : ", coupTotal, score);
			lettre = saisieLettre();

			switch (lettre)
			{
				case 'd' : 
					copieGrille(grilleJeu, grilleJeuPrec);
					score += deplacementDroite(grilleJeu);
					coupJouer = compareGrille(sauv, grilleJeu);
					break;
				case 'g' :
					copieGrille(grilleJeu, grilleJeuPrec);
					score += deplacementGauche(grilleJeu);
					coupJouer = compareGrille(sauv, grilleJeu);
					break;
				case 'h' : 
					copieGrille(grilleJeu, grilleJeuPrec);
					score += deplacementHaut(grilleJeu);
					coupJouer = compareGrille(sauv, grilleJeu);
					break;
				case 'b' :
					copieGrille(grilleJeu, grilleJeuPrec);
					score += deplacementBas(grilleJeu);
					coupJouer = compareGrille(sauv, grilleJeu);
					break;
				case 'r' :
					copieGrille(grilleJeuPrec, grilleJeu);
					break;
				default :
					printf("Erreur de saisie (dans le switch)\n\n");
					break;
			}
			
		}
		coupTotal++;
	}
	stop : freeTab2D(sauv);
	return score;
}


int main(int argc, char ** argv)
{
	srand(time(NULL));

	int ** grilleJeu = NULL; int ** grilleJeuPrec = NULL;
	grilleJeu = initTab2D(); grilleJeuPrec = initTab2D();
	if (grilleJeu == NULL || grilleJeuPrec == NULL)
	{
		perror("Erreur de l'initialisation du tableau, pointeur == NULL");
		exit(EXIT_FAILURE);
	}

	menu();
	unsigned long int scoreMax = 0;
	scoreMax = recupScoreMax();
	unsigned long int scoreEnCours = 0;

	scoreEnCours = jeu(grilleJeu, grilleJeuPrec);


	if (scoreEnCours > scoreMax)
	{
		printf("Votre score est de %ld, vous avez battu le meilleur score max (%ld)\n", scoreEnCours, scoreMax);
		scoreMax = scoreEnCours;
	}
	else
	{
		printf("Votre score est de %ld, vous n'avez pas battu le meilleur score max (%ld)\n", scoreEnCours, scoreMax);
	}

	ecritScore(scoreMax);


	freeTab2D(grilleJeu); freeTab2D(grilleJeuPrec);
	return EXIT_SUCCESS; 
}