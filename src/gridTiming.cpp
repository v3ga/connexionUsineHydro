//
//  gridTiming.cpp
//  connexionUsineHydro
//
//  Created by Julien on 15/04/2015.
//
//

#include "gridTiming.h"
#include "ofMain.h"

gridTiming::gridTiming(int size)
{
	mp_values 		= new float[size];
	mp_valuesReach 	= new float[size];
	mp_triggered	= new bool[size];
	m_size = size;
}

gridTiming::~gridTiming()
{
	delete[] mp_values;
	delete[] mp_valuesReach;
	delete[] mp_triggered;
}

bool gridTiming::isDone()
{
	for (int i=0;i<m_size;i++)
		if (mp_triggered[i] == false)
			return false;
	return true;
}

void gridTiming::resetValuesReach()
{
	for (int i=0;i<m_size;i++)
		mp_valuesReach[i] = ofRandom(0.5f); // TODO : put this in a variable
}

void gridTiming::resetValues()
{
	for (int i=0;i<m_size;i++)
		mp_values[i] = 0.0f;
}

void gridTiming::update(float dt)
{
	for (int i=0;i<m_size;i++)
	{
		if (!mp_triggered[i])
		{
			mp_values[i] += dt;
			if (mp_values[i]>=mp_valuesReach[i])
				mp_triggered[i] = true;
		}
	}
}
