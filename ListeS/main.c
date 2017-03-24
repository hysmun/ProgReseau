#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../dnslib/dnslib.h"

struct Data {
             int Compteur ;
	     char Message[80] ;
} ;


void list_print (sll_s * p_l)
{
int i;
int size = sll_sizeof (p_l);
sll_first (p_l);
for (i = 0; i < size; i++)
{
if (sll_data (p_l) != NULL)
{
   struct Data *pData ;
   pData = ( struct Data *) sll_data (p_l) ;
   printf ("%d %s\n", pData->Compteur , pData->Message );
}
sll_next (p_l);
}
printf ("\n");
}

int main (void)
{
sll_s *p_sll = NULL;
struct Data *pData ;
int Compteur ;

Compteur = 0 ;
printf ("\t-- Initialisation --\n");
p_sll = sll_new ();
list_print (p_sll);
printf ("\n\t-- Insertion --\n");
{
int i;
for (i = 0; i < 4; i++)
{
 pData = (struct Data * ) malloc( sizeof(struct Data) ) ;
 pData->Compteur++ ;
 strcpy(pData->Message,"coucou") ;
 sll_insert (p_sll, pData ) ;
}
}
list_print (p_sll);
printf ("\n\t-- Suppression --\n");
sll_removeFirst (p_sll);
list_print (p_sll);
printf ("\n\t-- Destruction --\n");
sll_delete (&p_sll);
list_print (p_sll) ;
return EXIT_SUCCESS;
}

