#include <stdlib.h>

long random(long __num)

{ return(long)((double)(((long)rand()*__num)/((long)((long)RAND_MAX+(long)1)))); }

void cadcpy (char *destino, char *origen) 
{
int n=0;
	while (origen[n]!=0)
	{
	destino[n]=origen[n];
	n++;
	};
	destino[n]=0;
};

void cadcat (char *destino, char *origen)
{
int n=0;
int m=0;
	while (destino[n]!=0)
		n++;
	while (origen[m]!=0)
	{
	destino[n]=origen[m];
	n++;		
	m++;
	};
	destino[n]=0;
};

int cadlen (char *cadena) {
int n=0;
	while (cadena[n]!=0)
		n++;
return n;
};
