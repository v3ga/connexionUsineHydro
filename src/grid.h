//
//  grid.h
//  connexionUsineHydro
//
//  Created by Julien on 02/03/2015.
//
//

#pragma once
#include "gridPixel.h"
#include "ofxDmx.h"
#include "ofxXmlSettings.h"

class animation;
class grid
{
   public:

 		grid		();
 		grid		(int rows, int cols);
 		~grid		();


		void		setRowsCols				(int rows, int cols);
		int			getRows					(){return m_rows;}
		int			getCols					(){return m_cols;}
		gridPixel*	getPixels				(){return mp_pixels;}
		int			getPixelsNb				(){return m_cols*m_rows;}
	
		void		deletePixels			();
		void		createPixels			();

		void		createPixelsAndSetDmx	(int channelStart=1);
		bool		setupDmx				(ofxXmlSettings& settings);
 		void		setChannelsDmx			(int channelStart=1); // no "0" for DMX

		void		setAnimation			(animation*);
		animation*	getAnimation			(){return mp_animation;}

		void		update					(float dt);
		void		sendPixelsDmx			();
		void		setPixelValue			(float value, int r, int c);
		void		setPixelValue			(float value, int index);
		gridPixel*	getPixel				(int r, int c);
 
		void		beginOffscreen			(){m_offscreen.begin();}
		void		endOffscreen			(){m_offscreen.end();}
		void		renderOffscreen			(ofFbo& other);
		ofFbo&		getOffscreen			(){return m_offscreen;}

   protected:
   		void			zeroAll					();
 
		int				m_rows,m_cols;
		gridPixel*		mp_pixels;

		animation*		mp_animation;
		ofFbo			m_offscreen;
		ofFloatPixels	m_offscreenFloatPix;

		ofxDmx			m_dmx;
		bool			m_isDmxSetup;
		bool			m_isDmxEnable;

};