//
//  toolMessages.cpp
//  connexionUsineHydro
//
//  Created by Julien on 12/03/2015.
//
//

#include "toolMessages.h"
#include "rqMessageManager.h"
#include "globals.h"

//--------------------------------------------------------------
toolMessages::toolMessages(toolManager* pParent, rqMessageManager* pMessagesManager) : tool("Messages", pParent)
{
	mp_messagesManager = pMessagesManager;
}

//--------------------------------------------------------------
void toolMessages::createControlsCustom()
{
	if (mp_canvas)
	{
		ofxUIWidgetFontType fontType = OFX_UI_FONT_SMALL;
		float dim = 16;
		int widthDefault = 320;

	    mp_canvas->addWidgetDown( new ofxUILabel("Messages",OFX_UI_FONT_LARGE) );
    	mp_canvas->addWidgetDown( new ofxUISpacer(widthDefault, 2) );

		if (mp_messagesManager)
		{
			mp_canvas->addWidgetDown(new ofxUISlider("period grab", 1.0f, 20.0f, &mp_messagesManager->m_period, widthDefault, dim ));
			
			mp_teMaxtimestamp = new ofxUITextInput("maxtimestamp", "", widthDefault, dim );
			mp_teMaxtimestamp->setAutoClear(false);
			mp_canvas->addWidgetDown(mp_teMaxtimestamp);

			mp_lblCurrentTimestamp = new ofxUILabel("maxtimestamp_current", OFX_UI_FONT_SMALL);
			mp_canvas->addWidgetDown(mp_lblCurrentTimestamp);
		}

		mp_canvas->autoSizeToFitWidgets();
		mp_canvas->disableAppDrawCallback();
	}
}

//--------------------------------------------------------------
void toolMessages::update()
{
	if (mp_lblCurrentTimestamp){
		mp_lblCurrentTimestamp->setLabel( "current timestamp = "+ofToString(RQMESSAGES->getMaxTimestamp()) );
	}
}


//--------------------------------------------------------------
void toolMessages::handleEvents(ofxUIEventArgs& e)
{
	string name = e.getName();
	if (name == "maxtimestamp")
	{
		ofxUITextInput* pTe = (ofxUITextInput*)e.widget;
		if (pTe->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
		{
			if (pTe->getTextString()!="")
			{
				RQMESSAGES->setTimestamp( ofToInt( pTe->getTextString() ) );
			}
		}
	}
}


