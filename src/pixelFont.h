//
//  pixelFont.h
//  connexionUsineHydro
//
//  Created by Julien on 27/02/2015.
//
//

#pragma once
#include "ofMain.h"

class pixelLetter;
class pixelFont
{
	public:
		pixelFont	();
		~pixelFont	();

		string					getName			()	{return m_name;}
		void					setName			(string name){m_name = name;}
		void					setFilename		(string filename){m_filename = filename;}
		string					getFilename		(){return m_filename;}
		bool					load			(string filename);
		pixelLetter*			getLetter		(int codePoint);
		pixelLetter*			getLetter		(string value);
 
 		string					encodeString	(string text); // removes unknown chars
		int						getWidth		(string text);
 
 
	protected:
		string					m_name;
		string					m_filename;
		int						m_rows,m_cols;
		vector<pixelLetter*>	m_letters;

		void		zeroAll		();
};