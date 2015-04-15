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
#include "Poco/UTF8String.h"


class rqMessageWord
{
	public:
 

};

class rqMessage
{
	public:
		rqMessage				();
		~rqMessage				();

		bool					read			(ofxXmlSettings& xml, int index);
		string					getWord			(int index);
		int						getWordsNb		(){return m_words.size();}
 
		int						m_timestamp;
		string					m_text;			// stored as utf8 sequence of caracters (see http://pocoproject.org/slides/040-StringsAndFormatting.pdf)
		vector<string>			m_words;

	private:
		void				zeroAll	();
};


