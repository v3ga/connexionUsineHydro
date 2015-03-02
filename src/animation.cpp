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

}

//--------------------------------------------------------------
animation::~animation()
{
	deleteScript();
}

//--------------------------------------------------------------
void animation::setGrid(grid* pGrid)
{
	mp_grid = pGrid;
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
}


//--------------------------------------------------------------
bool animation::loadScript(const char* s)
{
	OFAPPLOG->begin("animation::loadScript("+ofToString(s)+")");

	string pathAbs = s;
	if (pathAbs != "")
	{
		mp_script = ofxJSLoad(pathAbs,"___tmpScript___");
		if (mp_script)
		{
			mp_obj = JS_NewObject(ofxJSGetContext(), NULL, NULL, ofxJSGetGlobalObj());
    		JSBool ok = JS_SetPrivate(ofxJSGetContext(), mp_obj, (void*)this);
			JS_AddNamedRoot(ofxJSGetContext(), &mp_obj, m_name.c_str());


			if (ofxJSEvalOnObject(mp_script, mp_obj))
			{
				OFAPPLOG->println("OK evaluated '"+ofToString(s)+"'");
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
	return loadScript(m_pathAbsScript.c_str());
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
		if (mp_grid && ofxJSObject_IS_Array( array ))
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



