#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 1351
#define BACKLOG 10
#define BUFF_SIZE 1024

int main() {
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // get socket's file descriptor: AF_INET - IPv4, SOCK_STREAM - TCP
	setsockopt(
		socket_fd,
		SOL_SOCKET, // some level ))) 
		SO_REUSEADDR | SO_REUSEPORT, // don't until while the system close socket's descriptor
		nullptr,
		0
	); 

	 sockaddr_in address = { // we will listen this address
	 	AF_INET, //IPv4 family
	 	htons(PORT),
	 	INADDR_ANY // 0.0.0.0
	 }; 

	 bind(socket_fd, (sockaddr*) &address, sizeof(address));
	 listen(socket_fd, BACKLOG); // now start listening 

	 int addrlength = sizeof(address);
		 int new_socket_fd = accept( // get client's socket
		 	socket_fd,
		 	(sockaddr*) &address, // if not interested - NULL, NULL. I don't know why I'm interested here/ There is no reason. Just because.
		 	(socklen_t*) &addrlength // If not NULL, must be initialized with sizeof(address)
	);
	 while (true) {
		 char buffer[BUFF_SIZE] = {}; // initialize all elements with 0 :)
		 int count = read(new_socket_fd, buffer, BUFF_SIZE);
		 if (count == 0) return 0;
		 std::cout << buffer << std::endl;
		 std::cout << "count = " << count << std::endl;
	}

	return 0;
}