#include"prototype.h"
#include"fonction.c"

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