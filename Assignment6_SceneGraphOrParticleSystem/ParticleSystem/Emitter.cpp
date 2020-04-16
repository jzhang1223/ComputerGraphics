#include "Emitter.h"

Emitter::Emitter(const QVector3D& position, const QVector3D& orientation, unsigned int pps, Renderable* particleModel) {
    particles_ = QVector();
    position_ = position;
    orientation_ = orientation;
    particleEmitRate_ = pps;
    particleModel_ = particleModel
}

void Emitter::update(unsigned int msSinceLastFrame) {
    for(int i = 0; i < particles_.size(); i++) {
        particles[i].updateAndDraw();
    }
    // Add some new particles 
    // pps * (msSinceLastFrame / 1000)
}

void Emitter::emitParticle() {
    particles_.append(new Renderable());
}