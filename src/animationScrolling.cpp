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
	m_speed			= 2.5f;
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
	// Update all messages
	int nbMessagesScrolling = m_messagesScrolling.size();
	for (int i=0;i<nbMessagesScrolling;i++)
	{
		m_messagesScrolling[i]->update(dt);
	}

	// Check for «outside» messages and remove them
	vector<messageScrolling*>::iterator it = m_messagesScrolling.begin();
	for (; it != m_messagesScrolling.end(); )
	{
		if ((*it)->m_hasScrolled){
			delete *it;
			it = m_messagesScrolling.erase( it );
		}else{
			++it;
		}
	
	}

	// Check the end position of the last inserted message
	nbMessagesScrolling = m_messagesScrolling.size();
	if (nbMessagesScrolling>0)
	{
		messageScrolling* pLastMessage = m_messagesScrolling[nbMessagesScrolling-1];
		if (pLastMessage->hasPositionEndGotInside()){
			checkNewMessage();
		}
	 
	}
	// No message scrolling yet ? Try to get one
	else
	{
		checkNewMessage();
	}
}



//--------------------------------------------------------------
void animationScrolling::checkNewMessage()
{
  rqMessage* pMessage = RQMESSAGES->getMessage();
  if (pMessage)
	  createMessageScrolling(pMessage);
}

//--------------------------------------------------------------
void animationScrolling::renderOffscreen()
{
	ofBackground(0);
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
	pMessageScrolling->setPosition(mp_grid->getCols(),0);

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


