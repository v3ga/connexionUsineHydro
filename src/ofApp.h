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
		toolManager				m_toolManager;
		rqMessageManager		m_rqMessageManager;
 
};
