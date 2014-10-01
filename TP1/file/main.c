#include "file_priorite_int.h"
#include <stdio.h>

int main()
{
	file f;
	initialiser_file_defaut_int(&f);

	inserer_file_int(&f, 1);
	afficher_file_int(&f);
	inserer_file_int(&f, 2);
	afficher_file_int(&f);
	inserer_file_int(&f, 3);	
	afficher_file_int(&f);
	inserer_file_int(&f, 4);
	afficher_file_int(&f);
	inserer_file_int(&f, 5);
	afficher_file_int(&f);
	inserer_file_int(&f, 6);
	afficher_file_int(&f);

	printf("%d\n", recupere_element(&f));
	afficher_file_int(&f);
	printf("%d\n", recupere_element(&f));
	afficher_file_int(&f);
	printf("%d\n", recupere_element(&f));
	afficher_file_int(&f);
	
	free_file_int(&f);
	return 0;
}
