// --------------------------------------------------------
// --------------------------------------------------------
function Worm(grid)
{
	this.grid = grid;
	this.x = 0;
	this.y = 0;
	this.dirx = 0;
	this.frameCount = 0;
	this.frameSpeed = 25;

	this.reset = function()
	{
		this.dirx = Math.random() < 0.5 ? -1 : 1;
		this.x = this.dirx >0 ? grid.x : grid.x+grid.w;
		this.y = Math.random() < 0.5 ? 0 : 1;
		this.frameSpeed = 12;
		this.frameCount = 0;
	}

	this.update = function()
	{
		this.frameCount++;

		if (this.frameCount%this.frameSpeed==0)
		{		
			this.x += this.dirx;
			this.y = Math.random() < 0.5 ? 0 : 1;
			if (this.x>(this.grid.x+this.grid.w))
			{
				this.reset();
				return 1;
			}
		}
		return 0;
	}
}

// --------------------------------------------------------
// --------------------------------------------------------
function Grid(rows,cols)
{
	this.rows = rows;
	this.cols = cols;
	this.offscreenw = 0;
	this.offscreenh = 0;
	this.values = new Array(rows*cols);
	for (var i=0;i<this.values.length;i++)
		this.values[i]=0;

	this.setPixelValue = function(index, value)
	{
		this.values[i] = value;
	}

	this.setPixelValueRowCol = function(col, row, value)
	{
		this.values[col+this.cols*row] = value;
	}


	this.setPixelsAll = function(value)
	{
		for (var i=0;i<this.values.length;i++)
			this.values[i] = value;
	}
	
	this.set = function(otherGrid, parameters)
	{
		if (otherGrid.values.length == this.values.length)
		{
			// Relaxation
			if (parameters && parameters.relaxation)
			{
				for (var i=0;i<this.values.length;i++)
					 this.values[i] += (otherGrid.values[i]-this.values[i])*parameters.relaxation;
			}
			// Simple copy
			else
			{
				for (var i=0;i<this.values.length;i++)
					 this.values[i] = otherGrid.values[i];
			}
		}
	}
	
	this.fillRandomValues = function()
	{
		var nb = this.rows*this.cols;
		for (var i=0;i<nb;i++)
		{
			if (Math.random()>=0.5)
				this.values[i] = 0.9;
			else
				this.values[i] = 0.0;
		}
	}

	this.setOffscreenDim = function(w,h)
	{
		this.offscreenw = w;
		this.offscreenh = h;
	}

	
	this.drawPixel = function (x,y)
	{
		if (this.offscreenw == 0 || this.offscreenh == 0){
			println("offscreen dim = 0, call setOffscreenDim(w,h) before");
			return;
		}
		var wPixel = this.offscreenw/this.cols;
		var hPixel = this.offscreenh/this.rows;

		of.Rect(x*wPixel,y*hPixel,wPixel,hPixel);
	}

	this.drawLineH = function(x1,x2,y)
	{
		var wPixel = this.offscreenw/this.cols;
		var hPixel = this.offscreenh/this.rows;

		of.SetColor(255,255,255);
		of.Rect(x1*wPixel, y*hPixel, (x2-x1)*wPixel, hPixel);
	}


	this.draw = function (w,h)
	{
		var wPixel = w/this.cols;
		var hPixel = h/this.rows;
		var vPixel = 0;

		for (var r=0; r<this.rows; r++)
		{
			for (var c=0; c<this.cols; c++)
			{
				vPixel = this.values[c+this.cols*r]*255;
			
				of.SetColor( vPixel,vPixel,vPixel, 255 );
				of.Rect(c*wPixel,r*hPixel,wPixel,hPixel);
			}
		}
	}

}


// --------------------------------------------------------
// --------------------------------------------------------
function getRandomInt(min, max) 
{
  return Math.floor(Math.random() * (max - min)) + min;
}