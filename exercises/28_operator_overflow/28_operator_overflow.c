#include <stdio.h>
#include <limits.h>

#define CHECK_OVERFLOW(carry) \
    carry ? "Overflow" : "Not Overflow"

int check_add_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    __asm__ volatile(
        "add %2, %1\n\t"  // a + b → a
        "setc %0"         // 将进位标志存入carry
        : "=r"(carry), "+r"(a)
        : "r"(b)
        : "cc" // 声明修改了条件码寄存器
    );
    return carry;
}

int check_sub_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    __asm__ volatile(
        "subl %2, %1;"  // a = a - b
        "setc %0;"      // Set carry to 1 if CF is set, else 0
        : "=q"(carry), "+r"(a)
        : "r"(b)
        : "cc");
    return carry;
}

int check_mul_overflow_asm(unsigned int a, unsigned int b) {
    unsigned int high_bits;
    unsigned char overflow;
    __asm__ volatile(
        "mull %3;"  // edx:eax = eax * b
        "seto %0;"  // Set overflow to 1 if result > 32 bits
        : "=q"(overflow), "=d"(high_bits), "+a"(a)
        : "r"(b)
        : "cc");
    return overflow;
    // 如果a*b的结果超过了32位，overflow会被设置为1，否则为0
}

int check_div_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char is_div_zero;
    __asm__ volatile(
        "testl %1, %1;"  
        "setz %0;"       
        : "=q"(is_div_zero)
        : "r"(b)
        : "cc");
    return is_div_zero;
}

int main() {
    printf("(UINT_MAX + 1)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(UINT_MAX, 1)));   // 1
    printf("(1, 0)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(1, 0)));  
    printf("(0, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(0, 1)));          // 1
    printf("(2, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(2, 1)));
    printf("(UINT_MAX, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(UINT_MAX, 2)));   // 1
    printf("(1, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(1, 2)));
    printf("(10, 0)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(10, 0)));                         // 1
    printf("(2, 1)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(2, 1)));
    return 0;
}