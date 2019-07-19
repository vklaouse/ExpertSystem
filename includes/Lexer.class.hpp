// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Lexer.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/16 12:29:05 by semartin          #+#    #+#             //
//   Updated: 2017/11/16 12:29:08 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <cctype>
# include <vector>
# include "TokenFact.class.hpp"
# include "Operator.class.hpp"
# include "TokenMixed.class.hpp"

class Lexer
{
	
private:
	bool bError;
	std::ifstream *CFileStream;
	std::vector< std::vector<Token *> *> *CVectorToken;

	std::vector<std::string> VectorError;

	Lexer(void);
	void CheckLineFormat(std::string & szLine, int iLine);
	void LexLine(std::string szLine, int iLine);

public:
	Lexer(std::string szFileName, std::vector< std::vector<Token *> *> *CVector);
	~Lexer(void);

	static void deleteVector(std::vector<Token *> *vector);
	static void deleteToken(Token * token);
};

