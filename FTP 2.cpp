#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <sys/socket.h> // for socket
#include <sys/types.h>
#include <netinet/in.h> // sockaddr_in
#include <unistd.h> // for close
#include <arpa/inet.h> // for inet_aton
#include <netdb.h> // for gethostbyname
#include <iostream>

using namespace std;

int find_socket(char s[502] );
int find_socket(char s[502] ){
	int ia, ib, ic, id, ie, res1, res2, res, reali;
	 ia = s[40] - '0';
     ib = s[41] - '0';
     ic = s[42] - '0';
    id = s[44] - '0';
     ie = s[45] - '0';
    res1 = ia*100 + ib*10 + ic;
    if (s[46] == ')')
    {
    reali = 0;
    res2 = id*10 + ie;
    }
    else
    {
    reali = s[46] - '0';
    res2 = id*100 + ie*10 + reali;
    }
    res = res1*256 + res2;
    printf("%d",res);
    printf("\n");

		return res;
}


int hx_connect_v4(const char * ip, int port);

int create_sock(int port, int sock);
int create_sock(int port, int sock){
	sock = hx_connect_v4("exam.1434.ru", port);
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
		return sock;
} 
		
		

int hx_connect_v4(const char * ip, int port) {
  int sock, res;
  struct sockaddr_in addr;
  struct hostent *host = NULL;

  memset(&addr, 0, sizeof(addr));
  host = gethostbyname(ip);
  if (host == NULL) {
    printf("IP address or Domain name is wrong\n");
    return -1;
  }
  memcpy(&(addr.sin_addr.s_addr), host->h_addr_list[0], 4);
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1 ) {
     printf("Can't create socket\n");
     return -1;
    } 
  res = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  if ( res < 0 ) {
     printf("Can't connect to requested host\n");
     close(sock);
     return -1;
  }
  return sock;
}

void  send_message(int sock, const char *message, char answer[1000]);
void  send_message(int sock, const char *message, char answer[1000]){
   int x;
   x=send(sock, message, strlen(message), 0);
   if(x<0) {
      printf("Возникла ошибка при отправлении сообщения");
}
   else  {     
      recv(sock, answer, 1000, 0);
      printf("Was send: %s\n", message);
      printf("was get: %s\n", answer);
   }
}

void  point1(int sock);
void  point1(int sock){
	 int x;
	 char answer[1000];
   x=send(sock, "Kx97PASS R54GPnuOuY\r\n", strlen("Kx97PASS R54GPnuOuY\r\n"), 0);
   if(x<0) {
      printf("Возникла ошибка при отправлении сообщения");
      
   }
      recv(sock, answer, 1000, 0);
      printf("Was send: kx97PASS R54GPnuOuY");
      printf("was get: %s\n", answer);
   if(answer[0]!='2') {
   	  send(sock, "Kx97PASS 1tqtU7NGQC\r\n", strlen("Kx97PASS 1tqtU7NGQC\r\n"), 0);
   	  recv(sock, answer, 1000, 0);
   	  printf("Was send: Kx97PASS 1tqtU7NGQC ");
      printf("was get: %s\n", answer);
   }
   if(answer[0]!='2') {
   	  send(sock, "Kx97PASS 1tqtU7NGQC\r\n", strlen("Kx97PASS 1tqtU7NGQC\r\n"), 0);
   	  recv(sock, answer, 1000, 0);
   	  printf("Was send: Kx97PASS 1tqtU7NGQC");
      printf("was get: %s\n", answer);
   }
   
}
void  Get_new_connect(int sock, const char * message);
void  Get_new_connect(int sock, const char  *message){
   const char *u;
   char answer[1002],  I[14]="", *tok, s[501];
	 char listch[5001];
   int i, j, P=0, p=0, sock1, res,  sock2=-1, sock3=-1, sock4=-1;
   send_message(sock, message, answer);
   tok=strtok(answer, "(),");
   for(i=0 ; i<6; i++) {
      tok=strtok(NULL, "(),");
      if(i<4){
 	 strcat(I, tok);
 	 if(i<3) {
            strcat(I, ".");
         }
      }
      else {
         if(i==4) {
            for(j=0; j<(int)strlen(tok); j++) {
                P=P*10+tok[j]-'0';
            }
         }
         else {
	     for(j=0; j<(int)strlen(tok); j++) {
                p=p*10+tok[j]-'0';    
             }    
         }
      }
   }
  // printf("ПОРТ: %d\n", P);
  // printf("ПОРТ: %d\n", p);
   P=P*256+p;
   printf("ПОРТ: %d\n", P);
   strcat(I, "\0");
   printf("АЙПИ: %s\n", I);
   u=I;
   // printf("АЙПИ: %s\n", I);
   sock1=hx_connect_v4(u, P);
   if(sock1<0) {
       printf("ошибка при соединении с сервером");
   }
   else {
        printf("Connection 2 successfull\n");
 					/*		send(sock, "Kx97LIST\r\n", strlen("Kx97LIST\r\n") , 0);
         			recv(sock1, listch, 5000 , 0);
   					   cout<<"----------LIST----------\n"<<listch<<"\n";
        			printf("\n");
    				 while(recv(sock1, listch, 5000, 0)) {
      				    cout << listch << "\n";
       				}         
       		
       		
       		drwxrwxr-x    4 1000       33               4096 Apr 24 00:12 pOXg3muKHX16z8 */
    send(sock, "Kx97CWD pOXg3muKHX16z8\r\n", strlen("Kx97CWD pOXg3muKHX16z8\r\n"), 0);
		recv(sock, s, 500, 0);
	  cout << "CWD->\n" << s <<"\n";


		send(sock, "Kx97PWD\r\n", strlen("Kx97PWD\r\n"), 0);
		recv(sock, s, 500, 0);
		cout << "PWD->\n" << s << "\n";
		
		send(sock, "Kx97PASV\r\n", strlen("Kx97PASV\r\n") , 0);
    recv(sock, s, 500 , 0);
    for(long unsigned int i = 0; i < strlen(s); i++) {
        printf("%c",s[i]);
    }
    printf("\n");
		
		 res=find_socket(s);

		sock2=create_sock(res, sock2);
		if(sock2<0) {
				printf("второй сокет не создается");
		}
		printf("Второй сокет не создан");
		
	send(sock, "Kx97LIST -a\r\n", strlen("Kx97LIST -a\r\n"), 0);
	recv(sock, s, 500, 0);
	cout << "sockrecv->\n" << s << "\n";


	while(recv(sock2, listch, 5000, 0)) {
			cout <<"----------------------------------------------------------" << listch <<"\n";
}

		
	//	drwxrwxr-x    2 1000       33               4096 Apr 24 00:12 access
	//	drwxrwxr-x    2 1000       33               4096 Apr 24 00:12 unlock

send(sock, "Kx97CWD access\r\n", strlen("Kx97CWD access\r\n"), 0);
recv(sock, s, 500, 0);
std::cout << "CWD->\n" << s << std::endl;

//2pwd
send(sock, "Kx97PWD\r\n", strlen("Kx97PWD\r\n"), 0);
recv(sock, s, 500, 0);
std::cout << "PWD->\n" << s << std::endl;

// Pasv
  send(sock, "Kx97PASV\r\n", strlen("Kx97PASV\r\n") , 0);
  recv(sock, s, 500 , 0);
  for(long unsigned int i = 0; i < strlen(s); i++)
        {
        printf("%c",s[i]);
        }
  printf("\n");

		res=find_socket(s);
    sock3=create_sock(res, sock3);
    if(sock3<0) {
    		printf("возникла аошибка при создании 3 сокета");
    }
    printf("конекшн сакцесфул");
    
    send(sock,"Kx97STOR core.c\r\n", strlen("Kx97STOR core.c\r\n"),0);
		int cnt = 0;
			char farr[10000];
			FILE *f = fopen("core.c","r");
			int n = 1000;
			int fres = 0;
			while((fres = fread(farr,1,n,f)) > 0){
			int che = send(sock3,farr,fres,0);
			cnt += che;

			if (fres < 0)
				std::cout << "File sending error" << std::endl;
			}

			std::cout << "Отслано: " << cnt << std::endl;
			fclose(f);
			close(sock3);

// Pasv
  send(sock, "Kx97PASV\r\n", strlen("Kx97PASV\r\n") , 0);
  recv(sock, s, 500 , 0);
  for(long unsigned int i = 0; i < strlen(s); i++)
        {
        printf("%c",s[i]);
        }
  printf("\n");
  
  res=find_socket(s);
  sock4=create_sock(res, sock4);
  if(sock4<0) {
  		printf("при создании сокета 4 возникла проблема");
  }
  printf("4 сокет создан");

    
    send(sock, "Kx97CDUP\r\n", strlen("Kx97CDUP\r\n"), 0);
recv(sock, s, 500, 0);
std::cout << "parentpapka" << s << "\n" << std::endl;


//3cwd
send(sock, "Kx97CWD unlock\r\n", strlen("Kx97CWD unlock\r\n"), 0);
recv(sock, s, 500, 0);
std::cout << "CWD->\n" << s << std::endl;

//3pwd
send(sock, "Kx97PWD\r\n", strlen("Kx97PWD\r\n"), 0);
recv(sock, s, 500, 0);
std::cout << "PWD->\n" << s << std::endl;

send(sock,"Kx97STOR core.c\r\n", strlen("Kx97STOR core.c\r\n"),0);
recv(sock, s, 500, 0);

//file2
int cnt2 = 0;
char farr2[10000];
FILE*f2 = fopen("core.c","r");
n = 1000;
int fres2 = 0;
while((fres2 = fread(farr2,1,n,f2)) > 0){
int che2 = send(sock4,farr2,fres2,0);
cnt2 = cnt2 + che2;

if (fres2 < 0)
std::cout << "File sending error" << std::endl;
}

std::cout << "Отслано: " << cnt << std::endl;
fclose(f2);

recv(sock, s, 500, 0);
std::cout << s << std::endl;
		close(sock4);
    close(sock2);
    close(sock1);
   }
}

int main(void) {
   char s[1000], answer[1000];    //  a[1000]="RETR 3ux7lE.dat\n1"
   int  sock,  port=63822 ;
   sock = hx_connect_v4("exam.1434.ru", port);
   if(sock<0) {
       close(sock);
       return -1;
   }
   printf("Connection successfull\n");
   recv(sock, s, 1000, 0);
   printf("%s\n", s);
   send_message(sock, "Kx97USER Savchenko_AS\r\n", answer);
   send_message(sock, "Kx97TYPE I\r\n", answer);
   point1(sock);
   Get_new_connect(sock, "Kx97PASV\r\n");
   send_message(sock, "Kx97QUIT\r\n", answer);
	 close(sock);
   return 0;
}

