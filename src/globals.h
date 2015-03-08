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

class pixelFontManager;
class rqMessageManager;
class animation;
class Globals
{
	public:
		Globals					();
		static Globals*			instance();



		void					setPixelFontManager	(pixelFontManager* p){mp_pixelFontManager=p;}
		pixelFontManager*		getPixelFontManager	(){return mp_pixelFontManager;}

		void					setRQMessageManager	(rqMessageManager* p){mp_rqMessageManager=p;}
		rqMessageManager*		getRQMessageManager	(){return mp_rqMessageManager;}
 

		animation*				mp_animation;

	private:
		static Globals*			smp_instance;
		pixelFontManager*		mp_pixelFontManager;
		rqMessageManager*		mp_rqMessageManager;
};