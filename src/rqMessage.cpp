//
//  rqmessage.cpp
//  connexionUsineHydro
//
//  Created by Julien on 05/03/2015.
//
//

#include "rqMessage.h"

//--------------------------------------------------------------
rqMessage::rqMessage()
{
	zeroAll();
}

//--------------------------------------------------------------
void rqMessage::zeroAll()
{
	m_timestamp = 0;
	m_words.clear();
}

//--------------------------------------------------------------
bool rqMessage::read(ofxXmlSettings& xml, int index)
{
	m_timestamp = xml.getAttribute("msg", "timestamp", 0, index);
	m_text = xml.getValue("msg", "???", index);
 
	return true;
}

