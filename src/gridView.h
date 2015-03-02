//
//  gridView.h
//  connexionUsineHydro
//
//  Created by Julien on 02/03/2015.
//
//

#pragma once
#include "ofMain.h"

class grid;
class gridView
{
	public:
		gridView	();
 
		void		setGrid		(grid* pGrid);
		void		draw		(ofRectangle& rect);
 
 
 	protected:
		grid*		mp_grid;
		bool		m_isDrawChannelDmx;
};