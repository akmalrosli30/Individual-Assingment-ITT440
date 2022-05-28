#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//Function to compare two strings
int compare_strings(char x[], char y[])
{
	int z = 0;
	while (x[z] == y[z])
	{
		if (x[z] == '\0' || y[z] == '\0')
		break;
		z++;
	}
	
	if (x[z] == '\0' && y[z] =='\0')
	return 0;
	else
	return -1;
}

int main(){
	//Declare variables
	int socket_desc,Test1,Test2;
	char buffer[1024];
	struct sockaddr_in serverAdd;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	
	//Server settings
	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htcons(8888);
	serverAdd.sin_addr.s_addr = inet_addr("192.168.56.104");
	memset(serverAdd.sin_zero, '\0',sizeof serverAdd.sin_zero);
	bind(socket_desc,(struct sockaddr *) &serverAdd, sizeof(serverAdd));
	
	//Server listen
	if (listen(socket_desc,5)==0)
		{
		puts("\n########## WELCOME TO THE CHATROOM ##########");
		puts("             Server is listening....\n");
		}
	else
		puts("Error");
		
	//Bind - 1 server, 2 clients
	addr_size = sizeof serverStorage;
	Test1 = accept(socket_desc, (struct sockaddr *) &serverStorage, &addr_size);
	Test2 = accept(socket_desc, (struct sockaddr *) &serverStorage, &addr_size);
	
	int exit = 0;
	//Function where disconnect if "exit"
	while(exit == 0)
	{
		recv(Test1, buffer, 1024, 0); //receiving from Test1
		printf("%s\n --Send to Test2--\n", buffer); //sending to Test2
		send(Test2,buffer,1024,0);
		
		//Exit looping
		if (compare_strings(buffer,"exit")==0)
			{
			exit = 1;
			}
		
		else
			{
			//Empty buffer
			memset(&buffer[0],0,sizeof(buffer));
			
			recv(Test2, buffer,1024,0); //receiving from Test2
			printf ("%s\n --Send to Test1--\n",buffer); //sending to Test1
			send(Test1,buffer,1024,0);
			
			//Exit looping
			if (compare_strings(buffer, "exit")==0)
				{
				exit = 1;
				}
			}
		}
		
		return 0;
	}