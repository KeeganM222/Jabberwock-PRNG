/*
File:		Utilities.cpp
Author:		Keegan MacDonald
Created:	2025.01.11@12:57
Purpose:	Implement functions found in Utilities.h.
*/

#include "Utilities.h"

#include <SHA/SHA512.h>

// Implement Utilities module functions.

std::string SHA512String(const std::string& input) {
	SHA512 sha;
	return sha.hash(input);
}

std::vector<bool> SHA512Binary(const std::string& input) {
	std::string hashString = SHA512String(input);
	std::vector<bool> hashBinary;
	for (size_t i = 0; i < hashString.length(); i++) {
		char c = hashString[i];
		uint8_t bits = 0x00;
		for (size_t j = 0; j < 16; j++) {
			if (HEX_CHARACTERS[j] == c) {
				bits = (uint8_t)j;
				break;
			}
		}
		for (size_t j = 0; j < 4; j++) {
			hashBinary.push_back((bool)((bits >> (4 - j - 1)) & 0x01));
		}
	}
	return hashBinary;
}

std::string permuteString(const std::string& input) {
	std::string permutation = input;
	std::string seedHashString = SHA512String(input);
	size_t paddingIndex = 0;
	do {
		permutation += seedHashString[paddingIndex];
		paddingIndex++;
	} while (permutation.length() % 8 != 0);
	std::vector<std::string> chunks4;
	for (size_t i = 0; i < permutation.length(); i += 4) {
		chunks4.push_back(permutation.substr(i, 4));
	}
	permutation.clear();
	for (size_t i = 0; i < chunks4.size(); i++) {
		std::vector<bool> chunk4HashBinary = SHA512Binary(chunks4[i]);
		uint8_t permutation4Index = 0x00;
		for (size_t j = 508; j < 512; j++) {
			permutation4Index <<= 1;
			permutation4Index |= (uint8_t)chunk4HashBinary[j];
		}
		for (size_t j = 0; j < 4; j++) {
			permutation += chunks4[i][PERMUTATIONS_4[permutation4Index][j] - 1];
		}
	}
	std::vector<std::string> chunks8(8);
	size_t chunk8Length = permutation.length() / 8;
	for (size_t i = 0; i < 8; i++) {
		chunks8[i] = permutation.substr(i * chunk8Length, chunk8Length);
	}
	std::vector<bool> permutationHashBinary = SHA512Binary(permutation);
	uint8_t permutation8Index = 0x00;
	for (size_t i = 508; i < 512; i++) {
		permutation8Index <<= 1;
		permutation8Index |= (uint8_t)permutationHashBinary[i];
	}
	permutation.clear();
	for (size_t i = 0; i < 8; i++) {
		permutation += chunks8[PERMUTATIONS_8[permutation8Index][i] - 1];
	}
	return permutation;
}