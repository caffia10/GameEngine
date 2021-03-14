#ifndef POINT_MASS_H
#define POINT_MASS_H

#include "PointMass.h"

void Integrate(PointMass *pointMass, f32 duration)
{
    ASSERT(duration > 0.0);
    /* 
    Update linear position 
        =>  position = p + v * t = position + (velocity * duration)
    */
    pointMass->position += pointMass->velocity * duration;

    /*
     Velocity Update 
        =>  Vu = v * d^t + a * t = velocity * (damping^duration) + acceleration * duration
     
     Acceleration
         => a = 1 / m * mg = inverseMass * force
    
     Velocity
        => v = p / t =  position / duration
    */
    {
        // Work out the acceleration from the force
        v3 resultingAcceleration = pointMass->acceleration + (pointMass->forceAccumlated * pointMass->inverseMass);

        // Update linear velocity from the acceleration.
        pointMass->velocity += resultingAcceleration * duration;
    }

    // Impose drag
    pointMass->velocity *= powf(pointMass->damping, duration);

    // Clear the forces
    pointMass->forceAccumlated = {0, 0, 0};
}



#endif // POINT_MASS_H