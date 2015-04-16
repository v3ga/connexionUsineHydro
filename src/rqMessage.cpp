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
rqMessage::~rqMessage()
{
	
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
	// Timestamp
	m_timestamp = xml.getAttribute("msg", "timestamp", 0, index);

	if (m_timestamp == 1427821942) // for debug purpose, message is too long
		return false;
	
	// Text
	m_text = xml.getValue("msg", "???", index);

 	// Words
 	xml.pushTag("msg", index);
 	xml.pushTag("words");
	
	int nbWords = xml.getNumTags("w");
	string code = "";
	for (int i=0;i<nbWords;i++)
	{
		code = xml.getAttribute("w", "code", "", i);
		if (code != "")
		{
			m_words.push_back(code);
		}
	}

	xml.popTag();
	xml.popTag();
 
	return true;
}

//--------------------------------------------------------------
string rqMessage::getWord(int index)
{
	if (index < m_words.size())
	{
		return m_words.at(index);
	}
	return "";
}
