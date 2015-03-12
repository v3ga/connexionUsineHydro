//
//  toolAnimations.h
//  connexionUsineHydro
//
//  Created by Julien on 12/03/2015.
//
//

#pragma once
#include "tool.h"

class animation;
class animationCanvas;

class toolAnimations : public tool
{
	public:
		 toolAnimations			(toolManager* pParent);

		 void					setAnimation			(animation*);
		 void					createControls			(string fontName="", ofVec2f posCanvas=ofVec2f(), ofVec2f dimCanvas=ofVec2f(320,400));
		 void					createControlsCustom	();
		 void					loadData				();
		 void					saveData				();


	protected:
		animation*				mp_animation;
		animationCanvas*		mp_animationCanvas;
};
