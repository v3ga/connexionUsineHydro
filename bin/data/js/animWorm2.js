this.bClearScreen = 1;
this.frameSpeed = 20;
this.divide = [3,6,12];
this.worms = null;
this.grid = null;

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
	this.frameCount=0;

	this.d = 36;
	this.worms = new Array();

//	for (var i=0;i<6;i++)
	{
//		this.worms.push( new Worm(  {x:i*this.d, w:this.d} ) );
		var worm = new Worm(  {x:0, w:36} );
		worm.reset();
		this.worms.push( worm );
	}
}

//--------------------------------------------------------------
function renderOffscreen(w,h)
{
	of.Background(0,0,0);
	if (this.bClearScreen>0)
	{
		this.bClearScreen = 0;
	}

	var wPixel = w/this.grid.cols;
	var hPixel = h/this.grid.rows;
	for (var i=0; i<this.worms.length; i++)
	{
		var w = this.worms[i];
		of.SetColor(255,255,255);
		of.Rect(w.x*wPixel,w.y*hPixel,wPixel,hPixel);
	}


//	println(this.grid.cols)
}

//--------------------------------------------------------------
function update(dt)
{
	this.frameCount++;
	for (var i=0;i<this.worms.length;i++)
		this.bClearScreen = this.worms[i].update(this.frameCount);

	return null;	
}

