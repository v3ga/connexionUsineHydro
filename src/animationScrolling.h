//
//  animationScrolling.h
//  connexionUsineHydro
//
//  Created by Julien on 05/03/2015.
//
//

#pragma once

#include "animation.h"
#include "pixelFont.h"

class rqMessage;
class messageScrolling;
class animationScrolling : public animation
{
	public:
		animationScrolling			();
		~animationScrolling			();
	

		void						setup			();
		void						update			(float dt);
		void						renderOffscreen	();
		pixelFont*					getPixelFont	(){return mp_pixelFont;}
		float						getSpeed		(){return m_speed;}

 	protected:
		pixelFont*					mp_pixelFont;
		rqMessage*					mp_message;
		float						m_speed;		// pixels per second
 		vector<messageScrolling*>	m_messagesScrolling;

		void						createMessageScrolling	(rqMessage* pMessage);
		void						deleteMessages			();
		void						checkNewMessage			();
};