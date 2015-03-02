//
//  gridPixel.cpp
//  connexionUsineHydro
//
//  Created by Julien on 02/03/2015.
//
//

#include "gridPixel.h"

//--------------------------------------------------------------
gridPixel::gridPixel()
{
	zeroAll();
}

//--------------------------------------------------------------
void gridPixel::zeroAll()
{
	m_row = m_col = 0;
	m_value = 0.0f;
	m_channelDmx = 0;
}


