/*--------------------------------------
  Herman Vanstapel
  
  ex02\ser.c 
  
  Un serveur recevant une structure 
----------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "../udplib/udplib.h"
#include "structure.h"
#include "data.h"
#include "lib2016BM.h"

void die(char *s);

int main(int argc,char *argv[])
{
	int rc ;
	int Desc ;
	int res;
	struct sockaddr_in sthis ; /* this ce programme */
	struct sockaddr_in sos ; /* s = serveur */
	struct sockaddr_in sor ; /* r = remote */

	u_long  IpSocket ;
	u_short PortSocket ;

	int tm ;
	struct Requete UneRequete ;
	struct Seance UneSeance;

	memset(&sthis,0,sizeof(struct sockaddr_in)) ;
	memset(&sos,0,sizeof(struct sockaddr_in)) ; 
	memset(&sor,0,sizeof(struct sockaddr_in)) ; 

	printf("Ceci est le serveur\n") ;
	if ( argc!=3)
	{
		printf("ser ser port cli\n") ;
		exit(1) ;
	}

	/* Récupération IP & port   */
	IpSocket= inet_addr(argv[1]);
	PortSocket = atoi(argv[2]);
	// Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
	Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);

	if ( Desc == -1 )
		die("CreateSockets:") ;
	else
		fprintf(stderr,"CreateSockets %d\n",Desc) ;
	while(1)
	{
		tm = sizeof(struct Requete) ;
		rc = ReceiveDatagram( Desc,&UneRequete ,tm, &sor ) ;
		if ( rc == -1 )
			die("ReceiveDatagram") ;
		else
			fprintf(stderr,"bytes recus:%d Reference :%d\n",rc,UneRequete.Reference ) ;

		printf("Type recu %d\n", UneRequete.Type) ;
		res = Recherche("Seances",UneRequete.Reference,&UneSeance);
		if(res == 1)
			fprintf(stderr,"res:%d -- Reference:%s\n",res,UneSeance.Film);
		else
			exit(1);
		/* attention l'enum peut être codé en short */
		/* reponse avec psos */

		/* Début partie modifiée*/
		
		UneRequete.Type = OK ;
		strcpy(UneRequete.Film,UneSeance.Film);
		strcpy(UneRequete.Realisateur,UneSeance.Realisateur);
		
		/* Fin partie modifiée*/
		rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sor ) ;
		if ( rc == -1 )
			die("SendDatagram:") ;
		else
			fprintf(stderr,"bytes envoyes:%d\n",rc ) ;

	}

	close(Desc) ;
	return 1;
}

void die(char *s)
{
    perror(s);
    exit(1);
}
