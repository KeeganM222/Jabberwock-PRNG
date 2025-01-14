/*
File:		Generator.cpp
Author:		Keegan MacDonald
Created:	2025.01.11@11:59
Purpose:	Implement the main entry point to the Generator program for the
			Jabberwock PRNG.
*/

#include <Jabberwock/Jabberwock.h>

#include <iostream>
#include <fstream>
#include <bitset>

// Implement Generator module functions.

// The set of standard printable characters.
const static std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz`1234567890-=["
	"]\\;',./ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()_+{}|:\"<>?";

/*
Generate binary data with the Jabberwock PRNG and write it to a file or the
console.
Parameter: Jabberwock& jabberwock - The Jabberwock PRNG.
Parameter: size_t outputSymbolCount - The number of bytes to generate.
Parameter: const std::string& outputFileName - The file name to write to.
*/
void generateBinary(Jabberwock& jabberwock, size_t outputSymbolCount,
	const std::string& outputFileName) {
	std::ofstream outputFile;
	if (!outputFileName.empty()) {
		outputFile.open(outputFileName, std::ios::binary);
	}
	bool progress[10];
	for (size_t i = 0; i < 10; i++) {
		progress[i] = false;
	}
	for (size_t i = 0; i < outputSymbolCount; i++) {
		uint8_t byte = jabberwock.generate();
		if (!outputFileName.empty()) {
			outputFile.write((const char*)(&byte), 1);
			for (size_t j = 0; j < 10; j++) {
				if ((float)i / (float)outputSymbolCount > (float)j / 10.0f
					&& !progress[j]) {
					progress[j] = true;
					std::cout << (j * 10.0f) << "%, ";
				}
			}
		}
		else {
			std::cout << std::bitset<8>(byte);
		}
	}
}

/*
Generate text data with the Jabberwock PRNG and write it to a file or the
console.
Parameter: Jabberwock& jabberwock - The Jabberwock PRNG.
Parameter: size_t outputSymbolCount - The number of characters to generate.
Parameter: const std::string& outputFileName - The file name to write to.
Parameter: const std::string& allowedCharacters - The set of characters to
choose from when generating data.
*/
void generateText(Jabberwock& jabberwock, size_t outputSymbolCount,
	const std::string& outputFileName, const std::string& allowedCharacters) {
	std::ofstream outputFile;
	if (!outputFileName.empty()) {
		outputFile.open(outputFileName);
	}
	bool progress[10];
	for (size_t i = 0; i < 10; i++) {
		progress[i] = false;
	}
	for (size_t i = 0; i < outputSymbolCount; i++) {
		unsigned int selector = 0x00000000;
		for (size_t j = 0; j < 4; j++) {
			uint8_t byte = jabberwock.generate();
			selector <<= 8;
			selector |= (unsigned int)byte;
		}
		char character = allowedCharacters[
			selector % allowedCharacters.length()];
		if (!outputFileName.empty()) {
			outputFile << character;
			for (size_t j = 0; j < 10; j++) {
				if ((float)i / (float)outputSymbolCount > (float)j / 10.0f
					&& !progress[j]) {
					progress[j] = true;
					std::cout << (j * 10.0f) << "%, ";
				}
			}
		}
		else {
			std::cout << character;
		}
	}
}

/*
Generate integers with the Jabberwock PRNG and write it to a file or the
console.
Parameter: Jabberwock& jabberwock - The Jabberwock PRNG.
Parameter: size_t outputSymbolCount - The number of integers to generate.
Parameter: const std::string& outputFileName - The file name to write to.
Parameter: int minimum - The minimum output value to generate.
Parameter: int maximum - The maximum output value to generate.
*/
void generateIntegers(Jabberwock& jabberwock, size_t outputSymbolCount,
	const std::string& outputFileName, int minimum, int maximum) {
	std::ofstream outputFile;
	if (!outputFileName.empty()) {
		outputFile.open(outputFileName);
	}
	bool progress[10];
	for (size_t i = 0; i < 10; i++) {
		progress[i] = false;
	}
	for (size_t i = 0; i < outputSymbolCount; i++) {
		unsigned int selector = 0x00000000;
		for (size_t j = 0; j < 4; j++) {
			uint8_t byte = jabberwock.generate();
			selector <<= 8;
			selector |= (unsigned int)byte;
		}
		int range = maximum - minimum;
		int integer = minimum + (selector % (range + 1));
		if (!outputFileName.empty()) {
			outputFile << integer << ", ";
			for (size_t j = 0; j < 10; j++) {
				if ((float)i / (float)outputSymbolCount > (float)j / 10.0f
					&& !progress[j]) {
					progress[j] = true;
					std::cout << (j * 10.0f) << "%, ";
				}
			}
		}
		else {
			std::cout << integer << ", ";
		}
	}
}

/*
Generate floats with the Jabberwock PRNG and write it to a file or the console.
Parameter: Jabberwock& jabberwock - The Jabberwock PRNG.
Parameter: size_t outputSymbolCount - The number of floats to generate.
Parameter: const std::string& outputFileName - The file name to write to.
*/
void generateFloats(Jabberwock& jabberwock, size_t outputSymbolCount,
	const std::string& outputFileName, float minimum, float maximum) {
	std::ofstream outputFile;
	if (!outputFileName.empty()) {
		outputFile.open(outputFileName);
	}
	bool progress[10];
	for (size_t i = 0; i < 10; i++) {
		progress[i] = false;
	}
	for (size_t i = 0; i < outputSymbolCount; i++) {
		unsigned int selector = 0x00000000;
		for (size_t j = 0; j < 4; j++) {
			uint8_t byte = jabberwock.generate();
			selector <<= 8;
			selector |= (unsigned int)byte;
		}
		float range = maximum - minimum;
		float flt = minimum + (range * ((float)selector / (float)UINT_MAX));
		if (!outputFileName.empty()) {
			outputFile << flt << ", ";
			for (size_t j = 0; j < 10; j++) {
				if ((float)i / (float)outputSymbolCount > (float)j / 10.0f
					&& !progress[j]) {
					progress[j] = true;
					std::cout << (j * 10.0f) << "%, ";
				}
			}
		}
		else {
			std::cout << flt << ", ";
		}
	}
}

/*
The main entry point to the Generator program.
Parameter: int argc - The number of command line arguments to the program.
Parameter: char** argv - The command line arguments to the program.
Returns: int - The exit code of the program.
*/
int main(int argc, char** argv) {
	srand((unsigned int)time(0));
	std::cout << "Jabberwock PRNG Generator" << std::endl << std::endl;
	std::cout << "Seed: ";
	std::string seed = "";
	if (!std::getline(std::cin, seed)) {
		std::cout << "Invalid input" << std::endl;
		return EXIT_FAILURE;
	}
	if (seed.empty()) {
		for (size_t i = 0; i < 64; i++) {
			seed += CHARACTERS[rand() % CHARACTERS.length()];
		}
		std::cout << "Using default randomized seed \"" << seed << "\""
			<< std::endl;
	}
	std::cout << "Level count: ";
	std::string levelCountStr = "";
	if (!std::getline(std::cin, levelCountStr)) {
		std::cout << "Invalid input" << std::endl;
		return EXIT_FAILURE;
	}
	unsigned int levelCount = 0;
	if (!levelCountStr.empty()) {
		int levelCountInt = std::atoi(levelCountStr.c_str());
		if (levelCountInt <= 2) {
			std::cout << "Invalid level count" << std::endl;
			return EXIT_FAILURE;
		}
		levelCount = (unsigned int)levelCountInt;
	}
	else {
		levelCount = 4;
		std::cout << "Using default level count " << levelCount << std::endl;
	}
	Jabberwock jabberwock;
	jabberwock.seed(seed, levelCount);
	std::cout << "Seeded Jabberwock PRNG" << std::endl << std::endl;
	std::cout << "Output symbol count: ";
	std::string outputSymbolCountStr = "";
	if (!std::getline(std::cin, outputSymbolCountStr)) {
		std::cout << "Invalid input" << std::endl;
		jabberwock.clear();
		return EXIT_FAILURE;
	}
	size_t outputSymbolCount = 0;
	if (!outputSymbolCountStr.empty()) {
		int outputSymbolCountInt = std::atoi(outputSymbolCountStr.c_str());
		if (outputSymbolCountInt <= 0) {
			std::cout << "Invalid output symbol count" << std::endl;
			jabberwock.clear();
			return EXIT_FAILURE;
		}
		outputSymbolCount = (size_t)outputSymbolCountInt;
	}
	else {
		std::cout << "Invalid output symbol count" << std::endl;
		jabberwock.clear();
		return EXIT_FAILURE;
	}
	std::cout << "Output file name: ";
	std::string outputFileName = "";
	if (!std::getline(std::cin, outputFileName)) {
		std::cout << "Invalid input" << std::endl;
		jabberwock.clear();
		return EXIT_FAILURE;
	}
	std::ofstream outputFileTest(outputFileName);
	if (!outputFileTest.good() || outputFileName.empty()) {
		std::cout << "Using default console output" << std::endl;
		outputFileName = "";
	}
	outputFileTest.close();
	std::cout << std::endl << "Output types:" << std::endl << "1. Binary"
		<< std::endl << "2. Text" << std::endl << "3. Integers" << std::endl
		<< "4. Floats" << std::endl << "Option: ";
	std::string outputTypeStr = "";
	if (!std::getline(std::cin, outputTypeStr)) {
		std::cout << "Invalid input" << std::endl;
		jabberwock.clear();
		return EXIT_FAILURE;
	}
	int outputType = std::atoi(outputTypeStr.c_str());
	if (outputType <= 0 || outputType >= 5) {
		std::cout << "Invalid output type" << std::endl;
		jabberwock.clear();
		return EXIT_FAILURE;
	}
	if (outputType == 1) {
		std::cout << std::endl << "Generating binary..." << std::endl
			<< std::endl;
		generateBinary(jabberwock, outputSymbolCount, outputFileName);
	}
	else if (outputType == 2) {
		std::cout << std::endl << "Allowed characters: ";
		std::string allowedCharacters = "";
		if (!std::getline(std::cin, allowedCharacters)) {
			std::cout << "Invalid input" << std::endl;
			jabberwock.clear();
			return EXIT_FAILURE;
		}
		if (allowedCharacters.empty()) {
			allowedCharacters = CHARACTERS;
			std::cout << "Using default allowed character set \""
				<< allowedCharacters << "\"" << std::endl;
		}
		std::cout << std::endl << "Generating text..." << std::endl
			<< std::endl;
		generateText(jabberwock, outputSymbolCount, outputFileName,
			allowedCharacters);
	}
	else if (outputType == 3) {
		std::cout << std::endl << "Minimum value: ";
		std::string minimumStr = "";
		if (!std::getline(std::cin, minimumStr)) {
			std::cout << "Invalid input" << std::endl;
			jabberwock.clear();
			return EXIT_FAILURE;
		}
		int minimum = std::atoi(minimumStr.c_str());
		std::cout << "Using minimum value " << minimum << std::endl
			<< "Maximum value: ";
		std::string maximumStr = "";
		if (!std::getline(std::cin, maximumStr)) {
			std::cout << "Invalid input" << std::endl;
			jabberwock.clear();
			return EXIT_FAILURE;
		}
		int maximum = std::atoi(maximumStr.c_str());
		if (maximum <= minimum) {
			std::cout << "Invalid maximum value" << std::endl;
			jabberwock.clear();
			return EXIT_FAILURE;
		}
		std::cout << "Using maximum value " << maximum << std::endl
			<< std::endl;
		generateIntegers(jabberwock, outputSymbolCount, outputFileName,
			minimum, maximum);
	}
	else if (outputType == 4) {
		std::cout << std::endl << "Minimum value: ";
		std::string minimumStr = "";
		if (!std::getline(std::cin, minimumStr)) {
			std::cout << "Invalid input" << std::endl;
			jabberwock.clear();
			return EXIT_FAILURE;
		}
		float minimum = (float)std::atof(minimumStr.c_str());
		std::cout << "Using minimum value " << minimum << std::endl
			<< "Maximum value: ";
		std::string maximumStr = "";
		if (!std::getline(std::cin, maximumStr)) {
			std::cout << "Invalid input" << std::endl;
			jabberwock.clear();
			return EXIT_FAILURE;
		}
		float maximum = (float)std::atof(maximumStr.c_str());
		if (maximum <= minimum) {
			std::cout << "Invalid maximum value" << std::endl;
			jabberwock.clear();
			return EXIT_FAILURE;
		}
		std::cout << "Using maximum value " << maximum << std::endl
			<< std::endl;
		generateFloats(jabberwock, outputSymbolCount, outputFileName,
			minimum, maximum);
	}
	jabberwock.clear();
	std::cout << std::endl << std::endl << "Cleared Jabberwock PRNG"
		<< std::endl;
	return EXIT_SUCCESS;
}