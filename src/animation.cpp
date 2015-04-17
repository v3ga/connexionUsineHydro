//
//  animation.cpp
//  connexionUsineHydro
//
//  Created by Julien on 02/03/2015.
//
//

#include "animation.h"
#include "ofAppLog.h"

//--------------------------------------------------------------
animation::animation(string name)
{
	m_name = name;

	mp_grid 	= 0;
	mp_script 	= 0;
	mp_obj		= 0;
	m_scaleGridOffscreen = 1;
	m_isRenderOffscreen = true;
	m_alphaRectOver = 0.0f;
	m_alphaRectOverTarget = 0.0f;
}

//--------------------------------------------------------------
animation::~animation()
{
	deleteScript();
}

//--------------------------------------------------------------
void animation::setGrid(grid* pGrid, float scaleForOffscreen)
{
	mp_grid = pGrid;
	m_scaleGridOffscreen = scaleForOffscreen;
	m_offscreen.allocate(scaleForOffscreen*mp_grid->getCols(),scaleForOffscreen*mp_grid->getRows(),GL_RGBA32F);
	callScriptSetGrid();
}

//--------------------------------------------------------------
void animation::setup()
{
	callScriptSetup();
}

//--------------------------------------------------------------
void animation::update(float dt)
{
	callScriptUpdate(dt);

	m_alphaRectOver += (m_alphaRectOverTarget-m_alphaRectOver)*0.95*dt;
//	ofLog()<<"alpha="<<m_alphaRectOver;
}

//--------------------------------------------------------------
void animation::render()
{
	if (isRenderOffscreen())
	{
		m_offscreen.begin();
		renderOffscreen();

		if (m_alphaRectOver>=0.01f)
		{
			// ofLog() << m_alphaRectOver;
			ofPushStyle();
			ofEnableAlphaBlending();
			ofSetColor(0,m_alphaRectOver*255.0f);
			ofRect(0,0,m_offscreen.getWidth(),m_offscreen.getHeight());
			ofDisableAlphaBlending();
			ofPopStyle();
		}
		m_offscreen.end();


		if (mp_grid)
		{
			mp_grid->renderOffscreen( m_offscreen );
		}
	}
}

//--------------------------------------------------------------
void animation::renderOffscreen()
{
	callScriptRenderOffscreen();
}

//--------------------------------------------------------------
void animation::beginShader()
{
	m_shader.begin();
}

//--------------------------------------------------------------
void animation::endShader()
{
	m_shader.end();
}

//--------------------------------------------------------------
void animation::loadShader(string name)
{
	string v = "shaders/"+name+".vert";
	string f = "shaders/"+name+".frag";
	m_shader.load(v,f);
}


//--------------------------------------------------------------
bool animation::loadScript(const char* s)
{
	OFAPPLOG->begin("animation::loadScript("+ofToString(s)+")");
	m_pathAbsScript = s;
	OFAPPLOG->println("m_pathAbsScript=("+m_pathAbsScript+")");

	if (m_pathAbsScript != "")
	{
		mp_script = ofxJSLoad(m_pathAbsScript,"___tmpScript___");
		if (mp_script)
		{
			mp_obj = JS_NewObject(ofxJSGetContext(), NULL, NULL, ofxJSGetGlobalObj());
    		JSBool ok = JS_SetPrivate(ofxJSGetContext(), mp_obj, (void*)this);
			JS_AddNamedRoot(ofxJSGetContext(), &mp_obj, m_name.c_str());


			if (ofxJSEvalOnObject(mp_script, mp_obj))
			{
				OFAPPLOG->println("OK evaluated '"+ofToString(s)+"'");
				OFAPPLOG->println("m_pathAbsScript=("+m_pathAbsScript+")");

				OFAPPLOG->end();


				return true;
			}
			else{
				OFAPPLOG->println("ERROR cannot eval script '"+ofToString(s)+"'");
				deleteScript();
			}
		}
		else{
			OFAPPLOG->println("ERROR cannot load script '"+ofToString(s)+"'");
			deleteScript();
		}
	}
	else
	{
		OFAPPLOG->println("ERROR path for script '"+ofToString(s)+"' is empty..." );
	}

	OFAPPLOG->end();
	return false;
}

//--------------------------------------------------------------
void animation::deleteScript()
{
	if (mp_script){
		delete mp_script;
		mp_script=0;
	}
}

//--------------------------------------------------------------
bool animation::reloadScript()
{
	OFAPPLOG->begin("animation::reloadScript()");
	OFAPPLOG->println("m_pathAbsScript="+m_pathAbsScript);
	bool is = loadScript(m_pathAbsScript.c_str());
	OFAPPLOG->end();
	return is;
}


//--------------------------------------------------------------
void animation::callScriptSetup()
{
	if (isScript() && mp_obj)
	{
		ofxJSValue retVal;
		ofxJSCallFunctionNameObject_NoArgs_IfExists(mp_obj,"setup",retVal);
	}
}

//--------------------------------------------------------------
void animation::callScriptUpdate(float dt)
{
	if (isScript() && mp_obj )
	{
		ofxJSValue retVal;
		ofxJSValue args[1];
		args[0] = float_TO_ofxJSValue(dt);

		ofxJSCallFunctionNameObject_IfExists(mp_obj,"update", args,1,retVal);

		JSObject* array = JSVAL_TO_OBJECT(retVal);
		if (mp_grid && array && ofxJSObject_IS_Array( array ))
		{
			jsuint arrayLength=0;
			ofxJSArrayLength(array,arrayLength);
			if ((int)arrayLength == mp_grid->getPixelsNb())
			{
				jsval arrayValue;
				for (int i=0;i<mp_grid->getPixelsNb();i++)
				{
					JS_GetElement(ofxJavascript::smp_instance->getContext(), array, (jsint) i, &arrayValue);
				 	mp_grid->setPixelValue(ofxJSValue_TO_float(arrayValue), i);
				}
			}
		}
	}
}


//--------------------------------------------------------------
void animation::callScriptRenderOffscreen()
{
	if (isScript() && mp_obj )
	{
		ofxJSValue retVal;
		ofxJSValue args[2];
		args[0] = float_TO_ofxJSValue( m_offscreen.getWidth() );
		args[1] = float_TO_ofxJSValue( m_offscreen.getHeight() );

		ofxJSCallFunctionNameObject_IfExists(mp_obj,"renderOffscreen", args,2,retVal);
	}
}

//--------------------------------------------------------------
void animation::callScriptSetGrid()
{
	if (isScript() && mp_obj && mp_grid)
	{
		ofxJSValue retVal;
		ofxJSValue args[2];
		args[0] = int_TO_ofxJSValue(mp_grid->getRows());
		args[1] = int_TO_ofxJSValue(mp_grid->getCols());

		ofxJSCallFunctionNameObject_IfExists(mp_obj,"setGrid", args,2,retVal);
	}
}



