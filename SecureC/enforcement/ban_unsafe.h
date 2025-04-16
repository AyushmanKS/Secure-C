#ifndef BAN_UNSAFE_H
#define BAN_UNSAFE_H

// Use C11 static assert for compile-time blocking
#if __STDC_VERSION__ >= 201112L
    #include <assert.h>
    #define BLOCK_USE_OF(x) _Static_assert(0, #x " is unsafe. Use a safer alternative.")
#else
    #define BLOCK_USE_OF(x) typedef char BLOCK_##x##_is_unsafe[-1]
#endif

// Replace unsafe functions
#define strcpy(...) BLOCK_USE_OF(strcpy)
#define gets(...) BLOCK_USE_OF(gets)
#define sprintf(...) BLOCK_USE_OF(sprintf)
#define strcat(...) BLOCK_USE_OF(strcat)
#define strncpy(...) BLOCK_USE_OF(strncpy)

#endif // BAN_UNSAFE_H
