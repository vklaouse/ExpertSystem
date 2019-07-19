// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operator.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/04 17:16:38 by semartin          #+#    #+#             //
//   Updated: 2017/04/04 17:16:39 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Token.class.hpp"
#include "Operator.class.hpp"

/* CORE */
Operator::Operator(int iID) : Token(true), _iID(iID)
{
	_bNeg = false;
	if (iID == TOKEN_AND)
		_iPrecedence = AND_PRECEDENCE;
	else if (iID == TOKEN_OR)
		_iPrecedence = OR_PRECEDENCE;
	else 
		_iPrecedence = NO_PRECEDENCE;
	return ;
}

Operator::Operator(int iID, bool bNeg) : Token(true), _iID(iID)
{
	_bNeg = bNeg;
	if (iID == TOKEN_AND)
		_iPrecedence = AND_PRECEDENCE;
	else if (iID == TOKEN_OR)
		_iPrecedence = OR_PRECEDENCE;
	else 
		_iPrecedence = NO_PRECEDENCE;
	return ;
}

/* Accessors */
int Operator::iGetID(void) const
{
	return (_iID);
}




