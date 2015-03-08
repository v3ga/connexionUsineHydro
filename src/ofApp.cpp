#include "ofApp.h"
#include "ofAppLog.h"
#include "ofxXmlSettings.h"
#include "globals.h"
#include "js.h"

#include "animationWave.h"
#include "animationScrolling.h"


//--------------------------------------------------------------
void ofApp::setup()
{
	OFAPPLOG->begin("ofApp::setup()");
	
		ofxXmlSettings settings;
		if (settings.load("configuration.xml"))
		{
			OFAPPLOG->println("-loaded configuration.xml");

			// Test : loading a pixel font
			m_pixelFontManager.add("fonts/150228_pixelfont.xml");
			m_pixelFontManager.add("fonts/150306_pixelfont.xml");
			GLOBALS->setPixelFontManager(&m_pixelFontManager);

			// JS
			setupJS();
			string animScript = settings.getValue("animation:name","___EMPTY___");

			// Grid size + DMX
			m_grid.setRowsCols(2,72);
			m_grid.setupDmx(settings);

			// Creating animation
			if (animScript != "___EMPTY___")
			{
				mp_animation = new animation(animScript);
				string pathScript = ofFilePath::getAbsolutePath("js/"+animScript, true);
				mp_animation->loadScript(pathScript.c_str());
			}
			else
			{
				mp_animation = new animationScrolling();
			}
			GLOBALS->mp_animation = mp_animation;

			mp_animation->setup();
			mp_animation->setGrid(&m_grid);

			m_grid.setAnimation(mp_animation);

			// Grid view
			m_gridView.setGrid(&m_grid);
			m_gridView.setDrawChannels(false);
			
			// Messages
			m_rqMessageManager.setURLRQInstallations("http://exhibitions.2roqs.com/");
			m_rqMessageManager.setInstalId(50);
			m_rqMessageManager.setLog();
			m_rqMessageManager.setPeriod(3.0, true);
			m_rqMessageManager.setup();

			GLOBALS->setRQMessageManager(&m_rqMessageManager);

			// Controls
			m_toolManager.createControls(ofVec2f(ofGetWidth(),ofGetHeight()),ofVec2f(ofGetWidth(),ofGetHeight()));
		}

	OFAPPLOG->end();
}

//--------------------------------------------------------------
void ofApp::exit()
{
	delete mp_animation;
}

//--------------------------------------------------------------
void ofApp::update()
{
	float dt = ofGetLastFrameTime();

	m_rqMessageManager.update(dt);
	if (mp_animation){
		mp_animation->render();
		mp_animation->update(dt);
	}
	m_grid.update(dt);
	m_grid.sendPixelsDmx();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0);

	if (m_grid.getCols()>0)
	{
		float wRect = ofGetWidth() / (float)m_grid.getCols();
		float hRect = wRect;

		ofRectangle gridRect(0,0,ofGetWidth(),hRect);
		gridRect.setY( 0.5f*(ofGetHeight()-gridRect.getHeight()) );

		m_gridView.draw(gridRect);


		if (mp_animation)
		{
			ofRectangle gridAnimOffscreen(0,gridRect.getY()+gridRect.getHeight()+10,ofGetWidth(),hRect);
			mp_animation->getOffscreen().draw(gridAnimOffscreen);

			ofRectangle gridOffscreen(0,gridAnimOffscreen.getY()+gridAnimOffscreen.getHeight()+10,ofGetWidth(),hRect);
		     m_gridView.drawOffscreen(gridOffscreen);
		}




		m_toolManager.drawUI();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (mp_animation)
	{
		if (key == ' ')
		{
			bool reloadedScript = mp_animation->reloadScript();
	 		OFAPPLOG->println(" - reloaded script "+ofToString(reloadedScript));
			mp_animation->setGrid(&m_grid);
			mp_animation->setup();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
