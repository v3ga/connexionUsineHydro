function Grid(rows,cols)
{
	this.rows = rows;
	this.cols = cols;
	this.values = new Array(rows*cols);
	for (var i=0;i<this.values.length;i++)
		this.values[i]=0;

	this.setPixelValue = function(index, value)
	{
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
}