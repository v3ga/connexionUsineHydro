//
//  animation.h
//  connexionUsineHydro
//
//  Created by Julien on 02/03/2015.
//
//

#pragma once
#include "ofMain.h"
#include "grid.h"
#include "ofxJavascript.h"


class animation
{
	public:
			animation			(string name);
			virtual ~animation	();

		   virtual void		setGrid		(grid*);
				   grid*	getGrid		(){return mp_grid;}
 
		   // called once
		   // load data here
		   virtual void	setup		();
 
		   // will update the pixels of the grid
		   virtual void	update		(float dt);

		   // Script
		   bool				loadScript			(const char* pathAbs);
		   bool				reloadScript		();
		   void				deleteScript		();
		
			bool			isScript			(){return mp_script!=0;}

	protected:
			grid*			mp_grid;
			string			m_name;

			string			m_pathAbsScript;
			ofxJSScript*	mp_script;
			JSObject*		mp_obj;
 
			void			callScriptSetup		();
			void			callScriptUpdate	(float dt);
			void			callScriptSetGrid	();
};
