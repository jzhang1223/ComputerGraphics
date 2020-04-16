#include "Particle.h"

Particle::Particle(Renderable* model, const QVector3D& velocity, float lifespan) {
    modelToRender_ = model;
    // set default particle transform...
    velocity_ = velocity;
    secondsToLive_ = lifespan;
}

void Particle::updateAndDraw(unsigned int msSinceLastFrame) {
    secondsToLive_ -= msSinceLastFrame / 1000.0;
    // Draw here
}