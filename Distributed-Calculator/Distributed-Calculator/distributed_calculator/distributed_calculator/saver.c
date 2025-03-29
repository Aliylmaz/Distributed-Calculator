#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) { // Sonuç argümanını kontrol et
        fprintf(stderr, "Usage: saver <result>\n");
        exit(1);
    }

    // Results.txt dosyasını aç (append mode)
    FILE *file = fopen("results.txt", "a");
    if (!file) {
        perror("Failed to open results.txt");
        exit(1);
    }

    // Sonucu dosyaya yaz
    fprintf(file, "%s", argv[1]);
    fclose(file);

    return 0;
}
