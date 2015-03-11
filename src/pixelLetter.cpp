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
	string c = "";
	int nb = m_rows*m_cols;
	for (int i=0;i<nb;i++)
	{
	   c = strData.at(strPos);
	   c += strData.at(strPos+1);

	   if (c == "00")	mp_data[i] = 0;
	   else
	   if (c == "FF")	mp_data[i] = 255;
   
	   strPos+=2;
	}
}

