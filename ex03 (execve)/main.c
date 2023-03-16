#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	//okunacak dosya adı
	char *path = "test.txt";
	//komutun dizini
	char *command_path = "/bin/cat";
	
	int fd = open(path, O_RDONLY);
	// cat test.txt
	char *arguman[] = {command_path , path , NULL};
	
	//execve(command_path ,arguman ,NULL);
	
	char *new_command_path = "/usr/bin/grep";
	//grep "," test.txt
	char *newArg[] = {"grep" , "," , path, NULL};


	execve(new_command_path ,newArg ,NULL);


}

