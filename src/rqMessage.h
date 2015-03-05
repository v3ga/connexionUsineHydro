//
//  rqMessage.h
//  connexionUsineHydro
//
//  Created by Julien on 05/03/2015.
//
//

#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"

class rqMessage
{
	public:
		rqMessage			();

		bool				read(ofxXmlSettings& xml, int index);
	
 
		int					m_timestamp;
		string				m_text;
		vector<string>		m_words;


	private:
		void				zeroAll	();
};


