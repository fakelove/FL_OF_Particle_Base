#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include "ofxGui.h"
#include "ofxSSAO.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        
    ofEasyCam camera;


    
    ofImage scratch;
    
    ofLight pointLight;
    ofMaterial material;
    
    ofFbo fbo1;
    
    //float maxParticleSpeed, maxParticleAge, maxParticleSize;
    
    ofxPanel gui;
    ofxIntSlider maxParticleSpeed;
    ofxIntSlider maxParticleAge;
	ofxIntSlider maxParticleSize;
    ofxToggle addBlend;
    ofxFloatSlider gravity, wind, attraction;
    ofxIntSlider fadeAmt;
    ofxToggle pointLightSwitch;
    ofxToggle AlphaBlendSwitch;
    ofxToggle cameraSwitch;
    ofxToggle trailEnable;
    ofxIntSlider particleType;
    ofxFloatSlider turbSpeedX, turbSpeedY, turbAmtX, turbAmtY;
    
    float colorCount;
    
    ParticleEmitter emitter;
    
};
