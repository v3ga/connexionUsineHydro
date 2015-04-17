this.frameCount = 0;
this.lines = new Array();
this.lineSize = 3;
this.grid = null;
this.lineSizes = [1,3,6,12];
this.lineIndex = 0;
this.nbPlay = 0;

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
	this.lineSize = 36;// this.lineSizes[ 3 ]; // 4 excluded
	this.lineNb = 2;//36/this.lineSize;
	this.lines = new Array();
	this.lineIndex = 0;
	this.nbPlay = 0;
	
	var x=0;
	for (var i=0; i<this.lineNb; i++)
	{
		if (i%2==0)
			this.lines.push( {x1:x, x2:x+this.lineSize, y:0} );
		else 
			this.lines.push( {x1:x, x2:x+this.lineSize, y:1} );

		x+=this.lineSize;
	}
}

//--------------------------------------------------------------
function renderOffscreen(w,h)
{
	//println( this.lineSize  + "/"+ this.lineNb);

	of.Background(0,0,0);
	this.grid.setOffscreenDim(w,h);

	for (var i=0;i<=this.lineIndex;i++)
	{
		this.grid.drawLineH(this.lines[i].x1,this.lines[i].x2, this.lines[i].y);
	}
}

//--------------------------------------------------------------
function update(dt)
{
	this.frameCount++;
	if (this.frameCount%10 == 0)
	{
		this.lineIndex = (this.lineIndex+1);
		if (this.lineIndex >= this.lines.length){
			this.lineIndex = 0;
			this.nbPlay++;
			if (this.nbPlay>=2){
				resetParameters();
			}
		}
	}

	return null;	
}

