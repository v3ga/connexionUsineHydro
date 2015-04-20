this.angle = 0;
this.w = 0;
this.c = 0;

//--------------------------------------------------------------
// called once when instanced
function setup()
{
	this.x = 0;
}

//--------------------------------------------------------------
function setGrid(rows,cols)
{
	this.grid = new Grid(rows,cols);
}

//--------------------------------------------------------------
function renderOffscreen(w,h)
{
	this.w = w;

	of.Background(0,0,0);
	this.grid.setOffscreenDim(w,h);

	of.SetColor(c,c,c);


	of.Rect(0,0,w,h);
}

//--------------------------------------------------------------
function update(dt)
{
	this.angle += 100*dt; 
	this.c = of.Map( Math.cos( of.DegToRad(this.angle)),-1,1, 40,255);
//	this.c = 255*(Math.sin(of.DegToRad(angle))^13) * Math.cos(of.DegToRad(angle)-Math.PI/10)


	if (this.angle>=360)
		this.angle -= 360;
	return null;	
}

