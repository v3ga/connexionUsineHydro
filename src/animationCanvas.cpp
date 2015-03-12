//
//  animationCanvas.cpp
//  connexionUsineHydro
//
//  Created by Julien on 12/03/2015.
//
//

#include "animationCanvas.h"

//--------------------------------------------------------------
animationCanvas::animationCanvas() : ofxUICanvas()
{
	m_widthDefault = 320;
}

//--------------------------------------------------------------
void animationCanvas::createTitle(string title)
{
	addWidgetDown( new ofxUILabel(title,OFX_UI_FONT_LARGE) );
	addWidgetDown( new ofxUISpacer(m_widthDefault, 2) );
}

