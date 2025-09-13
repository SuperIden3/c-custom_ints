#ifndef INT128_T_H
#define INT128_T_H

#define _POSIX_C_SOURCE 200809L

#ifdef INT128_T_IMPLEMENTATION
#define INT128_T_IMPLEMENTATION
#else
#define INT128_T_IMPLEMENTATION extern
#endif // INT128_T_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

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

// --- // Macros

#define INT128_SIZE ((size_t)128) // Expected size of an `int128_t`
#define INT128_ACTUAL_SIZE (sizeof(int128_t)) // Actual size of an `int128_t` from `sizeof`.
#define INT128_TOSTRFUNC_REPRSIZE (sizeof(uint64_t) * 2 + 1) // The sizes of the two members plus a null terminator

// --- // Initialization

/**
 * @brief Allocates a new `int128_t` in memory
 * @param dst The address of a pointer to reassign to the allocation: `&(int128_t *)`
 * @param hi The high bits that will be assigned to the `int128_t` if it's allocated
 * @param lo The low bits that will be assigned to the `int128_t` if it's allocated
 * @return `INT128_T_SUCCESS` on successful allocation, `INT128_T_INVALID_ARG` if `NULL` is passed in, `INT128_T_NO_MEMORY` if `malloc` fails
 * @note Calls free on the pointer if it is not `NULL` before allocating new memory
 */
INT128_T_IMPLEMENTATION int128_error_t int128_new(int128_t * *const dst, uint64_t hi, uint64_t lo);

/**
 * @brief Frees an `int128_t` from memory
 * @param ptr The address of a pointer to free: `&(int128_t *)`
 * @return `INT128_T_SUCCESS` on successful free, `INT128_T_INVALID_ARG` if `NULL` is passed in
 */
INT128_T_IMPLEMENTATION int128_error_t int128_free(int128_t * *const ptr);

// --- // Equalities

/**
 * @brief Checks if two `int128_t`s are equal
 * @param a The first `int128_t`
 * @param b The second `int128_t`
 * @return `true` if they are equal, `false` otherwise
 */
INT128_T_IMPLEMENTATION bool int128_equals(int128_t a, int128_t b);

/**
 * @brief Checks if two `int128_t`s are not equal
 * @param a The first `int128_t`
 * @param b The second `int128_t`
 * @return `true` if they are not equal, `false` otherwise
 */
INT128_T_IMPLEMENTATION bool int128_not_equals(int128_t a, int128_t b);

/**
 * @brief Checks if `a` is less than `b`
 * @param a The first `int128_t`
 * @param b The second `int128_t`
 * @return `true` if `a` is less than `b`, `false` otherwise
 */
INT128_T_IMPLEMENTATION bool int128_less_than(int128_t a, int128_t b);

/**
 * @brief Checks if `a` is greater than `b`
 * @param a The first `int128_t`
 * @param b The second `int128_t`
 * @return `true` if `a` is greater than `b`, `false` otherwise
 */
INT128_T_IMPLEMENTATION bool int128_greater_than(int128_t a, int128_t b);

// --- // Arithmetic

/**
 * @brief Adds two `int128_t`s
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

// --- // Other

/**
 * @brief Turns an `int128_t` into a heap-allocated string representation.
 * @param a The `int128_t` to turn into a string
 * @param ret The address of a `char *` so it can point to a memory allocated `char *`
 * @note The implementation right now is just the higher bits and the lower bits represented as two `uint64_t`s with a NULL character at the end.
 */
INT128_T_IMPLEMENTATION int128_error_t int128_tostr(int128_t a, char * *const ret);

#ifdef INT128_T_IMPLEMENTATION

INT128_T_IMPLEMENTATION int128_error_t int128_new(int128_t * *const dst, uint64_t hi, uint64_t lo) {
	if (dst == NULL) return INT128_T_INVALID_ARG; // No pointer address given

	if (*dst != NULL) free(*dst); // Free the struct assuming it's on the heap
	*dst = malloc(sizeof(int128_t)); // Allocate it
	if (*dst == NULL) return INT128_T_NO_MEMORY; // Allocation failed

	// Assign
	(*dst)->hi = hi;
	(*dst)->lo = lo;

	return INT128_T_SUCCESS;
}

INT128_T_IMPLEMENTATION int128_error_t int128_free(int128_t * *const ptr) {
	if (ptr == NULL) return INT128_T_INVALID_ARG; // No pointer address given

	free(*ptr); // Free it
	*ptr = NULL; // Set to NULL

	return INT128_T_SUCCESS;
}

// --- //

INT128_T_IMPLEMENTATION bool int128_equals(int128_t a, int128_t b) { return (a.hi == b.hi) && (a.lo == b.lo); }

INT128_T_IMPLEMENTATION bool int128_not_equals(int128_t a, int128_t b) { return (a.hi != b.hi) || (a.lo != b.lo); }

INT128_T_IMPLEMENTATION bool int128_less_than(int128_t a, int128_t b) { return (a.hi < b.hi) || ((a.hi == b.hi) && (a.lo < b.lo)); }

INT128_T_IMPLEMENTATION bool int128_greater_than(int128_t a, int128_t b) { return (a.hi > b.hi) || ((a.hi == b.hi) && (a.lo > b.lo)); }

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

// --- //

INT128_T_IMPLEMENTATION int128_error_t int128_tostr(int128_t a, char * *const ret) {
	if (ret == NULL) return INT128_T_INVALID_ARG; // No pointer given

	*ret = (char*)malloc(INT128_TOSTRFUNC_REPRSIZE); // Allocate string for representation
	if (*ret == NULL) return INT128_T_NO_MEMORY; // malloc fails

	sprintf(*ret, "%" PRIu64 "%" PRIu64, a.hi, a.lo); // Format and add null terminator
	(*ret)[INT128_TOSTRFUNC_REPRSIZE - 1] = '\0';

	return INT128_T_SUCCESS;
}

#endif // INT128_T_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // INT128_T_H
