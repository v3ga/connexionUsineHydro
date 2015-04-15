this.grid = {};
this.timeWarm = 10.0;
this.time = 0;
this.valueWarm = 0;

//--------------------------------------------------------------
// called once when instanced
function setup()
{
	this.time = 0;
}

//--------------------------------------------------------------
function setGrid(rows,cols)
{
	this.grid = new Grid(rows,cols);
}

//--------------------------------------------------------------
function update(dt)
{
	this.time+=dt;
	this.valueWarm = this.time / this.timeWarm;
	if (this.valueWarm>1.0) this.valueWarm=1.0;
	this.grid.setPixelsAll( this.valueWarm );

	// Return the grid values (Array) to be sent to dmx (and drawn in application UI)
	// null if you don't want to set directly pixels in the grid
	return null;
}

//--------------------------------------------------------------
function renderOffscreen(w,h)
{
	of.Background(0,0,0);
	this.grid.draw(w,h);
}
