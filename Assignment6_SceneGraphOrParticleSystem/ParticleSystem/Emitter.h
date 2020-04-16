#include <QtGui>
#include Renderable.h
#include Particle.h

class Emitter {
    protected:
        QVector<Particle> particles_;
        QVector3D position_;
        QVector3D orientation_;
        unsigned int particleEmitRate_;
        Renderable* particleModel_;

    public:
        Emitter(const QVector3D& position, const QVector3D& orientation, unsigned int pps, Renderable* particleModel);

        void update(unsigned int msSinceLastFrame);
        void emitParticle();
};