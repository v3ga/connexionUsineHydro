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
	m_isHistory = true;
	m_historySize = 100;
}

//--------------------------------------------------------------
void gridPixel::setValue(float value)
{
	m_value = value;
	if (m_isHistory)
	{
		m_valueHistory.push_back(m_value);
		if (m_valueHistory.size()>=m_historySize){
			m_valueHistory.erase( m_valueHistory.begin() );
		}
	}
}



