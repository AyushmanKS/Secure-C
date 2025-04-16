#include <stdio.h>
#include <string.h>
#include <time.h>

void safe_strcpy(char *dest, const char *src, size_t size) {
    strncpy(dest, src, size - 1);
    dest[size - 1] = '\0';
}

int main() {
    char src[] = "Benchmarking secure strcpy replacement!";
    char dest[100];

    int iterations = 1000000;

    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        strcpy(dest, src);
    }
    clock_t end = clock();
    printf("Unsafe strcpy time: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < iterations; i++) {
        safe_strcpy(dest, src, sizeof(dest));
    }
    end = clock();
    printf("Safe strcpy time: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
