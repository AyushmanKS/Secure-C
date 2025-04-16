#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Safe strcpy alternative
void safe_strcpy(char *dest, const char *src, size_t size) {
    strncpy(dest, src, size - 1);
    dest[size - 1] = '\0';
}

// Safe sprintf alternative
void safe_sprintf(char *dest, size_t size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(dest, size, format, args);
    va_end(args);
}

// Safe gets alternative
void safe_input(char *buffer, size_t size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}
