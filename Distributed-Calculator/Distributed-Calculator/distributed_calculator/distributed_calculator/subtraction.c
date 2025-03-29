#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Komut satırı argüman kontrolü
    if (argc != 4) { // num1, num2, pipe_fd
        char error_msg[] = "Usage: subtraction <num1> <num2> <pipe_fd>\n";
        write(2, error_msg, strlen(error_msg));
        exit(1);
    }

    // Argümanları integer'a dönüştür
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int pipe_fd = atoi(argv[3]);

    // Çıkarma işlemi
    int result = num1 - num2;

    // Sonucu pipe'a yaz
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Subtraction Result: %d - %d = %d\n", num1, num2, result);

    write(pipe_fd, buffer, strlen(buffer)); // Sonucu pipe'a yaz
    close(pipe_fd); // Pipe'ı kapat

	 // Saver programını çağır
    execlp("./saver", "saver", buffer, NULL);
    perror("Saver execution failed");
    return 0;
}
