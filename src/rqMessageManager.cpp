//
//  rqMessageManager.cpp
//  connexionUsineHydro
//
//  Created by Julien on 05/03/2015.
//
//

#include "rqMessageManager.h"
#include "rqMessage.h"
#include "ofAppLog.h"

//--------------------------------------------------------------
rqMessageManager::rqMessageManager()
{
	zeroAll();
}

//--------------------------------------------------------------
rqMessageManager::~rqMessageManager()
{
	deleteMessages();
	zeroAll();
}

//--------------------------------------------------------------
void rqMessageManager::zeroAll()
{
	m_maxtimestamp = 0;
	m_period = 0;
	m_timePeriod = 0;
	m_isLog = false;
	m_isLoading = false;
}

//--------------------------------------------------------------
void rqMessageManager::updateURL()
{
	m_url = m_urlRQInstallations+"api.php?action=getMessages&instalId="+ofToString(m_instalId)+"&lastTimestamp="+ofToString(m_maxtimestamp);
}

//--------------------------------------------------------------
void rqMessageManager::deleteMessages()
{
	for (int i=0;i<m_messages.size();i++)
	{
		delete m_messages[i];
	}
	m_messages.clear();
}

//--------------------------------------------------------------
void rqMessageManager::setPeriod(float p, bool isImmediate)
{
	m_period = p;
	if (isImmediate) m_timePeriod = m_period;
}


//--------------------------------------------------------------
void rqMessageManager::setup()
{
	ofRegisterURLNotification(this);
}

//--------------------------------------------------------------
void rqMessageManager::update(float dt)
{
	m_timePeriod += dt;
	if (m_timePeriod>=m_period && m_isLoading==false)
	{
		loadNewMessages();
		m_timePeriod = 0.0f;
	}
}


//--------------------------------------------------------------
rqMessage* rqMessageManager::getMessage()
{
	if (isLoading()==false)
	{
		if (m_messages.size()>0)
		{
			rqMessage* pMessage = m_messages[0];
			m_messages.erase( m_messages.begin() ); // remove first element
			return pMessage; // let the caller delete this object when it is done with it
		}
	}
	return 0;
}

//--------------------------------------------------------------
rqMessage* rqMessageManager::getMessageAt(int index)
{
	if (index < m_messages.size())
	{
		return m_messages[index];
	}
	return 0;
}

//--------------------------------------------------------------
void rqMessageManager::loadNewMessages()
{
	m_isLoading = true;
	ofLoadURLAsync(m_url); // will call urlResponse function
}

//--------------------------------------------------------------
void rqMessageManager::urlResponse(ofHttpResponse& response)
{
	beginLog("rqMessageManager::urlResponse()");
	println(" - response.status="+ofToString(response.status));

	if (response.status==200/* && response.request.name == "async_req"*/)
	{
		// Check for rqerror
		
		// XML
		string data = response.data.getText();
		
		ofxXmlSettings xml;
		if ( xml.loadFromBuffer(data) )
		{
			// Maxtimestamp
			m_maxtimestamp = xml.getAttribute("messages", "maxtimestamp",0);
			println(" - m_maxtimestamp="+ofToString(m_maxtimestamp));
			updateURL();
			
			// Messages
			xml.pushTag("messages");
			int nbMessages = xml.getNumTags("msg");
		
			println(" - nb messages="+ofToString(nbMessages));
			
			for (int i=0;i<nbMessages;i++)
			{
				rqMessage* pNewMessage = new rqMessage();
				if (pNewMessage->read(xml, i))
				{
					println(" - message["+ofToString(i)+"] text="+pNewMessage->m_text+" / timestamp="+ofToString(pNewMessage->m_timestamp));

					m_messages.push_back(pNewMessage);
				}
				else{
					delete pNewMessage;
				}
			}
		 
			 xml.popTag();
		 
		}

		m_isLoading = false;
	}
	endLog();
}

//--------------------------------------------------------------
void rqMessageManager::beginLog(string s)
{
	if (m_isLog) OFAPPLOG->begin(s);
}

//--------------------------------------------------------------
void rqMessageManager::println(string s)
{
	if (m_isLog) OFAPPLOG->println(s);
}

//--------------------------------------------------------------
void rqMessageManager::endLog()
{
	if (m_isLog) OFAPPLOG->end();
}





