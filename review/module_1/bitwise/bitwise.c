#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Set the nth bit of a number x
 * 
 * @param x [in] The number to modify
 * @param n [in] The bit position to set (0-based)
 * @return int The modified number with the nth bit set
 */
int bit_set(int x, int n) {
    return x | (1 << n);
}

/**
 * @brief Clear the nth bit of a number x
 * 
 * @param x [in] The number to modify
 * @param n [in] The bit position to clear
 * @return int The modified number with the nth bit cleared
 */
int bit_clear(int x, int n) {
    return x & ~(1 << n);
}

/**
 * @brief Toggle the nth bit of a number x
 * 
 * @param x [in] The number to modify
 * @param n [in] The bit position to toggle
 * @return int The modified number with the nth bit toggled
 */
int bit_toggle(int x, int n) {
    return x ^ (1 << n);
}

/**
 * @brief Check if the nth bit of a number x is set
 * 
 * @param x [in] The number to check
 * @param n [in] The bit position to check
 * @return int 1 if the nth bit is set, 0 otherwise
 */
int bit_is_set(int x, int n) {
    return (x & (1 << n)) != 0;
}

/**
 * @brief Swap two variables using bitwise XOR
 * 
 * @param a [in,out] The first integer
 * @param b [in,out] The second integer
 * @return int 0 on success
 */
int bit_swap(int *a, int *b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    if (a != b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
    return 0;
}

/**
 * @brief Check if a number is a power of two
 * 
 * @param x [in] The number to check
 * @return int 1 if x is a power of two, 0 otherwise
 */
int is_power_of_two(int x) {
    if (x <= 0) {
        return 0;
    }
    return (x & (x - 1)) == 0;
}

/**
 * @brief Check if a number is even
 * 
 * @param x [in] The number to check
 * @return int 1 if x is even, 0 otherwise
 */
int is_even(int x) {
    return (x & 1) == 0;
}

/**
 * @brief Compute the two's complement of a number
 * 
 * @param x [in] The number to compute the two's complement for
 * @return int The two's complement of x
 */
int twos_complement(int x) {
    return ~x + 1;
}

/**
 * @brief Compare two integers using bitwise XOR
 * 
 * @param a [in] The first integer
 * @param b [in] The second integer
 * @return int 1 if a and b are equal, 0 otherwise
 */
int comparation(int a, int b) {
    return a^b == 0;
}

/**
 * @brief Find the position of the most significant bit set in a number
 * 
 * @param x [in] The number to check
 * @return int The position of the most significant bit set, or -1 if no bits are set
 */
int most_significant_bit_position(uint32_t x) {
    if (x == 0) {
        return -1;
    }
    int position = 0;
    while (x >>= 1) {
        position++;
    }
    return position;
}

/**
 * @brief Find the position of the least significant bit set in a number
 * 
 * @param x [in] The number to check
 * @return int The position of the least significant bit set, or -1 if no bits are set
 */
int least_significant_bit_position(uint32_t x) {
    if (x == 0) {
        return -1;
    }
    int position = 0;
    while ((x & 1) == 0) {
        x >>= 1;
        position++;
    }
    return position;
}

/**
 * @brief Clear the least significant bit set in a number
 * 
 * @param x [in] The number to modify
 * @return int The modified number with the least significant bit cleared
 */
uint32_t clear_least_significant_bit(uint32_t x) {
    return x & (x - 1);
}

/**
 * @brief Isolate the least significant bit set in a number
 * 
 * @param x [in] The number to modify
 * @return int The isolated least significant bit
 */
int32_t isolate_least_significant_bit(int32_t x) {
    return x & -(x);
}

/**
 * @brief Check if a number is a multiple of 8
 * 
 * @param x [in] The number to check
 * @return int 1 if x is a multiple of 8, 0 otherwise
 */
int is_multiple_of_8(int x) {
    return (x & 0x7) == 0;
}

int main() {
    printf("No. 1: Bit Set: %d\n", bit_set(5, 1)); // 7

    printf("No. 2: Bit Clear: %d\n", bit_clear(5, 0)); // 4

    printf("No. 3: Bit Toggle: %d\n", bit_toggle(5, 0)); // 4

    printf("No. 4: Bit Is Set: %d\n", bit_is_set(5, 2)); // 1

    // No. 5: Bit Swap
    int a = 5, b = 10;
    bit_swap(&a, &b);
    printf("No. 5: Bit Swap: a = %d, b = %d\n", a, b); // a = 10, b = 5

    printf("No. 6: Is Power of Two: %d\n", is_power_of_two(8)); // 1

    printf("No. 7: Is Even: %d\n", is_even(4)); // 1

    printf("No. 8: Two's Complement: %d\n", twos_complement(5)); // -5

    printf("No. 9: Comparation: %d\n", comparation(5, 5)); // 1

    printf("No. 10: Most Significant Bit Position: %d\n", most_significant_bit_position(18)); // 4

    printf("No. 11: Least Significant Bit Position: %d\n", least_significant_bit_position(18)); // 1

    printf("No. 12: Clear Least Significant Bit: %u\n", clear_least_significant_bit(18)); // 16

    printf("No. 13: Isolate Least Significant Bit: %d\n", isolate_least_significant_bit(18)); // 2

    printf("No. 14: Is Multiple of 8: %d\n", is_multiple_of_8(16)); // 1
    return 0;
}