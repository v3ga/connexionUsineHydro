//
//  pixelFontManager.h
//  connexionUsineHydro
//
//  Created by Julien on 27/02/2015.
//
//

#pragma once
#include "pixelFont.h"

class pixelFontManager
{
	public:
		pixelFontManager	();
		~pixelFontManager	();

	
		bool		add				(string filename);
 		pixelFont*	get				(string name);
 		pixelFont*	getByFilename	(string filename);
 
	

	protected:
	
		vector<pixelFont*>	m_fonts;

};
