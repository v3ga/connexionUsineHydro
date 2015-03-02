//
//  animationWave.cpp
//  connexionUsineHydro
//
//  Created by Julien on 02/03/2015.
//
//

#include "animationWave.h"

//--------------------------------------------------------------
animationWave::animationWave() : animation("wave")
{
	m_nbPixels 	= 4;
	m_angle		= 0;
}

//--------------------------------------------------------------
void animationWave::update(float dt)
{
	if (mp_grid)
	{
		float stepAngle = 45.0f / (float)(m_nbPixels-1);
		float value = 0.0f;
		for (int i=0;i<m_nbPixels;i++)
		{
			value = 0.5f*(1.0f+sin( ofDegToRad(m_angle+(float)i*stepAngle) ));
			mp_grid->setPixelValue( value, 0, i);
		}
		m_angle+=90*dt;
		if (m_angle>=360.0f) m_angle -= 360.0f;
	}
}
