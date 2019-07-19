#pragma once

#define WAY_EQUAL 0
#define WAY_DOWN 1
#define WAY_UP 2

template <typename T>
T XOR(const T & a, const T & b)
{
	return ((a || b) && !(a && b));
}

class Fact;

class Instr
{
private:
	Fact *firstLink;
	Fact *SecLink;
	Fact *next;
	int iOperator;
	int iWay;
	bool bNegOne;
	bool bNegTwo;
	bool bNegNext;

	int iIteration;

	Instr(void);

public:
	Instr(Fact *fL, Fact *sL, Fact *next, int Op, int way);

	void SetNeg(bool first, bool snd, bool next);

	//Accessor
	Fact * getFirstLink() { return firstLink; };
	Fact * getSecLink() { return SecLink; };
	Fact * getNext() { return next; };

	int iGetOperator() { return iOperator; } ;
	int iGetWay() { return iWay; } ;
	int iGetNbIteration() { return iIteration; };

	void IncreaseInteration() { iIteration++; };
	void ResetIteration() { iIteration = 0; };

	bool bGetNegOne() { return bNegOne; } ;
	bool bGetNegTwo() { return bNegTwo; } ;
	bool bGetNegNext() { return bNegNext; } ;


	~Instr(void) {};

};