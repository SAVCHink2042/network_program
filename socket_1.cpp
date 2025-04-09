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
  char s[85], *buf;
  int a, b, c, d, i;
  // connect to 127.0.0.1 and port 1234
  int res, sock = hx_connect_v4("exam.1434.ru", 63819);
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
  printf("Connection successfull\n");

  // send and recv

  

  recv(sock, s, 84, 0);
  printf("%c", s[77]);
  printf("%c", s[78]);
  printf("%c", s[79]);
  printf("%c", s[80]);
  printf("\n");
   // cout<<s[80];
 a=s[77]-'0';
 b=s[78]-'0';
 c=s[79]-'0';
 d=s[80]-'0';
 res=1000*a+100*b +10*c+d;
 printf("%d\n", res);
 buf= new char [res+ 1000];
 send(sock, "T", 1, 0);
 recv(sock, buf, res+1000, 0);
 printf("КОД: ");
   for ( i=0 ; i< 6; i++) {
  		printf("%c" , buf[i+res]);
  }
  delete [] buf;
  close(sock);
  return 0;
}
