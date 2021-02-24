#include <iostream>
#include "Type.h"

int main()
{
	TypeMod mods[] = { TypeMod::Const, TypeMod::None };
	Type constCharPtr(TypeKind::Char, 1, false, 1, mods);
	std::cout << constCharPtr << std::endl;
	std::cin.get();
}