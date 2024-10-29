#include "ftp_test.h"


// Initializing a client socket.
// To ensure the client socket connect with the target server,
// We assumed "./client -h 127.0.0.1 -p 8080".
int init(int argc, char *argv[]){


  int sock;
  if(argc != 5 || strcmp(argv[1], "-h") || strcmp(argv[3], "-p")){
    printf("unvalid command line\n");
    printf("./client -h <address> -p <port>\n");
    exit(1);
  }

  // client socket initialization

    sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock == -1) {
    printf("socket creation failed\n");
    return False;
    }


    struct sockaddr_in the_server_address;
    
    memset(&the_server_address, 0, sizeof(the_server_address));
    the_server_address.sin_family = AF_INET;
    the_server_address.sin_port = htons(atoi(argv[4]));
if (inet_pton(AF_INET, argv[2], &the_server_address.sin_addr) <= 0) {
      perror("The Address get error!\n");
      return False;
  }

  // connection test

   if (connect(sock, (struct sockaddr*)&the_server_address, sizeof(the_server_address)) == -1) {
        perror("connect Error");
        close(sock);
        return False;
}

  return sock; // return initialized socket
}

void ls(){
  system("ls");
}

// Implementing "changedir" function.

void changedir(const char* name){ 
  if (chdir(name) != 0) {
    printf("function chdir error");
  }
}


// Input : socket & file_name you want to upload to server
// Return : if the socket success to upload the accesible file, return "True". Otherwise, return "False".
int upload(int sock, const char* file_name){
  FILE *file_f = fopen(file_name, "rb");
  char mesaj[1500];
  if (file_f == NULL) return False;

  snprintf(mesaj, 1500, "Zagruzka %s", file_name);

  send(sock, mesaj, 1500, 0);
  char mymesaj2[1500];
  long len;
  while((len = fread(mymesaj2, 1, 1500, file_f)) > 0){
        send(sock, mymesaj2, len, 0);
        
        if (len < 1500) break;
  }

  fclose(file_f);
  remove(file_name);
  
  return True;
}
            

// Input : socket & file_name you want to download from server
// Return : if the socket success to download the accessible file, return "True". Otherwise, return "False".
int download(int sock, const char* file_name){
  FILE *file_f = fopen(file_name, "wb");
  if (file_f == NULL) return False;
 
  char mesaj2[1500];

  snprintf(mesaj2, 1500, "Skachka %s", file_name);

  send(sock, mesaj2, 1500, 0);
  
  char mymesaj2[1500];
  long len;
  while((len = recv(sock, mymesaj2, 1500, 0)) >0){
      
        fwrite(mymesaj2, 1, len, file_f);
        if (len<1500) break;
  }

  fclose(file_f);
  return True;
}


// Terminate function should send the terminate signal to server.
void terminate(int sock){
    char term_msg[1500] = "Zahlopnut";
    send(sock, term_msg, 1500, 0);
    close(sock);
}
