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
		bool					load			(string filename);
		pixelLetter*			getLetter		(int codePoint);
		pixelLetter*			getLetter		(string value);

	protected:
		string					m_name;
		int						m_rows,m_cols;
		vector<pixelLetter*>	m_letters;

		void		zeroAll		();
};