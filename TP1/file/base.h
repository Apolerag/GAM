#define ALLOUER(X,NB) X = malloc(sizeof(*(X)) * (NB))


#ifndef ABS
#define ABS(A) ( (A)>=0 ? (A) : -(A) )
#endif

#ifndef MAX
#define MAX(A,B) ( (A)>=(B) ? (A) : (B) )
#endif
