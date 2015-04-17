//
//  toolMessages.h
//  connexionUsineHydro
//
//  Created by Julien on 12/03/2015.
//
//

#pragma once
#include "tool.h"

class rqMessageManager;
class toolMessages : public tool
{
	public:
		 toolMessages			(toolManager* pParent,rqMessageManager* pManager);
		 void					createControlsCustom	();
		 void					update					();
		 void					handleEvents			(ofxUIEventArgs& e);


		rqMessageManager*		mp_messagesManager;
		ofxUITextInput*			mp_teMaxtimestamp;
		ofxUILabel*				mp_lblCurrentTimestamp;
};

