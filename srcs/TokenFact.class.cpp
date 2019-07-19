// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TokenFact.class.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/16 15:31:28 by semartin          #+#    #+#             //
//   Updated: 2017/11/16 15:31:29 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Token.class.hpp"
#include "TokenFact.class.hpp"

TokenFact::TokenFact(std::string szName, bool Neg) : Token(false), _szName(szName)
{
	_bNeg = Neg;
	return ;
}