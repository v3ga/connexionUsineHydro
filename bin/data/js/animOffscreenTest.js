this.period = 0.5;
this.time = 0;
this.render = false;

//--------------------------------------------------------------
// called once when instanced
function setup()
{
	this.time = period;
}

//--------------------------------------------------------------
function renderOffscreen(w,h)
{
	if (this.render)
	{
		of.Background(0,0,0);
		of.SetColor(255,255,255);
		for (i=0;i<2;i++){
			var x = Math.random()*w;
			var d = Math.random()*h;
			of.Ellipse(x,h/2,3*d,d);
		}


		this.render = false;
	}



}

//--------------------------------------------------------------
function update(dt)
{
	this.time+=dt;
	if (this.time>=this.period)
	{
		this.time = 0;
		this.render = true;
	}
	return null;	
}

