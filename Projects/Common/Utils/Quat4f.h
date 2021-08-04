/*
 *
 * Copyright (C) <2014> <w-hs - cglab projects>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUAT4F_H__F1B3C959_7040_4622_8798_4243FDA11191__INCLUDED_)
#define AFX_QUAT4F_H__F1B3C959_7040_4622_8798_4243FDA11191__INCLUDED_

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#include "CompilerPre.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

/* Copyright (C) Dante Treglia II and Mark A. DeLoura, 2000.
* All rights reserved worldwide.
*
* This software is provided "as is" without express or implied
* warranties. You may freely copy and compile this source into
* applications you distribute provided that the copyright text
* below is included in the resulting source code, for example:
* "Portions Copyright (C) Dante Treglia II and Mark A. DeLoura, 2000"
*/
//==========================================================
// C++ Matrix Library
// Version: 2.6
// Date: May 19, 2000
// Authors: Dante Treglia II and Mark A. DeLoura
// Thanks to: Miguel Gomez, Stan Melax, Pete Isensee,
//   Gabor Nagy, Scott Bilas, James Boer, Eric Lengyel
//==========================================================

#include <cmath>
#include <cassert>

#include "Vector3f.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

class CG221_API Quat4f // : public _SQuaternion
{
public:
	float w;
	float x, y, z;	

	//assign
	const CG221::Quat4f& operator = ( const CG221::Quat4f& q )
	{
		w = q.w;
		x = q.x;
		y = q.y;
		z = q.z;

		return *this;
	}

	//compare
	int operator == ( const CG221::Quat4f& q ) const
	{
		return (q.w==w && q.x==x && q.y==y && q.z==z);
	}

	int operator != ( const CG221::Quat4f& q ) const
	{
		return (q.w!=w || q.x!=x || q.y!=y || q.z!=z);
	}

	//negate
	CG221::Quat4f operator - () const
	{
		return Quat4f( -w, -x, -y, -z );
	}

	void operator += ( const CG221::Quat4f& q )
	{
		w += q.w;
		x += q.x;
		y += q.y;
		z += q.z;
	}

	void operator -= ( const CG221::Quat4f& q )
	{
		w -= q.w;
		x -= q.x;
		y -= q.y;
		z -= q.z;
	}

	void operator *= ( const float s )
	{
		w *= s;
		x *= s;
		y *= s;
		z *= s;
	}

	void operator /= ( float s )
	{
		s = 1/s;
		w *= s;
		x *= s;
		y *= s;
		z *= s;
	}

	//add
	const CG221::Quat4f operator + ( const CG221::Quat4f& q ) const
	{
		return Quat4f( w + q.w, x + q.x, y + q.y, z + q.z );
	}

	//subtract
	const CG221::Quat4f operator - ( const CG221::Quat4f& q ) const
	{
		return Quat4f( w - q.w, x - q.x, y - q.y, z - q.z );
	}

	//multiply
	const CG221::Quat4f operator * ( const float s ) const
	{
		return Quat4f( w * s, x * s, y * s, z * s );
	}

	//multiply
	const CG221::Quat4f operator * ( const Quat4f& q) const
	{
		CG221::Vector3f vec;
		vec.x = x;
		vec.y = y;
		vec.z = z;
		CG221::Vector3f vecQ;
		vecQ.x = q.x;
		vecQ.y = q.y;
		vecQ.z = q.z;
		CG221::Vector3f vecNew;
		vecNew = vec.cross(vec, vecQ) + vecQ * w + vec * q.w;
		CG221::Quat4f qResult = CG221::Quat4f( w * q.w - vec.DotProduct(vecQ), vecNew);
		if (qResult.length() > 0) {
			qResult.normalize();
		}
		return qResult;
	}

	//// Multiplying a quaternion q with a vector v applies the q-rotation to v
	//Vector3f Quat4f::operator* (const Vector3f &vec) const
	//{
	//	Vector3f vn(vec);
	//	vn.normalize();

	//	Quat4f vecQuat;
	//	Quat4f resQuat;

	//	vecQuat.x = vn.x;
	//	vecQuat.y = vn.y;
	//	vecQuat.z = vn.z;
	//	vecQuat.w = 0.0f;

	//	resQuat = vecQuat * this->getConjugate();
	//	resQuat = *this * resQuat;

	//	return (Vector3f(resQuat.x, resQuat.y, resQuat.z));
	//}

	//pre - multiply
	friend inline const CG221::Quat4f operator * ( const float s, const CG221::Quat4f& v )
	{
		return v * s;
	}

	//divide
	const CG221::Quat4f operator / ( float s ) const
	{
		s = 1/s;
		return CG221::Quat4f( w*s, x*s, y*s, z*s );
	}

	//dot product
		float dot( const Quat4f& q ) const
	{
		return (float) (w*q.w + x*q.x + y*q.y + z*q.z);
	}

	//magnitude
		float length() const
	{
		return( (float)sqrt( (double)(w*w + x*x + y*y + z*z) ) );
	}

	//unit vector
	const CG221::Quat4f unit() const
	{
		return (*this) / length();
	}

	//make this a unit vector
	void normalize()
	{
		(*this) /= length();
	}

	//equal within an error 'w'
	bool nearlyEquals( const CG221::Quat4f& q, const float e ) const
	{
		return fabs(w-q.w)<e && fabs(x-q.x)<e && fabs(y-q.y)<e && fabs(z-q.z)<e;
	}

	/* old
	//spherically linearly interpolate between two unit quaternions, a and b
	inline const Quat4f Slerp( const Quat4f& a, const Quat4f& b, const float u )
	{
		const float theta = acosf( a.dot( b ) );//angle between two unit quaternions
		const float t = 1 / sinf( theta );

		return  t * (a * sinf( (1-u)*theta ) + b * sinf( u*theta ) );
	}
	*/

	//spherically linearly interpolate between two unit quaternions, a and b
	inline const CG221::Quat4f Slerp( const CG221::Quat4f& a, const CG221::Quat4f& b, const float u )
	{

		const float fDot = a.dot( b );
		const float theta = acosf( fDot );//angle between two unit quaternions
		if (theta < 0.001) {
			return a;
		}
		else {
			const float t = 1 / sinf( theta );
			float fCoeff0 = (float)sinf((float)((1.0-u)*theta))*t;
			float fCoeff1 = (float)sinf((float)(u*theta))*t;
			// Do we need to invert rotation?
			if (fDot < 0.0f)
			{
				fCoeff0 = -fCoeff0;
				// taking the complement requires renormalisation
				Quat4f q(fCoeff0 * a + fCoeff1 * b);
				q.normalize();
				return q;
			}
			else {
				return fCoeff0 * a + fCoeff1 * b;
			}

			//return  t * (a * sinf( (1-u)*theta ) + b * sinf( u*theta ) );
		}

	}

	// convert quaternion to axis angle
	void quatToAA(CG221::Vector3f *pAxis, float *pAngle)
	{
		//const float PI = 3.1415926f;
		CG221::Quat4f q = *this;
		q.normalize();
		*pAngle = (float)(2.0 * std::acos(q.w));

		float fS = (float)(std::sin((*pAngle) / 2.0));
		if ( fS != 0 ) {
			(*pAxis).x = q.x / fS;
			(*pAxis).y = q.y / fS;
			(*pAxis).z = q.z / fS;
		} else {
			*pAxis = CG221::Vector3f(0, 0, 0);
		}

		// convert from radians to degrees
		*pAngle = (float)(*pAngle * 180.0 / CG221::PEE);
	}

	// convert aa to quat
	void fromAA(CG221::Vector3f axis, float a)
	{
		float a2 = deg2Rad(a/2);
		w = std::cos(a2);
		x = std::sin(a2) * axis.x;
		y = std::sin(a2) * axis.y;
		z = std::sin(a2) * axis.z;
		normalize();
	}

	//// Convert from Euler Angles
	//void fromEuler(float pitch, float yaw, float roll)
	//{
	//	// Basically we create 3 Quaternions, one for pitch, one for yaw, one for roll
	//	// and multiply those together.
	//	// the calculation below does the same, just shorter

	//	float p = deg2Rad(pitch);
	//	float y = deg2Rad(yaw);
	//	float r = deg2Rad(roll);

	//	float sinp = sin(p);
	//	float siny = sin(y);
	//	float sinr = sin(r);
	//	float cosp = cos(p);
	//	float cosy = cos(y);
	//	float cosr = cos(r);

	//	this->x = sinr * cosp * cosy - cosr * sinp * siny;
	//	this->y = cosr * sinp * cosy + sinr * cosp * siny;
	//	this->z = cosr * cosp * siny - sinr * sinp * cosy;
	//	this->w = cosr * cosp * cosy + sinr * sinp * siny;

	//	normalise();
	//}

	// We need to get the inverse of a quaternion to properly apply a quaternion-rotation to a vector
	// The conjugate of a quaternion is the same as the inverse, as long as the quaternion is unit-length
	CG221::Quat4f getConjugate()
	{
		return CG221::Quat4f(-x, -y, -z, w);
	}

	// Convert a quaternion (q) to a 4x4 matrix (m)
	static void toMatrix(const CG221::Quat4f &q, CG221::Matrix4f &m);

	CG221::Matrix4f * getMatrix();
	void getMatrix(CG221::Matrix4f &m);

	void rotate(CG221::Vector3f *v);

	//////////////////////////////////////////////////////////////////////

	Quat4f() : w(1), x(0), y(0), z(0) {}
	Quat4f(const CG221::Quat4f& q) {
		this->w = q.w;
		this->x = q.x;
		this->y = q.y;
		this->z = q.z;
	}
	Quat4f( const float w, const float x, const float y, const float z ) : w(w), x(x), y(y), z(z) {}
	Quat4f( const float w, const CG221::Vector3f v) {
		this->w = w;
		x = v.x;
		y = v.y;
		z = v.z;
	}
	/// construct quaternion from angle-axis
	Quat4f(const CG221::Vector3f &axis, float angle)
	{
		const float a = angle * 0.5f;
		const float s = (float) sin(a);
		const float c = (float) cos(a);
		w = c;
		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
	}
	virtual ~Quat4f();

	//////////////////////////////////////////////////////////////////////

	static Quat4f * create();
	static Quat4f * create(const CG221::Quat4f& q);
	static Quat4f * create(const float w, const float x, const float y, const float z);
	static Quat4f * create(const float w, const CG221::Vector3f v);	
	static Quat4f * create(const CG221::Vector3f &axis, float angle);
	static void destroy(Quat4f * quat);

	//////////////////////////////////////////////////////////////////////

};

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

} // namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_QUAT4F_H__F1B3C959_7040_4622_8798_4243FDA11191__INCLUDED_)

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
