/*
 *  js.cpp
 *  versatubes
 *
 *  Created by 2Roqs on 04/05/12.
 *  Copyright 2012 2Roqs. All rights reserved.
 *
 */

#include "js.h"
#include "globals.h"
#include "ofAppLog.h"
#include "animation.h"

//--------------------------------------------------------------
bool setupJS()
{
	OFAPPLOG->begin("setupJS()");

	bool ret = false;

	int err = ofxJSInitialize();
	if (err==0)
	{
		ofxJSDefineFunctionGlobal("loadShader",						&loadShader,					1); // name, function pointer, args number
		ofxJSDefineFunctionGlobal("beginShader",					&beginShader,					0); // name, function pointer, args number
		ofxJSDefineFunctionGlobal("endShader",						&endShader,						0); // name, function pointer, args number
		ofxJSDefineFunctionGlobal("setUniform1fShader",				&setUniform1fShader,			2); // name, function pointer, args number
		ofxJSDefineFunctionGlobal("setUniform2fShader",				&setUniform2fShader,			3); // name, function pointer, args number



		// Load globals
		ofxJSScript* pScript = ofxJSLoadFromData("js/lib.js", "lib"); // "exampleId" is used for error reporting
		bool evalOk = false;
		if (pScript)
		{
			evalOk = ofxJSEval(pScript);
			if (evalOk){
				OFAPPLOG->println("- loaded js/lib.js");
			}
		}

		if (!evalOk)
			OFAPPLOG->println("- ERROR loading (or evaluating) js/lib.js");

		ret = evalOk;
	}
	else
	{
		OFAPPLOG->println("- ERROR inializing JS engine");
	}
	
	OFAPPLOG->end();
	
	return ret; // TODO err checking
}


//--------------------------------------------------------------
ofxJSDefineFunctionCpp(loadShader)
{
	animation* pAnimation = GLOBALS->mp_animation;
	if (argc==1 && pAnimation)
	{
		pAnimation->loadShader(ofxJSValue_TO_string(argv[0]));
		return JS_TRUE;
	}

	return JS_FALSE;
}

//--------------------------------------------------------------
ofxJSDeclareFunctionCpp(beginShader)
{
	animation* pAnimation = GLOBALS->mp_animation;
	if (pAnimation)
		pAnimation->beginShader();
	return JS_TRUE;
}

//--------------------------------------------------------------
ofxJSDeclareFunctionCpp(endShader)
{
	animation* pAnimation = GLOBALS->mp_animation;
	if (pAnimation)
		pAnimation->endShader();

	return JS_TRUE;
}

//--------------------------------------------------------------
ofxJSDeclareFunctionCpp(setUniform1fShader)
{
	animation* pAnimation = GLOBALS->mp_animation;
	if (argc==2 && pAnimation)
	{
		pAnimation->m_shader.setUniform1f(ofxJSValue_TO_string(argv[0]).c_str(), ofxJSValue_TO_float(argv[1]));
		return JS_TRUE;
	}
	return JS_FALSE;
}

//--------------------------------------------------------------
ofxJSDeclareFunctionCpp(setUniform2fShader)
{
	animation* pAnimation = GLOBALS->mp_animation;
	if (argc==3 && pAnimation)
	{
		pAnimation->m_shader.setUniform2f(ofxJSValue_TO_string(argv[0]).c_str(), ofxJSValue_TO_float(argv[1]), ofxJSValue_TO_float(argv[2]));
		return JS_TRUE;
	}
	return JS_FALSE;
}


