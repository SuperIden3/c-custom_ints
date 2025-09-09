#ifndef INT128_T_H
#define INT128_T_H

#define _POSIX_C_SOURCE 200809L

#ifdef INT128_T_IMPLEMENTATION
#define INT128_T_IMPLEMENTATION
#else
#define INT128_T_IMPLEMENTATION extern
#endif // INT128_T_IMPLEMENTATION

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint64_t hi;
    uint64_t lo;
} int128_t;

typedef enum {
    INT128_T_SUCCESS,
    INT128_T_INVALID_ARG,
    INT128_T_NO_MEMORY
} int128_error_t;

/**
 * @brief Allocates a new `int128_t` in memory.
 * @param dst The address of a pointer to reassign to the allocation: `&(int128_t *)`
 * @return `INT128_T_SUCCESS` on successful allocation, `INT128_T_INVALID_ARG` if `NULL` is passed in, `INT128_T_NO_MEMORY` if `malloc` fails
 */
INT128_T_IMPLEMENTATION int128_error_t int128_new(int128_t * *const dst);

/**
 * @brief Frees an `int128_t` from memory.
 * @param ptr The address of a pointer to free: `&(int128_t *)`
 * @return `INT128_T_SUCCESS` on successful free, `INT128_T_INVALID_ARG` if `NULL` is passed in
 */
INT128_T_IMPLEMENTATION int128_error_t int128_free(int128_t * *const ptr);

// --- //

/**
 * @brief Adds two `int128_t`s.
 * @param a The first `int128_t`
 * @param b The second `int128_t`
 * @return The sum of the two `int128_t`s
 */
INT128_T_IMPLEMENTATION int128_t int128_add(int128_t a, int128_t b);

/**
 * @brief Subtracts two `int128_t`s
 * @param a The first `int128_t`
 * @param b The second `int128_t1
 * @return The difference of the two in another `int128_t`
 */
INT128_T_IMPLEMENTATION int128_t int128_subtract(int128_t a, int128_t b);

#ifdef INT128_T_IMPLEMENTATION

INT128_T_IMPLEMENTATION int128_error_t int128_new(int128_t * *const dst) {
    if (dst == NULL) return INT128_T_INVALID_ARG; // No pointer address given

    *dst = malloc(sizeof(int128_t)); // Allocate it
    if (*dst == NULL) return INT128_T_NO_MEMORY; // Allocation failed

    return INT128_T_SUCCESS;
}

INT128_T_IMPLEMENTATION int128_error_t int128_free(int128_t * *const ptr) {
    if (ptr == NULL) return INT128_T_INVALID_ARG; // No pointer address given

    free(*ptr); // Free it
    *ptr = NULL; // Set to NULL

    return INT128_T_SUCCESS;
}

// --- //

INT128_T_IMPLEMENTATION int128_t int128_add(int128_t a, int128_t b) {
    int128_t c;

    c.lo = a.lo + b.lo; // Add the low bits
    c.hi = a.hi + b.hi + (uint64_t)(c.lo < a.lo); // Add the high bits and the carry by checking if the sum wrapped back to zero

    return c;
}

INT128_T_IMPLEMENTATION int128_t int128_subtract(int128_t a, int128_t b) {
    int128_t c;

    c.lo = a.lo - b.lo; // Subtract the low bits
    c.hi = a.hi - b.hi - (uint64_t)(c.lo > a.lo); // Subtract the high bits and the carry by checking if the sum wrapped back to the maximum value of a uint64_t

    return c;
}

#endif // INT128_T_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // INT128_T_H
