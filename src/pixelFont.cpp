//
//  pixelFont.cpp
//  connexionUsineHydro
//
//  Created by Julien on 27/02/2015.
//
//

#include "pixelFont.h"
#include "pixelLetter.h"
#include "ofxXmlSettings.h"
#include "ofAppLog.h"
#include "utils.h"

//--------------------------------------------------------------
pixelFont::pixelFont()
{
	zeroAll();
}

//--------------------------------------------------------------
pixelFont::~pixelFont()
{
	for (int i=0;i<m_letters.size();i++)
		delete m_letters[i];
 	m_letters.clear();
}


//--------------------------------------------------------------
void pixelFont::zeroAll()
{
	m_name = "???";
	m_rows = 0;
	m_cols = 0;
}

//--------------------------------------------------------------
bool pixelFont::load(string filename)
{
	OFAPPLOG->begin("pixelFont::load("+filename+")");
	setFilename(filename);
	
	ofxXmlSettings data;
	bool ok = false;
	if ( data.load(ofToDataPath(filename)) )
	{
		// Read data here
		m_name = data.getAttribute("pixelfont", "name", "", 0);
		if (m_name != "")
		{
			OFAPPLOG->println("- name="+m_name);
			m_rows = data.getAttribute("pixelfont", "rows", 0, 0);
			m_cols = data.getAttribute("pixelfont", "cols", 0, 0);

			OFAPPLOG->println("- rows="+ofToString(m_rows)+",cols="+ofToString(m_cols));
			if (m_rows && m_cols)
			{
				data.pushTag("pixelfont");
				int nbLetters = data.getNumTags("char");
				OFAPPLOG->println("- found "+ofToString(nbLetters)+" letters");
				int codePoint=0;
				string strValue="";
				string strData="";
				for (int i=0;i<nbLetters;i++)
				{
					codePoint 	= data.getAttribute("char", "i", 0,i);
					strData 	= data.getValue("char","",i);
					strValue 	= data.getAttribute("char", "c", "",i);
					if (codePoint>0 && strValue!="" && strData!="")
					{
						OFAPPLOG->println("- adding letter (codePoint,char,data)=("+ofToString(codePoint)+","+strValue+","+strData+")");
					
						m_letters.push_back( new pixelLetter(codePoint,m_rows,m_cols,strValue,strData) );

					}
				}
				data.popTag();

				ok = true;
			}
		}
	}

	OFAPPLOG->end();
	return ok;
}

//--------------------------------------------------------------
pixelLetter* pixelFont::getLetter(int codePoint)
{
	for (int i=0;i<m_letters.size();i++)
	{
		if (m_letters[i]->m_codePoint == codePoint)
			return m_letters[i];
	}
	return 0;
}

//--------------------------------------------------------------
pixelLetter* pixelFont::getLetter(string value)
{
	for (int i=0;i<m_letters.size();i++)
	{
		if (m_letters[i]->m_c == value)
			return m_letters[i];
	}
	return 0;
}

//--------------------------------------------------------------
string pixelFont::encodeString(string text)
{
	string s;

	string::iterator it = text.begin();
	while (it != text.end())
	{
		int codePoint = (int) utf8::next(it, text.end());
		pixelLetter* pLetter = getLetter( codePoint );
		if (pLetter){
			s = s + pLetter->m_c;
		}
	}
	
	return s;
}

//--------------------------------------------------------------
int pixelFont::getWidth(string text)
{
	int w = 0;

	string::iterator it = text.begin();
	while (it != text.end())
	{
		int codePoint = (int) utf8::next(it, text.end());
		pixelLetter* pLetter = getLetter( codePoint );
		if (pLetter)
			w+=pLetter->m_cols;
	}

	return w;
}






