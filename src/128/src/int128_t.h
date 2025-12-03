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
#define INT128_ACTUAL_SIZE (sizeof(int128_t)) // Actual size of an `int128_t` from `sizeof`
#define INT128_UINT64_MSB ((uint64_t)(1 << 63)) // The most significant bit in a `uint64_t`
#define INT128_ZERO ((int128_t){ .hi = 0, .lo = 0 }) // The zero value for `int128_t`

#define INT128_FROM(hi, lo) ((int128_t){ .hi = (uint64_t)(hi), .lo = (uint64_t)(lo) }) // `int128_t` from `hi` and `lo` values

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

/**
 * @brief Divides an `int128_t` by 10 and returns the remainder.
 * @ param a A pointer to a `int128_t` so that the struct changes as it's divided by 10`
 * @return A `uint8_t` containing the remainder
 */
INT128_T_IMPLEMENTATION uint8_t int128_divide_mod10(int128_t *a);

// --- // Other

/**
 * @brief Shifts an `int128_t` to the left a specified number of bits, also counting overflow
 * @param a The `int128_t`
 * @param bit_count The specified number of bits to shift left
 * @returns The shifted-left `int128_t`
 */
INT128_T_IMPLEMENTATION int128_t int128_shift_left(int128_t a, size_t bit_count);

/**
 * @brief Shifts an `int128_t` to the right a specified number of bits, also counting overflow
 * @param a The `int128_t`
 * @param bit_count The specified number of bits to shift right
 * @returns The shifted-right `int128_t`
 */
INT128_T_IMPLEMENTATION int128_t int128_shift_right(int128_t a, size_t bit_count);

/**
 * @brief Shifts an `int128_t` to the left a specified number of bits, wrapping around the bits that overflow on the left to the right side
 * @example Shifting bits { hi = most significant bit of a 64-bit integer, lo = 0 } left by 1 bit results in { hi = 0, lo = 1 }
 * @param a The `int128_t`
 * @param bit_count The specified number of bits to shift left
 * @returns The shifted-left `int128_t`
 */
INT128_T_IMPLEMENTATION int128_t int128_shift_left_wrap(int128_t a, size_t bit_count);

/**
 * @brief Shifts an `int128_t` to the right a specified number of bits, wrapping around the bits that overflow on the left to the right side
 * @example Shifting bits { hi = 0, lo = most significant bit of a 64-bit integer } right by 1 bit results in { hi = most significant bit of a 64-bit integer, lo = 0 }
 * @param a The `int128_t`
 * @param bit_count The specified number of bits to shift right
 * @returns The shifted-right `int128_t`
 */
INT128_T_IMPLEMENTATION int128_t int128_shift_right_wrap(int128_t a, size_t bit_count);

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

INT128_T_IMPLEMENTATION uint8_t int128_divide_mod10(int128_t *a) {
	if (a == NULL) return 0; // No int128_t to operate on

	uint64_t new_hi, new_lo; 

	// Divide high limb
	uint64_t rem = a->hi % 10; // 128-bit numerator = (remainder << 64) + hi
	new_hi = a->hi / 10;

	// Divide low limb using leftover remainder
	// numerator = rem * 2^64 + lo
	// split lo into two 32-bit halves to avoid overflow
	uint64_t lo = a->lo;

	// Decompose lo for safe multiplication
	uint64_t hi32 = lo >> 32;
	uint64_t lo32 = lo & 0xffffffffull;

	// Compute numerator = (rem << 64) + lo
	uint64_t part1 = (rem << 32) + hi32;
	uint64_t q1 = part1 / 10;
	uint64_t r1 = part1 % 10;

	uint64_t part2 = (r1 << 32) + lo32;
	uint64_t q2 = part2 / 10;
	uint64_t r2 = part2 % 10;

	new_lo = (q1 << 32) | q2;
	rem = r2;

	a->hi = new_hi;
	a->lo = new_lo;

	return rem;
}

// --- //

INT128_T_IMPLEMENTATION int128_t int128_shift_left(int128_t a, size_t bit_count) { 
	if (bit_count >= 128) return (int128_t){ .hi = 0, .lo = 0 }; // Shifted out of existence

	if (bit_count >= 64) return (int128_t){ .hi = (a.lo << (bit_count - 64)), .lo = 0 }; // All low bits shifted into high bits

	return (int128_t){ .hi = (a.hi << bit_count) | (a.lo >> (64 - bit_count)), .lo = (a.lo << bit_count) }; // hi: shift high bits left, add overflow from low bits; lo: shift low bits left
}

INT128_T_IMPLEMENTATION int128_t int128_shift_right(int128_t a, size_t bit_count) {
	if (bit_count >= 128) return (int128_t){ .hi = 0, .lo = 0 }; // Shifted out of existence

	if (bit_count >= 64) return (int128_t){ .hi = 0, .lo = (a.hi >> (bit_count - 64)) }; // All high bits shifted into low bits

	return (int128_t){ .hi = (a.hi >> bit_count), .lo = (a.lo >> bit_count) | (a.hi << (64 - bit_count)) }; // hi: shift high bits right; lo: shift low bits right, add overflow from high bits
}

INT128_T_IMPLEMENTATION int128_t int128_shift_left_wrap(int128_t a, size_t bit_count) { return (int128_t){ .hi = (a.hi << bit_count) | (a.lo >> (64 - bit_count)), .lo = (a.lo << bit_count) | (a.hi >> (64 - bit_count)) }; }

INT128_T_IMPLEMENTATION int128_t int128_shift_right_wrap(int128_t a, size_t bit_count) { return (int128_t){ .hi = (a.hi >> bit_count) | (a.lo << (64 - bit_count)), .lo = (a.lo >> bit_count) | (a.hi << (64 - bit_count)) }; }

INT128_T_IMPLEMENTATION int128_error_t int128_tostr(int128_t a, char * *const ret) {
	if (ret == NULL) return INT128_T_INVALID_ARG; // No pointer given

	if (*ret != NULL) return INT128_T_INVALID_ARG; // Can't trust; only fixed length of 256
	*ret = calloc(256, sizeof(char));
	if (*ret = NULL) return INT128_T_NO_MEMORY; // calloc fails

	

	return INT128_T_SUCCESS;
}

#endif // INT128_T_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // INT128_T_H
