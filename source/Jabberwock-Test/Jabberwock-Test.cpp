/*
File:		Jabberwock-Test.cpp
Author:		Keegan MacDonald
Created:	2025.01.12@13:00
Purpose:	Implement the main entry point to the Jabberwock-test program for
			the Jabberwock PRNG.
*/

#include <Jabberwock/Jabberwock.h>

#include <iostream>
#include <fstream>
#include <chrono>

// Implement Jabberwock-Test module functions

// The set of standard printable characters.
const static std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz`1234567890-=["
	"]\\;',./ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()_+{}|:\"<>?";

/*
The main entry point of the Jabberwock-Test program; generates 100x128502B data
files using random seeds for 4-level Jabberwock PRNG trees.
Parameter: int argc - The number of command line arguments for the program.
Parameter: char** argv - The command line arguments for the program.
Returns: int - The exit code of the program.
*/
int main(int argc, char** argv) {
	std::cout << "Jabberwock PRNG Test" << std::endl << std::endl;
	std::cout << "Output file count: ";
	std::string outputFileCountStr = "";
	if (!std::getline(std::cin, outputFileCountStr)) {
		std::cout << "Invalid input" << std::endl;
		return EXIT_FAILURE;
	}
	size_t outputFileCount = 0;
	if (!outputFileCountStr.empty()) {
		int outputFileCountInt = std::atoi(outputFileCountStr.c_str());
		if (outputFileCountInt < 1) {
			std::cout << "Invalid output file count" << std::endl;
			return EXIT_FAILURE;
		}
		outputFileCount = (size_t)outputFileCountInt;
	}
	else {
		outputFileCount = 100;
		std::cout << "Using default output file count " << outputFileCount
			<< std::endl;
	}
	std::cout << "Output file size: ";
	std::string outputFileSizeStr = "";
	if (!std::getline(std::cin, outputFileSizeStr)) {
		std::cout << "Invalid input" << std::endl;
		return EXIT_FAILURE;
	}
	size_t outputFileSize = 0;
	if (!outputFileSizeStr.empty()) {
		int outputFileSizeInt = std::atoi(outputFileSizeStr.c_str());
		if (outputFileSizeInt < 1) {
			std::cout << "Invalid output file size" << std::endl;
			return EXIT_FAILURE;
		}
		outputFileSize = (size_t)outputFileSizeInt;
	}
	else {
		outputFileSize = 128502;
		std::cout << "Using default output file size " << outputFileSize
			<< "B" << std::endl;
	}
	std::cout << "Level count: ";
	std::string levelCountStr = "";
	if (!std::getline(std::cin, levelCountStr)) {
		std::cout << "Invalid input" << std::endl;
		return EXIT_FAILURE;
	}
	size_t levelCount = 0;
	if (!levelCountStr.empty()) {
		int levelCountInt = std::atoi(levelCountStr.c_str());
		if (levelCountInt < 3) {
			std::cout << "Invalid level count" << std::endl;
			return EXIT_FAILURE;
		}
		levelCount = (size_t)levelCountInt;
	}
	else {
		levelCount = 4;
		std::cout << "Using default level count " << levelCount << std::endl;
	}
	std::cout << std::endl;
	srand((unsigned int)time(0));
	for (size_t outputFileIndex = 0; outputFileIndex < outputFileCount;
		outputFileIndex++) {
		std::string outputFileName = "Data/"
			+ std::to_string(outputFileIndex + 1) + ".bin";
		std::cout << "Generating data file \"" << outputFileName << "\""
			<< std::endl;
		std::string seed = "";
		for (size_t i = 0; i < 64; i++) {
			seed += CHARACTERS[rand() % CHARACTERS.length()];
		}
		std::cout << "Seed value: \"" << seed << "\"" << std::endl
			<< "Level count: 4" << std::endl;
		Jabberwock jabberwock;
		jabberwock.seed(seed, 4);
		std::cout << "Seeded Jabberwock PRNG" << std::endl;
		bool progress[10];
		for (size_t i = 0; i < 10; i++) {
			progress[i] = false;
		}
		std::ofstream outputFile(outputFileName, std::ios::binary);
		std::chrono::steady_clock::time_point start
			= std::chrono::steady_clock::now();
		for (size_t i = 0; i < outputFileSize; i++) {
			for (size_t j = 0; j < 10; j++) {
				if ((float)i / (float)outputFileSize > (float)j / 10.0f
					&& !progress[j]) {
					progress[j] = true;
					std::cout << (j * 10.0f) << "%, ";
				}
			}
			uint8_t outputByte = jabberwock.generate();
			outputFile.write((const char*)(&outputByte), 1);
		}
		std::chrono::steady_clock::time_point end
			= std::chrono::steady_clock::now();
		std::cout << "Generated in " << std::chrono::duration_cast<
			std::chrono::seconds>(end - start).count() << "s" << std::endl;
		outputFile.close();
		jabberwock.clear();
		std::cout << "Cleared Jabberwock PRNG" << std::endl << std::endl;
	}
	return EXIT_SUCCESS;
}