// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TokenMixed.class.cpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/20 16:49:31 by semartin          #+#    #+#             //
//   Updated: 2017/11/20 16:49:32 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Token.class.hpp"
#include "TokenMixed.class.hpp"

TokenMixed::TokenMixed(bool Neg, Fact *fact) : Token(false, true),  _fact(fact)
{
	_bNeg = Neg;
	return ;
}