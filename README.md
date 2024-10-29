# Simple FTP Server-Client
![C](https://img.shields.io/badge/Language-C-blue)
![Sockets](https://img.shields.io/badge/Networking-Sockets-green)

A simple File Transfer Protocol server-client implementation in C, using sockets for basic file upload, download, and directory change operations. The project has a server and a client that communicate over a specified port, allowing file exchange between them.

---

## How It Works

The FTP server listens on a specified port and waits for a client to connect. The client can send commands to upload, download, change directories, and terminate the connection.

### Supported Commands:
- **Upload**: Upload a file from client to server.
- **Download**: Download a file from server to client.
- **Terminate**: Close the connection.

---

## Features

- **Server-Client Communication**: Manages connection between client and server over TCP.
- **File Transfer**: Supports secure upload and download of files.
- **Directory Navigation**: The client can change directories on the server.
- **Error Handling**: Basic validation for commands and connection errors.

---

## Project Structure

The project is structured as follows:
- **server.c**: Implements server functionalities, including accepting connections and processing commands.
- **client.c**: Implements client functionalities, such as connecting to the server, uploading, and downloading files.
- **ftp_test.h**: Header file with shared definitions and helper functions.

---

## Getting Started

### Prerequisites

You need to have a C compiler and networking libraries installed.

### Building the Project

1. **Compile the server**:
   ```bash
   gcc -o server server.c -lpthread
   ```
2. **Compile the client**:
   ```bash
   gcc -o client client.c -lpthread
   ```

### Running the Server

1. **Start the server** on a specified port (e.g., 8080):
   ```bash
   ./server -p 8080
   ```
2. The server listens for incoming client connections and handles requests.

### Running the Client

1. **Connect the client** to the server using the server's IP address and port:
   ```bash
   ./client -h 127.0.0.1 -p 8080
   ```

### Sample Commands

- **Upload a File**: `upload(sock, "filename")`
- **Download a File**: `download(sock, "filename")`
- **Terminate Connection**: `terminate(sock)`

---

## Acknowledgments

- **Socket Programming**: This project is a simple example of socket programming in C.
- Inspiration from basic FTP implementations and command-line utilities.
