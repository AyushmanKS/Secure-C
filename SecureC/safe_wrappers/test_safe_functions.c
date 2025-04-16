#include <stdio.h>
#include "safe_functions.c"  // This will include your safe functions

int main() {
    char dest[20];
    safe_strcpy(dest, "Ayushman", sizeof(dest));
    printf("✅ Safe copy: %s\n", dest);

    char input[20];
    printf("Enter your name: ");
    safe_input(input, sizeof(input));
    printf("👋 Welcome, %s!\n", input);

    char buffer[30];
    safe_sprintf(buffer, sizeof(buffer), "Hi %s", input);
    printf("📝 Output: %s\n", buffer);

    return 0;
}
