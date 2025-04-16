#include <stdio.h>
#include <string.h>
#include "../enforcement/ban_unsafe.h" #enforced copiler restrictions

int main() {
    char src[] = "HelloSecureWorld";
    char dest[10];

    strcpy(dest, src);  // Unsafe: Buffer overflow
    printf("Copied: %s\n", dest);

    char name[10];
    gets(name);  
    printf("Hello %s\n", name);

    char buffer[10];
    sprintf(buffer, "%s", "VeryLongInputString");  
    printf("%s\n", buffer);

    return 0;
}
