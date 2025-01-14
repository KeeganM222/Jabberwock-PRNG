/*
File:		GLFSRNode.cpp
Author:		Keegan MacDonald
Created:	2025.01.11@12:48
Purpose:	Implement the GLFSRNode class functions found in Nodes.h.
*/

#include "Nodes.h"
#include "Utilities.h"

// Implement GLFSRNode class functions.

void GLFSRNode::seed(const std::string& seed, unsigned int) {
	const std::vector<std::vector<size_t>> GLFSR_CONFIGS = {
		{ 1024, 1024, 1015, 1002, 1001, },
		{ 777, 777, 776, 767, 761, },
		{ 777, 777, 748, },
		{ 667, 667, 664, 660, 659, },
		{ 666, 666, 664, 659, 656, },
		{ 665, 665, 661, 659, 654, },
		{ 665, 665, 632, },
		{ 512, 512, 510, 507, 504, },
		{ 511, 511, 509, 503, 501, },
		{ 511, 511, 501, },
		{ 444, 444, 435, 432, 431, },
		{ 333, 333, 331, 329, 325, },
		{ 333, 333, 331, },
		{ 303, 303, 297, 291, 290, },
		{ 256, 256, 254, 251, 246, },
		{ 222, 222, 220, 217, 214, },
	};
	std::vector<bool> seedHashBinary = SHA512Binary(seed);
	uint8_t lsbs4 = 0x00;
	for (size_t i = 508; i < 512; i++) {
		lsbs4 <<= 1;
		lsbs4 |= (uint8_t)seedHashBinary[i];
	}
	size_t config = (size_t)lsbs4;
	m_state.resize(GLFSR_CONFIGS[config][0]);
	for (size_t i = 0; i < m_state.size(); i++) {
		m_state[i] = seedHashBinary[i % seedHashBinary.size()];
	}
	m_taps.resize(GLFSR_CONFIGS[config][0]);
	for (size_t i = 0; i < m_taps.size(); i++) {
		m_taps[i] = false;
	}
	for (size_t i = 1; i < GLFSR_CONFIGS[config].size(); i++) {
		m_taps[m_taps.size() - GLFSR_CONFIGS[config][i]] = true;
	}
}

uint8_t GLFSRNode::generate() {
	uint8_t byte = 0x00;
	for (size_t bit = 0; bit < 8; bit++) {
		bool outputBit = m_state[m_state.size() - 1];
		byte <<= 1;
		byte |= (uint8_t)outputBit;
		for (size_t i = m_state.size() - 1; i > 0; i--) {
			m_state[i] = m_state[i - 1];
		}
		m_state[0] = false;
		if (outputBit) {
			for (size_t i = 0; i < m_state.size(); i++) {
				if (m_taps[i]) {
					m_state[i] = !m_state[i];
				}
			}
		}
	}
	return byte;
}

void GLFSRNode::clear() {
	for (size_t i = 0; i < m_state.size(); i++) {
		m_state[i] = false;
	}
	m_state.clear();
	for (size_t i = 0; i < m_taps.size(); i++) {
		m_taps[i] = false;
	}
	m_taps.clear();
}