//
//  animationWords.h
//  connexionUsineHydro
//
//  Created by Julien on 15/04/2015.
//
//

#pragma once

#include "animation.h"




class rqMessage;
class animationWords : public animation
{
public:
		animationWords			();
		~animationWords			();
 
		void					setup				();
		void					update				(float dt);
		void					renderOffscreen		();
		void					setGrid				(grid*, float scaleForOffscreen);
		void					drawString			(string textEncoded, float x, float y);
		bool					isActive			();


		float					m_wordSpeedScrolling;		// pixels per second
		float					m_timeWordShow;
		float					m_timeWordIn,m_timeWordOut;


 	protected:
		pixelFont*				mp_pixelFont;

		// Current message displayed
		rqMessage*				mp_message;
		string					m_word;
		int						m_wordLength;
		int						m_indexWordMessage;
		ofVec2f					m_wordPosition;

		float					m_timeNewMessageShow;
		int						m_state;
		float					m_timeState;
		float					m_timeDoneScroll;


	
		void					initMessageData			();
		int						selectNextWord			();
		void					checkNewMessage			();
		void					resetGridTimeNewMsg		();
		void					resetGridTime			();

		float					getWordAlpha			(float t);
		int						getWordLength			(string word);

		float*					mp_gridTimeNewMsg;
		float*					mp_gridTime;

		string					getStateAsString		();
 

		enum
		{
			HAS_NO_MESSAGE			= 0,
			SHOWING_WORD			= 1,
			SHOWING_WORD_SCROLLING	= 2,
			HIDE_WORD_TRANSTION		= 3,
			SHOW_WORD_TRANSTION		= 4,
			SHOW_WORD_NEW_MESSAGE	= 5
		};

};