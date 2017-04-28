/*---------------------------------------------------------------
   Vanstapel Herman
   ex02\cli.c

 Le client dit bonjour en utilisant un structure  et
 le serveur fait de même
------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "../udplib/udplib.h"
#include "structure.h"
#include "utils.h"

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
	int rc ;
	int Desc ;
	int tm ;
	int choix;

	u_long  IpSocket , IpServer;
	u_short PortSocket, PortServer ; 

	struct sockaddr_in sthis ; /* this ce programme */
	struct sockaddr_in sos ; /* s = serveur */
	struct sockaddr_in sor ; /* r = remote */
	struct Requete UneRequete ;
	
	

	memset(&sthis,0,sizeof(struct sockaddr_in)) ;
	memset(&sos,0,sizeof(struct sockaddr_in)) ; 
	memset(&sor,0,sizeof(struct sockaddr_in)) ; 

	if (argc!=5)

	{
		printf("cli client portc serveur ports\n") ;
		exit(1) ;
	}

	/* Récupération IP & port   */
	IpSocket= inet_addr(argv[1]);
	PortSocket = atoi(argv[2]);

	IpServer = inet_addr(argv[3]) ;
	PortServer = atoi(argv[4]);

	// Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
	Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);

	if ( Desc == -1 )
		die("CreateSockets:") ; 
	else
		fprintf(stderr,"CreateSockets %d\n",Desc) ;

	sos.sin_family = AF_INET ;
	sos.sin_addr.s_addr= IpServer ;
	sos.sin_port = htons(PortServer) ;
	/* Début partie modifée */

	UneRequete.Type = Question;
	printf("Saisie numero de seance : ");
	scanf("%d",&choix);
	UneRequete.Reference = choix;
		
	/* Fin partie modifée*/

	rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sos ) ;

	if ( rc == -1 )
		die("SendDatagram") ;
	else
		fprintf(stderr,"Envoi de %d bytes\n",rc ) ;

	memset(&UneRequete,0,sizeof(struct Requete)) ;
	tm = sizeof(struct Requete) ;

	rc = ReceiveDatagram( Desc, &UneRequete,tm, &sor ) ;
	if ( rc == -1 )
		die("ReceiveDatagram") ;
	else
	{
		fprintf(stderr,"bytes recus:%d\n",rc) ;
		fprintf(stderr,"Film:%s /t Realisateur:%s/n",UneRequete.Film,UneRequete.Realisateur);
	}	

	close(Desc) ;
	return 1;
}