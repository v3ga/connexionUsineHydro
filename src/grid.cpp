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
	m_isDmxSetup	= false;
	m_isDmxEnable	= false;
	m_attenuation	= 1.0f;
	m_power			= 0.0f;
	m_powerNorm		= 0.0f;
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
				mp_pixels[c+r*m_cols].setRowCol(r,c);
			}
		}

		m_offscreen.allocate(m_cols, m_rows, GL_RGBA32F);
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
	
	m_isDmxEnable = settings.getAttribute("dmx", "enable", 0) > 0;

	if (m_isDmxEnable)
	{
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
	}
	else
	{
		OFAPPLOG->println("- Dmx not enabled. ");
	}

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
				mp_pixels[c+r*m_cols].setChannelDmx(channel++);
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
	// Offscreen > pixels
	m_offscreen.readToPixels(m_offscreenFloatPix);

	ofFloatColor color;
	gridPixel* pGridPixel = 0;
	for (int r=0;r<m_rows;r++)
	{
		for (int c=0;c<m_cols;c++)
		{
			color = m_offscreenFloatPix.getColor(c,r);

			pGridPixel = mp_pixels+(c+r*m_cols);
			pGridPixel->setValue( m_attenuation*color[0] );
			pGridPixel->update(dt);
		}
	}
	
	computePower();
}

//--------------------------------------------------------------
void grid::computePower()
{
	int nb = getPixelsNb();
	float powerMax = nb * mp_pixels[0].m_powerMax;
	m_power=0.0;
	for (int i=0;i<nb;i++){
		m_power += mp_pixels[i].m_power;
	}
	
	if (powerMax>0.0)
		m_powerNorm = m_power/powerMax;
	else
		m_powerNorm = 0.0;
}

//--------------------------------------------------------------
void grid::sendPixelsDmx()
{
	// Send to dmx
	if (m_isDmxEnable && m_isDmxSetup && mp_pixels)
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
		mp_pixels[c+r*m_cols].setValue(value);
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
		return mp_pixels+(c+r*m_cols);
	}
	return 0;
}

//--------------------------------------------------------------
void grid::renderOffscreen(ofFbo& other)
{
	beginOffscreen();
	ofBackground(0,0,200);
	//ofRect(0,0,m_offscreen.getWidth(),m_offscreen.getHeight());
	ofSetColor(255);
	
	other.getTextureReference().bind();
//	other.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);

		glTexCoord2f(other.getWidth(), 0);
		glVertex2f(m_offscreen.getWidth(), 0);

		glTexCoord2f(other.getWidth(), other.getHeight());
		glVertex2f(m_offscreen.getWidth(), m_offscreen.getHeight());

		glTexCoord2f(0, other.getHeight());
		glVertex2f(0,m_offscreen.getHeight());
	glEnd();
	other.getTextureReference().unbind();

	endOffscreen();
}








