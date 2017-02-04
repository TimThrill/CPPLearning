#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int main()
{
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	memset(&addr, 0x00, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET; /* Set protocol */
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8888);   /* Set server port number */

	connect(clientSocket, (struct sockaddr*)&addr, sizeof(addr));
	char a[6] = "hello";
	sleep(1);
	int ret = send(clientSocket, a, 6, 0);
}

