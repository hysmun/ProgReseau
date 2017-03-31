
typedef enum TypeRequete 
{
   Question = 1 ,
	Achat = 2 ,
	Livraison= 3 ,
	OK = 4,
	Fail = 5
}TypeRequete;

typedef struct Requete
{
	enum TypeRequete Type ;
	int Numero ;
	int NumeroFacture ;
	int Date ;
	int Reference ;
	int Places ;
	int Prix ;
	char Film[80] ;
	char NomClient[80] ;
	char Realisateur[30];
}Requete;
