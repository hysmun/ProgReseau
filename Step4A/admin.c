/******************************************
  Herman Vanstapel
  2014 Basé sur Fichiers
*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "lib2016BM.h"
#include "utils.h"

/****************************
*
*				MAIN
*
*
*****************************
*/

int main()
{
	char Choix ;
	//char Tampon[80] ;
	//int res ;
	struct Seance  UnRecord ;
	int Numero ;
	while(1)
	{
		printf("----------------------\n") ;
		printf("1) Ajout              \n") ;
		printf("2) Seances              \n") ;  
		printf("3) Recherche          \n") ;   
		printf("4) Achat              \n") ;  
		printf("5) Factures           \n") ;
		printf("6) A propos           \n") ;
		printf("7) exit               \n") ; 
		printf("----------------------\n") ; 
		Choix=ReadChar() ;
		switch(Choix)
		{
			case '1': 
			{
				struct Seance  UnRecord ;
				//FILE *sortie ;
				char Redo ;

				Redo='y' ;
				while ( Redo=='Y' || Redo=='y')
				{
					SaiSieRecord(&UnRecord ) ;
					CreationAjoutFichier("Seances",&UnRecord) ; 
					printf("Encoder un autre (Y/N) ?)") ;
					Redo=ReadChar() ;
				}
				break ;	
			}
			case '2': 
				Listing("Seances") ;
				break ;
			case '3': printf("Saisie Reference:");
				fflush(stdin);
				scanf("%d",&Numero);
				Recherche("Seances",Numero,&UnRecord);
				AfficheRecord(&UnRecord);
				break;
			case '4':
				ListingAchat("Achats");
			case '5': 
				ListingFacture("Facture") ;
				break ;
			case '6': 
				APropos("Step 2","Brajkovic Antoine","Mauhin Remy") ;
				break ;
			case '7': 
				exit(0) ; 
		}
	}
	return 1;
}








