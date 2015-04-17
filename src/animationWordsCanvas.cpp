//
//  animationWordsCanvas.cpp
//  connexionUsineHydro
//
//  Created by Julien on 15/04/2015.
//
//

#include "animationWordsCanvas.h"
#include "animationWords.h"

//--------------------------------------------------------------
animationWordsCanvas::animationWordsCanvas(animationWords* pAnim) : animationCanvas()
{
	mp_animWords = pAnim;
}

//--------------------------------------------------------------
void animationWordsCanvas::createControls()
{
	createTitle("Words");
	if (mp_animWords)
	{
		addWidgetDown(new ofxUISlider("speedScrolling", 0.5f, 4.0f, &mp_animWords->m_wordSpeedScrolling, m_widthDefault, 20 ));
		addWidgetDown(new ofxUISlider("timeIn", 0.2f, 1.0f, &mp_animWords->m_timeWordIn, m_widthDefault, 20 ));
		addWidgetDown(new ofxUISlider("timeShowPerLetter", 0.05f, 0.6f, &mp_animWords->m_timeShowPerLetter, m_widthDefault, 20 ));
		addWidgetDown(new ofxUISlider("timeOut", 0.2f, 1.0f, &mp_animWords->m_timeWordOut, m_widthDefault, 20 ));
	}
}
