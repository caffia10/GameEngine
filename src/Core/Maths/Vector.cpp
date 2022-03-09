#include "Vector.h"

f32 GetAngle(const Vector3& vectorA, const Vector3& vectorB)
{
	f32 firstStepResult = GetDotProduct(vectorA, vectorB) / GetMagnitude(vectorA) * GetMagnitude(vectorB);
	return acosf(firstStepResult);
}

Vector3 GetProjection(const Vector3& vectorA, const Vector3& vectorB)
{
	float scalar = GetDotProduct(vectorA, vectorB) / (Square(GetMagnitude(vectorB)));
	return  vectorA - (vectorB * scalar);
}


// -------------------------- Vector 2 ----------------------------------

f32 GetAngle(const Vector2& vectorA, const Vector2& vectorB)
{
	f32 firstStepResult = GetDotProduct(vectorA, vectorB) / GetMagnitude(vectorA) * GetMagnitude(vectorB);
	return acosf(firstStepResult);
}

Vector2 GetCrossProduct(const Vector2& vectorA, const Vector2& vectorB)
{
	const Vector3 vectorAuxA = { vectorA.x, vectorA.y, 0.0f };
	const Vector3 vectorAuxB = { vectorB.x, vectorB.y, 0.0f };

	const Vector3 result = GetCrossProduct(vectorAuxA, vectorAuxB);

	return { result.x, result.y };
}

Vector2 GetProjection(const Vector2& vectorA, const Vector2& vectorB)
{
	float scalar = GetDotProduct(vectorA, vectorB) / (Square(GetMagnitude(vectorB)));
	return  vectorA - (vectorB * scalar);
}

Vector2 GetNormalVector(const Vector2& vector)
{
	const f32 magnitude = GetMagnitude(vector);

	return { vector.x / magnitude, vector.y / magnitude };
}
