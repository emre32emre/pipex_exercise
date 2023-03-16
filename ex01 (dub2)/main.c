#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// int dup2(int oldfd, int newfd);
// , newfd'yi kapatır ve oldfd'yi newfd'ye atar
int main()
{
	// int dup2(int oldfd, int newfd);
	// , newfd'yi kapatır ve oldfd'yi newfd'ye atar
	
	int fd = open("test.txt",O_CREAT | O_RDWR ,777);

	chmod("test.txt",S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	
	printf("Bu çıktı stdout a gidicek fd:%d \n",fd);

	dup2(fd,STDOUT_FILENO);

	printf("bu çıktı dosyaya yönlendirilecek\n");

}