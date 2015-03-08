//--------------------------------------------------------------
// called once when instanced
function setup()
{
	this.center = null;
	loadShader("wave");
}

//--------------------------------------------------------------
function renderOffscreen(w,h)
{
	if (this.center == null){
		this.center  = {};
	}
	this.center.x = w/2;
	this.center.y = h/2;

	var frequence = 0.125;
	var timeFactor = 1;
	
//	loadShader("wave"); // uncomment for live glsl editing :-)
	beginShader();
		setUniform1fShader("resolutionx", w );
		setUniform1fShader("resolutiony", h );
		setUniform1fShader("centerx", this.center.x );
		setUniform1fShader("centery", this.center.y );
		setUniform1fShader("time", of.GetElapsedTimef() );
		setUniform1fShader("frequence", frequence );
		setUniform1fShader("timeFactor", timeFactor );
		of.Rect(0,0,w,h);
	endShader();
}

//--------------------------------------------------------------
function update(dt)
{
	return null;	
}

