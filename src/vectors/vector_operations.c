/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:46:07 by tday              #+#    #+#             */
/*   Updated: 2025/02/02 14:01:04 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

/*
	Summary
	Creates and returns a vector with the specified x, y, and z components.

	Inputs
	[float] x: The x component of the vector.
	[float] y: The y component of the vector.
	[float] z: The z component of the vector.

	Outputs
	[t_Vector3] Returns a t_Vector3 structure initialized with the given x, y,
		and z components.

	Explanation
	This is a constructor-like function that creates a 3D vector. In computer
	graphics, vectors are used to represent:
	- Directions (like ray directions or surface normals)
	- Positions in 3D space (like object locations or intersection points)
	- Movements or offsets
	The function provides a clean and consistent way to create new vectors
	throughout the ray tracer.
*/
t_Vector3	vector(float x, float y, float z)
{
	t_Vector3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

/*
	Summary
	Normalizes a 3D vector, scaling it to unit length.

	Inputs
	[t_Vector3] v: The vector to be normalized, containing x, y, and z
		components.

	Outputs
	t_Vector3: The normalized vector with unit length.

	Explanation
	Normalization is a crucial operation in computer graphics that converts a
	vector to unit length while preserving its direction. The process involves:
	1. Calculating the vector's length using the Pythagorean theorem in 3D:
	   length = √(x² + y² + z²)
	2. Dividing each component by this length to scale the vector
	The function includes special handling for zero-length vectors to prevent
	division by zero, returning a zero vector in this case.
	
	Normalized vectors are essential for:
	- Ray directions in ray tracing
	- Surface normals for lighting calculations
	- Direction vectors for camera and light sources
*/
t_Vector3	vect_normalise(t_Vector3 v)
{
	float		len;
	t_Vector3	normalised_vector;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0)
	{
		normalised_vector.x = 0.0;
		normalised_vector.y = 0.0;
		normalised_vector.z = 0.0;
	}
	else
	{
		normalised_vector.x = v.x / len;
		normalised_vector.y = v.y / len;
		normalised_vector.z = v.z / len;
	}
	return (normalised_vector);
}

/*
	Summary
	Calculates and returns the sum of two vectors.

	Inputs
	[t_Vector3] a: The first vector to be added.
	[t_Vector3] b: The second vector to be added.

	Outputs
	[t_Vector3] Returns a vector representing the sum of the two input vectors.
	
	Explanation
	Vector addition is a fundamental operation in 3D graphics where each
	component is added independently:
	- result.x = a.x + b.x
	- result.y = a.y + b.y
	- result.z = a.z + b.z
	
	Common uses in ray tracing include:
	- Moving points in space (point + displacement)
	- Combining multiple vectors (like adding light contributions)
	- Calculating new positions (origin + direction * distance)
*/
t_Vector3	vect_add(t_Vector3 a, t_Vector3 b)
{
	t_Vector3	vector;

	vector.x = a.x + b.x;
	vector.y = a.y + b.y;
	vector.z = a.z + b.z;
	return (vector);
}

/*
	Summary
	Calculates and returns the difference between two vectors.

	Inputs
	[t_Vector3] a: The vector to be subtracted from.
	[t_Vector3] b: The vector to subtract.

	Outputs
	[t_Vector3] Returns a vector representing the difference between the two
		input vectors.
	
	Explanation
	Vector subtraction is performed component-wise, where each component of the
	second vector is subtracted from the corresponding component of the first:
	- result.x = a.x - b.x
	- result.y = a.y - b.y
	- result.z = a.z - b.z
	
	Common uses in 3D graphics include:
	- Finding direction vectors between two points (target - origin)
	- Calculating relative positions (point - reference_point)
	- Computing displacement vectors (end_position - start_position)
*/
t_Vector3	vect_subtract(t_Vector3 a, t_Vector3 b)
{
	t_Vector3	vector;

	vector.x = a.x - b.x;
	vector.y = a.y - b.y;
	vector.z = a.z - b.z;
	return (vector);
}

/*
	Summary
	Calculates and returns the cross product of two vectors, which is a vector
	perpendicular to both input vectors and represents their area in 3D space.

	Inputs
	[t_Vector3] a: The first vector.
	[t_Vector3] b: The second vector.

	Outputs
	[t_Vector3] Returns a vector representing the cross product of the two input
		vectors.

	Explanation
	Produces a new vector perpendicular to both input vectors. This makes it
	particularly useful in ray tracing for:
	- Generating camera coordinate systems (creating a right vector from up and
	  forward vectors)
	- finding the normal vector of a plane
	- finding vectors that are perpendicular to known vectors
*/
t_Vector3	vect_cross(t_Vector3 a, t_Vector3 b)
{
	t_Vector3	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
}

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
	- The magnitude equals |a| * |b| * cos(θ), where θ is the angle between vectors

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
t_Vector3 vect_reflect(t_Vector3 incident, t_Vector3 normal)
{
	float dot_product = vect_dot(incident, normal);
	t_Vector3 reflection;

	reflection.x = incident.x - 2 * dot_product * normal.x;
	reflection.y = incident.y - 2 * dot_product * normal.y;
	reflection.z = incident.z - 2 * dot_product * normal.z;

	return (reflection);
}
