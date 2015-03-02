//
//  animationWave.h
//  connexionUsineHydro
//
//  Created by Julien on 02/03/2015.
//
//

#pragma once
#include "animation.h"

class animationWave : public animation
{
	public:
		animationWave		();
		void	update		(float dt);

	protected:
		int		m_nbPixels; // can be different from grid pixels number (for test case)
		float	m_angle;
};