//
//  toolMessages.cpp
//  connexionUsineHydro
//
//  Created by Julien on 12/03/2015.
//
//

#include "toolMessages.h"
#include "rqMessageManager.h"

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
		}

		mp_canvas->autoSizeToFitWidgets();
		mp_canvas->disableAppDrawCallback();
	}
}