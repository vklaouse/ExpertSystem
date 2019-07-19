// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operator.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/04 17:16:17 by semartin          #+#    #+#             //
//   Updated: 2017/04/04 17:16:20 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

# include <iostream>
# include "Token.class.hpp"

# define TOKEN_AND 		0 // +
# define TOKEN_OR 		1 // |
# define TOKEN_XOR		2 // ^
# define TOKEN_NEG		3 // ! 
# define TOKEN_OPEN		4 // (
# define TOKEN_CLOSE	5 // )
# define TOKEN_IMPLY	6 // =>
# define TOKEN_EQUAL	7 // <=>
# define TOKEN_QUERY	8 // ?
# define TOKEN_FACT		9 // =
# define TOTAL_TOKEN	10

# define NO_PRECEDENCE 0
# define OR_PRECEDENCE 1
# define XOR_PRECEDENCE 2
# define AND_PRECEDENCE 3

class Operator : public Token
{
	
private:
	int _iID;
	int _iPrecedence;

	Operator(void);

public:
	Operator(int iID);
	Operator(int iID, bool bNeg);
	virtual ~Operator(void) {};

	/* Accessors */
	int iGetID(void) const;

	void SetNeg(bool bNeg) { _bNeg = bNeg; } ;

	int iGetPrecedence(void) { return _iPrecedence; };
};