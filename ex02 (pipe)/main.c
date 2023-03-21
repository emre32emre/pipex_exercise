#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	// kanalın giriş ve çıkış yönlerini temsilen
	int     fd[2], nbytes;
	
	// mesajın yönünü ifade etmek için çekirdek tarafından döndürülen değer
	int   childpid;
	
	// gönderilecek olan mesaj
	char    msg[] = "musa kocabaş\n";
	
	// maksimum mesaj boyutu
	char    readbuffer[40];
	
	// iletişim kanalını oluşturan sistem çağrısı
	pipe(fd);
	
	// hata kontrolü
	childpid = fork();
	if(childpid == -1) 
	{
		perror("fork işlemi başarısız!");
		exit(1);
	}
	// 0 okuma 1 yazma ucu 

	if(childpid == 0) 
	{
		// child procress
		// kanalın giriş tarafını kapat
		close(fd[0]);
		
		// çıkış tarafına mesajı yazdır
		write(fd[1], msg, (strlen(msg)+1));
		printf("Kanaldan gönderilen mesaj: %s", msg);
		exit(0);
	} else {
		// kanalın çıkış tarafını kapat
		close(fd[1]);
		
		// kanaldan gelen mesajı oku
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		printf("Kanaldan gelen mesaj: %s", readbuffer);
	}
	
	return(0);
}