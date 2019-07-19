// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fact.class.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/16 15:29:27 by semartin          #+#    #+#             //
//   Updated: 2017/11/16 15:29:27 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
 
#pragma once

#include <iostream>
#include <vector>
#include "Instr.class.hpp"

#define STATE_FALSE 0
#define STATE_TRUE 1
#define STATE_UNKNOWN 2

class Fact
{

private:
	std::string const szName;
	int	iState;
	bool bIsSet;

public:
	Fact(std::string & name);
	Fact();
	~Fact() {} ;

	std::vector<Instr *> tabLink;

	std::string szGetName() { return (szName == "") ? "TokenMixed" : szName; };
	int iGetState() { return iState; };
	bool bGetIsSet() { return bIsSet; };

	void SetState(int state);
	void SetIsSet(bool set) { bIsSet = set; };

	static bool bUnknown;
	static void setUnknown(bool unknown) { Fact::bUnknown = unknown; };
};