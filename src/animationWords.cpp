//
//  animationWords.cpp
//  connexionUsineHydro
//
//  Created by Julien on 15/04/2015.
//
//

#include "animationWords.h"
#include "rqMessage.h"
#include "pixelFont.h"
#include "pixelLetter.h"
#include "pixelFontManager.h"
#include "rqMessageManager.h"
#include "utf8.h"
#include "globals.h"
#include "utils.h"

//--------------------------------------------------------------
animationWords::animationWords() : animation("Words")
{
	mp_pixelFont 			= 0;
	m_timeWordShow 			= 3.0f;
	m_timeNewMessageShow	= 0.25f;
	mp_message 				= 0;
	mp_gridTimeNewMsg		= 0;
	m_indexWordMessage		= 0;
	m_wordSpeedScrolling	= 5.0f;
	m_state = HAS_NO_MESSAGE;
	m_timeWordIn			= 0.4f;
	m_timeWordOut			= 0.4f;
}

//--------------------------------------------------------------
animationWords::~animationWords()
{
	delete[] mp_gridTimeNewMsg;
	mp_gridTimeNewMsg = 0;
}

//--------------------------------------------------------------
string animationWords::getStateAsString()
{
	if (m_state == HAS_NO_MESSAGE) return "has no message";
	if (m_state == SHOWING_WORD) return "showing word";
	if (m_state == SHOWING_WORD_SCROLLING) return "showing word scrolling";
	
	return "???";
}

//--------------------------------------------------------------
void animationWords::setGrid(grid* pGrid, float scaleForOffscreen)
{
	animation::setGrid(pGrid, scaleForOffscreen);
	mp_gridTimeNewMsg = new float[ mp_grid->getPixelsNb() ];
}

//--------------------------------------------------------------
void animationWords::resetGridTimeNewMsg()
{
	int nb = mp_grid->getPixelsNb();
	for (int i=0;i<nb;i++)
		mp_gridTimeNewMsg[i] = ofRandom( 0.5f );
}

//--------------------------------------------------------------
void animationWords::resetGridTime()
{
	int nb = mp_grid->getPixelsNb();
	for (int i=0;i<nb;i++)
		mp_gridTimeNewMsg[i] = ofRandom( 0.5f );
}



//--------------------------------------------------------------
void animationWords::setup()
{
	mp_pixelFont = PIXELFONTS->getByFilename("fonts/150311_pixelfont.xml");
}

//--------------------------------------------------------------
void animationWords::initMessageData()
{
	m_indexWordMessage = 0;
}

//--------------------------------------------------------------
int animationWords::selectNextWord()
{
	if (m_indexWordMessage < mp_message->getWordsNb())
	{
		m_word = mp_pixelFont->encodeString( mp_message->getWord(m_indexWordMessage) );
		m_wordLength = getWordLength(m_word);

		if (m_wordLength<=mp_grid->getCols())
		{
			int deltax = (mp_grid->getCols() - m_wordLength)/2;
			deltax -= deltax%3;

			m_wordPosition.set(deltax,0);
			return SHOWING_WORD;
		}
		else
		{
			m_wordPosition.set(0,0);
			m_timeDoneScroll = 0.0f;
			return SHOWING_WORD_SCROLLING;
		}
	}
	else
	{
		delete mp_message;
		mp_message = 0;
		return HAS_NO_MESSAGE;
	}
}

//--------------------------------------------------------------
void animationWords::update(float dt)
{
	m_stringDebug = "messages remaining = "+ofToString(RQMESSAGES->getMessageNb());
	m_stringDebug += "\nstate="+getStateAsString();
	if (mp_message)
	{
	   m_stringDebug +=  " / message = "+mp_message->m_text;

		if (m_word != "")
			m_stringDebug +=  " / word="+m_word;
	}

	// ----------------------------------------

	if (m_state == HAS_NO_MESSAGE)
	{
		mp_message = RQMESSAGES->getMessage();
		if (mp_message)
		{
			m_timeState = 0;
			m_indexWordMessage = 0;
			
			m_state = selectNextWord();
		}
	}
	
	// ----------------------------------------

	else if (m_state == SHOWING_WORD)
	{
		m_timeState += dt;
		if (m_timeState>=(m_timeWordIn+m_timeWordShow+m_timeWordOut))
		{
			m_timeState = 0.0f;
			
			m_indexWordMessage = m_indexWordMessage+1;
			m_state = selectNextWord();
		}
	}
	
	// ----------------------------------------

	else if (m_state == SHOWING_WORD_SCROLLING)
	{
		m_timeState += dt;
		int delta = m_wordLength - mp_grid->getCols();
		bool isDoneScroll = (int)m_wordPosition.x <= -delta;

		// Scroll afer showing the message
		if (m_timeState>=(m_timeWordIn+m_timeWordShow) && !isDoneScroll)
		{
			m_wordPosition.x -= m_wordSpeedScrolling*dt;
		}
		
		if(isDoneScroll)
		{
			m_timeDoneScroll += dt;
			if (m_timeDoneScroll >= (m_timeWordShow+m_timeWordOut))
			{
				m_timeState = 0.0f;
				m_indexWordMessage = m_indexWordMessage+1;
				m_state = selectNextWord();
			}
		}
	}
}

//--------------------------------------------------------------
void animationWords::renderOffscreen()
{
	ofBackground(0);

	ofPushStyle();
	ofSetColor(255);

	ofPushMatrix();
	ofScale(m_scaleGridOffscreen,m_scaleGridOffscreen);

	if (m_word != "")
	{
		ofSetColor( 255, 255*getWordAlpha(m_timeState) );
		drawString(m_word, m_wordPosition.x,0);
	}

	ofPopMatrix();

	ofPopStyle();
	
}

//--------------------------------------------------------------
void animationWords::checkNewMessage()
{
}

//--------------------------------------------------------------
void animationWords::drawString(string textEncoded, float x, float y)
{
	string::iterator it = textEncoded.begin();
	while (it != textEncoded.end())
	{
		int codePoint = (int) utf8::next(it, textEncoded.end());
		pixelLetter* pLetter = mp_pixelFont->getLetter( codePoint );
		if (pLetter)
		{
			for (int r=0; r<pLetter->m_rows; r++)
			{
				for (int c=0; c<pLetter->m_cols; c++)
				{
					unsigned char cc = pLetter->mp_data[c+r*pLetter->m_cols];
					if (cc>0)
					{
						ofRect(x+c,y+r,1,1);
					}
				}
			}
		}

		x = x+3; // next char position
	}
}

//--------------------------------------------------------------
float animationWords::getWordAlpha(float t)
{
	// TODO : put this timing in variables
	// VARIABLES !
	

	if (m_state == SHOWING_WORD)
	{
		float tMax = m_timeWordShow;
		if (t<=m_timeWordIn)
		{
			float b = m_timeWordIn;
			return t/b;
		}
		else if (t<=(m_timeWordIn+m_timeWordShow))
		{
			return 1.0f;
		}
		else
		{
			float tMax 	= m_timeWordIn+m_timeWordShow+m_timeWordOut;
			float c 	= m_timeWordIn+m_timeWordShow;
			
			// pente = 1
			ofLog() << 1.0/(tMax-c)*(tMax-t);
			
			return 1.0/(tMax-c)*(tMax-t);
		}
	}
	else
	if (m_state == SHOWING_WORD_SCROLLING)
	{
		float tMax = m_timeWordIn;
		if (t<=m_timeWordIn)
		{
			float b = m_timeWordIn;
			return t/b;
		}
		else if (t<=(m_timeWordIn+m_timeWordShow))
		{
			return 1.0f;
		}
		else
			return 1.0f-m_timeDoneScroll/(m_timeWordOut+m_timeWordShow);
	}

}

//--------------------------------------------------------------
int animationWords::getWordLength(string word)
{
	return utils::lengthUtf8(word) * 3;
}


