/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:46:07 by tday              #+#    #+#             */
/*   Updated: 2025/04/12 08:59:53 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
