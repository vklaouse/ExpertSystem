// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Token.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/04 17:08:56 by semartin          #+#    #+#             //
//   Updated: 2017/04/04 17:08:59 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

# include <iostream>

class Token
{
	
private:
	bool _bIsOperator;
	bool _bIsMixed;

	Token(void);

protected:
	bool _bNeg;

public:
	Token(bool bIsOperator);
	Token(bool bIsOperator, bool bIsMixed);
	virtual ~Token(void) {};

	/* Accessors */
	bool bGetIsOperator(void) const;
	bool bGetIsMixed(void) const;
	bool bGetNeg() const { return _bNeg; } ;
};