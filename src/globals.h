//
//  globals.h
//  connexionUsineHydro
//
//  Created by Julien on 05/03/2015.
//
//

#pragma once

#define GLOBALS Globals::instance()
#define PIXELFONTS GLOBALS->getPixelFontManager()
#define RQMESSAGES GLOBALS->getRQMessageManager()
#define APP GLOBALS->getApp()

#define OFAPP_PATH_JS(file) ofFilePath::getAbsolutePath("js/file", true).c_str()

class pixelFontManager;
class rqMessageManager;
class animation;
class ofApp;
class Globals
{
	public:
		Globals					();
		static Globals*			instance();

		ofApp*					getApp				(){return mp_app;}
		void					setApp				(ofApp* p){mp_app = p;}


		void					setPixelFontManager	(pixelFontManager* p){mp_pixelFontManager=p;}
		pixelFontManager*		getPixelFontManager	(){return mp_pixelFontManager;}

		void					setRQMessageManager	(rqMessageManager* p){mp_rqMessageManager=p;}
		rqMessageManager*		getRQMessageManager	(){return mp_rqMessageManager;}
 

		animation*				mp_animationCurrent;

	private:
		static Globals*			smp_instance;

		ofApp*					mp_app;
		pixelFontManager*		mp_pixelFontManager;
		rqMessageManager*		mp_rqMessageManager;
};