#include "util.hpp"

mat4 Maths::createTransformationMatrix(vec3 translation,
									   float rx,
								       float ry,
									   float rz,
									   float sz)
{
	mat4 matrix = mat4();
	matrix = translate(matrix, translation);
	matrix = rotate(matrix, radians(rx), vec3(1, 0, 0));
	matrix = rotate(matrix, radians(ry), vec3(0, 1, 0));
	matrix = rotate(matrix, radians(rz), vec3(0, 0, 1));
	matrix = scale(matrix, vec3(sz, sz, sz));

	return matrix;
}
