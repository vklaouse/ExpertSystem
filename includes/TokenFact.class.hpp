// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TokenFact.class.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/16 15:31:12 by semartin          #+#    #+#             //
//   Updated: 2017/11/16 15:31:12 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include "Token.class.hpp"

class TokenFact : public Token
{

private:
	std::string _szName;

	TokenFact();

public:
	TokenFact(std::string szName, bool Neg);
	virtual ~TokenFact(void) {};

	/*Accessors*/
	std::string szGetName() const {return _szName;} ;

};