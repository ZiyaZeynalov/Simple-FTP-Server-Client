#include "ftp_test.h"

int main(int argc, char *argv[]){

  int serv_sock; // server socket
  int clnt_sock; // client socket
  if(argc != 3 || strcmp(argv[1], "-p")){
    printf("invalid kom1 line\n");
    printf("./server -p <port>\n");
    exit(1);
  }
  
  // Initializing server socket.
  serv_sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in the_server_address;

  memset(&the_server_address, 0, sizeof(the_server_address));
  the_server_address.sin_family = AF_INET;
  the_server_address.sin_addr.s_addr = INADDR_ANY;
  the_server_address.sin_port = htons(8080);


  // Binding the server socket .

  if (bind(serv_sock, (struct sockaddr*)&the_server_address, sizeof(the_server_address)) < 0) {
  printf("bind failed");
  close(serv_sock);
  exit(1);
    }

  // Setting the server socket to listening mode.

  printf("Server start: listen on port %s\n", argv[2]);


  if(listen(serv_sock, 99) < 0){
    printf("listen error\n");
    exit(1);
  }

  // Accepting client sockets if they request to accept.
  printf("Waiting for new connections...\n");

  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_size = sizeof(clnt_addr);
clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

if (clnt_sock < 0){
  perror("accept unfortunately failed..):");
  exit(1);
}


  changedir("server_files");
  while(True){
    
    char mesaj[1500];
    char kom1[750], kom2[750];

    recv(clnt_sock, mesaj, 1500, 0);
    sscanf(mesaj, "%s %s", kom1, kom2);
    
    if(strcmp(kom1, "Zagruzka") == 0){
        
        FILE *file_f = fopen(kom2, "wb");
        if(file_f == NULL) continue; 
        
        char mymesaj[1500];
        long len;
        while((len = recv(clnt_sock, mymesaj, 1500, 0)) > 0){
            fwrite(mymesaj, 1, len, file_f);
            if (len<1500) break;
        }
        fclose(file_f);  
        
    }

    else if(strcmp(kom1, "Skachka") == 0){

        FILE *file_f = fopen(kom2, "rb");
        if(file_f == NULL) continue; 
        
        char mymesaj2[1500];
        long len;
        while((len = fread(mymesaj2, 1, 1500, file_f)) > 0){
            send(clnt_sock, mymesaj2, len, 0);
            if (len<1500) break;
        }
        fclose(file_f);
        remove(kom2);

        }
    else if(strcmp(kom1, "Zahlopnut") == 0){

      printf("Finalizing client socket.\n");
      close(clnt_sock);
      close(serv_sock);
      exit(0);
    }
    
      
  }
  
  
}



