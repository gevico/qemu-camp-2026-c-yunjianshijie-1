#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#ifdef DEBUG_LEVEL

#define DEBUG_PRINT(fmt, ...)                                                                \
    do {                                                                                     \
        if (DEBUG_LEVEL >= 3) {                                                              \
            void *buf[30];                                                                   \
            int n = backtrace(buf, 30);                                                      \
            backtrace_symbols_fd(buf, n, 1);                                                 \
        } else if (DEBUG_LEVEL == 2) {                                                       \
            printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); \
        }                                                                                    \
    } while (0)

#else





















#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

    //! MUST BE ENSURE THE DEBUG_PRINT("x=%d", x) AT THE 48 LINE

    // 测试代码
    void test() {
    int x = 42;
    DEBUG_PRINT("x=%d", x);
}

int main() {
    test();
    return 0;
}