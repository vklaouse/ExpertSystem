// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TokenMixed.class.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/20 16:49:44 by semartin          #+#    #+#             //
//   Updated: 2017/11/20 16:49:44 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include "Fact.class.hpp"
#include "Token.class.hpp"

class TokenMixed : public Token
{

private:
	Fact 	*_fact;

	TokenMixed();

public:
	TokenMixed(bool Neg, Fact *fact);
	virtual ~TokenMixed(void) {};

	/*Accessors*/
	Fact	*getFact() const { return _fact; } ;

};