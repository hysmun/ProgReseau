
enum TypeRequete {
       Question = 1 ,
       Reponse  = 2,
       Livraison = 3,
       OK = 4,
       Fail = 5
     } ;

struct Requete
{
  enum TypeRequete Type ;
  char Message[40] ; 
} ; 
