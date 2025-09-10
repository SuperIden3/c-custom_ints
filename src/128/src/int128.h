#ifndef INT128_H
#define INT128_H

#define _POSIX_C_SOURCE 200809L

#ifdef INT128_IMPLEMENTATION
#define INT128_IMPLEMENTATION
#else
#define INT128_IMPLEMENTATION extern
#endif // INT128_IMPLEMENTATION

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint64_t hi;
    uint64_t lo;
} int128;

typedef enum {
    INT128_SUCCESS,
    INT128_INVALID_ARG,
    INT128_NO_MEMORY
} int128_error_t;

/**
 * @brief Allocates a new `int128` in memory.
 * @param dst The address of a pointer to reassign to the allocation: `&(int128 *)`
 * @return `INT128_SUCCESS` on successful allocation, `INT128_INVALID_ARG` if `NULL` is passed in, `INT128_NO_MEMORY` if `malloc` fails
 */
INT128_IMPLEMENTATION int128_error_t int128_new(int128 * *const dst);

/**
 * @brief Frees an `int128` from memory.
 * @param ptr The address of a pointer to free: `&(int128 *)`
 * @return `INT128_SUCCESS` on successful free, `INT128_INVALID_ARG` if `NULL` is passed in
 */
INT128_IMPLEMENTATION int128_error_t int128_free(int128 * *const ptr);

/**
 * @brief Makes a new `int128` on the stack
 * @param high The high bits
 * @param low The low bits
 * @return A stack-allocated `int128` with the corresponding numbers.
 */
INT128_IMPLEMENTATION int128 int128_from(uint64_t high, uint64_t low);

// --- //

/**
 * @brief Adds two `int128`s.
 * @param a The first `int128`
 * @param b The second `int128`
 * @return The sum of the two `int128`s
 */
INT128_IMPLEMENTATION int128 int128_add(int128 a, int128 b);

/**
 * @brief Subtracts two `int128`s
 * @param a The first `int128`
 * @param b The second `int1281
 * @return The difference of the two in another `int128`
 */
INT128_IMPLEMENTATION int128 int128_subtract(int128 a, int128 b);

#ifdef INT128_IMPLEMENTATION

INT128_IMPLEMENTATION int128_error_t int128_new(int128 * *const dst) {
    if (dst == NULL) return INT128_INVALID_ARG; // No pointer address given

    *dst = malloc(sizeof(int128)); // Allocate it
    if (*dst == NULL) return INT128_NO_MEMORY; // Allocation failed

    return INT128_SUCCESS;
}

INT128_IMPLEMENTATION int128_error_t int128_free(int128 * *const ptr) {
    if (ptr == NULL) return INT128_INVALID_ARG; // No pointer address given

    free(*ptr); // Free it
    *ptr = NULL; // Set to NULL

    return INT128_SUCCESS;
}

INT128_IMPLEMENTATION int128 int128_from(uint64_t high, uint64_t low) {
    int128 c;

    c.lo = low;
    c.hi = high;

    return c;
}

// --- //

INT128_IMPLEMENTATION int128 int128_add(int128 a, int128 b) {
    int128 c;

    c.lo = a.lo + b.lo; // Add the low bits
    c.hi = a.hi + b.hi + (uint64_t)(c.lo < a.lo); // Add the high bits and the carry by checking if the sum wrapped back to zero

    return c;
}

INT128_IMPLEMENTATION int128 int128_subtract(int128 a, int128 b) {
    int128 c;

    c.lo = a.lo - b.lo; // Subtract the low bits
    c.hi = a.hi - b.hi - (uint64_t)(c.lo > a.lo); // Subtract the high bits and the carry by checking if the sum wrapped back to the maximum value of a uint64_t

    return c;
}

#endif // INT128_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // INT128_H
