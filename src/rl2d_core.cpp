#include <cmath>
#include <tuple>
#include "rl2d_core.h"

Vec2d::Vec2d()
	: pos{ 0.0f, 0.0f } {}

Vec2d::Vec2d(float x, float y) 
	: pos{x, y} {}

Vec2d Vec2d::copy() {
	return Vec2d(pos.x, pos.y);
}
void Vec2d::set(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void Vec2d::mult(float n) {
	pos.x = pos.x * n;
	pos.y = pos.y * n;
}

void Vec2d::div(float n) {
	pos.x = pos.x / n;
	pos.y = pos.y / n;
}

void Vec2d::add(Vec2d v) {
	pos.x = pos.x + v.pos.x;
	pos.y = pos.y + v.pos.y;
}

void Vec2d::sub(Vec2d v) {
	pos.x = pos.x - v.pos.x;
	pos.y = pos.y - v.pos.y;
}

float Vec2d::dot(Vec2d v) {
	return pos.x * v.pos.x + pos.y * v.pos.y;
}

float Vec2d::cross(Vec2d v) {
	return pos.x * v.pos.y - pos.y * v.pos.x;
}

float Vec2d::magsq() {
	return pos.x * pos.x + pos.y * pos.y;
}

float Vec2d::mag() {
	return sqrt(magsq());
}

void Vec2d::normalize() {
	float len = mag();
	if (len > 0) div(len);
}

void Vec2d::setmag(float magnitude) {
	normalize();
	mult(magnitude);
}

void Vec2d::limit(float max) {
	if (mag() > max) {
		setmag(max);
	}
}

float Vec2d::distance(Vec2d v) {
	Vec2d vdist = copy();
	vdist.sub(v);
	return vdist.mag();
}

Vec2d Vec2d::perp() {
	return Vec2d(-pos.y, pos.x);
}

void Vec2d::rotate(Vec2d base, float n) {
	Vec2d direction = copy();
	direction.sub(base);
	float x = direction.pos.x * cosf(n) - direction.pos.y * sinf(n);
	float y = direction.pos.x * sinf(n) + direction.pos.y * cosf(n);
	pos.x = x + base.pos.x;
	pos.y = y + base.pos.y;
}

Vec2d addVec(Vec2d v1, Vec2d v2) {
	return Vec2d(v1.pos.x + v2.pos.x, v1.pos.y + v2.pos.y);
}

Vec2d subVec(Vec2d v1, Vec2d v2) {
	return Vec2d(v1.pos.x - v2.pos.x, v1.pos.y - v2.pos.y);
}

Vec2d multVec(Vec2d v, float n) {
	Vec2d vmult = v.copy();
	vmult.mult(n);
	return vmult;
}

void DrawArrow(Vec2d v_base, Vec2d v_target, Color c) {
	//Vec2d v_heading = subVec(v_target, v_base);
	DrawLineEx(v_base.pos, v_target.pos, 4, c);
}

//intersection of line a(start_a, end_a) and line_b(start_b, end_b)
std::tuple<float, Vec2d> intersect(Vec2d start_a, Vec2d end_a, Vec2d start_b, Vec2d end_b) {
	Vec2d a = subVec(end_a, start_a);
	Vec2d b = subVec(end_b, start_b);
	float cross1 = a.cross(b);
	float cross2 = b.cross(a);
	if (cross1 != 0) {
		float s = subVec(start_b, start_a).cross(b) / cross1;
		float u = subVec(start_a, start_b).cross(a) / cross2;
		if (s > 0 && s < 1 && u > 0 && u < 1) {
			return std::tuple<float, Vec2d>(s, addVec(start_a, multVec(a, s)));
		}
	}
	return std::tuple<float, Vec2d>(0.0f, Vec2d(0, 0));
}

// Mindistance between point p and line a(start_a, end_a)
float minDist(Vec2d p, Vec2d start_a, Vec2d end_a) {
  float dist = -1.0;

  //Vektor start_a to end_a (line_a)
  Vec2d line_a = subVec(end_a, start_a);
  //Vektor imaginary line start_a to p
  Vec2d start_a_to_p = subVec(p, start_a);
  //Magnitude of line_a
  float magnitude = line_a.mag();

  //Scalarprojecton from line (start_a to p) on line_a
  line_a.normalize();
  float sp = line_a.dot(start_a_to_p);

  //Scalarprojection in magnitude of line a0a1?
  if (sp > 0 && sp <= magnitude) {
    line_a.mult(sp);
    dist = subVec(start_a_to_p, line_a).mag();
  }
  return dist;
}


Matrix3x1 vecToMatrix3x1(Vec2d point) {

	return { {point.pos.x, point.pos.y, 1} };
}

Vec2d matrix3x1ToVec(Matrix3x1 matrix) {

	return Vec2d(matrix.index[0], matrix.index[1]);
}

Matrix3x1 matmul3x1(Matrix3x3 a, Matrix3x1 b) {
	Matrix3x1 result = { {0, 0, 0} };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.index[i] += a.index[i][j] * b.index[j];
		}
	}
	return result;
}

Matrix3x1 rotate(Vec2d point, Vec2d center, float angel) {

	Matrix3x1 matrix_point = vecToMatrix3x1(point);
	Matrix3x1 matrix_center = vecToMatrix3x1(center);

	Matrix3x3 m_rotate = {{
		{cosf(angel), -sinf(angel), 0}, 
		{sinf(angel), cosf(angel), 0}, 
		{0, 0, 1}
		}};

	Matrix3x3 m_transform_center = {{
		{1, 0, -matrix_center.index[0]},
        {0, 1, -matrix_center.index[1]},
    	{0, 0, 1}
	}};

	Matrix3x3 m_transform_center_back = {{
		{1, 0, matrix_center.index[0]},
        {0, 1, matrix_center.index[1]},
    	{0, 0, 1}
	}};
		
	Matrix3x1 matrix_p_transformed = matmul3x1(m_transform_center, matrix_point);
    Matrix3x1 matrix_p_transformed_rotated = matmul3x1(m_rotate, matrix_p_transformed);

	return matmul3x1(m_transform_center_back, matrix_p_transformed_rotated);
}