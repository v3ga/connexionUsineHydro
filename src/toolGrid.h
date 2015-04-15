//
//  toolGrid.h
//  connexionUsineHydro
//
//  Created by Julien on 11/03/2015.
//
//

#pragma once
#include "tool.h"

class grid;
class ofxUIValuePlotter;
class toolGrid : public tool
{
	public:
		 toolGrid			(toolManager* pParent);
 
 
		 void				createControlsCustom	();
		 void				setGrid					(grid* pGrid=0){mp_grid=pGrid;}
		 void				update					();
		 void				handleEvents			(ofxUIEventArgs& e);

	protected:
		grid*						mp_grid;
		ofxUIValuePlotter*			mp_uiPlotterPower;
		float						m_periodPlot;
		float						m_timePlot;

};


