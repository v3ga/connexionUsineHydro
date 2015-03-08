this.fSin2 = 0.5;
this.dSin2 = 0;
this.fTime = 0;

//--------------------------------------------------------------
// called once when instanced
function setup()
{
	this.fSin2 = Math.random()*3.0+0.2;
	this.dSin2 = Math.random()*200.0+50.0
	this.fTime = Math.random()*0.5+0.5;

	loadShader("plasma");
}

//--------------------------------------------------------------
function renderOffscreen(w,h)
{
	beginShader();
		setUniform1fShader("resolutionx", w );
		setUniform1fShader("resolutiony", h );
		setUniform1fShader("time", this.fTime*of.GetElapsedTimef() );
		setUniform1fShader("fSin2", this.fSin2 );
		setUniform1fShader("dSin2", this.dSin2 );
		of.Rect(0,0,w,h);
	endShader();
}

//--------------------------------------------------------------
function update(dt)
{
	return null;	
}

