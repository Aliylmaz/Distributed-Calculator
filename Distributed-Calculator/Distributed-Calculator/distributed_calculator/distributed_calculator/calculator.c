#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Kullanıcıya gösterilecek menü
void menu() {
    printf("\n========================================\n");
    printf("          Welcome to Calculator         \n");
    printf("========================================\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, num1, num2;
    int pipe_fd[2]; // Pipe için file descriptors
    char result_buffer[50]; // Sonucu tutacak buffer

    while (1) {
        menu();

        // Kullanıcının menü seçimi
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 5) {
            printf("\nInvalid choice! Please enter a number between 1 and 5.\n");
            while (getchar() != '\n'); // Buffer temizle
            continue;
        }

        if (choice == 5) { // Çıkış seçeneği
            printf("\n========================================\n");
            printf("    Thank you for using the calculator! \n");
            printf("========================================\n\n");
            break;
        }

        // Kullanıcıdan iki sayı al
        printf("\nEnter two numbers (e.g., 10 5): ");
        if (scanf("%d %d", &num1, &num2) != 2) {
            printf("\nInvalid input! Please enter two valid numbers.\n");
            while (getchar() != '\n'); // Buffer temizle
            continue;
        }

        // Pipe oluştur
        if (pipe(pipe_fd) == -1) {
            perror("Pipe failed");
            exit(1);
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork failed");
            exit(1);
        }

        if (pid == 0) { // Child process
            close(pipe_fd[0]); // Pipe'ın okuma ucunu kapat
            char num1_str[20], num2_str[20], pipe_write_fd_str[20];
            snprintf(num1_str, sizeof(num1_str), "%d", num1);
            snprintf(num2_str, sizeof(num2_str), "%d", num2);
            snprintf(pipe_write_fd_str, sizeof(pipe_write_fd_str), "%d", pipe_fd[1]);

            // İlgili işlem programını çalıştır (pipe'ın yazma ucunu gönderiyoruz)
            switch (choice) {
                case 1: execlp("./addition", "addition", num1_str, num2_str, pipe_write_fd_str, NULL); break;
                case 2: execlp("./subtraction", "subtraction", num1_str, num2_str, pipe_write_fd_str, NULL); break;
                case 3: execlp("./multiplication", "multiplication", num1_str, num2_str, pipe_write_fd_str, NULL); break;
                case 4: execlp("./division", "division", num1_str, num2_str, pipe_write_fd_str, NULL); break;
                default: exit(1);
            }
            perror("execlp failed");
            exit(1);
        } else { // Parent process
            close(pipe_fd[1]); // Pipe'ın yazma ucunu kapat
            wait(NULL); // Çocuk işleminin bitmesini bekle

            // Pipe üzerinden sonucu oku
            memset(result_buffer, 0, sizeof(result_buffer));
            ssize_t bytes_read = read(pipe_fd[0], result_buffer, sizeof(result_buffer) - 1);
            close(pipe_fd[0]); // Pipe'ın okuma ucunu kapat

            if (bytes_read > 0) {
                result_buffer[bytes_read] = '\0'; // String sonlandırıcı ekle
                printf("\n========================================\n");
                printf("             ***** RESULT *****         \n");
                printf("%s", result_buffer); // Sonucu göster
                printf("========================================\n");
            } else {
                printf("\nError: Failed to read result.\n");
            }
        }
    }

    return 0;
}
