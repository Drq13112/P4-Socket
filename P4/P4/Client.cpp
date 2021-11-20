/*
* Ejemplo de cliente de eco sobre el protocolo TCP.
*/


#include "P4.h"
#include <sys/un.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/errno.h>

using namespace std;

#define SERV_TCP_PORT 7000
#define SERV_HOST_ADDR "157.88.188.157"
#define MAXLINE 512


char* pname;
//int argc;
//char argv[];

int main(int argc, char **argv)  
{

	//descriptor referido al socket 
	int sockfd;

	/*
	* Especificaion al otro socket que es una direccion ( cuya longitud
	*  es addrlen) del socket en el espacio de comunicaion 
	*/
	struct sockaddr_in serv_addr;
	struct hostent* server_host;

	if (argc != 2)
	{
		printf("Uso: cliente <direccion_servidor> \n");
		exit(1);
	}

	//Datos que se transnmiten
	char DATA[MAXLINE];

    //Tengo que averiguar que es el pname concretamente, por ahora lo dejo así
	pname = argv[0];

	/*
	* 
	* Creación del socket
	* 
	* 
	* Crea un punto de acceso al canal de comunicación
	* y devuelve un descriptor (mediante un entero) del socket:
	* 
	* int domain->entorno de comunicaciones:
	* 
	* -AF_INET->Familia de protocolos IPv4
	* La familia de protocolos determina el uso de una ruta absoluta Nombre como direccion
	* 
	*-int type->define el tipo de socket->SOCK_STREAM
	* 
	* Protocolo->IPPROTO_TCP
	* 
	* Si hay algún error la funcion socket devuelve -1
	*/
	if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("client: can't open stream socket");
		exit(1);
	}
	
	/*funcion que coloca 'n' bits de valor cero en la referncia señalada*/
    bzero((char*)&serv_addr, sizeof(serv_addr));

	server_host = gethostbyname(agrv[1]);

	memcpy(server_host->h_addr, &serv_addr.sin_addr, server_host->h_length);
	
	/*Datos del server*/
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	serv_addr.sin_port = htons(SERV_TCP_PORT);

	/*
	* 
	* Solitar/iniciar un aconexion con el servidor. Dihca 
	* quedara bloqueada hastaa que el servidor acepte la conexion.
	* 
	* Si no hay servidor que atiend, se obtendra un códifo de error (-1)
	* 
	* Se debe especificar la dirección IP del servidor y el númeor del puerto
	* al que se quiere conectar
	* 
	* Asigna un numero libre de puerto local al socket.  
	* En el caso de un TCP socket, intenta establecer una conexion TCP
	* 
	*/
	if(connect(sockfd,( struct sockaddr_in*)serv_addr, sizeof(serv_addr))<0)
	{
		perror("client: can't connect to server");
		exit(1);
	}

	printf("INTRODUCIR MENSAJE: \n");

	gets(DATA);

	/*
	* Recibir datos a través del descripot del socket
	* El cliente y el servidor deben conocer que datos esperan recibir, 
	* y cuales deben enciar, bajo un formato determinado
	*/
	if ((write(sockfd,DATA, 2*sizeof(int)) < 0)
	{
		perror("writing on stream socket");
		exit(1);
	}
		
	if ((read(sockfd, DATA, sizeof(int) < 0)
	{
		perror("reading stream message");
		exit(1);
	}
			
	printf("eco recibido: %s\n", DATA);
	close(sockfd);
	exit(0);
}

void gets(char *DATA) {

	cin.getline(DATA, MAXLINE);
}