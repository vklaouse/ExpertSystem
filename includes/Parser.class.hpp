#pragma once

# include <vector>
# include <cstdlib>
# include "TokenFact.class.hpp"
# include "Operator.class.hpp"
# include "Fact.class.hpp"
# include "TokenMixed.class.hpp"
# include "Lexer.class.hpp"

class Parser
{
private:
	std::vector< std::vector<Token *> *> *CVectorToken;
	std::vector<Fact *> *FactTab;
	std::vector<std::string> nodeValueTab;
	std::vector<Instr *> *tabInstr;

	bool bDebug;

	Parser(void);
	void	splitLineToken(std::vector<Token *> *tokenLine);
	std::vector<Token *> *ShuntingYardAlgo(std::vector<Token *> *Input);
	void buildGraph(std::vector<Token *> *input1, std::vector<Token *> *input2, Operator *middleToken, bool bFirstFact, bool bNextFact);
	Fact * buildNode(std::vector<Token *> *input1, int way);
	Fact * getFact(Token * token);
	void ParseNodeValue(std::vector<Token *> *tokenTab);
	void SetNodeValue();
	void ParseQuery(std::vector<Token *> *tokenTab, std::vector<std::string> *tabQuery);

	void PrintMemory(std::vector<Token *> toto);
	void PrintFactTab();
	void PrintNode(Fact * fact, Instr * instr);

public:
	void PrintGraph();
	Parser(std::vector< std::vector<Token *> *> *, std::vector<Fact *> *, std::vector<std::string> *, std::vector<Instr *> *,bool);
	~Parser(void) {};
};