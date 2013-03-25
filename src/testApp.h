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
        
    ofxSSAO ssao;
    void loadShader();
    ofEasyCam camera;

    ParticleEmitter ParticleEmitter;
    
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
    ofxFloatSlider MaxThresh, MinThresh ;
    ofxFloatSlider gravity, wind, attraction;
    ofxIntSlider exponent, ssaoRadius, bumpSlider;
    ofxToggle SSAOswitch;
    ofxToggle pointLightSwitch;
    ofxToggle AlphaBlendSwitch;
    ofxToggle cameraSwitch;
    
    float colorCount;
    
    
};
