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
	m_attenuation = 1.0f;
	m_powerMax = 300.0;
	m_power = 0.0;
}

//--------------------------------------------------------------
void gridPixel::setValue(float value)
{
	m_valueTarget = m_attenuation*value;

	if (m_isHistory)
	{
		m_valueHistory.push_back(m_value);
		if (m_valueHistory.size()>=m_historySize){
			m_valueHistory.erase( m_valueHistory.begin() );
		}
	}
}

//--------------------------------------------------------------
void gridPixel::update(float dt)
{
//	m_value += (m_valueTarget-m_value)*0.1;
	m_value = m_valueTarget;
	m_power = ofMap(m_value,0.0,1.0f, 0.0f,m_powerMax);
}



