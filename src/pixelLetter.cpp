//
//  pixelLetter.cpp
//  connexionUsineHydro
//
//  Created by Julien on 28/02/2015.
//
//

#include "pixelLetter.h"

//--------------------------------------------------------------
pixelLetter::pixelLetter(int codePoint, int rows, int cols, string value, string strData)
{
	m_codePoint = codePoint;
	m_c =  value;
	m_rows = rows;
	m_cols = cols;
	mp_data = new unsigned char[m_rows*m_cols];
	memset(mp_data, 0, sizeof(unsigned char));
	decode(strData);
}

//--------------------------------------------------------------
pixelLetter::~pixelLetter()
{
	delete[] mp_data;
	mp_data = 0;
}

//--------------------------------------------------------------
void pixelLetter::decode(string strData)
{
	int strPos=0;
	for (int r=0;r<m_rows;r++)
	{
		for (int c=0;c<m_cols;c++)
		{
			
		
			strPos+=2;
		}
	}
}

