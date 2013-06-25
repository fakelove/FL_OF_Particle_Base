//
//  BallEmitter.h
//  particleEngine1
//
//  Created by Mary Scahill on 2/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef particleEngine1_BallEmitter_h
#define particleEngine1_BallEmitter_h

#include "ofMain.h"
#include "Particle.h"

#define ParticleSize 200

class ParticleEmitter : public ofBaseApp{
private:
    int centerX;
    int centerY;
    ofPoint origin;
    float rotation;
    ofColor startColor, endColor;
    pType type;
    
public:
    void setup(ofPoint origin, int maxSpeed, int maxSize, int maxAge, ofColor _startColor, ofColor _endColor);
    void update(float maxSpeed, int maxSize, int maxAge);
    void setForces(float _gravity, float _wind, float _attraction, ofVec2f _turbSpeed, ofVec2f _turbAmt);
    void draw(int x, int y, pType _type);
    void setOrigin(ofPoint _origin);
    void setColors(ofColor _startColor, ofColor _endColor);
    
    Particle* p[ParticleSize];
};


#endif
