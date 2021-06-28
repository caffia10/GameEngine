#include "ForceGenerator.h"

void UpdateGravityForce(PointMass *pointMass, f32 duration, v3 gravity)
{
    // check that we do not have infinite mass.
    if (!HasFiniteMass(pointMass))
        return;

    // Apply the mass-scaled force to the point mass.
    pointMass->forceAccumlated += gravity * GetMass(pointMass);
}
// ---------------------------------------------------

void UpdateDragForce(PointMass *pointMass, f32 duration, f32 k1, f32 k2)
{
    /** drag force calc 
     * => fdrag = -Nv * (k1 * |Nv| + k2 * |Nv|^2)
     *    Nv = normalized velocity 
     */

    v3 force = pointMass->velocity;

    // Calculate the total drag coefficient.
    f32 dragCoefficient = V3Length(force);
    dragCoefficient = k1 * dragCoefficient + k2 * dragCoefficient * dragCoefficient;

    // Calculate the final force and apply it.
    V3Normalize(force);
    force *= -dragCoefficient;
    pointMass->forceAccumlated += force;
}