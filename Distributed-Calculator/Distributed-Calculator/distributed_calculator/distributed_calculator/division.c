#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Komut satırı argüman kontrolü
    if (argc != 4) { // num1, num2, pipe_fd
        char error_msg[] = "Usage: division <num1> <num2> <pipe_fd>\n";
        write(2, error_msg, strlen(error_msg));
        exit(1);
    }

    // Argümanları integer'a dönüştür
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int pipe_fd = atoi(argv[3]);

    // Sıfıra bölme kontrolü
    if (num2 == 0) {
        // Hata mesajını yalnızca stderr'e yaz
        char error_msg[] = "Error: Division by zero is not allowed!\n";
        write(2, error_msg, strlen(error_msg));
        close(pipe_fd); // Pipe'ı kapat
        exit(1);        // Program hata kodu ile çıkış yapar
    }

    // Bölme işlemi
    float result = (float)num1 / num2;

    // Sonucu pipe'a yaz
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Division Result: %d / %d = %.2f\n", num1, num2, result);
    write(pipe_fd, buffer, strlen(buffer)); // Sonucu pipe'a yaz
    close(pipe_fd); // Pipe'ın yazma ucunu kapat

		 // Saver programını çağır
    execlp("./saver", "saver", buffer, NULL);
    perror("Saver execution failed");
    return 0;
}
