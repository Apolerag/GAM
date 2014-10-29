/*! \file main.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>  
#include <math.h>  
#include <time.h>

#include "fenetre.h"
#include "enveloppe.h"


/*! variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/*! bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

int main(int argc, char **argv)  
{  
	int c;
	int nbPoints = 50;
	vertex *v = NULL;
	enveloppe e1,e2;
	initialiseEnveloppe(&e1);
	initialiseEnveloppe(&e2);
	
	opterr = 0;
	while ((c = getopt(argc, argv, "n:")) != EOF)
	{
		switch (c)
		{	
			case 'n': 
				if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
					nbPoints = 50;
				break;
			case 'h': 
			case '?': 
				return EXIT_SUCCESS;  
				break;
			default : printf("Shouldn't be here, really...\n");
				break;
		}
	}

	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
	glutInitWindowPosition(5,5);  
	glutInitWindowSize(700,700);

	glutCreateWindow("fenêtre"); 
	definitionFenetre(0, 700, 0, 700, 10);

	winInit();
	ALLOUER(v,nbPoints);
	selectPoints (v, nbPoints);
	jarvis(v, &e1,nbPoints);
	enveloppeConvexeBrut(v, &e2,nbPoints);


	glutMainLoop(); 
	clearFenetre(v,nbPoints);
	return EXIT_SUCCESS;  


}  	
	
