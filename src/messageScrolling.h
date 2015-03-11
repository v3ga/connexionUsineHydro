//
//  messageScrolling.h
//  connexionUsineHydro
//
//  Created by Julien on 11/03/2015.
//
//

#pragma once
#include "ofMain.h"

class animationScrolling;
class rqMessage;

class messageScrolling
{
	public:
		messageScrolling	(animationScrolling* pAnimation, rqMessage* pMessage);


		void				setPosition				(float x, float y=0.0f);
		void				setSpeed				(float speed);
		void				update					(float dt);
		void				drawOffscreen			();
		float				getPositionEnd			(){return m_position.x+m_width;}
		bool				hasPositionEndGotInside	();

		ofVec2f				m_speedOffscreen;

 
		animationScrolling*	mp_animParent;	// parent animation
		rqMessage*			mp_message;		// refering message
		string				m_textEncoded; 	// using a pixelfont and mp_message->m_text
		ofVec2f				m_position;		// position in pixels
		float				m_width;		// width in pixels

		bool				m_hasScrolled;	// tells if the message was dislpayed and now is hidden
		bool				m_isInside;		// tells if the end position of the message is inside the grid
		bool				m_isInsideLastTime; // same bu the frame before
};
