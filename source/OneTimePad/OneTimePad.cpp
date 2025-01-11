/*
File:		OneTimePad.cpp
Author:		Keegan MacDonald
Created:	2025.01.10@20:50
Purpose:	Test the build configuration of the OneTimePad project.
*/

#include "OneTimePad.h"

#include <Jabberwock/Jabberwock.h>

#include <iostream>

void OneTimePad::oneTimePad_test() {
	std::cout << "One time pad test" << std::endl;
}

int main(int argc, char** argv) {
	OneTimePad oneTimePad;
	oneTimePad.oneTimePad_test();
	Jabberwock jabberwock;
	jabberwock.jabberwock_test();
}