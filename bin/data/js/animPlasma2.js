this.fSin2 = 0.5;
this.dSin2 = 0;
this.fTime = 0;

this.fSin2_target = 0.5;
this.dSin2_target = 0;
this.fTime_target = 0;

this.periodChangeParam = 10.0;
this.time = 0.0;

//--------------------------------------------------------------
// called once when instanced
function setup()
{
	resetParameters();
	loadShader("plasma");
}


//--------------------------------------------------------------
function resetParameters()
{
	this.fSin2_target = Math.random()*3.0+0.2;
	this.dSin2_target = Math.random()*200.0+50.0
	this.fTime_target = Math.random()*0.5+0.5;
}

//--------------------------------------------------------------
function computeParameters(relaxation)
{
	this.fSin2 += (this.fSin2_target-this.fSin2)*relaxation*dt;
	this.dSin2 += (this.dSin2_target-this.dSin2)*relaxation*dt;
	this.fTime += (this.fTime_target-this.fTime)*relaxation*dt;
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
	this.time += dt;
	if (this.time>=this.periodChangeParam){
		this.time = 0;
		resetParameters();
	}



	return null;	
}

