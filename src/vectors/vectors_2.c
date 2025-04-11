/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:04:17 by tday              #+#    #+#             */
/*   Updated: 2025/04/11 22:16:14 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Calculates and returns the dot product of two vectors, which is a scalar
	representing the magnitude of their projection onto each other.
	The scalar value (float just representing magnitude not direction) result of
	the dot product tells us how much of vector b aligns with vector a.

	Inputs
	[t_Vector3] a: The first vector.
	[t_Vector3] b: The second vector.

	Outputs
	[float] Returns a scalar value representing the dot product of the two input
		vectors.
	
	Explanation
	The dot product is calculated by multiplying corresponding components and
	summing the results: a.x * b.x + a.y * b.y + a.z * b.z

	This operation has several key properties useful in ray tracing:
	- The result is positive when vectors point in similar directions
	- The result is negative when vectors point in opposite directions
	- The result is zero when vectors are perpendicular
	- The magnitude equals |a| * |b| * cos(θ), where θ is the angle between
		vectors

	Common uses include:
	- Testing if vectors are facing same/opposite directions (for lighting)
	- Finding angles between vectors (like light rays and surface normals)
	- Calculating projections of one vector onto another
	- Computing distances and intersection points
*/
float	vect_dot(t_Vector3 a, t_Vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
	Summary
	Multiplies a vector by a scalar, scaling each of its components by the given
	scalar value.

	Inputs
	[t_Vector3] v: The vector to be scaled.
	[float] scalar: The scalar value to multiply the vector by.

	Outputs
	[t_Vector3] Returns a vector whose components have been scaled by the scalar
		value.

	Explanation
	Scalar multiplication scales a vector's magnitude while preserving its
	direction (or reversing it for negative scalars). Each component is
	multiplied by the scalar:

	Common uses in ray tracing include:
	- Scaling vectors to a specific length
	- Moving along a ray direction (origin + direction * distance)
	- Adjusting vector magnitudes (like scaling normal vectors)
	- Applying intensity factors to colors or light vectors
*/
t_Vector3	vect_multiply_scalar(t_Vector3 v, float scalar)
{
	t_Vector3	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

/*
	Summary
	Calculates and returns the Euclidean distance between two vectors in 3D
	space.

	Inputs
	[t_Vector3] a: The first vector (point).
	[t_Vector3] b: The second vector (point).

	Outputs
	[float] Returns the distance between the two input vectors.

	Explanation
	The distance is calculated using the Pythagorean theorem in 3D space:
	1. Find the vector between the points using subtraction (a - b)
	2. Calculate the length of this vector using the dot product with itself
	   and taking the square root: √((ax-bx)² + (ay-by)² + (az-bz)²)

	Common uses in ray tracing include:
	- Determining hit distances for ray intersections
	- Calculating light attenuation based on distance
	- Finding the closest object to a point
	- Computing shadow ray lengths
*/
float	vect_distance(t_Vector3 a, t_Vector3 b)
{
	t_Vector3	difference;
	float		distance;

	difference = vect_subtract(a, b);
	distance = sqrt(vect_dot(difference, difference));
	return (distance);
}

/*
	Summary
	Calculates the reflection vector of an incident vector about a normal vector
	using the formula R = I - 2(I·N)N, where I is the incident vector and N is
	the normal vector.

	Inputs
	[t_Vector3] incident: The incoming vector to be reflected.
	[t_Vector3] normal: The normal vector of the surface (should be normalized).

	Outputs
	[t_Vector3] Returns the reflected vector.

	Explanation
	The reflection vector is calculated using the formula R = I - 2(I·N)N, where:
	- I is the incident vector
	- N is the normal vector
	- I·N is the dot product of I and N
	
	This formula works because:
	1. The dot product (I·N) gives the projection of I onto N
	2. Multiplying by 2N and subtracting from I creates the reflection
	3. The angle between I and N equals the angle between R and N

	Common uses in ray tracing include:
	- Computing reflections for mirrors and shiny surfaces
	- Calculating specular highlights in lighting models
	- Implementing recursive ray tracing for multiple bounces
*/
t_Vector3	vect_reflect(t_Vector3 incident, t_Vector3 normal)
{
	float		dot_product;
	t_Vector3	reflection;

	dot_product = vect_dot(incident, normal);
	reflection.x = incident.x - 2 * dot_product * normal.x;
	reflection.y = incident.y - 2 * dot_product * normal.y;
	reflection.z = incident.z - 2 * dot_product * normal.z;
	return (reflection);
}
