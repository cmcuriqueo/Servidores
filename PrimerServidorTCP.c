#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PORTNUMBER  12345

int
main(void)
{
	char buf[10];
	int s, n, ns, len;
	struct sockaddr_in direcc;

	/* Crea un socket. */
	s = socket(AF_INET, SOCK_STREAM, 0);

	/* Crea la direccion del servidor. */
	bzero((char *) &direcc, sizeof(direcc));
	direcc.sin_family = AF_INET;
	direcc.sin_port = htons(PORTNUMBER);
	direcc.sin_addr.s_addr = htonl(INADDR_ANY); /* Usa la wildcard address.*/
	len = sizeof(struct sockaddr_in);

	/* Hago el bind del socket con la direccion. */
	if( bind(s, (struct sockaddr *) &direcc, len))
		printf("bind error");

	/* Cuantos pedidos de conexion puedo encolar.  */
	listen(s, 5);
    
	while(1){//para que no finalice la ejecucion cuando se cierre la conexion
		/* Espero y Acepto una conexion.  */
		ns = accept(s, (struct sockaddr *) &direcc, &len);

		/* Leo desde el socket hasta un end-of-file e
		 * imprimo en la salida estandar.  */
		printf("Connection from : %s\n",inet_ntoa(direcc.sin_addr));

		while ((n = recv(ns, buf, sizeof(buf), 0)) > 0){
			write(ns, buf, n);//para servidor de eco (Cliente)
			//write(1, buf, n) para imprimir por pantalla (Servido)
		}
		close(ns);
	}
	close(s);
	exit(0);
}
