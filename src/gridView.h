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
 
		void		setGrid			(grid* pGrid);
		void		setDrawChannels	(bool is=true){m_isDrawChannelDmx=is;}
		void		draw			(ofRectangle& rect);
		void		drawOffscreen	(ofRectangle& rect);
 
 
 	protected:
		grid*		mp_grid;
		bool		m_isDrawChannelDmx;
};