#include <QtGui>
#include "Renderable.h"

class particle {
    protected:
        Renderable* modelToRender_;
        QMatrix4x4 particleTransform_;
        QVector3D velocity_;
        float secondsToLive_;

    public:
        Particle(Renderable* model, const QVector3D& velocity, float lifespan);

        void updateAndDraw(unsigned int msSinceLastFrame);
        bool isDead() const {
            return secondsToLive_ < 0.0;
        }
}