#pragma once

enum class TypeKind: unsigned
{
	Error,
	Void,

	Int,

	Char,

	Last = Char,
};

constexpr const char *const TypeKindNames[(unsigned)TypeKind::Last + 1] =
{
	"Error",
	"Void",

	"Int",

	"Char",
};

static bool defConstArr[] = { false };

class Type
{
private:
	TypeKind mKind = TypeKind::Error;
	unsigned mSize;

	bool mReference = false;
	unsigned mNumPointers = 0;
	bool *mConstArray = defConstArr;
public:
	Type(TypeKind kind, unsigned size, bool isRef, unsigned numPointers, bool *constArray)
		: mKind(kind), mSize(size), mReference(isRef), mNumPointers(numPointers), mConstArray(constArray) {}

	TypeKind GetKind() const
	{ return mKind; }

	unsigned GetSize() const
	{ return mSize; }

	bool GetIsReference() const
	{ return mReference; }

	unsigned GetNumPointers() const
	{ return mNumPointers; }

	bool *GetConstArray() const
	{ return mConstArray; }

	__declspec(property(get = GetKind)) TypeKind Kind;
	__declspec(property(get = GetSize)) unsigned Size;
	__declspec(property(get = GetIsReference)) bool IsReference;
	__declspec(property(get = GetNumPointers)) unsigned NumPointers;
	__declspec(property(get = GetConstArray)) bool *ConstArray;
};

std::ostream &operator <<(std::ostream &os, bool b)
{ return os << (b ? "true" : "false"); }

std::ostream &operator <<(std::ostream &os, TypeKind kind)
{ return os << TypeKindNames[(unsigned)kind]; }

std::ostream &operator <<(std::ostream &os, const Type &ty)
{
	if (*ty.ConstArray)
		os << "const ";
	os << ty.Kind;
	for (unsigned i = 0; i < ty.NumPointers; i++)
	{
		if (ty.ConstArray[i + 1])
			os << "const ";
		os << '*';
	}

	if (ty.IsReference)
		os << '&';

	return os;
}