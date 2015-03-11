//
//  gridPixel.h
//  connexionUsineHydro
//
//  Created by Julien on 02/03/2015.
//
//

#pragma once
#include "ofMain.h"

class gridPixel
{
	public:
		gridPixel		();

		void			setRowCol		(int row, int col){m_row = row; m_col = col;}
		void			setValue		(float value);
		void			setChannelDmx	(int channelDmx){m_channelDmx = channelDmx;}
		int				getValueDmx		(){return (int) ofMap(m_value,0.0f,1.0f,0,255);}
		vector<float>&	getHistory		(){return m_valueHistory;}

		int				m_row, m_col;
		int				m_channelDmx;
		float			m_value;



	protected:
		void			zeroAll			();

		bool			m_isHistory;
		int				m_historySize;
		vector<float>	m_valueHistory;

};