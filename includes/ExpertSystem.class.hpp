#pragma once

#include "Instr.class.hpp"
#include "Fact.class.hpp"
#include "Operator.class.hpp"
#include <vector>

#define NB_ITERATION_INSTR 2

class ExpertSystem
{

private:

	std::vector<Fact *> * tabFact;
	std::vector<std::string> * tabQuery;
	std::vector<Instr *> * tabInstr;

	bool bVerbose;
	bool bUnknown;
	bool bDebug;

	ExpertSystem();

	int getStateValue(int iState, bool bNeg);
	void SetState(int iState, bool bNeg, Fact * fact);
	void PrintVerbose(std::string instr, std::string fact1, std::string fact2, std::string next, bool bNeg1, bool bNeg2, bool bNegNext, std::string str, int iState);
	void PrintVerboseUp(std::string instr, std::string fact1, std::string fact2, std::string next, bool bNeg1, bool bNeg2, bool bNegNext, int iStateNext, int iStateTwo, int iStateOne);
	void PrintImply(std::string fact1, std::string next, bool bNeg1, bool bNegNext, int iStateOne, int iStateNext);
	void PrintEQUAL(std::string fact1, std::string next, bool bNeg1, bool bNegNext, int iStateOne, int iStateNext);
	

	void wayDownAND(Instr * instr);
	void wayDownOR(Instr * instr);
	void wayDownXOR(Instr * instr);
	void wayDownIMPLY(Instr * instr);
	void wayDownEQUAL(Instr * instr);

	void wayUpAND(Instr * instr, Fact * queryFact);
	void wayUpOR(Instr * instr, Fact * queryFact);
	void wayUpXOR(Instr * instr, Fact * queryFact);
	void wayUpIMPLY(Instr * instr);
	void backWardChaining(Fact *, Instr *);

	void displayResult();
	void resetInstr();

public:
	ExpertSystem(std::vector<Fact *> *, std::vector<std::string> *, std::vector<Instr *> *,bool, bool, bool);
	~ExpertSystem() {} ;

	static bool bRestart;
};