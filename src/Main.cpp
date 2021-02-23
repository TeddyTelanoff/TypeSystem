#include <iostream>
#include "Type.h"

int main()
{
	bool constMap[] = { true, false };
	Type constCharPtr(TypeKind::Char, 1, false, 1, constMap);
	std::cout << constCharPtr << std::endl;
	std::cin.get();
}