/*
File:		Jabberwock.h
Author:		Keegan MacDonald
Created:	2025.01.12@15:34
Purpose:	Declare the wrapper class of the Jabberwock PRNG library.
*/

#ifndef JABBERWOCK_JABBERWOCK_H
#define JABBERWOCK_JABBERWOCK_H

#include "Nodes.h"

// The main wrapper class of the Jabberwock PRNG library.
class Jabberwock {
public:
	/*
	Initialize the Jabberwock PRNG's memory.
	Parameter: const std::string& seed - The seed data for the PRNG.
	Parameter: unsigned int levelCount - The number of levels for the PRNG tree.
	*/
	void seed(const std::string&, unsigned int);
	/*
	Get a pseudo-random byte of output from the Jabberwock PRNG.
	Returns: uint8_t - A pseudo-random byte.
	*/
	uint8_t generate();
	/*
	Free the Jabberwock PRNG's memory.
	*/
	void clear();

private:
	// The root node of the Jabberwock PRNG tree.
	XORNode m_root;
};

#endif