#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "lib2016BM.h"
#include "utils.h"
#include "structure.h"


void DelNewLine(char *Chaine)
{
 Chaine[strlen(Chaine)-1] = 0 ;
}

char ReadChar()
{
 char Tampon[80] ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 return Tampon[0] ;
} 

void MonPrintf(char* tempo, int espace,int taille )
{
 int Count ;
 printf("%s",tempo) ; 
 Count = espace-taille ;
 while ( Count>0 )
 {
       printf(" ");
       Count-- ;
 }
}


void SaiSieRecord(struct Seance *UnRecord )
{
 char Tampon[80] ;
 printf("Saisie Reference :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 UnRecord -> Reference = atoi(Tampon) ;
 printf("Saisie Film :") ;
 fgets(UnRecord->Film,sizeof UnRecord->Film,stdin ) ;
 printf("Saisie r :") ;
 fgets(UnRecord->Realisateur,sizeof UnRecord->Realisateur,stdin ) ;
 
 printf("Saisie Places :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 UnRecord -> Places = atoi(Tampon) ;
 
 DelNewLine(UnRecord->Film) ;
 printf("%d\n",UnRecord->Reference ) ;
 printf("%s\n",UnRecord->Film) ;
 printf("%d\n",UnRecord->Places ) ;
 printf("-----------------------\n") ;
 return ;
}



void CreationAjoutFichier(char *NomFichier,struct Seance  *UnRecord )
{
	FILE *sortie ;
	//char Redo ;
	//int nbr ;

	sortie = fopen(NomFichier,"a") ; /* Si le fichier existe, on le cree sinon on ajoute */
	if ( sortie == NULL )
	{
		fprintf(stderr,"Echec Ouverture\n") ;
		exit(0) ;
	}
	else
		fprintf(stderr,"Ouverture reussie \n") ;
	setvbuf(sortie, (char *)NULL, _IOLBF, 0) ; /* ceci supprime la bufferisation */

	printf("Position actuelle dans le fichier %ld\n",ftell(sortie)) ;
	fwrite(UnRecord,sizeof(struct Seance ),1,sortie) ;
	fflush(sortie) ;
	fclose(sortie) ;
}

void AfficheRecord(struct Seance  *UnRecord)
{
 char Tampon[80] ;
 sprintf(Tampon,"%d",UnRecord->Reference ) ;  MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%s",UnRecord->Film) ;    MonPrintf(Tampon,50,strlen(Tampon)) ;
 sprintf(Tampon, "%s", UnRecord->Realisateur);   MonPrintf(Tampon,30,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UnRecord->Places) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 printf("\n") ;
}

void AfficheFacture(struct Facture *UneFacture)
{
 char Tampon[80] ;
 sprintf(Tampon,"%d",UneFacture->NumeroFacturation ) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%s",UneFacture->NomClient) ; MonPrintf(Tampon,60,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->Places) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->Reference) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->DateFacturation ) ; MonPrintf(Tampon,8,strlen(Tampon)) ;
 
 printf("\n") ;
}

void Listing(char *NomFichier)
{
	struct Seance  UnRecord ;
	FILE *sortie ;
	//char Tampon[80] ;
	//int  Numero ;
	int  nbr ;

	sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
	if ( sortie == NULL )
	{
		fprintf(stderr,"Echec Ouverture\n") ;
		exit(0) ;
	}
	else
		fprintf(stderr,"Ouverture reussie \n") ;


	nbr = fread(&UnRecord,sizeof(UnRecord),1,sortie) ;

	while ( !feof(sortie) )
	{
		fprintf(stderr,"Record lu %d et Position actuelle dans le fichier %ld\n",nbr,ftell(sortie)) ;
		AfficheRecord( &UnRecord) ;
		nbr = fread(&UnRecord,sizeof(UnRecord),1,sortie) ;
	}
	fclose(sortie) ;
}

void ListingFacture(char *NomFichier)
{
	struct Facture UneFacture ;
	FILE *sortie ;
	//char Tampon[80] ;
	//int  Numero ;
	int  nbr ;

	sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
	if ( sortie == NULL )
	{
		fprintf(stderr,"Echec Ouverture\n") ;
		exit(0) ;
	}
	else
		fprintf(stderr,"Ouverture reussie \n") ;


	nbr = fread(&UneFacture,sizeof(struct Facture),1,sortie) ;

	while ( !feof(sortie) )
	{
		fprintf(stderr,"Record lu %d et Position actuelle dans le fichier %ld\n",nbr,ftell(sortie)) ;
		AfficheFacture( &UneFacture) ;
		nbr = fread(&UneFacture,sizeof(struct Facture),1,sortie) ;
	}
	fclose(sortie) ;
}
