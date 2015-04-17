//
//  rqMessageManager.h
//  connexionUsineHydro
//
//  Created by Julien on 05/03/2015.
//
//

#pragma once
#include "ofMain.h"

class rqMessage;
class rqMessageManager
{
	public:
		rqMessageManager		();
		~rqMessageManager		();
	
		void					setInstalId				(int instalId){m_instalId = instalId;updateURL();}
		void					setURLRQInstallations	(string url){m_urlRQInstallations=url;updateURL();}
		void					setLog					(bool is=true){m_isLog = is;}
		void					setPeriod				(float p, bool isImmediate=false);
		void					saveTimestampFile		(int ts);
		void					loadTimestampFile		();
 		bool					isLoading				(){return m_isLoading;}
 
		rqMessage*				getMessage				();
		rqMessage*				getMessageAt			(int index); // wont remove the message from list, use carefully
		int						getMessageNb			();

 		void					setTimestamp			(int ts);
		int						getMaxTimestamp			(){return m_maxtimestamp;}
 
 
 

		void					setup					();
		void					update					(float dt);
		void 					urlResponse				(ofHttpResponse& response);

		float					m_period;
 

	protected:
		void					zeroAll			();

		void					updateURL		();

		void					deleteMessages	();
		void					loadNewMessages	();

		void					beginLog		(string s);
		void					println			(string s);
		void					endLog			();

		vector<rqMessage*>		m_messages;
		int						m_maxtimestamp;
		int						m_desiredtimestamp;
		bool					m_bResetTimestamp;

		int						m_instalId;
		string					m_urlRQInstallations;
		string					m_url;
 
		float					m_timePeriod;
		bool					m_isLoading;
		bool					m_isLog;
 
		ofMutex					m_mutex;
};

