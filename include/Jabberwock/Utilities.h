/*
File:		Utilities.h
Author:		Keegan MacDonald
Created:	2025.01.11@12:52
Purpose:	Declare miscellaneous utility functions for the Jabberwock PRNG
			library.
*/

#ifndef JABBERWOCK_UTILITIES_H
#define JABBERWOCK_UTILITIES_H

#include <string>
#include <vector>

// The set of hex symbols for converting between hex and binary.
const std::string HEX_CHARACTERS = "0123456789abcdef";
// A set of 16 permutations of 4 objects.
const static std::vector<std::vector<size_t>> PERMUTATIONS_4 = {
		{ 2, 1, 3, 4, },
		{ 3, 1, 2, 4, },
		{ 2, 3, 1, 4, },
		{ 3, 2, 1, 4, },
		{ 3, 2, 4, 1, },
		{ 3, 4, 2, 1, },
		{ 4, 2, 3, 1, },
		{ 4, 1, 3, 2, },
		{ 1, 4, 3, 2, },
		{ 4, 3, 1, 2, },
		{ 1, 3, 4, 2, },
		{ 2, 1, 4, 3, },
		{ 1, 2, 4, 3, },
		{ 2, 4, 1, 3, },
		{ 1, 4, 2, 3, },
		{ 4, 1, 2, 3, },
};
// A set of 16 permutations of 8 objects.
const static std::vector<std::vector<size_t>> PERMUTATIONS_8 = {
	{ 1, 3, 6, 5, 8, 7, 4, 2, },
	{ 1, 5, 8, 4, 6, 3, 7, 2, },
	{ 8, 6, 5, 1, 2, 3, 7, 4, },
	{ 2, 1, 6, 7, 4, 3, 8, 5, },
	{ 3, 2, 8, 7, 5, 6, 4, 1, },
	{ 3, 6, 1, 2, 8, 7, 5, 4, },
	{ 4, 8, 5, 2, 6, 7, 1, 3, },
	{ 4, 7, 2, 5, 1, 6, 8, 3, },
	{ 5, 3, 4, 6, 8, 1, 7, 2, },
	{ 5, 7, 1, 6, 3, 2, 8, 4, },
	{ 7, 1, 8, 6, 4, 5, 2, 3, },
	{ 2, 4, 3, 7, 1, 6, 8, 5, },
	{ 6, 2, 5, 3, 1, 7, 8, 4, },
	{ 6, 5, 2, 3, 1, 7, 8, 4, },
	{ 7, 8, 6, 4, 3, 2, 5, 1, },
	{ 8, 4, 1, 2, 3, 5, 7, 6, },
};
/*
Compute the SHA-512 hash of an input string and return it as a hex string.
Parameter: const std::string& input - The input string.
Returns: std::string - The hex representation of the hash of the input string.
*/
extern std::string SHA512String(const std::string&);
/*
Compute the SHA-512 hash of an input string and return it as binary.
Parameter: const std::string& input - The input string.
Returns: std::vector<bool> - The binary representation of the hash of the input
string.
*/
extern std::vector<bool> SHA512Binary(const std::string&);
/*
Permute an input string by its SHA-512 hash.
Parameter: const std::string& input - The input string.
Returns: std::string - The permuted string.
*/
extern std::string permuteString(const std::string&);

#endif