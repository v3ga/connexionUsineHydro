this.rows = 0;
this.cols = 0;
this.grid = {};
this.gridTarget = {};
this.period = 0.5;
this.time = 0;

//--------------------------------------------------------------
// called once when instanced
function setup()
{
	this.time = period;
}

//--------------------------------------------------------------
function setGrid(rows,cols)
{
	this.grid 		= new Grid(rows,cols);
	this.gridTarget = new Grid(rows,cols);
}

//--------------------------------------------------------------
function update(dt)
{
	this.time+=dt;
	if (this.time>=this.period)
	{
	 	this.gridTarget.fillRandomValues();
		this.time = 0;
	}
	// this.grid.set(this.gridTarget); // copy
	this.grid.set(this.gridTarget, {relaxation : 0.4});

	// Return the grid values (Array) to be sent to dmx (and drawn in application UI)
	return this.grid.values;
}

