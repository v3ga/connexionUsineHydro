this.speed = 2;
this.angle = 0;
this.w = 0;
this.h = 0;
this.wPixel = 0;

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
	of.Background(0,0,0);
	this.grid.setOffscreenDim(w,h);
	this.wPixel = w/this.grid.cols;
	var hPixel = h/this.grid.rows;

	of.SetColor(255,255,255);

//	this.grid.drawPixel(this.x,0);
//	this.grid.drawPixel(this.x,1);
	this.w = w;

//	of.Rect(this.x-2*wPixel, 0, this.wPixel, 2*hPixel);
//	of.Rect(this.x-wPixel, 0, this.wPixel, 2*hPixel);
	of.Rect(this.x, 0, this.wPixel, hPixel);
	of.Rect(this.x+this.wPixel, 0, this.wPixel, hPixel);
	of.Rect(w-this.x, hPixel, this.wPixel, hPixel);
	of.Rect(w-this.x-this.wPixel, hPixel, this.wPixel, hPixel);
//	of.Rect(this.x+wPixel, 0, this.wPixel, 2*hPixel);
}

//--------------------------------------------------------------
function update(dt)
{
	if (this.w>0)
	{
		this.angle += 40*dt; 
		this.x = of.Map( Math.cos( of.DegToRad(this.angle)),Math.cos(of.DegToRad(30+90)),Math.cos(of.DegToRad(30)), 0,this.w);
		if (this.angle>=180)
			this.angle =0;
	}

	return null;	
}

