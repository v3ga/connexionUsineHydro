#include "ofApp.h"
#include "ofAppLog.h"
#include "ofxXmlSettings.h"
#include "globals.h"
#include "js.h"

#include "animationWave.h"
#include "animationScrolling.h"
#include "animationWords.h"

#include "toolGrid.h"
#include "toolMessages.h"
#include "toolAnimations.h"

//--------------------------------------------------------------
void ofApp::setAnimCurrent(animation* pAnimation)
{
	if (mp_animationCurrent != pAnimation)
	{
		mp_animationCurrent = pAnimation;
		GLOBALS->mp_animationCurrent = mp_animationCurrent;

		m_grid.setAnimation(mp_animationCurrent);
	}
}

//--------------------------------------------------------------
void ofApp::setup()
{
	GLOBALS->setApp(this);

	OFAPPLOG->begin("ofApp::setup()");
	
		ofxXmlSettings settings;
		if (settings.load("configuration.xml"))
		{
			OFAPPLOG->println("-loaded configuration.xml");

			// Test : loading a pixel font
			m_pixelFontManager.add("fonts/150228_pixelfont.xml");
			m_pixelFontManager.add("fonts/150306_pixelfont.xml");
			m_pixelFontManager.add("fonts/150311_pixelfont.xml");

			GLOBALS->setPixelFontManager(&m_pixelFontManager);

			// JS
			setupJS();
			string animScript = settings.getValue("animation:name","___EMPTY___");

			// Grid size + DMX
			m_grid.setRowsCols(2,36);
			m_grid.setupDmx(settings);

			// Warm up
			m_skipWarmup = false;
			m_timeWarmup = settings.getValue("warmup:time", 15*60.0);
			
			
			mp_animationWarmup = new animation("Warmup");
			mp_animationWarmup->loadScript( ofFilePath::getAbsolutePath("js/animWarmup.js", true).c_str() );
			mp_animationWarmup->setup();
			mp_animationWarmup->setGrid(&m_grid);

			// Transition
			mp_animationTransition = new animation(animScript);
			setAnimCurrent(mp_animationTransition); // for loadShader function
			string pathScript = ofFilePath::getAbsolutePath("js/"+animScript, true);
			mp_animationTransition->loadScript(pathScript.c_str());
			mp_animationTransition->setup();
			mp_animationTransition->setGrid(&m_grid);

			// Animation messages
			mp_animation = new animationWords();
			mp_animation->setup();
			mp_animation->setGrid(&m_grid);

			setAnimCurrent(mp_animationWarmup);

			// Grid view
			m_gridView.setGrid(&m_grid);
			m_gridView.setDrawChannels(true);
			
			// Messages
			m_rqMessageManager.setURLRQInstallations("http://exhibitions.2roqs.com/");
			m_rqMessageManager.setInstalId(50);
			m_rqMessageManager.setLog(true);
			m_rqMessageManager.setPeriod(3.0, true);
			m_rqMessageManager.setup();

			GLOBALS->setRQMessageManager(&m_rqMessageManager);

			// Controls
			toolGrid* 		pToolGrid 		= new toolGrid(&m_toolManager);
			pToolGrid->setGrid(&m_grid);

			toolMessages* 	pToolMessages 	= new toolMessages(&m_toolManager, &m_rqMessageManager);
			toolAnimations* pToolAnimations = new toolAnimations(&m_toolManager);
			pToolAnimations->setAnimation(mp_animation);
			
			m_toolManager.setLogo("images/logo.png");
			m_toolManager.addTool(pToolGrid);
			m_toolManager.addTool(pToolMessages);
			m_toolManager.addTool(pToolAnimations);

			m_toolManager.createControls(ofVec2f(ofGetWidth(),ofGetHeight()),ofVec2f(ofGetWidth(),ofGetHeight()));
			m_toolManager.loadData();

		}

	OFAPPLOG->end();
	
	// App state
	m_appState = OFAPP_STATE_WARMP_UP;
	m_timeState = 0.0f;
}


//--------------------------------------------------------------
void ofApp::exit()
{
	m_toolManager.saveData();
	delete mp_animation;
	delete mp_animationWarmup;
	delete mp_animationTransition;
}

//--------------------------------------------------------------
void ofApp::update()
{
	float dt = ofGetLastFrameTime();
	m_timeState += dt;

	m_rqMessageManager.update(dt);
	m_toolManager.update();

	// State changes
	if (m_appState == OFAPP_STATE_WARMP_UP)
	{
		if (m_timeState>=m_timeWarmup || m_skipWarmup)
		{
			 m_timeState = 0.0f;
			 m_appState = OFAPP_STATE_SHOW_MSG;

			 setAnimCurrent(mp_animation);
		}
	}
	else
	if (m_appState == OFAPP_STATE_SHOW_MSG)
	{
		// No more messages in db & animation not doing things
		if (RQMESSAGES->getMessageNb() == 0 && !mp_animationCurrent->isActive())
		{
			 m_timeState = 0.0f;
//			 m_appState = OFAPP_STATE_SHOW_ANIMS_WAIT;
			 m_appState = OFAPP_STATE_SHOW_ANIMS;
			 mp_animationTransition->setAlphaRectOver(1.0f);
			 mp_animationTransition->setAlphaRectOverTarget(0.0f);
			 mp_animationTransition->setup();
			 setAnimCurrent(mp_animationTransition);
		}
	}
/*	else
	if (m_appState == OFAPP_STATE_SHOW_ANIMS_WAIT)
	{
		// Wait before showing animation
		if (m_timeState >= 5.0f)
		{
			m_timeState = 0.0f;
			 m_appState = OFAPP_STATE_SHOW_ANIMS;
			 setAnimCurrent(mp_animationTransition);
		}
	}
*/
	else
	if (m_appState == OFAPP_STATE_SHOW_ANIMS)
	{
		// New message !
		if (RQMESSAGES->getMessageNb()>0)
		{
			 m_timeState = 0.0f;
//			 m_appState = OFAPP_STATE_SHOW_MSG;

			 mp_animationTransition->setAlphaRectOver(0.0f);
			 mp_animationTransition->setAlphaRectOverTarget(1.0f);

			m_appState = OFAPP_STATE_SHOW_MSG_TRANSITION;

//			 setAnimCurrent(mp_animation);
		}
	}
	else
	if (m_appState == OFAPP_STATE_SHOW_MSG_TRANSITION)
	{
	 	if (mp_animationTransition && mp_animationTransition->m_alphaRectOverTarget >= 0.99f){
			m_timeState = 0.0f;
			m_appState = OFAPP_STATE_SHOW_MSG;
			setAnimCurrent(mp_animation);
		}
	}




	if (mp_animationCurrent){
		mp_animationCurrent->update(dt);
		mp_animationCurrent->render();
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
		float hRect = m_grid.getRows()*wRect;

		ofRectangle gridRect(0,0,ofGetWidth(),hRect);
		gridRect.setY( 0.5f*(ofGetHeight()-gridRect.getHeight()) );

		m_gridView.draw(gridRect);


		if (mp_animationCurrent)
		{
			ofRectangle gridAnimOffscreen(0,gridRect.getY()+gridRect.getHeight()+10,ofGetWidth(),hRect);
			mp_animationCurrent->getOffscreen().draw(gridAnimOffscreen);

			ofRectangle gridOffscreen(0,gridAnimOffscreen.getY()+gridAnimOffscreen.getHeight()+10,ofGetWidth(),hRect);
		     m_gridView.drawOffscreen(gridOffscreen);
		}





		m_toolManager.drawUI();
	}


	if (mp_animationCurrent)
	{
		ofSetColor(255);
		m_stringDebug = "app state="+getStateAsString();
		
		m_stringDebug+="\n"+mp_animationCurrent->getStringDebug();
		ofDrawBitmapString(m_stringDebug, 5, ofGetHeight()-3*12);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (mp_animationCurrent)
	{
		if (key == ' ')
		{
			if (mp_animationCurrent->isScript())
			{
				bool reloadedScript = mp_animation->reloadScript();
		 		OFAPPLOG->println(" - reloaded script "+ofToString(reloadedScript));
				mp_animationCurrent->setGrid(&m_grid);
				mp_animationCurrent->setup();
			}
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

//--------------------------------------------------------------
string ofApp::getStateAsString()
{
	if (m_appState == OFAPP_STATE_WARMP_UP) return "Warm up";
	if (m_appState == OFAPP_STATE_SHOW_MSG) return "Showing messages";
	if (m_appState == OFAPP_STATE_SHOW_ANIMS) return "Showing animations";
	if (m_appState == OFAPP_STATE_SHOW_ANIMS_WAIT) return "Showing animations (wait)";
	if (m_appState == OFAPP_STATE_SHOW_MSG_TRANSITION) return "Transition to messages";

	return "???";
}
