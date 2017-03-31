#ifdef DATAH

#else


#define DATAH

typedef struct Seance 
{ 
	int Reference ;
	char Film[60] ;
	int  Places ;
	int  Salle ;
	char Date[10] ;
	char Realisateur[30];
}Seance;

typedef struct Facture
{
	int NumeroFacturation ;
	char NomClient[60] ;
	int DateFacturation ;
	int Places ;
	int Reference ;
}Facture;  	
#endif
