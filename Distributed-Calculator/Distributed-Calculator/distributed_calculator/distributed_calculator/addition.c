#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 4) { // num1, num2, pipe_fd
        fprintf(stderr, "Usage: addition <num1> <num2> <pipe_fd>\n");
        exit(1);
    }

    int num1 = atoi(argv[1]);// 1. sayı
    int num2 = atoi(argv[2]);// 2. sayı
    int pipe_fd = atoi(argv[3]);

    int result = num1 + num2;
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Addition Result: %d + %d = %d\n",num1,num2,result);//sonuç formatlama

    write(pipe_fd, buffer, strlen(buffer)); // Pipe'a sonucu yaz
    close(pipe_fd); // Pipe'ın yazma ucunu kapat

	  // Saver programını çağır
    execlp("./saver", "saver", buffer, NULL);
    perror("Saver execution failed");

    return 0;
}
