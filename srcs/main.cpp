// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/16 14:13:36 by semartin          #+#    #+#             //
//   Updated: 2017/11/16 14:13:36 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Lexer.class.hpp"
#include "Parser.class.hpp"
#include "ExpertSystem.class.hpp"
#include "Fact.class.hpp"

static void helper()
{
	std::cout << std::endl << "Usage: ./Expert_System [ file.txt ] [ -v | -d | -u ]" << std::endl << std::endl;
	std::cout << "	-v	Describe the comportement of the program." << std::endl;
	std::cout << "	-d	Show the result of all facts and look for any incoherences." << std::endl;
	std::cout << "	-u	Let you set as true or false any facts when they are unknown." << std::endl << std::endl;
}

int main(int ac, char **av)
{
	if (ac >= 2)
	{
		std::vector<std::string> vecArgv;

		bool	bVerbose = false;
		bool 	bDebug = false;
		bool	bUnknown = false;
		
		for (size_t i = 0; i < static_cast<size_t>(ac) - 1; i++)
		{
			vecArgv.push_back(std::string(av[i + 1]));
			if (vecArgv.back().compare("-v") == 0)
			{
				bVerbose = true;
				vecArgv.pop_back();
			}
			else if (vecArgv.back().compare("-d") == 0)
			{
				bDebug = true;
				vecArgv.pop_back();
			}
			else if (vecArgv.back().compare("-u") == 0)
			{
				bUnknown = true;
				vecArgv.pop_back();
			}
		}
		for (size_t i = 0; i < vecArgv.size(); i++)
		{
			std::vector< std::vector<Token *> *> CVectorToken;
			std::vector<Fact *> TabFact;
			std::vector<std::string> TabQuery;
			std::vector<Instr *> TabInstr;

			Fact::setUnknown(bUnknown);
			Lexer(vecArgv[i], &CVectorToken);
			Parser(&CVectorToken, &TabFact, &TabQuery, &TabInstr ,bDebug);
			ExpertSystem(&TabFact, &TabQuery, &TabInstr,bVerbose, bUnknown, bDebug);
			return 0;
		}
		helper();
	}
	else
		helper();
	return 0;
}