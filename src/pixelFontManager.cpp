//
//  pixelFontManager.cpp
//  connexionUsineHydro
//
//  Created by Julien on 27/02/2015.
//
//

#include "pixelFontManager.h"
#include "ofAppLog.h"

//--------------------------------------------------------------
pixelFontManager::pixelFontManager()
{
}

//--------------------------------------------------------------
pixelFontManager::~pixelFontManager()
{
	for (int i=0;i<m_fonts.size();i++)
		delete m_fonts[i];
	m_fonts.clear();
}

//--------------------------------------------------------------
bool pixelFontManager::add(string filename)
{
	OFAPPLOG->begin("pixelFontManager::add("+filename+")");

	bool ok = false;

	pixelFont* pFont = new pixelFont();

	if (pFont->load(filename))
	{
		if ( get(pFont->getName()) == 0)
		{
			m_fonts.push_back( pFont );
			ok = true;
		}
		else{
			OFAPPLOG->println("- ALREADY EXISTS, not adding it to the fonts list.");
		}
	}
	else
	{
		OFAPPLOG->println("- ERROR loading the file.");
	}

	if (!ok)
		delete pFont;

	OFAPPLOG->end();

	return ok;
}

//--------------------------------------------------------------
pixelFont* pixelFontManager::get(string name)
{
	for (int i=0;i<m_fonts.size();i++)
		if (m_fonts[i]->getName() == name)
			return m_fonts[i];
	return 0;
}
