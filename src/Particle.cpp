//
//  Particle.cpp
//  particleEngine1
//
//  Created by Mary Scahill on 2/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Particle.h"

Particle::Particle(ofPoint origin, int _maxSpeed, int _maxSize, int _maxAge, ofColor _startColor, ofColor _endColor){

    startColor = _startColor;
    endColor = _endColor;
    currentColor = _startColor;
    
    pt.x=origin.x;
    pt.y=origin.y;
    offset.x = ofRandomf(); //this just randomizes the initial position so the "thrust" doesnt go in the same direction
    offset.y = ofRandomf();
    offset.z = ofRandomf();
    
    velocity.set(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1) );
    
    gravity.set(0, ofRandom(-1,1));
    gravity.set(0, gravity.y*(0.1*radius));
    wind.set(ofRandom(-1,1), 0);
    isDragging = false;

	radius = ofRandom(3,_maxSize);
    age = 0;
    dead = false;
    maxAge = ofRandom(0,_maxAge)+50;
    rotation.x = ofRandom(360);
    rotation.y = ofRandom(360);
    rotation.z = ofRandom(360);
    
    attractionStrength = 5; //just set negative to make it repulsion..
    
}

void Particle::update(int _particleID, ofPoint attractPoint, float _maxVelocity){

    //could use particleID to further randomize the particles, 
    
    age++; //age the particle
    
    computeFriction(); //compute friction of our moving body
    //computeAttraction(attractPoint);
    
    applyForce(computeAttraction(attractPoint));
    applyForce(wind);
    applyForce(gravity);
    applyForce(friction); //compute and accumulate all of our forces on acceleration
    
    velocity = velocity + acceleration; //change speed based on acceleration
    velocity.limit(_maxVelocity); //make sure we don't go too fast...
    
    pt = pt + velocity; //increment position
    
    
    //Edge checking
    
    int maxSpeed = _maxVelocity; //in either direction
    if (pt.x-radius<=0) {
        pt.x = 0+radius;
        velocity.x = -velocity.x;
        velocity.x = ofClamp(velocity.x, -maxSpeed, maxSpeed);
    }
    if (pt.x+radius >= ofGetWidth()) {
        pt.x = ofGetWidth()-radius; 
        velocity.x = -velocity.x;
        velocity.x = ofClamp(velocity.x, -maxSpeed, maxSpeed);
    }
    
    if (pt.y-radius<=0) {
        pt.y = 0+radius; 
        velocity.y = -velocity.y;
        velocity.y = ofClamp(velocity.y, -maxSpeed, maxSpeed);
    }
    if (pt.y+radius >= ofGetHeight()) {
        pt.y = ofGetHeight()-radius; 
        velocity.y = -velocity.y;
        velocity.y = ofClamp(velocity.y, -maxSpeed, maxSpeed);
    }
    
    acceleration.set(0, 0); //reset acceleration so it does not accumulate
    
    //color.set(255, ofMap(age, 0, maxAge, 255,0), ofMap(age, 0, maxAge, 255,0), ofMap(age, 0, maxAge, 255,0)); //this changes color over life
    
    currentColor = startColor*(1-(age/maxAge)) + endColor*(age/maxAge); //interpolate between the two colors...this seems to interpolate slower than the next line
    //currentColor = startColor.lerp(endColor, age/maxAge);
    
    if (age >= maxAge) dead = true;
    
    rotation.x = rotation.x + 5*(age/maxAge); //this set of statements makes things spin faster as they age...as age approaches max age, the value gets closer to 1, but starts close to 0
    rotation.y = rotation.y + 8*(age/maxAge);
    rotation.z = rotation.z + 3*(age/maxAge);
    
    radius = radius - 0.5*(age/maxAge); //this makes them smaller as they age
    radius = ofClamp(radius, 0, 500);
    
}

void Particle::draw(){

    
    //ofCircle( pt, radius);
    
    ofPushMatrix();
    ofTranslate(pt);
    //ofRotateX(rotation.x);
    //ofRotateY(rotation.y);
    //ofRotateZ(rotation.z);
    ofFill();
    ofSetColor(currentColor);
    //ofSetSphereResolution(15-15*((2*age)/maxAge));
    ofSphere(0,0, radius-radius*(age/maxAge));
    
    //ofRect(0,0, radius-radius


    //ofBox(0,0, radius-radius*(age/maxAge));
    //ofBox(0,0, radius-radius*0.5*(age/maxAge)); //adding in extra boxes but gl depth test will need to be disabled in the main testapp!
    //ofBox(0,0, radius-radius*0.7*(age/maxAge));
    //ofRotateY(30*ofGetElapsedTimef());
    //ofCircle( 0,0, radius);
    //ofRotateX(30*ofGetElapsedTimef());
    //ofCircle( 0,0, radius);
    ofPopMatrix();
}

ofPoint Particle::getPoint(){
    return pt;
}
void Particle::applyForce(ofVec3f force){
    acceleration = acceleration + (force/radius); //scale the force's influence depending on its size
}

void Particle::computeFriction(){
    //compute friction
    float c = 0.4; //friction amount
    friction = -velocity; //friction is the opposite of velocity
    friction = friction.normalize();
    friction = friction*c;
}

ofPoint Particle::computeAttraction(ofPoint attractor){
    ofPoint force;
    float magnitude;
    float mass = 60;
    force = attractor - pt; //attraction vector...subtract the mover from the attractor to get direction
    magnitude = force.length();
    magnitude = ofClamp(magnitude, 2,25); //arbitrary values
    force = force.normalize(); //get direction of vector
  //gravity constant...increase to get more attraction
    float strength = (attractionStrength*mass * radius)/(magnitude * magnitude);
    force = force * strength;
    return force;
}

float Particle::getMass(){
    return radius;
}

bool Particle::isInside(ofRectangle dragBox) {
    if (dragBox.inside(pt)){
        return true; 
    } else {
        return false;
    }
}

bool Particle::bIsDead(){
    return dead;
}

void Particle::setWind(float _wind){
    wind.x = _wind;
}

void Particle::setGravity(float _gravity){
    gravity.y = _gravity;
}

void Particle::setAttraction(float _attraction){
    attractionStrength = _attraction;
}

