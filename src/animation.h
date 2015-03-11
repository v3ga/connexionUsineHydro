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


class pixelFont;
class animation
{
	public:
			animation			(string name);
			virtual ~animation	();

		   virtual void		setGrid				(grid*, float scaleForOffscreen=20);
				   grid*	getGrid				(){return mp_grid;}
 
		   // called once
		   // load data here
		   virtual void		setup				();
 
		   // will update the pixels of the grid
		   virtual void		update				(float dt);
 
		   // render to the grid offscreen
		   virtual	void	render				();
		   virtual	void	renderOffscreen		();
		   virtual	bool	isRenderOffscreen	(){return true;}
		   			ofFbo&	getOffscreen		(){return m_offscreen;}
			float			m_scaleGridOffscreen;
 
		   // Utility
		   //virtual void 	drawTextGrid		(string s, pixelFont*, int x=0, int y=0);
 
		   // shader stuf
			void			beginShader			();
			void			endShader			();
			void			loadShader			(string name);
			ofShader		m_shader;
 

		   // scripts
		   bool				loadScript			(const char* pathAbs);
		   bool				reloadScript		();
		   void				deleteScript		();
		
			bool			isScript			(){return mp_script!=0;}

	protected:
			grid*			mp_grid;
			string			m_name;
 
			ofFbo			m_offscreen;

			string			m_pathAbsScript;
			ofxJSScript*	mp_script;
			JSObject*		mp_obj;
 
			void			callScriptSetup				();
			void			callScriptUpdate			(float dt);
			void			callScriptRenderOffscreen	();
			void			callScriptSetGrid			();
};
