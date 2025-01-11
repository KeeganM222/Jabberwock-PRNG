/*
File:		Generator.cpp
Author:		Keegan MacDonald
Created:	2025.01.10@20:49
Purpose:	Test the build configuration of the Generator project.
*/

#include "Generator.h"

#include <Jabberwock/Jabberwock.h>

#include <iostream>

void Generator::generator_test() {
	std::cout << "Generator test" << std::endl;
}

int main(int argc, char** argv) {
	Generator generator;
	generator.generator_test();
	Jabberwock jabberwock;
	jabberwock.jabberwock_test();
}