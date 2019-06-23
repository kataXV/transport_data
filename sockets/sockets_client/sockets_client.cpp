#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <termios.h>

#define PORT 1351
#define BACKLOG 10
#define BUFF_SIZE 1024

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

char getch() {
	char buf = 0;
	termios old = {0};
	fflush(stdout);
	if (tcgetattr(0, &old) < 0)
		perror("tcgetaddr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0)
		perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0)
		perror("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		perror("tcsetattr ~ICANON");
	return buf;
}

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
	 	htons(PORT)
	 }; 
	 inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
	 connect (
	 	socket_fd,
	 	(sockaddr*) &address,
	 	sizeof(address)
	 );

	 while (true) {
	 	const char* str = nullptr;
	 	int state = 0;
	 	auto ch = getch();
	 	if (ch == '\033') {
	 		getch();
	 		switch (getch()) {
	 			case 'A': state = 1; break;
	 			case 'B': state = 2; break;
	 			case 'C': state = 3; break;
	 			case 'D': state = 4; break;
	 		}
	 	} else {
	 		switch (ch) {
	 			case 'w': state = 1; break;
	 			case 's': state = 2; break;
	 			case 'd': state = 3; break;
	 			case 'a': state = 4; break;
	 		}
	 	}
	 	switch (state) {
	 		case UP: str = "up"; break;
	 		case DOWN: str = "down"; break;
	 		case RIGHT: str = "right"; break;
	 		case LEFT: str = "left"; break;
	 	}
	 	if (str != nullptr) {
	 		write(socket_fd, str, strlen(str));
	 	}
	 }
	 // auto str = "hello";
	 // write(socket_fd, str, strlen(str));

	return 0;
}