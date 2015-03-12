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
		 void					createControlsCustom();


		rqMessageManager*		mp_messagesManager;
};

