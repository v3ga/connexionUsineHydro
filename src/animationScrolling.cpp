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
#include "messageScrolling.h"
#include "ofAppLog.h"
#include "globals.h"


//--------------------------------------------------------------
animationScrolling::animationScrolling() : animation("scrolling")
{
	mp_pixelFont 	= 0;
	mp_message		= 0;
}

//--------------------------------------------------------------
animationScrolling::~animationScrolling()
{
	deleteMessages();
}

//--------------------------------------------------------------
void animationScrolling::setup()
{
	mp_pixelFont = PIXELFONTS->getByFilename("fonts/150311_pixelfont.xml");
}

//--------------------------------------------------------------
void animationScrolling::update(float dt)
{
	int nbMessagesScrolling = m_messagesScrolling.size();
	for (int i=0;i<nbMessagesScrolling;i++)
	{
		m_messagesScrolling[i]->update(dt);
	}


	if (m_messagesScrolling.size()==0)
	{
		rqMessage* pMessage = RQMESSAGES->getMessage();
		if (pMessage)
		{
			createMessageScrolling(pMessage);
		}
	}

}

//--------------------------------------------------------------
void animationScrolling::renderOffscreen()
{
	int nbMessagesScrolling = m_messagesScrolling.size();
	for (int i=0;i<nbMessagesScrolling;i++)
	{
		m_messagesScrolling[i]->drawOffscreen();
	}
}


//--------------------------------------------------------------
void animationScrolling::createMessageScrolling(rqMessage* pMessage)
{
	OFAPPLOG->begin("animationScrolling::createMessageScrolling()");
	
	messageScrolling* pMessageScrolling = new messageScrolling(this, pMessage);
	pMessageScrolling->setPosition(0,0);
	if (pMessageScrolling->m_textEncoded != "")
	{
		OFAPPLOG->println("- encoded text="+pMessageScrolling->m_textEncoded);
	
		m_messagesScrolling.push_back(pMessageScrolling);
	}
	else
	{
		delete pMessageScrolling;
		OFAPPLOG->println("- encoded text is empty...");
	}

	OFAPPLOG->end();
}

//--------------------------------------------------------------
void animationScrolling::deleteMessages()
{
	for (int i=0;i<m_messagesScrolling.size();i++){
		delete m_messagesScrolling[i];
	}
	m_messagesScrolling.clear();
}


