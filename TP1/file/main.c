#include "file_priorite_int.h"
#include <stdio.h>

int main()
{
	file f;
	initialiserFileDefautInt(&f);

	insererFileInt(&f, 1);
	afficherFileInt(&f);
	insererFileInt(&f, 2);
	afficherFileInt(&f);
	insererFileInt(&f, 3);	
	afficherFileInt(&f);
	insererFileInt(&f, 4);
	afficherFileInt(&f);
	insererFileInt(&f, 5);
	afficherFileInt(&f);
	insererFileInt(&f, 6);
	afficherFileInt(&f);

	printf("%d\n", recupereElement(&f));
	afficherFileInt(&f);
	printf("%d\n", recupereElement(&f));
	afficherFileInt(&f);
	printf("%d\n", recupereElement(&f));
	afficherFileInt(&f);
	
	freeFileInt(&f);
	return 0;
}
