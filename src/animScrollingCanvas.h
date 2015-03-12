//
//  animScrollingCanvas.h
//  connexionUsineHydro
//
//  Created by Julien on 12/03/2015.
//
//

#pragma once
#include "animationCanvas.h"


class animationScrolling;
class animScrollingCanvas : public animationCanvas
{
	public:
		animScrollingCanvas			(animationScrolling*);
		void						createControls			();


		animationScrolling*			mp_animScrolling;

};
