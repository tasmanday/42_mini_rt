/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:46:07 by tday              #+#    #+#             */
/*   Updated: 2024/12/31 17:33:00 by tday             ###   ########.fr       */
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
	[t_Vector3] Returns a t_Vector3 structure initialized with the given x, y, and z
	components.
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
	SUMMARY:
		Normalizes a 3D vector, scaling it to unit length.

	INPUTS:
		t_Vector3 v: The vector to be normalized, containing x, y, and z components.

	OUTPUTS:
		t_Vector3: The normalized vector with unit length.
*/
t_Vector3	vect_normalise(t_Vector3 v)
{
	float	len;
	t_Vector3	normalised_vector;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0) // check for zero length
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
	[t_Vector3] Returns a vector representing the difference between the two input vectors.
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
	Calculates and returns the cross product of two vectors, which is a vector perpendicular
	to both input vectors and represents their area in 3D space.

	Inputs
	[t_Vector3] a: The first vector.
	[t_Vector3] b: The second vector.

	Outputs
	[t_Vector3] Returns a vector representing the cross product of the two input vectors.
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

	The scalar value (float just representing magnitude not direction) result of the dot product tells us how much of vector b aligns with vector a.

	Inputs
	[t_Vector3] a: The first vector.
	[t_Vector3] b: The second vector.

	Outputs
	[float] Returns a scalar value representing the dot product of the two input vectors.
*/
float	vect_dot(t_Vector3 a, t_Vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
	Summary
	Multiplies a vector by a scalar, scaling each of its components by the given scalar value.

	Inputs
	[t_Vector3] v: The vector to be scaled.
	[float] scalar: The scalar value to multiply the vector by.

	Outputs
	[t_Vector3] Returns a vector whose components have been scaled by the scalar value.
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
	Calculates and returns the Euclidean distance between two vectors in 3D space.

	Inputs
	[t_Vector3] a: The first vector (point).
	[t_Vector3] b: The second vector (point).

	Outputs
	[float] Returns the distance between the two input vectors.
*/
float	vect_distance(t_Vector3 a, t_Vector3 b)
{
	t_Vector3	difference;
	float		distance;

	difference = vect_subtract(a, b);
	distance = sqrt(vect_dot(difference, difference));
	return (distance);
}
