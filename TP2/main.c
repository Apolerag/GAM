/*! \file main.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>  
#include <math.h>  

#include "fenetre.h"


/*! variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/*! bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

int main(int argc, char **argv)  
{  

	int c;
	int pol;
	int option1 = 0, option2 = 0, option3 = 0;
	
	opterr = 0;
	while ((c = getopt(argc, argv, "1i:2o:3")) != EOF)
	{
		switch (c)
		{
			case '1': 
				option1 = 1;
				break;
			case '2': 
				option2 = 1;
				break;
			case '3': 
				option3 = 1;
				break;
			case 'o': /*verifier non null*/
				out = optarg;
				break;
			case 'i': /*verifier non null*/
				in = optarg; 
				break;
			case 'h': 
			case '?': 
				printf("-1 partie 1 du tp\n");
				printf("-2 partie 2 du tp\n");
				printf("-3 partie 3 du tp\n");
				printf("-ichaine ouvre le fichier \"chaine\" en lecture \n");
				printf("-ochaine ouvre le fichier \"chaine\" en écriture \n");
				return EXIT_SUCCESS;  
				break;
			default : printf("Shouldn't be here, really...\n");
				break;
		}
	}

	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
	glutInitWindowPosition(5,5);  
	glutInitWindowSize(500,500);

	glutCreateWindow("fenetre"); 
	definitionFenetre(0, 500, 0, 500, 10);
	winInit();
	//glutDisplayFunc(display);	

	if(option1 && out != NULL)
	{
		glutMouseFunc(coordonnesPoint);
		ecrireFichier(out, &P);
	}
	else if(option2 && in != NULL)
	{
		lireFichier(in, &P);
		assert(P.p != NULL);
		pol = controlePolygoneSimple();
		printf("controlePolygoneSimple : %d\n", pol);
		//glutDisplayFunc(displayPolygone);
	}

	glutMainLoop(); 
  
	clearFenetre();
	return EXIT_SUCCESS;  
}  	
