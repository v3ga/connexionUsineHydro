//
//  gridTiming.h
//  connexionUsineHydro
//
//  Created by Julien on 15/04/2015.
//
//

#pragma once

class gridTiming
{
	public:
		gridTiming		(int size);
		~gridTiming		();

		void			resetValuesReach		();
		void			resetValues				();

		bool			isDone					();
		void			update					(float dt);

		float*			mp_valuesReach;
		float*			mp_values;
 		bool*			mp_triggered;
 
		int				m_size;
};

