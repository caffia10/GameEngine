
#ifndef RIGID_BODY_H 
#define RIGID_BODY_H


struct RigidBody
{
    v3 acceleration;

    v3 velocity;

    v3 position;   
};

/*
    We don't need to create methods to get speed and direction 
    because we already have "these" created by vector calculations.

    GetSpeed => V3Length(velocity)
    GetDirection =>    V3Normalize(velocity)
*/

void UpdatePosition(RigidBody &rigidBody, f32 time)
{
    rigidBody.position += rigidBody.velocity * time;
}

#endif  // RIGID_BODY_H