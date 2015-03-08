//
//  animationScrolling.h
//  connexionUsineHydro
//
//  Created by Julien on 05/03/2015.
//
//

#pragma once

#include "animation.h"
#include "pixelFont.h"

class rqMessage;
class animationScrolling : public animation
{
	public:
		animationScrolling			();
	

		void			setup		();
		void			update		(float dt);
 
 	protected:
		pixelFont*		mp_pixelFont;
		rqMessage*		mp_message;
 
};