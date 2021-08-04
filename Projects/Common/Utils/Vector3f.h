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

#ifndef __Vector3f_H__
#define __Vector3f_H__

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#include "CompilerPre.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#include <cmath>
#include <cassert>

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

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

static const float PEE		= 3.141592653589793f;
static const float PEE_HALF	= 1.57079632679489661923f;
static const float PEE_TWO	= 6.28318530717958647692f;
static const float PEE_INV	= 0.31830988618379067154f;

static inline float deg2Rad(float a) { return a*0.01745329252f; }
static inline float rad2Deg(float a) { return a*57.29577951f; }

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

class CG221_API Vector3f;
class CG221_API Matrix4f;

CG221::Vector3f CG221_API Normalized(const CG221::Vector3f &a);
float CG221_API DotProduct(const CG221::Vector3f &a, const CG221::Vector3f &b);
void CG221_API SwapVec(CG221::Vector3f &a, CG221::Vector3f &b);
CG221::Vector3f CG221_API CrossProduct(const CG221::Vector3f &a, const CG221::Vector3f &b);
bool CG221_API NearlyEquals(const CG221::Vector3f &a, const CG221::Vector3f &b, float r);

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

class CG221_API Vector3f
{
public:
	float x, y, z;

	CG221::Vector3f& copy(const CG221::Vector3f &v) { x = v.x; y = v.y; z = v.z;  return *this; }

	CG221::Vector3f& operator=(const CG221::Vector3f& that) 
    {
	  x = that.x;
	  y = that.y;
	  z = that.z;
      return *this;
    }

	// Operators
	// Array indexing
	float &operator [] (unsigned int i) {
		assert(i<3);
		return *(&x+i);
	}

	// Array indexing
	const float &operator [] (unsigned int i) const {
		assert(i<3);
		return *(&x+i);
	}

	// Add a Vector3f to this one
	CG221::Vector3f &operator += (const CG221::Vector3f &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	// Subtract a Vector3f from this one
	CG221::Vector3f &operator -= (const CG221::Vector3f &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	// Multiply the Vector3f by a float
	CG221::Vector3f &operator *= (float f) {
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	// Divide the Vector3f by a float
	CG221::Vector3f &operator /= (float f) {
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	// Are these two Vector3f's equal?
	friend bool operator == (const CG221::Vector3f &a, const CG221::Vector3f &b) {
		return((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
	}

	// Are these two Vector3f's not equal?
	friend bool operator != (const CG221::Vector3f &a, const CG221::Vector3f &b) {
		return((a.x != b.x) || (a.y != b.y) || (a.z != b.z));
	}

	// Negate a Vector3f
	friend CG221::Vector3f operator - (const CG221::Vector3f &a) {
		return CG221::Vector3f(-a.x, -a.y, -a.z);
	}

	// Add two Vector3f's
	friend CG221::Vector3f operator + (const CG221::Vector3f &a, const CG221::Vector3f &b) {
		CG221::Vector3f ret(a);
		ret += b;
		return ret;
	}

	// Subtract one vector3 from another
	friend CG221::Vector3f operator - (const CG221::Vector3f &a, const CG221::Vector3f &b) {
		CG221::Vector3f ret(a);
		ret -= b;
		return ret;
	}

	// Multiply vector3 by a float
	friend CG221::Vector3f operator * (const CG221::Vector3f &v, float f) {
		return Vector3f(f * v.x, f * v.y, f * v.z);
	}

	// Multiply vector3 by a float
	friend CG221::Vector3f operator * (float f, const CG221::Vector3f &v) {
		return CG221::Vector3f(f * v.x, f * v.y, f * v.z);
	}

	// Divide vector3 by a float
	friend CG221::Vector3f operator / (const CG221::Vector3f &v, float f) {
		return CG221::Vector3f(v.x / f, v.y / f, v.z / f);
	}

	// Set Values
	void set(float xIn, float yIn, float zIn) {  
		x = xIn;
		y = yIn;
		z = zIn;
	}

	// Get length of a Vector3f
	float length() const {
		return(float) sqrt(x*x + y*y + z*z);
	}

	// Get squared length of a Vector3f
	float lengthSqr() const {
		return(x*x + y*y + z*z);
	}

	// Does Vector3f equal (0, 0, 0)?
	bool isZero() const {
		return((x == 0.0F) && (y == 0.0F) && (z == 0.0F));
	}

	// Normalize a Vector3f
	CG221::Vector3f &normalize() {
		float m = length();
		if (m > 0.0F)
			m = 1.0F / m;
		else
			m = 0.0F;
		x *= m;
		y *= m;
		z *= m;
		return *this;
	}

	// Cross product of two Vector3f's
	CG221::Vector3f cross(const CG221::Vector3f &a, const CG221::Vector3f &b)
	{
		return Vector3f( a.y*b.z - a.z*b.y, a.z*b.x -  a.x*b.z, a.x*b.y - a.y*b.x);
	}
	// Cross product of one Vector3f's
	CG221::Vector3f cross(const CG221::Vector3f &b)
	{
		return CG221::Vector3f(y*b.z - z*b.y, z*b.x -  x*b.z, x*b.y - y*b.x);
	}
	// Dot product of two Vector3f's
	float DotProduct(const CG221::Vector3f &b)
	{
		return x*b.x + y*b.y + z*b.z;
	}

	bool doMaxCheck(const CG221::Vector3f& refVec) const;
	bool doMinCheck(const CG221::Vector3f& refVec) const;
	void getMax(const CG221::Vector3f& refVec); 
	void getMin(const CG221::Vector3f& refVec); 
	const CG221::Vector3f& invert();
	CG221::Vector3f getOrthogonal(const CG221::Vector3f& refVector) const;

	
	Vector3f() { x = 0; y = 0; z = 0; };
	Vector3f(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
	Vector3f(const CG221::Vector3f &v) { x = v.x; y = v.y; z = v.z; }
	virtual ~Vector3f();

	//////////////////////////////////////////////////////////////////////

	static CG221::Vector3f * create();
	static CG221::Vector3f * create(float _x, float _y, float _z);
	static CG221::Vector3f * create(const CG221::Vector3f &v);
	static void destroy(CG221::Vector3f *v);

	//////////////////////////////////////////////////////////////////////
};

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

typedef std::vector<CG221::Vector3f *> VectorVector3f;


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

} // namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
#endif // __Vector3f_H__
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
