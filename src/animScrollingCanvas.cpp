//
//  animScrollingCanvas.cpp
//  connexionUsineHydro
//
//  Created by Julien on 12/03/2015.
//
//

#include "animScrollingCanvas.h"
#include "animationScrolling.h"


//--------------------------------------------------------------
animScrollingCanvas::animScrollingCanvas(animationScrolling* pAnim) : animationCanvas()
{
	mp_animScrolling = pAnim;
}

//--------------------------------------------------------------
void animScrollingCanvas::createControls()
{
	createTitle("Scrolling");
	if (mp_animScrolling)
	{
		addWidgetDown(new ofxUISlider("speed", 0.5f, 4.0f, &mp_animScrolling->m_speed, m_widthDefault, 20 ));
	}
}




