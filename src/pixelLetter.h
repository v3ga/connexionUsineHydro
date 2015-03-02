//
//  pixelLetter.h
//  connexionUsineHydro
//
//  Created by Julien on 28/02/2015.
//
//

#pragma once
#include "ofMain.h"

class pixelLetter
{
	public:
	   	pixelLetter			(int codePoint, int rows, int cols, string value, string strData);
	   	~pixelLetter		();

		void				decode(string strData);


		int					m_rows;
		int					m_cols;
		int					m_i;
		string				m_c;
		unsigned char*		mp_data;
};
