# SecureC: Secure Replacements for Unsafe C Library Functions

## ✨ Project Overview
C standard library functions like `strcpy`, `gets`, and `sprintf` are **notoriously unsafe** and have been the cause of countless vulnerabilities due to **buffer overflows** and **memory corruption**.

This project aims to:
- ❌ Identify and block unsafe functions at **compile time**.
- ✔️ Provide safe alternatives (custom or Rust-based).
- ⚡ Benchmark safe vs unsafe behavior.

---

## 🔍 Problem Statement
Many standard C functions:
- Do **not perform bounds checking** (e.g., `strcpy`, `gets`)
- Can cause **buffer overflows**, **segmentation faults**, and **undefined behavior**.
- Still exist in legacy codebases and are hard to detect manually.

> “How do we ensure developers are **forced to use** safe alternatives?”

---

## ⚙️ Implementation Steps

### 1. Directory Structure
```
SecureC/
├── enforcement/           # Compile-time blocking macros
│   └─ ban_unsafe.h
├── rust_wrappers/         # (Optional) Rust safe bindings
│   └─ safe_wrappers.rs
├── safe_wrappers/         # Safe versions of unsafe C functions
│   └─ safe_functions.c / .h
├── unsafe_examples/       # Demo file using unsafe code
│   ├─ unsafe_demo.c
│   └─ README.md
└── benchmarks/            # Optional benchmarking
    └─ benchmark.c
```

---

### 2. Unsafe Demo File (unsafe_examples/unsafe_demo.c)
Example usage of unsafe functions:
```c
strcpy(dest, src);
gets(name);
sprintf(buffer, "%s", "VeryLongInputString");
```

---

### 3. Enforcement Header (enforcement/ban_unsafe.h)
```c
#define BLOCK_USE_OF(x) _Static_assert(0, #x " is unsafe. Use a safer alternative.")
#define strcpy(...) BLOCK_USE_OF(strcpy)
#define gets(...) BLOCK_USE_OF(gets)
#define sprintf(...) BLOCK_USE_OF(sprintf)
```

**Effect:** When any banned function is used, it causes a compile-time error:
```
error: static assertion failed: "strcpy is unsafe. Use a safer alternative."
```

---

### 4. Safe Alternatives (safe_wrappers/safe_functions.c)
```c
void safe_strcpy(char* dest, const char* src, size_t size) {
    strncpy(dest, src, size - 1);
    dest[size - 1] = '\0';
}
```
Use in safe code:
```c
safe_strcpy(dest, src, sizeof(dest));
```

---

### 5. Optional: Rust Wrappers (rust_wrappers/safe_wrappers.rs)
```rust
#[no_mangle]
pub extern "C" fn safe_strcpy(dest: *mut u8, src: *const u8, len: usize) {
    unsafe {
        std::ptr::copy_nonoverlapping(src, dest, len - 1);
        *dest.add(len - 1) = 0;
    }
}
```
Compile Rust to staticlib and call it from C if desired.

---

### 6. Benchmark Unsafe vs Safe (benchmarks/benchmark.c)
```c
// Use clock() to time unsafe vs safe function copies
clock_t start = clock();
for (int i = 0; i < N; i++) strcpy(dest, src);
clock_t end = clock();
```
Compare time taken by `strcpy` and `safe_strcpy`.

---

## 📊 Flowchart: SecureC Workflow
```text
[ Developer Writes Code ]
            |
            v
[ Includes ban_unsafe.h ]
            |
            v
[ Uses unsafe function like strcpy? ] -- Yes --> [ Compilation Error ]
            |                                         ^
            No                                        |
            v                                         |
  [ Compiles Successfully with safe_strcpy, etc. ] <--
```

---

## 🎯 Output Example
```bash
$ gcc -std=c11 unsafe_demo.c -o demo
In file included from unsafe_demo.c:
error: static assertion failed: "strcpy is unsafe. Use a safer alternative."
```

---

## 📊 Benchmark Graph (ASCII Approximation)
```
strcpy (unsafe):       ########## (slow)
safe_strcpy (safe):    #######    (faster with safety)
```
> Note: Replace with matplotlib/Excel graph if submitting visually.

---

## 🚀 Conclusion
- Unsafe functions are blocked **at compile time** using `_Static_assert`.
- Safe alternatives are easy to use and safer.
- Optional: Rust wrappers for even stronger memory safety.

---

## 🔧 How to Compile & Run
### To test unsafe example:
```bash
cd unsafe_examples
gcc -std=c11 unsafe_demo.c -o unsafe_demo
```
Expected: You get compile-time error due to banned functions.

### To run safe version:
```bash
cd safe_wrappers
gcc -std=c11 safe_functions.c ../safe_examples/safe_demo.c -o safe_demo
./safe_demo
```

---

## 💼 Author & Acknowledgement
Created by: **Ayushman Kumar Singh**  
Tools used: C, Rust, GCC, Visual Studio Code

Inspired by the need to modernize legacy C systems and prevent common cyber threats through safer programming practices.

