/*
File:		OneTimePad.cpp
Author:		Keegan MacDonald
Created:	2025.01.13@08:23
Purpose:	Implement the main entry point to the OneTimePad program for the
			Jabberwock PRNG.
*/

#include <Jabberwock/Jabberwock.h>

#include <iostream>
#include <fstream>

// Implement OneTimePad module functions.

// The set of standard printable characters.
const static std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz`1234567890-=["
	"]\\;',./ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()_+{}|:\"<>?";
// The set of hex characters.
const static std::string HEX_CHARACTERS = "0123456789ABCDEF";

/*
The main entry point to the OneTimePad program.
Parameter: int argc - The number of command line arguments to the program.
Parameter: char** argv - The command line arguments to the program.
Returns: int - The exit code of the program.
*/
int main(int argc, char** argv) {
	srand((unsigned int)time(0));
	std::cout << "Jabberwock PRNG One-Time-Pad" << std::endl << std::endl;
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
	std::cout << "Input file name: ";
	std::string inputFileName = "";
	if (!std::getline(std::cin, inputFileName)) {
		std::cout << "Invalid input" << std::endl;
		jabberwock.clear();
		return EXIT_FAILURE;
	}
	std::ifstream inputFile;
	inputFile.open(inputFileName, std::ios::binary);
	if (!inputFile.good()) {
		std::cout << "Invalid input file" << std::endl;
		jabberwock.clear();
		return EXIT_FAILURE;
	}
	inputFile.seekg(0, std::ios::end);
	size_t inputFileSize = (size_t)inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);
	inputFileSize -= (size_t)inputFile.tellg();
	std::cout << "Input file contains " << inputFileSize << "B" << std::endl;
	std::cout << "Output file name: ";
	std::string outputFileName = "";
	if (!std::getline(std::cin, outputFileName)) {
		std::cout << "Invalid input" << std::endl;
		jabberwock.clear();
		return EXIT_FAILURE;
	}
	std::ofstream outputFile;
	outputFile.open(outputFileName, std::ios::binary);
	if (!outputFile.good()) {
		std::cout << "Invalid output file" << std::endl;
		jabberwock.clear();
		return EXIT_FAILURE;
	}
	std::cout << std::endl << "Processing..." << std::endl << std::endl;
	bool progress[10];
	for (size_t i = 0; i < 10; i++) {
		progress[i] = false;
	}
	for (size_t i = 0; i < inputFileSize; i++) {
		uint8_t inputByte = 0x00;
		inputFile.read((char*)(&inputByte), 1);
		uint8_t outputByte = inputByte ^ jabberwock.generate();
		inputByte = 0x00;
		outputFile.write((const char*)(&outputByte), 1);
		outputByte = 0x00;
		for (size_t j = 0; j < 10; j++) {
			if ((float)i / (float)inputFileSize > (float)j / 10.0f
				&& !progress[j]) {
				progress[j] = true;
				std::cout << (j * 10.0f) << "%, ";
			}
		}
	}
	std::cout << "Finished" << std::endl;
	inputFile.close();
	outputFile.close();
	jabberwock.clear();
	std::cout << std::endl << "Cleared Jabberwock PRNG" << std::endl;
	return EXIT_SUCCESS;
}