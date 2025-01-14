/*
File:		Node.cpp
Author:		Keegan MacDonald
Created:	2025.01.11@12:02
Purpose:	Implement the Node class functions found in Nodes.h.
*/

#include "Nodes.h"
#include "Utilities.h"

// Implement Node class functions.

void Node::seed(const std::string& seed, unsigned int levelCount) {
	std::string permutedSeed = permuteString(seed);
	for (Node* child : m_children) {
		child->seed(permutedSeed, levelCount - 1);
		permutedSeed = permuteString(permutedSeed);
	}
}

void Node::clear() {
	for (Node* child : m_children) {
		child->clear();
	}
	m_children.clear();
}