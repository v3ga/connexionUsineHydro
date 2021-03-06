//
//  messageScrolling.cpp
//  connexionUsineHydro
//
//  Created by Julien on 11/03/2015.
//
//

#include "messageScrolling.h"
#include "animationScrolling.h"
#include "rqMessage.h"
#include "pixelFont.h"
#include "pixelLetter.h"
#include "utf8.h"

//--------------------------------------------------------------
messageScrolling::messageScrolling(animationScrolling* pAnimation, rqMessage* pMessage)
{
	mp_animParent 		= pAnimation;
	mp_message			= pMessage;
	m_hasScrolled		= false;
	m_isInside			= false;
	m_isInsideLastTime	= false;
	
	if (pAnimation->getPixelFont())
	{
		m_textEncoded	= pAnimation->getPixelFont()->encodeString(pMessage->m_text);
		m_width			= pAnimation->getPixelFont()->getWidth(m_textEncoded);
	}

}

//--------------------------------------------------------------
void messageScrolling::setPosition(float x, float y)
{
	m_position.set(x,y);
}

//--------------------------------------------------------------
void messageScrolling::update(float dt)
{
	grid* pGrid = mp_animParent->getGrid();
	if (pGrid)
	{
		m_position.x -= mp_animParent->getSpeed()*dt;
		
		// Inside ?
		m_isInsideLastTime = m_isInside;
		m_isInside = getPositionEnd()<=pGrid->getCols()-2;
		
		// Out of screen ?
		// ofLog() << "x=" << m_position.x << ",w="<<m_width<<";end="<<getPositionEnd();
		if (getPositionEnd()<=-1)
		{
			m_hasScrolled = true; // will be removed by parent
		}
	}
}


//--------------------------------------------------------------
bool messageScrolling::hasPositionEndGotInside()
{
	if (m_isInside && !m_isInsideLastTime) return true;
	return false;
}

//--------------------------------------------------------------
void messageScrolling::drawOffscreen()
{
	pixelFont* pPixelFont = mp_animParent->getPixelFont();
	grid* pGrid = mp_animParent->getGrid();

	if (pPixelFont==0 || pGrid==0) return;


	float scaleOffscreen = mp_animParent->m_scaleGridOffscreen;
	float x = m_position.x;
	float y = 0;


	ofPushStyle();
	ofSetColor(255);


	ofPushMatrix();
	ofScale(scaleOffscreen,scaleOffscreen);

	ofPushMatrix();
	string::iterator it = m_textEncoded.begin();
	while (it != m_textEncoded.end())
	{
		int codePoint = (int) utf8::next(it, m_textEncoded.end());
		pixelLetter* pLetter = pPixelFont->getLetter( codePoint );
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
	ofPopMatrix();

 
	ofPopMatrix();
	ofPushStyle();
}
