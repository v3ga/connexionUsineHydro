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
	mp_pixelFontManager = 0;
	mp_rqMessageManager	= 0;
	mp_animation		= 0;
}

//--------------------------------------------------------------
Globals* Globals::instance()
{
	if (smp_instance == 0)
		smp_instance = new Globals();
	return smp_instance; 
}
