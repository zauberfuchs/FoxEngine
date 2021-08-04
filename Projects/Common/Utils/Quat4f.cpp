
#include "Quat4f.h"
#include "Matrix4f.h"


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

namespace CG221 {

	Quat4f * Quat4f::create()
	{
		return new Quat4f();
	}

	Quat4f * Quat4f::create(const CG221::Quat4f& q)
	{
		return new Quat4f(q);
	}

	Quat4f * Quat4f::create(const float w, const float x, const float y, const float z)
	{
		return new Quat4f(w, x, y, z);
	}

	Quat4f * Quat4f::create(const float w, const CG221::Vector3f v)
	{
		return new Quat4f(w, v);
	}

	Quat4f * Quat4f::create(const CG221::Vector3f &axis, float angle)
	{
		return new Quat4f(axis, angle);
	}

	void Quat4f::destroy(Quat4f * quat)
	{
		delete quat;
		quat = NULL;
	}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Quat4f::~Quat4f()
{

}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

void Quat4f::rotate(CG221::Vector3f *v)
{

	/*Vector3 vn(vec);
	vn.normalise();

	Quaternion vecQuat, resQuat;
	vecQuat.x = vn.x;
	vecQuat.y = vn.y;
	vecQuat.z = vn.z;
	vecQuat.w = 0.0f;

	resQuat = vecQuat * getConjugate();
	resQuat = *this * resQuat;

	return (Vector3(resQuat.x, resQuat.y, resQuat.z));*/


	//// nVidia SDK implementation
	//Vector3f qvec(x, y, z);
	//Vector3f uv(qvec.cross(*v));
	//Vector3f uuv(qvec.cross(uv));
	//uv  *= (2.0f * w);
	//uuv *= 2.0f;
	//Vector3f vtmp = uv + uuv;
	//*v = *v + vtmp;

	CG221::Quat4f qtmp;

	qtmp.w = (-(x * x) - (y * y) - (z * z));
	qtmp.x = ( (w * x) + (y * z) - (z * y));
	qtmp.y = ( (w * y) - (x * z) + (z * x));
	qtmp.z = ( (w * z) + (x * y) - (y * x));

	CG221::Vector3f vo;
	v->x = ((qtmp.z * v->y) - (qtmp.w * v->x) - (qtmp.y * v->z));
	v->y = ((qtmp.x * v->z) - (qtmp.w * v->y) - (qtmp.z * v->x));
	v->z = ((qtmp.y * v->x) - (qtmp.w * v->z) - (qtmp.x * v->y));

	/*v->x = vo.x;
	v->y = vo.y;
	v->z = vo.z;*/
}


// Convert a quaternion (q) to a 4x4 matrix (m)
void Quat4f::toMatrix(const CG221::Quat4f &q, CG221::Matrix4f &m)
{
	/*
	If q is guaranteed to be a unit quaternion, s will always
	be 1.  In that case, this calculation can be optimized out.
	*/
	double norm = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
	double s = (norm > 0) ? 2 / norm : 0;

	/*
	Precalculate coordinate products
	*/
	double xx = q.x * q.x * s;
	double yy = q.y * q.y * s;
	double zz = q.z * q.z * s;
	double xy = q.x * q.y * s;
	double xz = q.x * q.z * s;
	double yz = q.y * q.z * s;
	double wx = q.w * q.x * s;
	double wy = q.w * q.y * s;
	double wz = q.w * q.z * s;

	/*
	Calculate 3x3 matrix from orthonormal basis
	*/

	/*
	x axis
	*/
	m.col[0].x = (float) (1.0 - (yy + zz));
	m.col[0].y = (float) (xy + wz);
	m.col[0].z = (float) (xz - wy);

	/*
	y axis
	*/
	m.col[1].x = (float) (xy - wz);
	m.col[1].y = (float) (1.0 - (xx + zz));
	m.col[1].z = (float) (yz + wx);

	/*
	z axis
	*/
	m.col[2].x = (float) (xz + wy);
	m.col[2].y = (float) (yz - wx);
	m.col[2].z = (float) (1.0 - (xx + yy));

	/*
	4th row and column of 4x4 matrix
	Translation and scale are not stored in quaternions, so these
	values are set to default (no scale, no translation).
	For systems where m comes pre-loaded with scale and translation
	factors, this code can be excluded.
	*/
	m.col[0].w = m.col[1].w = m.col[2].w = m.col[3].x = m.col[3].y = m.col[3].z = 0.0;
	m.col[3].w = 1.0;

}

// Convert a quaternion (q) to a 4x4 matrix (m)
CG221::Matrix4f * Quat4f::getMatrix()
{
	CG221::Matrix4f *m = new CG221::Matrix4f();
	m->identity();

	getMatrix(*m);

	return m;
}

// Convert a quaternion (q) to a 4x4 matrix (m)
void Quat4f::getMatrix(CG221::Matrix4f &m)
{
	/*
	If q is guaranteed to be a unit quaternion, s will always
	be 1.  In that case, this calculation can be optimized out.
	*/
	double norm = x * x + y * y + z * z + w * w;
	double s = (norm > 0) ? 2 / norm : 0;

	/*
	Precalculate coordinate products
	*/
	double xx = x * x * s;
	double yy = y * y * s;
	double zz = z * z * s;
	double xy = x * y * s;
	double xz = x * z * s;
	double yz = y * z * s;
	double wx = w * x * s;
	double wy = w * y * s;
	double wz = w * z * s;

	/*
	Calculate 3x3 matrix from orthonormal basis
	*/

	/*
	x axis
	*/
	m.col[0].x = (float) (1.0 - (yy + zz));
	m.col[0].y = (float) (xy + wz);
	m.col[0].z = (float) (xz - wy);

	/*
	y axis
	*/
	m.col[1].x = (float) (xy - wz);
	m.col[1].y = (float) (1.0 - (xx + zz));
	m.col[1].z = (float) (yz + wx);

	/*
	z axis
	*/
	m.col[2].x = (float) (xz + wy);
	m.col[2].y = (float) (yz - wx);
	m.col[2].z = (float) (1.0 - (xx + yy));

	/*
	4th row and column of 4x4 matrix
	Translation and scale are not stored in quaternions, so these
	values are set to default (no scale, no translation).
	For systems where m comes pre-loaded with scale and translation
	factors, this code can be excluded.
	*/
	m.col[0].w = m.col[1].w = m.col[2].w = m.col[3].x = m.col[3].y = m.col[3].z = 0.0;
	m.col[3].w = 1.0;
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

} // namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
