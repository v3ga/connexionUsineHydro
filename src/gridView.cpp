//
//  gridView.cpp
//  connexionUsineHydro
//
//  Created by Julien on 02/03/2015.
//
//

#include "gridView.h"
#include "grid.h"

//--------------------------------------------------------------
gridView::gridView()
{
	mp_grid = 0;
	m_isDrawChannelDmx = true;
}

//--------------------------------------------------------------
void gridView::setGrid(grid* pGrid)
{
	mp_grid = pGrid;
}

//--------------------------------------------------------------
void gridView::draw(ofRectangle& rect)
{
	if (mp_grid)
	{
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(rect.getX(),rect.getY());
	
		int rows = mp_grid->getRows();
		int cols = mp_grid->getCols();

		if (rows>0 && cols>0)
		{
			float stepx = rect.getWidth() / (float)cols;
			float stepy = rect.getHeight() / (float)rows;

			float x=0;
			float y=0;
			gridPixel* pGridPixel=0;
			for (int r=0;r<rows;r++)
			{
				x=0;
				for (int c=0;c<cols;c++)
				{
					pGridPixel = mp_grid->getPixel(r,c);
					if (pGridPixel)
					{
						ofPushMatrix();

							ofTranslate(x,y);

							ofFill();
							ofSetColor(255.0f, pGridPixel->getValueDmx() );
							ofRect(0,0,stepx,stepy);


							ofNoFill();
							ofSetColor(255.0f, 255.0f );
							ofRect(0,0,stepx,stepy);
					 
						 	if (m_isDrawChannelDmx)
							{
								ofSetColor((1.0f-pGridPixel->m_value)*255.0f);
								ofDrawBitmapString( ofToString(pGridPixel->m_channelDmx)+"/"+ofToString((int)(pGridPixel->getValueDmx())), 4,12 );
							}
					 

						ofPopMatrix();
					}
					x+=stepx;
				}
				y+=stepy;
			}
		
		}

		ofPopMatrix();
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void gridView::drawOffscreen(ofRectangle& rect)
{
	if (mp_grid)
	{
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(rect.getX(),rect.getY());
	
		mp_grid->getOffscreen().draw(0,0,rect.getWidth(),rect.getHeight());
	
		ofPopMatrix();
		ofPushStyle();
	}

}


