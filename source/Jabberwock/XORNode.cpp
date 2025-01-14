/*
File:		XORNode.cpp
Author:		Keegan MacDonald
Created:	2025.01.12@00:55
Purpose:	Implement the XORNode class functions found in Nodes.h.
*/

#include "Nodes.h"
#include "Utilities.h"

// Implement XORNode class functions.

void XORNode::seed(const std::string& seed, unsigned int levelCount) {
	std::vector<bool> seedHashBinary = SHA512Binary(seed);
	if (levelCount > 1) {
		uint8_t XORCount = 2 + (uint8_t)seedHashBinary[508];
		for (size_t i = 0; i < XORCount; i++) {
			m_children.push_back(new XORNode);
		}
		uint8_t ANDCount = 1 + (uint8_t)seedHashBinary[509];
		for (size_t i = 0; i < ANDCount; i++) {
			m_children.push_back(new ANDNode);
		}
		uint8_t ORCount = 1 + (uint8_t)seedHashBinary[510];
		for (size_t i = 0; i < ORCount; i++) {
			m_children.push_back(new ORNode);
		}
	}
	else {
		uint8_t glfsrCount = 0x00;
		for (size_t i = 510; i < 512; i++) {
			glfsrCount <<= 1;
			glfsrCount |= (uint8_t)seedHashBinary[i];
		}
		glfsrCount += 5;
		for (size_t i = 0; i < glfsrCount; i++) {
			m_children.push_back(new GLFSRNode);
		}
	}
	Node::seed(seed, levelCount);
}

uint8_t XORNode::generate() {
	uint8_t byte = m_children[0]->generate();
	for (size_t i = 1; i < m_children.size(); i++) {
		byte ^= m_children[i]->generate();
	}
	return byte;
}