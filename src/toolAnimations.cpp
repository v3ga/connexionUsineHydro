//
//  toolAnimations.cpp
//  connexionUsineHydro
//
//  Created by Julien on 12/03/2015.
//
//

#include "toolAnimations.h"
#include "animScrollingCanvas.h"
#include "animationWordsCanvas.h"

//--------------------------------------------------------------
toolAnimations::toolAnimations(toolManager* pParent) : tool("Animations", pParent)
{
	mp_animation 		= 0;
	mp_animationCanvas 	= 0;
	mp_canvas = 0;
}

//--------------------------------------------------------------
void toolAnimations::setAnimation(animation* pAnimation)
{
	 mp_animation = pAnimation;
}

//--------------------------------------------------------------
void toolAnimations::createControls(string fontName, ofVec2f posCanvas, ofVec2f dimCanvas)
{

	// TEMP : may be a factory here
	mp_animationCanvas = new animationWordsCanvas((animationWords*) mp_animation);
	mp_animationCanvas->createControls();

	mp_canvas = mp_animationCanvas;

//	mp_canvas = new ofxUICanvas();

	createControlsCustom();
}

//--------------------------------------------------------------
void toolAnimations::createControlsCustom()
{
	if (mp_canvas)
	{
		mp_canvas->autoSizeToFitWidgets();
		mp_canvas->disableAppDrawCallback();
	}

}

//--------------------------------------------------------------
void toolAnimations::loadData()
{
	if (mp_canvas)
		mp_canvas->loadSettings( getDataPath("Animation_scrolling.xml") );
}

//--------------------------------------------------------------
void toolAnimations::saveData()
{
	if (mp_canvas)
		mp_canvas->saveSettings( getDataPath("Animation_scrolling.xml") );
}
