this.bClearScreen = 1;
this.frameSpeed = 20;

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
	this.bClearScreen = 1;
	this.wormx = 0;
	this.wormy = Math.random()>0.5 ? 0 : 1;
	this.frameCount=0;
	this.frameSpeed = getRandomInt(10,20);
}

//--------------------------------------------------------------
function renderOffscreen(w,h)
{
	if (this.bClearScreen>0)
	{
		this.bClearScreen = 0;
		of.Background(0,0,0);
	}

	this.frameCount++;
	if (this.frameCount%25==0)
	{
		of.SetColor(255,255,255);
		this.grid.setOffscreenDim(w,h);
		this.grid.drawPixel(this.wormx, this.wormy);

		this.wormx += 1;
		this.wormy = Math.random()>0.5 ? 0 : 1;

		if (this.wormx > this.grid.cols){
			this.resetParameters();
		}
	}
}

//--------------------------------------------------------------
function update(dt)
{
	return null;	
}

