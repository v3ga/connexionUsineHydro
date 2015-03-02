/*
 *  js.cpp
 *  versatubes
 *
 *  Created by 2Roqs on 04/05/12.
 *  Copyright 2012 2Roqs. All rights reserved.
 *
 */

#include "js.h"
#include "ofAppLog.h"
//--------------------------------------------------------------
bool setupJS()
{
	OFAPPLOG->begin("setupJS()");

	bool ret = false;

	int err = ofxJSInitialize();
	if (err==0)
	{
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

