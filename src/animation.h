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
		   virtual	bool	isRenderOffscreen	(){return m_isRenderOffscreen;}
		   virtual  void	setRenderOffscreen	(bool is=true){m_isRenderOffscreen=is;}
		   			ofFbo&	getOffscreen		(){return m_offscreen;}

			float			m_scaleGridOffscreen;
			bool			m_isRenderOffscreen;


			void			setAlphaRectOverTarget	(float a){m_alphaRectOverTarget=a;}
			void			setAlphaRectOver		(float a){m_alphaRectOver=a;}
 			float			m_alphaRectOver,m_alphaRectOverTarget;

 
		   // Utility
		   //virtual void 	drawTextGrid		(string s, pixelFont*, int x=0, int y=0);
 
		   // shader stuff
			void			beginShader			();
			void			endShader			();
			void			loadShader			(string name);
			ofShader		m_shader;
 
 
 
 			// Activity
			virtual	bool	isActive			(){return false;}
 

		   // scripts
		   bool				loadScript			(const char* pathAbs);
		   bool				reloadScript		();
		   void				deleteScript		();
		
			bool			isScript			(){return mp_script!=0;}
 
			string			getStringDebug		(){return m_stringDebug;}
			string			m_pathAbsScript;

	protected:
			grid*			mp_grid;
			string			m_name;
 
			ofFbo			m_offscreen;

			ofxJSScript*	mp_script;
			JSObject*		mp_obj;
 
			void			callScriptSetup				();
			void			callScriptUpdate			(float dt);
			void			callScriptRenderOffscreen	();
			void			callScriptSetGrid			();
 
			string			m_stringDebug;
};
