// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fact.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/16 15:29:16 by semartin          #+#    #+#             //
//   Updated: 2017/11/16 15:29:16 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Fact.class.hpp"
#include "ExpertSystem.class.hpp"

bool Fact::bUnknown = false;

Fact::Fact(std::string & name) : szName(name), iState(STATE_FALSE), bIsSet(false)
{
	
}

Fact::Fact() : szName(""), iState(STATE_FALSE), bIsSet(false)
{
}

void Fact::SetState(int state) 
{
	int tmp;
	if (!bIsSet || iState == state)
	{
		if (Fact::bUnknown && state == STATE_UNKNOWN)
		{
			std::cout << "The value of \033[32m\"" << szGetName() << "\"\033[m is \033[31mUNKNOWN\033[m, please enter 2 for \033[31mtrue\033[m and 1 for \033[31mfalse\033[m : ";
			std::cin >> tmp;
			if (tmp != 2 && tmp != 1)
			{
				std::cout << "\033[31mFUCK YOU BITCH THIS ISN'T 0 OR 1! ARE YOU STUPID DUMBASS!\033[m" << std::endl;
				exit(0);
			}
			iState = tmp - 1;
			bIsSet = true;
			ExpertSystem::bRestart = true;
		}
		else
		{
			iState = state;
		}
	}
	else if (bIsSet && state == STATE_UNKNOWN)
		return;
	else
	{
		std::cerr <<  "\033[31mIncoherence in the rules :\033[m Trying to set a fact that has already been set." << std::endl;
		exit(0);
	}
}
