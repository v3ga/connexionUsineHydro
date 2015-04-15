//
//  animationWordsCanvas.h
//  connexionUsineHydro
//
//  Created by Julien on 15/04/2015.
//
//

#pragma once
#include "animationCanvas.h"

class animationWords;
class animationWordsCanvas : public animationCanvas
{
	public:
		animationWordsCanvas		(animationWords*);
		void						createControls			();


		animationWords*				mp_animWords;

};