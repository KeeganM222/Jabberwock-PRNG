/*
File:		Nodes.h
Author:		Keegan MacDonald
Created:	2025.01.11@11:32
Purpose:	Declare all the types of nodes in the Jabberwock PRNG tree.
*/

#ifndef JABBERWOCK_NODES_H
#define JABBERWOCK_NODES_H

#include <string>
#include <vector>

// An abstract node in the Jabberwock PRNG tree.
class Node {
public:
	/*
	Initialize this node's memory and that of its children.
	Parameter: const std::string& seed - The seed data for this node.
	Parameter: unsigned int - The number of levels in the tree below this node.
	*/
	virtual void seed(const std::string&, unsigned int);
	/*
	Generate a pseudo-random byte of output data from this node.
	Returns: uint8_t - A pseudo-random byte.
	*/
	virtual uint8_t generate() = 0;
	/*
	Free this node's memory and that of its children.
	*/
	virtual void clear();

protected:
	// The set of pointers to this node's children.
	std::vector<Node*> m_children;
};

// An XOR node in the Jabberwock PRNG tree.
class XORNode : public Node {
public:
	/*
	Initialize the memory of this XOR node's children.
	Parameter: const std::string& seed - The seed data for this XOR node.
	Parameter: unsigned int levelCount - The number of levels in the tree below
	this XOR node.
	*/
	void seed(const std::string&, unsigned int) override;
	/*
	Generate a pseudo-random byte of output data from this XOR node.
	Returns: uint8_t - The XOR sum of the output bytes of this XOR node's
	children.
	*/
	uint8_t generate() override;
};

// An AND node in the Jabberwock PRNG tree.
class ANDNode : public Node {
public:
	/*
	Initialize the memory of this AND node's children.
	Parameter: const std::string& seed - The seed data for this AND node.
	Parameter: unsigned int levelCount - The number of levels in the tree below
	this AND node.
	*/
	void seed(const std::string&, unsigned int) override;
	/*
	Generate a pseudo-random byte of output data from this AND node.
	Returns: uint8_t - The AND product of the output bytes of this AND node's
	children.
	*/
	uint8_t generate() override;
};

// An OR node in the Jabberwock PRNG tree.
class ORNode : public Node {
public:
	/*
	Initialize the memory of this OR node's children.
	Parameter: const std::string& seed - The seed data for this OR node.
	Parameter: unsigned int levelCount - The number of levels in the tree below
	this OR node.
	*/
	void seed(const std::string&, unsigned int) override;
	/*
	Generate a pseudo-random byte of output data from this OR node.
	Returns: uint8_t - The OR gate combination of the output bytes of this OR
	node's children.
	*/
	uint8_t generate() override;
};

// A Galois linear feedback shift register node in the Jabberwock PRNG tree.
class GLFSRNode : public Node {
public:
	/*
	Initialize this GLFSR node's memory.
	Parameter: const std::string& seed - The seed data for this GLFSR node.
	Parameter: unsigned int - Unused parameter.
	*/
	void seed(const std::string&, unsigned int) override;
	/*
	Generate a pseudo-random byte of output data from this GLFSR node.
	Returns: uint8_t - A pseudo-random byte.
	*/
	uint8_t generate() override;
	/*
	Free this GLFSR node's memory.
	*/
	void clear() override;

private:
	// The current state buffer of this node's GLFSR.
	std::vector<bool> m_state;
	// The tap buffer of this node's GLFSR.
	std::vector<bool> m_taps;
};

#endif