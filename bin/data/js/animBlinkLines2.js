this.frameCount = 0;
this.y = 0;

//--------------------------------------------------------------
// called once when instanced
function setup()
{
	resetParameters();
}

//--------------------------------------------------------------
function setGrid(rows,cols)
{
	this.grid = new Grid(rows,cols);
}


//--------------------------------------------------------------
function resetParameters()
{
	this.frameCount = 0;
}

//--------------------------------------------------------------
function renderOffscreen(w,h)
{
	of.Background(0,0,0);
	this.grid.setOffscreenDim(w,h);
	this.grid.drawLineH(0, this.grid.cols, this.y);
}

//--------------------------------------------------------------
function update(dt)
{
	this.frameCount++;
	if (this.frameCount%15 == 0)
	{
		this.y = this.y == 0 ? 1 : 0; 
	}

	return null;	
}

