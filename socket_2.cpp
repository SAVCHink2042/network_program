#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/socket.h> // for socket
#include <sys/types.h>
#include <netinet/in.h> // sockaddr_in
#include <unistd.h> // for close
#include <arpa/inet.h> // for inet_aton
#include <netdb.h> // for gethostbyname



int hx_connect_v4(const char * ip, int port)
{
  int sock, res;
  struct sockaddr_in addr;
  struct hostent *host = NULL;

  // fill structure for input
  memset(&addr, 0, sizeof(addr));
  host = gethostbyname(ip);
  if (host == NULL) {
    return -3;
  }
  // Write resolved IP address of a server to the address structure
  memcpy(&(addr.sin_addr.s_addr), host->h_addr_list[0], 4);
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;

  // create socket for TCP connection
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    return -1;
  }

  // connect socket with the remote address
  res = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  if ( res < 0 ) {
     close(sock);
     return -2;
  }

  return sock;
}


int main(void) {
  char buf[12];
  // connect to 127.0.0.1 and port 1234
  int i, resport, k, sock = hx_connect_v4("exam.1434.ru", 63821) , sock1;
  if (sock == -1 ) {
    printf("Can't create socket\n");
    return -1;
  } else if (sock == -2 ) {
    printf("Can't connect to requested host\n");
    return -1;
  } else if (sock == -3 ) {
    printf("IP address or Domain name is wrong\n");
    return -1;
  }
  printf("Connection  successfull\n");

  k=send(sock, "coffee999", strlen("coffee999"), 0);
  printf("СЕНД ОТПРАВИл: %d\n", k);
  k=recv(sock, buf, 11, 0);
  printf("\n");
  if(k==11) {
			for(i=0; i< 11; i++) {
					printf("%c", buf[i]);
			}
   }
   else {
   		printf("Какая-то ошибка: %d", k);
   		return -1;
   }
   
   resport=10000*(buf[2]-'0')+1000*(buf[3]-'0')+100*(buf[4]-'0')+(buf[5]-'0')*10+(buf[6]-'0');
   printf("%d\n", resport);
   
   sock1= hx_connect_v4("exam.1434.ru", resport);
   
   if (sock1 == -1 ) {
    printf("Can't create socket\n");
    return -1;
  } else if (sock1 == -2 ) {
    printf("Can't connect to requested host\n");
    return -1;
  } else if (sock1 == -3 ) {
    printf("IP address or Domain name is wrong\n");
    return -1;
  }
  printf("Connection 2 successfull\n");
  

   close(sock);
   close(sock1);
  

  
 //  close(sock1);
   return 0;
}
