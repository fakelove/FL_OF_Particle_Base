#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofEnableAlphaBlending();
  
    
    pointLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));

    
    // specular color, the highlight/shininess color //
	pointLight.setSpecularColor( ofColor(240.f, 240.f, 240.f));
	pointLight.setPointLight();
       
    scratch.loadImage("of.png");
    //light.setPosition(200, 200, 200);
    
    gui.setup("Panel");
    gui.add(maxParticleSpeed.setup("Speed", 10, 0,50));
    gui.add(maxParticleSize.setup("Size", 50, 0.0, 200.0));
    gui.add(maxParticleAge.setup("Age", 50, 0.0, 4000.0));
    gui.add(MaxThresh.setup("MaxThresh", .3, -3, 3));
    gui.add(MinThresh.setup("MinThresh", 0, -3, 3));
    gui.add(exponent.setup("exponent", 1, -10, 10));
    gui.add(ssaoRadius.setup("ssaoRadius", 30, -500, 500));
    gui.add(bumpSlider.setup("bumpSlider", 30, -500, 500));
    gui.add(addBlend.setup("AddBlend", false));
    gui.add(SSAOswitch.setup("SSAO", false));
    gui.add(AlphaBlendSwitch.setup("AlphaBlend", false));
    gui.add(pointLightSwitch.setup("PointLight", true));
    gui.add(cameraSwitch.setup("Camera", false));
    gui.add(gravity.setup("Gravity", 0, -30, 30));
    gui.add(wind.setup("Wind", 0, -30, 30));
    gui.add(attraction.setup("Attraction", 0, -30, 30));
    
    ParticleEmitter.setup(ofPoint(ofGetWidth()/2, ofGetHeight()/2), maxParticleSpeed, maxParticleSize, maxParticleAge, ofColor(80,120,255,255),ofColor(0,255,0,0));

	material.setShininess( 120 );
    // the light highlight of the material //
	material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    //camera.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
    
    fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    ofFbo::Settings s;
    s.width			= 600;
    s.height			= 600;
    s.internalformat   = GL_RGBA;
    s.useDepth			= true;
    // and assigning this values to the fbo like this:
    fbo1.allocate(s);
    
    fbo1.begin();
    ofClear(0, 0, 0);
    fbo1.end();
    colorCount = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    //ofSetFrameRate(60);
    
    ssao.setup( ofGetWidth(), ofGetHeight(), GL_RGBA16F );
	ssao.setRayReflection( true );
	ssao.setRadius(ssaoRadius);
	ssao.setExponent(exponent);
	ssao.setMinThreshold(MinThresh);
	ssao.setMaxThreshold(MaxThresh);
    ssao.setWeight(1.0);
    ssao.setNumSamples(8);
    
    // radius of the sphere //
	float radius		= 180.f;
	ofPoint center;
    center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    
    pointLight.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x, 
						   sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y, 
						   -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
    //pointLight.setPosition(ofPoint(ofGetMouseX(), ofGetMouseY()));
    
    ofSetWindowTitle("FPS: " + ofToString(ofGetFrameRate()));
    ParticleEmitter.update(maxParticleSpeed, maxParticleSize, maxParticleAge);
    ParticleEmitter.setOrigin(ofPoint(ofGetMouseX(), ofGetMouseY()));
    
    ParticleEmitter.setForces(gravity, wind, attraction);
    
    ofColor colorStart, colorEnd;
    
    colorCount = (colorCount + 1);
    colorCount = fmod(colorCount, 255);
    colorStart.setHsb(colorCount, 255,255);
    colorEnd.setHsb(255-colorCount, 255,255);

    ofRect(400, 400, 200, 200);
    ParticleEmitter.setColors(ofColor(colorStart), ofColor(colorEnd));

}

//--------------------------------------------------------------
void testApp::draw(){

    
    ofDisableBlendMode();
    ofBackgroundGradient(ofColor::gray,ofColor(30,10,30), OF_GRADIENT_CIRCULAR);

    glEnable(GL_DEPTH_TEST);
    if(SSAOswitch) ssao.begin();
    
    //fbo1.begin(); //not working yet
    
    if( ofGetKeyPressed('c') ){
		ofClear(0,0,0, 0);
	}	
    
    int fadeAmnt = 1;
	if(ofGetKeyPressed('1')){
		fadeAmnt = 1;
	}else if(ofGetKeyPressed('2')){
		fadeAmnt = 5;
	}else if(ofGetKeyPressed('3')){
		fadeAmnt = 15;
	}  
    
	ofFill();
	ofSetColor(0,0,0, fadeAmnt);
	//ofRect(0,0,ofGetWidth(),ofGetHeight());

    if(cameraSwitch) camera.begin();
    
    if(AlphaBlendSwitch) ofEnableAlphaBlending();
    if(pointLightSwitch) ofEnableLighting(); 
    if(pointLightSwitch) material.begin(); //this gives the boxes shininess
    if(pointLightSwitch) pointLight.enable();

    ofPushMatrix();
    if(addBlend) ofEnableBlendMode(OF_BLENDMODE_ADD);
    ParticleEmitter.draw(-ofGetWidth()/2,-ofGetHeight()/2);
    ofPopMatrix();

    if(pointLightSwitch) material.end();
    if(pointLightSwitch) pointLight.disable();
    if(pointLightSwitch) ofDisableLighting();
    
    if(cameraSwitch) camera.end();
    
    //fbo1.end();
    
    if(SSAOswitch) ssao.end();
    if(SSAOswitch) ssao.draw();
    
    ofSetColor(255);
    
    ofPushMatrix();
    //fbo1.draw(0, 0);
    ofPopMatrix();
    
    ofSetColor(255);
    glDisable(GL_DEPTH_TEST);
    if(AlphaBlendSwitch) ofDisableAlphaBlending();//must be disabled for gui to draw correctly
    ofDisableLighting(); //must be disabled for gui to draw correctly
    ofEnableArbTex();
    gui.draw();
    

 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}