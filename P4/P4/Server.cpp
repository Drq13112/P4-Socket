
#include <sys/types.h>
#include <sys/sockets.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/errno.h>

int int main(int agrc, char*argv[])
{
	int sockfd,newsockfd,size;

	struct sockaddr_in serv_addr, client_addr;

	

	/*Obtener un descriptor de archivo para el socket*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))< 0)
	{

		perror("error al abrir el socket\n");
		exit(1);
	}
    



	/*funcion que coloca 'n' bits de valor cero en la referncia señalada*/
	void bzero((char*)&serv_addr, sizeof(ser_addr));

	/*Datos del server*/
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	serv_addr.sin_port = htons(SERV_TCP_PORT);

	//En caso de que queramos dar directamente la ip del server
	//serv_addr.sin_addr=htonl(ipaddress);	



	/*Asociar el programa al socket*/
	/*Asocia un socket con una 'socket address structure'(direccion IP y númoer de puerto local)*/
	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
	{
		perror("No se pudo asociar el socket ");
		exit(1);
	}

	/*Aceptacion de conexiones en modo pasivo*/
	/* Pone en modo escucha un TCP socket
	*
	* Avisa al sistema operativo qeu comience la
	* conexion de red. El sistema registrará la conexion
	* de cualquier cliente.
	*
	*/
	listen(sockfd, 5);
	/*
	{
		printf("No se puede oir en el port %d:%s\n", portnum);
		exit(1);
	}
	*/

	while(1)
	{
		printf("esperando conexion\n");
		newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr));
		
		if (newsockfd)
		{
			perror("No se pudo asociar el socket ");
			exit(1);
		}

		read(newsockfd, DATA, sizeof(DATA));//envia la peticion

		write(newsockfd, DATA, sizeof(DATA));//envia el resultado

		close(newsockfd);
	}

	close(sockfd);
	exit(0);
}




