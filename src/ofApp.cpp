#include "ofApp.h"
#include "ofAppLog.h"
#include "ofxXmlSettings.h"
#include "js.h"

#include "animationWave.h"


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

			// JS
			setupJS();
			string animScript = settings.getValue("animation:name","___EMPTY___");

			// Grid size + DMX
			m_grid.setRowsCols(1,4);
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
				mp_animation = new animationWave();
			}

			mp_animation->setup();
			mp_animation->setGrid(&m_grid);

			m_grid.setAnimation(mp_animation);

			// Grid view
			m_gridView.setGrid(&m_grid);


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

	m_grid.update(dt);
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
