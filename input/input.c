#include <stdio.h>
#include <unistd.h>
#include <termios.h>

main()
{
 char  tampon[80] ;
 int val ;
 while(1)
 {
  printf("Saisie chaine") ;
  fgets( tampon, sizeof(tampon) , stdin );
  printf("Saisie entier:") ;
  tcflush(0 , TCIFLUSH ) ;
  scanf("%d",&val) ;
  printf("Le résultat est %s , %d \n", tampon,val) ;
  tcflush(0 , TCIFLUSH ) ;
 }
}
