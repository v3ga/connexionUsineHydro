//
//  animationScrolling.cpp
//  connexionUsineHydro
//
//  Created by Julien on 05/03/2015.
//
//

#include "animationScrolling.h"
#include "pixelFontManager.h"
#include "rqMessageManager.h"
#include "rqMessage.h"
#include "globals.h"

//--------------------------------------------------------------
animationScrolling::animationScrolling() : animation("scrolling")
{
	mp_pixelFont 	= 0;
	mp_message		= 0;
}

//--------------------------------------------------------------
void animationScrolling::setup()
{
	mp_pixelFont = PIXELFONTS->getByFilename("fonts/150306_pixelfont.xml");
}

//--------------------------------------------------------------
void animationScrolling::update(float dt)
{
	if (mp_message==0)
	{
		mp_message = RQMESSAGES->getMessageAt(13);
	}
	if (mp_message)
	{
		if (mp_pixelFont)
		{
			string encoded = mp_pixelFont->encodeString( mp_message->m_text );
			ofLog() << encoded;
		}
	}
}
