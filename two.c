#include "two.h"

/*! \file two.c
* \author JM Moreau, A Chemier, R Lhomme
* \date 2004 - 2014
*/

/*! Generation d'un nombre aleatoire entre deux bornes.
* \arg a : borne inferieure
* \arg b : borne superieure.
* \warning verifier que random() retourne bien un entier long entre 0 et RAND_MAX inclus.
*/
double myRandom (double a, double b)
{
	double tmp = random(); /* long int in [0, RAND_MAX] */

	return a+tmp*((b-a)/RAND_MAX);
}

/*! Incantation d'ouverture de fenetre OpenGL */
void winInit()
{
	gluOrtho2D(minX, maxX, minY, maxY);
}

/*! Calcul le determinant de la matrice 3*3 abcdefghi
* \arg a, b, c la premiere ligne de la matrice
* \arg c, d, e la deuxieme ligne de la matrice
* \arg g, h, i la troisieme ligne de la matrice
*/
double determinant(double a, double b, double c,
				double d, double e, double f,
				double g, double h, double i)
{
	return (a * e * i + d * h * c + g * b * f ) - ( g * e * c + a * h * f + d * b * i);
}

/*! Calcul l'orientation polaire des Vertex A, B et C
* \arg A, B et C les trois Vertices dont on veut calculer l'angle
*/
Orientation orientationPolaire(vertex A, vertex B, vertex C)
{
	double det = determinant(1,1,1,
						   A.coords[0],B.coords[0],C.coords[0],
						   A.coords[1],B.coords[1],C.coords[1]);
	if(det < 0) return DROITE;
	else if(det > 0) return GAUCHE;
	else return ALIGNES;
}

/*! Generations des sites */
void selectPoints (void)
{
	int n = nbPoints;

	while (--n >= 0)
	{
		T[n].coords[0] = myRandom(minX+10, maxX-10);
		T[n].coords[1] = myRandom(minY+10, maxY-10);
	}
	Orientation orient = orientationPolaire(T[0],T[1],T[2]);
	if( orient == ALIGNES) 
		selectPoints();
	else if(orient == DROITE) // réorganisation des points dans l'ordre trigo
	{
		vertex tampon = T[1];
		T[1] = T[2];
		T[2] = tampon;
	}
}

/*! Recupere les coordonnées d'un polygone stockées dans un fichier
*
*/
void lireFichier(const char *fichier)
{
	FILE *f;
	if((f = fopen(fichier,"r")) != NULL)
	{
		int i;
		fscanf(f,"%d",&nbFic);
		L = (vertex *) malloc(sizeof(vertex)*nbFic);
		for(i = 0; i< nbFic; i++)
		{
			fscanf(f,"%lf %lf",&L[i].coords[0], &L[i].coords[1]);
		}
		fclose(f);
	}
}

/* Retourne l'indice du min lexicographique des points du fichier dans le tableau */
int minLexicographique()
{
	vertex * minL = &L[0];
	int indice = 0 ;
	
	int i ;
	for(i = 1; i < nbFic; i++) 
	{
		if( (L[i].coords[0] < minL->coords[0]) ||
			((L[i].coords[0] == minL->coords[0]) && (L[i].coords[1] < minL->coords[1])) )
		{
			minL = &L[i]; 
			indice = i ;
		}
	}
	return indice ;
}

/*! Calcul la position des vertices par rapport au triangle
* 
*/
void positionPointsParRapportTriangle(void)
{
	int n = nbPoints;
	
	while (--n >= 3)
	{
		Orientation O1 = orientationPolaire(T[0],T[1],T[n]) ;
		Orientation O2 = orientationPolaire(T[1],T[2],T[n]) ;
		Orientation O3 = orientationPolaire(T[2],T[0],T[n]) ;
		
		if(O1 == DROITE || O2 == DROITE || O3 == DROITE)
			T[n].position = DEHORS; 
		else if(O1 == ALIGNES || O2 == ALIGNES  || O3 == ALIGNES )
			T[n].position = DESSUS; 
		else T[n].position = DEDANS; 
	}
	T[0].position = T[1].position = T[2].position = TRIANGLE ;
}

/*! Determine si le polygone tourne dans le sens horaire ou trigonometrique
*
*/
Sens sensPolygone() 
{
	int minLex = minLexicographique();
	Orientation o = orientationPolaire(L[minLex - 1], L[minLex], L[minLex + 1]);
	if(o == DROITE)
		return HORAIRE ;
	else
		return TRIGONOMETRIQUE ;
}

/*! Affichage.
*\warning Particularite: "callback function", ie pas d'argument transmis... Tout en global, yeurk!
*/
void display(void)
{
	int n = nbPoints;

	glColor3f(0.0, 0.0, 0.0); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_POINTS);

	while (--n >= 0)
	{
		
		switch(T[n].position)
		{
			case TRIANGLE :
				glColor3f(1.0, 1.0, 1.0);
				break;
			case DEDANS :
				glColor3f(0.0, 1.0, 0.0);
				break;
			case DEHORS :
				glColor3f(1.0, 0.0, 0.0);
				break;
			case DESSUS :
				glColor3f(0.0, 0.0, 1.0);
				break;
			default :
				glColor3f(0.0, 0.0, 0.0);
		}
		glVertex2f(T[n].coords[0], T[n].coords[1]);
	}
	glEnd();

	glFlush();
}

/*! \brief Fonction principale: on peut choisir le nombre de points
* en utilisant l'option "-nX" où X est un entier strictement
* positif.
* \remark Mettre opterr a 0 equivaut a supprimer volontairement les messages d'erreur renvoyes par getopt 
* lors de la lecture d'options non prevus sur la ligne de commande. Dans ces cas, l'erreur est traitee grace au
* fait que getopt retourne la valeur '?', qui est donc traitee a part
* \remark "n:" signifie que l'option n s'accompagne de la lecture immediate d'une valeur. Il ne faut pas
* laisser d'espace entre -n et le nombre tape. Exemple: two -n1000.\par
* La lecture est effectuee par un sscanf (lecture d'une chaine supposee formattee) sur l'argument ad hoc, optarg,
* declare dans les routines de lecture de la ligne de commande.
*/
int main(int argc, char **argv)  
{  
	int c;
	
	opterr = 0;
	while ((c = getopt(argc, argv, "n:f:?h")) != EOF)
	{
		switch (c)
		{
			case 'n': 
				if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
					nbPoints = 50;
				break;
			case 'f': 
				if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
					nbPoints = 50;
				break;
			case 'h': 
			case '?': 
				printf("use option -nX or -fX (no space), with 0 < X.\n");
				return EXIT_SUCCESS;  
				break;
			default : printf("Shouldn't be here, really...\n");
				break;
		}
	}
	assert(nbPoints > 0);
	T = (vertex *) malloc(sizeof(vertex)*nbPoints);
	assert(T != NULL);

	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
	glutInitWindowPosition(5,5);  
	glutInitWindowSize(300,300);  
	glutCreateWindow("Triangle");  

	winInit();
	
	lireFichier("coord.txt");
	printf("%d\n",sensPolygone());

	glutDisplayFunc(display);
	glutMainLoop();  

	return EXIT_SUCCESS;  
}  
