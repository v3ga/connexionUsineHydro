#pragma once

#include "ofMain.h"
#include "pixelFontManager.h"
#include "grid.h"
#include "gridView.h"
#include "tool.h"
#include "rqMessageManager.h"

class ofApp : public ofBaseApp{

	public:


		void setup();
		void exit();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
 
 
		pixelFontManager		m_pixelFontManager;
		grid					m_grid;
		gridView				m_gridView;
		animation*				mp_animation;
		animation*				mp_animationCurrent;
		animation*				mp_animationWarmup;
		animation*				mp_animationTransition;
		toolManager				m_toolManager;
		rqMessageManager		m_rqMessageManager;
 

		int						m_appState;
		float					m_timeState;
		float					m_timeWarmup;
		bool					m_skipWarmup;

		void					skipWarmup		(){m_skipWarmup=true;}
		void					setAnimCurrent	(animation* pAnimation);

 		enum
		{
			OFAPP_STATE_WARMP_UP			= 0,
			OFAPP_STATE_SHOW_MSG			= 1,
			OFAPP_STATE_SHOW_ANIMS			= 2,
			OFAPP_STATE_SHOW_ANIMS_WAIT		= 3,
			OFAPP_STATE_SHOW_MSG_TRANSITION = 4
		};
 
		string					getStateAsString();
		string					m_stringDebug;

 
};
