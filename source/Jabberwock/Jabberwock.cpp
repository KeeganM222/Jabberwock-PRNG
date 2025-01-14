/*
File:		Jabberwock.cpp
Author:		Keegan MacDonald
Created:	2025.01.12@15:34
Purpose:	Implement Jabberwock class functions found in Jabberwock.h.
*/

#include "Jabberwock.h"

// Implement Jabberwock class functions.

void Jabberwock::seed(const std::string& seed, unsigned int levelCount) {
	m_root.seed(seed, levelCount - 1);
}

uint8_t Jabberwock::generate() {
	return m_root.generate();
}

void Jabberwock::clear() {
	m_root.clear();
}