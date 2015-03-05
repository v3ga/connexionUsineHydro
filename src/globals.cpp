//
//  globals.cpp
//  connexionUsineHydro
//
//  Created by Julien on 05/03/2015.
//
//

#include "globals.h"


#include "globals.h"

//--------------------------------------------------------------
Globals* Globals::smp_instance = 0;

//--------------------------------------------------------------
Globals::Globals()
{
}

//--------------------------------------------------------------
Globals* Globals::instance()
{
	if (smp_instance == 0)
		smp_instance = new Globals();
	return smp_instance; 
}
