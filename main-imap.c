/* 
* Instituto Tecnológico de Costa Rica
* Administración de Tecnologías de la Información
* Ataque y Protección de Sistemas Informáticas
* Tarea #3
* Leandro Ulloa Porras / 201001626
* 
*/
/* Socket TCP - IMAP - email.Aol.com server -Port 143. */



#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
   int sock,i; /*id de la conexión Socket-variable temporal de socket */
   struct sockaddr_in servaddr,cliaddr;
   /* Estructura para la dirección  del seridor y  cliente */
   
   
   char cap1[] = "A1 CAPABILITY\n";
   char login[] = "A2 LOGIN cursosapi@aol.com jlup0509\n";
   char cap2[] = "A3 CAPABILITY\n";   
   char select_imbox[] = "A5 SELECT INBOX\n";
   char query[]= "A1 FETCH 1:* BODY.PEEK[HEADER.FIELDS (SUBJECT)]\n";
   char logout[] = "A1 LOGOUT\n";
   /* Mensajes a enviar al socket de conexión al servidor imap */
   
   char buffer[1024];
   /* Buffer de almacamiento de los mensajes recidos por el servidor  */ 


   sock=socket(AF_INET,SOCK_STREAM,0);
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr("64.12.88.129"); /*Aol Server*/
   servaddr.sin_port=htons(143);
   /* Definición de la conexión del socket con el servidor de correo  */
   
   if ((connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr)))<0){
	   printf("Error connect\n");
   } 
   else{ /* si devuelve l1, a conexión de estableció y se realizan 
	      * asignaciones de variables temporales para el envío del
	      * mensaje correspondiente, esto para la  establecimiento
	      * de una sesión de imap al servidor de correo AOL */
	
	/* solicitud de conexión de imap */
    i = send(sock,cap1,strlen(cap1),0); 
    if (i < 0) /* si i es menor que cero, no se estableció conexión*/
         error("ERROR writing to socket");
	/* respuesta de servidor */
    bzero(buffer,256);
    i = read(sock,buffer,255);
    if (i < 0) 
         error("ERROR reading from socket");
    printf("Envia capability: %s\n"); 
    
	
	/* Envío de privilegios de usuarios */
    i = send(sock,login,strlen(login),0);
    if (i < 0) 
         error("ERROR de escritura en socket");
    bzero(buffer,256);
    //respuesta server loggin
    i = read(sock,buffer,255);
    if (i < 0) 
         error("ERROR de lectura desde el socket");
    printf("%s\n",buffer);         
    bzero(buffer,256);
    i = read(sock,buffer,255);
    if (i < 0) 
         error("ERROR de lectura desde el socket");
    printf("%s\n",buffer);
    
	/* Validación de conexión */
    i = send(sock,cap2,strlen(cap2),0);
    if (i < 0) 
         error("ERROR de escritura en socket");
	// respuesta server 
    bzero(buffer,256);
    i = read(sock,buffer,255);
    if (i < 0) 
         error("ERROR de lectura desde el socket");
    printf("\n"); 
    
	/* Solicitud de selección del inbox */
    i = send(sock, select_imbox,strlen(select_imbox),0);
    if (i < 0) 
         error("ERROR de escritura en socket");
    bzero(buffer,256);
    //respuesta server loggin
    i = read(sock,buffer,255);
    if (i < 0) 
         error("ERROR de lectura desde el socket");
    printf("%s\n",buffer);         
    bzero(buffer,256);
    i = read(sock,buffer,255);
    if (i < 0) 
         error("ERROR de lectura desde el socket");
    printf("%s\n",buffer);
    
	/* Solicitud de asuntos de la lista seleccionada de correo */
    i = send(sock,query,strlen(query),0);
    if (i < 0) 
         error("ERROR de escritura en socket");
    bzero(buffer,256);
    //respuesta server consulta
    i = read(sock,buffer,255);
    if (i < 0) 
         error("ERROR de lectura desde el socket");
    printf("\n");         
    bzero(buffer,256);
    i = read(sock,buffer,255);
    if (i < 0) 
         error("ERROR de lectura desde el socket");
    printf("%s\n");
    
    /* Envío de petición de desconexión */
    i = send(sock,logout,strlen(logout),0);
    if (i < 0) 
         error("ERROR de escritura en socket");
    bzero(buffer,256);
    //respuesta server logout
    i = read(sock,buffer,255);
    if (i < 0) 
         error("ERROR de lectura desde el socket");
    printf("%s\n",buffer);         
    bzero(buffer,256);
    i = read(sock,buffer,255);
    if (i < 0) 
         error("ERROR de lectura desde el socket");
    printf("%s\n",buffer);
	}   
     
 }
 
 
 /* 
* Bibliografía de vínculos consultados para la realización de la tarea
*  
* [1] http://www.developpez.net/forums/d517451/c-cpp/c/reseau/
* 	  connexion-imap-c/
* [2] http://stackoverflow.com/questions/10850965/creating-a-tcp-socket
*     -connection-and-keep-the-connection-open-across-several-vie
* [3] http://stackoverflow.com/questions/7698488/turn-a-simple-socket-
*     into-an-ssl-socket
* [3] http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
* [4] https://github.com/dunix/imapC/blob/master/source/main.c
* [5] http://shoe.bocks.com/net/
* [6] http://www.faqs.org/rfcs/rfc3501.html
* [7] http://donsutherland.org/crib/imap
* [8] http://stackoverflow.com/questions/12490648/imap-fetch-subject
* [9] http://stackoverflow.com/questions/11633150/socket
* 	  -read-write-error
* [10]http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html#units
*/
             


   
