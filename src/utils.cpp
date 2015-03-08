//
//  utils.cpp
//  connexionUsineHydro
//
//  Created by Julien on 06/03/2015.
//
//

#include "utils.h"

int utils::lengthUtf8(string s)
{
	if ( utf8::is_valid(s.begin(), s.end()) )
		return (int) utf8::distance(s.begin(), s.end());
	return 0;
}
