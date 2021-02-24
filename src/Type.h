#pragma once

enum class TypeKind: unsigned
{
	Error,
	Void,

	Byte,
	Short,
	Int,
	Long,

	Bool,
	Char,
	WChar,

	Last = WChar,
};

constexpr const char *const TypeKindNames[(unsigned)TypeKind::Last + 1] =
{
	"Error",
	"Void",

	"Byte",
	"Short",
	"Int",
	"Long",

	"Bool",
	"Char",
	"WChar",
};

#pragma warning(disable: 26812)
enum TypeMod: char
{
	None = 0 << 0,
	Const = 1 << 0,
};

static TypeMod defMods[] = { TypeMod::None };

class Type
{
private:
	TypeKind mKind = TypeKind::Error;
	unsigned mSize;

	bool mReference = false;
	unsigned mNumPointers = 0;
	TypeMod *mModifiers = defMods;
public:
	Type(TypeKind kind, unsigned size, bool isRef, unsigned numPointers, TypeMod *mods)
		: mKind(kind), mSize(size), mReference(isRef), mNumPointers(numPointers), mModifiers(mods) {}

	TypeKind GetKind() const
	{ return mKind; }

	unsigned GetSize() const
	{ return mSize; }

	bool GetIsReference() const
	{ return mReference; }

	unsigned GetNumPointers() const
	{ return mNumPointers; }

	TypeMod *GetModifiers() const
	{ return mModifiers; }

	__declspec(property(get = GetKind)) TypeKind Kind;
	__declspec(property(get = GetSize)) unsigned Size;
	__declspec(property(get = GetIsReference)) bool IsReference;
	__declspec(property(get = GetNumPointers)) unsigned NumPointers;
	__declspec(property(get = GetModifiers)) TypeMod *Modifiers;
};

std::ostream &operator <<(std::ostream &os, bool b)
{ return os << (b ? "true" : "false"); }

std::ostream &operator <<(std::ostream &os, TypeKind kind)
{ return os << TypeKindNames[(unsigned)kind]; }

std::ostream &operator <<(std::ostream &os, const Type &ty)
{
	if (*ty.Modifiers)
		os << "const ";
	os << ty.Kind;
	for (unsigned i = 0; i < ty.NumPointers; i++)
	{
		if (ty.Modifiers[i + 1] & TypeMod::Const)
			os << "const ";
		os << '*';
	}

	if (ty.IsReference)
		os << '&';

	return os;
}