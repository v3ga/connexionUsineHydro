//
//  animationCanvas.h
//  connexionUsineHydro
//
//  Created by Julien on 12/03/2015.
//
//

#pragma once
#include "ofxUI.h"

class animationCanvas : public ofxUICanvas
{
	public:
		animationCanvas			();
		virtual void			createControls	(){}
		virtual void			createTitle		(string title);

		float					m_widthDefault;

};

