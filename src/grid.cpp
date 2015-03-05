//
//  grid.cpp
//  connexionUsineHydro
//
//  Created by Julien on 02/03/2015.
//
//

#include "grid.h"
#include "animation.h"
#include "ofAppLog.h"


//--------------------------------------------------------------
grid::grid()
{
	zeroAll();
}

//--------------------------------------------------------------
grid::grid(int rows, int cols)
{
	zeroAll();
	setRowsCols(rows,cols);
}

//--------------------------------------------------------------
grid::~grid()
{
	deletePixels();
}

//--------------------------------------------------------------
void grid::zeroAll()
{
	m_rows 			= 0;
	m_cols 			= 0;
	mp_pixels 		= 0;
	mp_animation	= 0;
	m_isDmxSetup	= true;
}


//--------------------------------------------------------------
void grid::setRowsCols(int rows, int cols)
{
	zeroAll();

	m_rows = rows;
	m_cols = cols;

	createPixels();
}

//--------------------------------------------------------------
void grid::deletePixels()
{
	delete[] mp_pixels;
	mp_pixels = 0;
}

//--------------------------------------------------------------
void grid::createPixels()
{
	OFAPPLOG->begin("grid::createPixels()");
	
	deletePixels();
	if (m_rows>0 && m_cols>0)
	{
		OFAPPLOG->println("- rows="+ofToString(m_rows)+";cols="+ofToString(m_cols));

	 	mp_pixels = new gridPixel[m_rows*m_cols];
		for (int r=0;r<m_rows;r++)
		{
			for (int c=0;c<m_cols;c++)
			{
				mp_pixels[c+r*m_rows].setRowCol(r,c);
			}
		}
	}
	else
	{
		OFAPPLOG->begin("- WARNING ! cannot create pixels (rows or cols is 0)");
	}

	OFAPPLOG->end();
}


//--------------------------------------------------------------
bool grid::setupDmx(ofxXmlSettings& settings)
{
	OFAPPLOG->begin("grid::setupDmx()");
	
	string port = settings.getValue("dmx:port", "???");

	m_isDmxSetup	= false;
	if ( m_dmx.connect(port) )
	{
		OFAPPLOG->println("- OK connected to bus "+port);
		m_isDmxSetup = true;
	}
	else
	{
		OFAPPLOG->println("- ERROR connecting to bus "+port);
	}

	setChannelsDmx();
	

	OFAPPLOG->end();
}


//--------------------------------------------------------------
void grid::setChannelsDmx(int channelStart)
{
	OFAPPLOG->begin("grid::setChannelsDmx("+ofToString(channelStart)+")");
	if (mp_pixels)
	{
		int channel = channelStart;

		for (int r=0;r<m_rows;r++)
		{
			for (int c=0;c<m_cols;c++)
			{
				mp_pixels[c+r*m_rows].setChannelDmx(channel++);
			}
		}
	}

	OFAPPLOG->end();
}

//--------------------------------------------------------------
void grid::createPixelsAndSetDmx(int channelStart)
{
	createPixels();
	setChannelsDmx(channelStart);
}

//--------------------------------------------------------------
void grid::setAnimation(animation* pAnimation)
{
	mp_animation = pAnimation;
	if (mp_animation)
		mp_animation->setGrid(this);
}


//--------------------------------------------------------------
void grid::update(float dt)
{
	// Animation
	if (mp_animation)
		mp_animation->update(dt);

	// Send to dmx
	if (m_isDmxSetup && mp_pixels)
	{
		int nb = m_rows*m_cols;
		gridPixel* pGridPixel=0;
		for (int i=0; i<nb; i++)
		{
			pGridPixel = mp_pixels+i;
			m_dmx.setLevel(pGridPixel->m_channelDmx, pGridPixel->getValueDmx());
		}
		m_dmx.update();
	}
}

//--------------------------------------------------------------
void grid::setPixelValue(float value, int r, int c)
{
	if (mp_pixels && (r<m_rows && c<m_cols))
	{
		mp_pixels[c+r*m_rows].setValue(value);
	}
}

//--------------------------------------------------------------
void grid::setPixelValue(float value, int index)
{
	if (mp_pixels && index<getPixelsNb())
	{
		mp_pixels[index].setValue(value);
	}
}

//--------------------------------------------------------------
gridPixel* grid::getPixel(int r, int c)
{
	if (mp_pixels && (r<m_rows && c<m_cols))
	{
		return mp_pixels+(c+r*m_rows);
	}
	return 0;
}






