//
//  toolGrid.cpp
//  connexionUsineHydro
//
//  Created by Julien on 11/03/2015.
//
//

#include "toolGrid.h"
#include "grid.h"
#include "ofxUIValuePlotter.h"

//--------------------------------------------------------------
toolGrid::toolGrid(toolManager* pParent) : tool("Grille",pParent)
{
	mp_grid 			= 0;
	mp_uiPlotterPower 	= 0;

   	m_periodPlot		= 0.15f;
	m_timePlot			= 0.0f;
}

//--------------------------------------------------------------
void toolGrid::createControlsCustom()
{
	if (mp_canvas)
	{
		ofxUIWidgetFontType fontType = OFX_UI_FONT_SMALL;
		float dim = 16;
		int widthDefault = 320;

	    mp_canvas->addWidgetDown( new ofxUILabel("Grille",OFX_UI_FONT_LARGE) );
    	mp_canvas->addWidgetDown( new ofxUISpacer(widthDefault, 2) );

		if (mp_grid)
		{
			mp_canvas->addWidgetDown(new ofxUISlider("attenuation", 0.0f, 1.0f, &mp_grid->m_attenuation, widthDefault, dim ));

			mp_uiPlotterPower = new ofxUIValuePlotter(0,0,widthDefault,100,100,0.0f,1.0f,&mp_grid->m_powerNorm,"Power");

			mp_canvas->addWidgetDown(mp_uiPlotterPower);
		}
	
		mp_canvas->autoSizeToFitWidgets();
		mp_canvas->disableAppDrawCallback();
	}
}

//--------------------------------------------------------------
void toolGrid::update()
{
	float dt = ofGetLastFrameTime();

	if (mp_grid)
	{
		if (mp_uiPlotterPower)
		{
			m_timePlot+=dt;
ofLog() << m_timePlot;
			if (m_timePlot>=m_periodPlot)
			{
				mp_uiPlotterPower->addPoint( mp_grid->getPowerNorm() );
				m_timePlot=0.0f;
			}
		}
	}
}
