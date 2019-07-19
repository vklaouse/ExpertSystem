#include "Parser.class.hpp"

Parser::Parser(std::vector< std::vector<Token *> *> *CVector, std::vector<Fact *> * link, std::vector<std::string> * tabQuery, std::vector<Instr *> * TabInstr,bool debug) 
			: CVectorToken(CVector), FactTab(link), tabInstr(TabInstr), bDebug(debug)
{
	for (size_t i = 0; i < CVectorToken->size(); i++)
	{
		if ((*(*CVectorToken)[i])[0]->bGetIsOperator())
		{
			Operator* tmp = reinterpret_cast<Operator *>((*(*CVectorToken)[i])[0]);
			if (tmp->iGetID() == TOKEN_QUERY || tmp->iGetID() == TOKEN_FACT)
			{
				if (tmp->iGetID() == TOKEN_FACT)
				{
					ParseNodeValue(CVectorToken->at(i));
				}
				else
				{
					ParseQuery(CVectorToken->at(i), tabQuery);
				}
				continue ;
			}
		}
		splitLineToken((*CVectorToken)[i]);
	}
	SetNodeValue();

}

void Parser::ParseQuery(std::vector<Token *> *tokenTab, std::vector<std::string> * tabQuery)
{
	if (!bDebug)
	{
		for (size_t i = 1; i < tokenTab->size(); i++)
		{
			if (tokenTab->at(i)->bGetIsOperator())
			{
				std::cerr << "Error : Why do you have an operator in the query ?" << std::endl;
				exit(0);
			}
			tabQuery->push_back(dynamic_cast<TokenFact *>(tokenTab->at(i))->szGetName());
		}
	}
	else
	{
		for (size_t i = 0; i < FactTab->size(); i++)
		{
			tabQuery->push_back(FactTab->at(i)->szGetName());
		}
	}
}

void Parser::ParseNodeValue(std::vector<Token *> *tokenTab)
{
	for (size_t i = 1; i < tokenTab->size(); i++)
	{
		if (tokenTab->at(i)->bGetIsOperator())
		{
			std::cerr << "Error : Why do you have an operator in the fact ?" << std::endl;
			exit(0);
		}
		nodeValueTab.push_back(dynamic_cast<TokenFact *>(tokenTab->at(i))->szGetName());
	}
}

void Parser::SetNodeValue()
{
	bool bExist = false;

	for (size_t i = 0; i < nodeValueTab.size(); i++)
	{
		bExist = false;
		for (size_t j = 0; j < FactTab->size(); j++)
		{
			if (nodeValueTab[i] == FactTab->at(j)->szGetName())
			{
				bExist = true;
				FactTab->at(j)->SetState(STATE_TRUE);
				FactTab->at(j)->SetIsSet(true);
			}
		}
		if (!bExist)
		{
			FactTab->push_back(new Fact(nodeValueTab[i]));
			FactTab->back()->SetState(STATE_TRUE);
			FactTab->back()->SetIsSet(true);
		}
	}
}


void	Parser::splitLineToken(std::vector<Token *> *tokenLine)
{
	std::vector<Token *> *input1 = new std::vector<Token *>;
	std::vector<Token *> *input2 = new std::vector<Token *>;
	Operator *middleToken = NULL;
	bool lineMiddle = false;

	bool bFirstFact = false;
	bool bNextFact = false;

	for (size_t i = 0; i < tokenLine->size(); i++)
	{
		if ((*tokenLine)[i]->bGetIsOperator())
		{
			Operator* tmp = dynamic_cast<Operator *>((*tokenLine)[i]);
			if (tmp->iGetID() == TOKEN_IMPLY || tmp->iGetID() == TOKEN_EQUAL)
				lineMiddle = true;
		}
		if (lineMiddle && !middleToken)
		{
			middleToken = dynamic_cast<Operator *>(tokenLine->at(i));
			if (i == 1 && tokenLine->at(0)->bGetNeg())
			{	
				bFirstFact = true;
			}
			if (i == tokenLine->size() - 2 && tokenLine->at(i + 1)->bGetNeg())
			{
				bNextFact = true;
			}
		}
		else if(!lineMiddle)
			input1->push_back((*tokenLine)[i]);
		else
			input2->push_back((*tokenLine)[i]);
	}
	if (!input1->size() || !input2->size())
	{
		std::cerr << "Error : Wrong rule." << std::endl;
		exit(0);
	}
	input1 = ShuntingYardAlgo(input1);	
	input2 = ShuntingYardAlgo(input2);
	buildGraph(input1, input2, middleToken, bFirstFact, bNextFact);
	Lexer::deleteVector(input1);
	Lexer::deleteVector(input2);
}

std::vector<Token *>	*Parser::ShuntingYardAlgo(std::vector<Token *> *Input)
{
	std::vector<Token *> *Output = new std::vector<Token *>;
	std::vector<Token *> Stack;
	Token *tmp;
	size_t iNbNeg = 0;
	bool bNeg = false;

	for (size_t i = 0; i < Input->size(); i++)
	{
		if (!Input->at(i)->bGetIsOperator())
			Output->push_back(Input->at(i));
		else if (Input->at(i)->bGetIsOperator() 
			&& (dynamic_cast<Operator *>(Input->at(i)))->iGetID() >= TOKEN_AND
			&& (dynamic_cast<Operator *>(Input->at(i)))->iGetID() <= TOKEN_XOR) 
		{
			while (Stack.size()
				&& Stack.back()->bGetIsOperator() 
				&& (dynamic_cast<Operator *>(Stack.back()))->iGetID() >= TOKEN_AND
				&& (dynamic_cast<Operator *>(Stack.back()))->iGetID() <= TOKEN_XOR
				&& (dynamic_cast<Operator *>(Input->at(i)))->iGetPrecedence() <= (dynamic_cast<Operator *>(Stack.back()))->iGetPrecedence())
			{
				Output->push_back(Stack.back());
				Stack.pop_back();
			}
			Stack.push_back(Input->at(i));
		}
		else if (Input->at(i)->bGetIsOperator() 
			&& (dynamic_cast<Operator *>(Input->at(i)))->iGetID() == TOKEN_OPEN)
		{
			Stack.push_back(Input->at(i));
		}
		else if (Input->at(i)->bGetIsOperator() 
			&& (dynamic_cast<Operator *>(Input->at(i)))->iGetID() == TOKEN_CLOSE)
		{
			iNbNeg = 0;
			while (Stack.size() 
				&& (dynamic_cast<Operator *>(Stack.back()))->iGetID() != TOKEN_OPEN)
			{
				Output->push_back(Stack.back());
				Stack.pop_back();
				iNbNeg ++;
			}
			if (!Stack.size())
			{
				std::cerr << "There are mismatched closed parentheses." << std::endl;
				exit(0);
			}
			else
			{
				bNeg = true;
				tmp = Stack.back();
				Stack.pop_back();
				delete tmp;
			}
			tmp = Input->at(i);
			delete tmp;
			for	(size_t j = 0; j < iNbNeg; j++)
			{
				(dynamic_cast<Operator *>(Output->at(Output->size() - j - 1)))->SetNeg(bNeg);
			}
		}
	}
	while (Stack.size())
	{
		if ((dynamic_cast<Operator *>(Stack.back()))->iGetID() == TOKEN_OPEN)
		{
			std::cerr << "There are mismatched opened parentheses." << std::endl;
			exit(0);
		}	
		Output->push_back(Stack.back());
		Stack.pop_back();
	}
	delete Input;
	return(Output);

}

void Parser::buildGraph(std::vector<Token *> *input1, std::vector<Token *> *input2, Operator *middleToken, bool bFirstFact, bool bNextFact)
{
	Fact * wayIn;
	Fact * wayOut;
	Instr *instr;

	if (middleToken->iGetID() == TOKEN_EQUAL)
	{
		wayIn = buildNode(input1, WAY_EQUAL);
		wayOut = buildNode(input2, WAY_EQUAL);
		instr = new Instr(wayIn, NULL, wayOut, TOKEN_EQUAL, WAY_EQUAL);
		instr->SetNeg(bFirstFact, 0, bNextFact);
	}
	else
	{
		wayIn = buildNode(input1, WAY_DOWN);
		wayOut = buildNode(input2, WAY_UP);
		instr = new Instr(wayIn, NULL, wayOut, TOKEN_IMPLY, WAY_DOWN);
		instr->SetNeg(bFirstFact, 0, bNextFact);
	}
	tabInstr->push_back(instr);
	wayIn->tabLink.push_back(instr);
	wayOut->tabLink.push_back(instr);
}

Fact * Parser::buildNode(std::vector<Token *> *input, int iWay)
{
	Fact *fact1;
	Fact *fact2;
	Fact *next;

	Token *token1;
	Token *token2;
	Token *token3;
	Operator *op;
	
	Instr *instr;
	TokenMixed *concatToken;

	size_t i = 0;
	if (input->size() == 1)
	{
		return getFact(input->back());
	}
	while (!input->at(i)->bGetIsOperator())
		i++;
	if (i < 2)
	{
		std::cerr << "Operator without any Fact isn't very smart :')" << std::endl;
		exit(0);
	}
	op = dynamic_cast<Operator *>(input->at(i));
	fact1 = getFact(input->at(i - 2));
	fact2 = getFact(input->at(i - 1));
	next = new Fact();
	concatToken = new TokenMixed(op->bGetNeg(), next);
	token1 = input->at(i - 2);
	token2 = input->at(i - 1);
	token3 = input->at(i);

	input->erase(input->begin() + i - 2, input->begin() + i + 1);
	i -= 2;
	input->insert(input->begin() + i, concatToken);
	instr = new Instr(fact1, fact2, next, op->iGetID(), iWay);
	instr->SetNeg(token1->bGetNeg(),token2->bGetNeg(),op->bGetNeg());

	Lexer::deleteToken(token1);
	Lexer::deleteToken(token2);
	Lexer::deleteToken(token3);

	fact1->tabLink.push_back(instr);
	fact2->tabLink.push_back(instr);
	next->tabLink.push_back(instr);
	tabInstr->push_back(instr);
	return buildNode(input, iWay);
}

Fact * Parser::getFact(Token *token)
{
	if (!token->bGetIsMixed())
	{
		std::string szTmp = dynamic_cast<TokenFact *>(token)->szGetName();
		for (size_t i = 0; i < FactTab->size(); i++)
		{
			if (szTmp == FactTab->at(i)->szGetName())
				return FactTab->at(i);
		}
		Fact * tmpFact = new Fact(szTmp);
		FactTab->push_back(tmpFact);
		return tmpFact;
	}
	else
	{
		return dynamic_cast<TokenMixed *>(token)->getFact();
	}
}

void Parser::PrintGraph()
{
	for (size_t i = 0; FactTab->size() > i; i++)
	{
		std::cout << "Maillion N° "<< FactTab->at(i)->szGetName() << " et " << FactTab->at(i)->iGetState() << std::endl;
		for (size_t j = 0; j < FactTab->at(i)->tabLink.size(); j++)
		{
			std::cout << "1st Link = " << FactTab->at(i)->tabLink[j]->getFirstLink()->szGetName() << std::endl;
			if (FactTab->at(i)->tabLink[j]->getSecLink())
				std::cout << "2nd Link = " << FactTab->at(i)->tabLink[j]->getSecLink()->szGetName() << std::endl;
			std::cout << "Next = " << FactTab->at(i)->tabLink[j]->getNext()->szGetName() << std::endl;
			std::cout << "Operator = " << FactTab->at(i)->tabLink[j]->iGetOperator() << std::endl;
			std::cout << "Way = " << FactTab->at(i)->tabLink[j]->iGetWay() << std::endl;
			PrintNode(FactTab->at(i)->tabLink[j]->getNext(), FactTab->at(i)->tabLink[j]);
			std::cout << "____________________++++++++++_________________________________" << std::endl;
		}
	}
}

void Parser::PrintNode(Fact * fact, Instr * instr)
{
	if (fact->szGetName() != "")
		return;

	std::cout << "1------------------------------------------------- Fact = " << fact << std::endl;
	for (size_t i = 0; i < fact->tabLink.size(); i++)
	{
		if (instr == fact->tabLink[i])
			continue ;

		std::cout << "1st Link = " << fact->tabLink[i]->getFirstLink()->szGetName() << std::endl;
		if (fact->tabLink[i]->getSecLink())
			std::cout << "2nd Link = " << fact->tabLink[i]->getSecLink()->szGetName() << std::endl;
		std::cout << "Next = " << fact->tabLink[i]->getNext()->szGetName() << std::endl;
		std::cout << "Operator = " << fact->tabLink[i]->iGetOperator() << std::endl;
		std::cout << "Way = " << fact->tabLink[i]->iGetWay() << std::endl;
		if (fact->tabLink[i]->getNext() != fact)
			PrintNode(fact->tabLink[i]->getNext(), fact->tabLink[i]);
		std::cout << "2----------------------------------------------------" << std::endl;
	}
}

void Parser::PrintFactTab()
{
	for (size_t i = 0; FactTab->size() > i; i++)
	{
		std::cout << FactTab->at(i)->szGetName() << std::endl;
	}
}

void Parser::PrintMemory(std::vector<Token *> toto)
{
	for (size_t i = 0; i < toto.size(); i++)
	{
		if (toto[i]->bGetIsMixed())
		{
			std::cout << "Mixed Token here" << std::endl;
		}
		else if (toto[i]->bGetIsOperator())
		{
			std::cout << "Operator is = " << (dynamic_cast<Operator *>(toto[i]))->iGetID() << std::endl;
		}
		else
		{
			std::cout << "FactName is = " << (dynamic_cast<TokenFact *>(toto[i]))->szGetName() << 
				" And is neg? =" << (dynamic_cast<TokenFact *>(toto[i]))->bGetNeg() << std::endl;
		}
	}
	std::cout << "||||||||||||||||||||" << std::endl;
}

