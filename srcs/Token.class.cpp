// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Token.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/04 17:07:02 by semartin          #+#    #+#             //
//   Updated: 2017/04/04 17:07:16 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Token.class.hpp"

/* CORE */
Token::Token(bool bIsOperator) : _bIsOperator(bIsOperator), _bIsMixed(false)
{
	return ;
}

Token::Token(bool bIsOperator, bool bIsMixed) : _bIsOperator(bIsOperator), _bIsMixed(bIsMixed)
{
	return ;
}

/* Accessors */
bool Token::bGetIsOperator(void) const
{
	return (_bIsOperator);
}

bool Token::bGetIsMixed(void) const
{
	return (_bIsMixed);
}


