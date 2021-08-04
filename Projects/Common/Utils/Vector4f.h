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

#if !defined(AFX_VECTOR4F_H__F990EDCF_DA7F_44A7_8888_183A1B8B3544__INCLUDED_)
#define AFX_VECTOR4F_H__F990EDCF_DA7F_44A7_8888_183A1B8B3544__INCLUDED_

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

#include "CompilerPre.h"

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

class CG221_API Vector4f;

CG221::Vector4f CG221_API Normalized(const CG221::Vector4f &a);
float CG221_API DotProduct(const CG221::Vector4f &a, const CG221::Vector4f &b);
void CG221_API SwapVec(CG221::Vector4f &a, CG221::Vector4f &b);
bool CG221_API NearlyEquals(const CG221::Vector4f &a, const CG221::Vector4f &b, float r);

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

class CG221_API Vector4f // : public _SQuaternion  
{
public:
	float x, y, z, w;

	Vector4f() : x(0), y(0), z(0), w(0) {};
	virtual ~Vector4f();

	// Constructor with initializing float values
	Vector4f(float inX, float inY, float inZ, float inW): x(inX), y(inY), z(inZ), w(inW) {};

	// Constructor with initializing Vector4f
	Vector4f(const CG221::Vector4f &v): x(v.x), y(v.y), z(v.z), w(v.w) {};

	// Constructor with initializing Vector3f
	explicit Vector4f(const CG221::Vector3f &v): x(v.x), y(v.y), z(v.z), w(0.0F) {};
	
	// Operators

	// Array indexing
	float &operator [] (unsigned int i) {
		assert(i<4);
		//return *(&x+i);
		return(i == 0) ? x : (i == 1) ? y : (i == 2) ? z : w;
	}

	// Array indexing
	const float &operator [] (unsigned int i) const {
		assert(i<4);
		//return *(&x+i);
		return(i == 0) ? x : (i == 1) ? y : (i == 2) ? z : w;
	}

	// Assign from a Vector3f
	CG221::Vector4f &operator = (const CG221::Vector3f &v) { 
		x = v.x;
		y = v.y;
		z = v.z;
		w = 0.0F;
		return *this;
	}

	// Add a Vector4f to this one
	CG221::Vector4f &operator += (const CG221::Vector4f &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	// Subtract a Vector4f from this one
	CG221::Vector4f  &operator -= (const CG221::Vector4f &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	// Multiply the Vector4f by a float
	CG221::Vector4f &operator *= (float f) {
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}

	// Divide the Vector4f by a float
	CG221::Vector4f &operator /= (float f) {
		x /= f;
		y /= f;
		z /= f;
		w /= f;
		return *this;
	}

	// Are these two Vector4f's equal?
	friend bool operator == (const CG221::Vector4f &a, const CG221::Vector4f &b) {
		return((a.x == b.x) && (a.y == b.y) &&
			(a.z == b.z) && (a.w == b.w));
	}

	// Are these two Vector4f's not equal?
	friend bool operator != (const CG221::Vector4f &a, const CG221::Vector4f &b) {
		return((a.x != b.x) || (a.y != b.y) ||
			(a.z != b.z) || (a.w != b.w));
	}

	// Negate a Vector4f
	friend CG221::Vector4f operator - (const CG221::Vector4f &a) {
		return Vector4f(-a.x, -a.y, -a.z, -a.w);
	}

	// Add two Vector4f's
	friend CG221::Vector4f operator + (const CG221::Vector4f &a, const CG221::Vector4f &b) {
		CG221::Vector4f ret(a);
		ret += b;
		return ret;
	}

	// Subtract one Vector4f from another
	friend CG221::Vector4f operator - (const CG221::Vector4f &a, const CG221::Vector4f &b) {
		CG221::Vector4f ret(a);
		ret -= b;
		return ret;
	}

	// Multiply Vector4f by a float
	friend CG221::Vector4f operator * (const CG221::Vector4f &v, float f) {
		return CG221::Vector4f(f * v.x, f * v.y, f * v.z, f * v.w);
	}

	// Multiply Vector4f by a float
	friend CG221::Vector4f operator * (float f, const CG221::Vector4f &v) {
		return CG221::Vector4f(f * v.x, f * v.y, f * v.z, f * v.w);
	}

	// Divide Vector4f by a float
	friend CG221::Vector4f operator / (const CG221::Vector4f &v, float f) {
		return CG221::Vector4f(v.x / f, v.y / f, v.z / f, v.w / f);
	}

public:
	// Methods
	// Set Values
	void  set(float xIn, float yIn, float zIn, float wIn) {
		x = xIn;
		y = yIn;
		z = zIn;
		w = wIn;
	}

	// Get length of a Vector4f
	float length() const {
		return(float) sqrt(x*x + y*y + z*z + w*w);
	}

	// Get squared length of a Vector4f
	float lengthSqr() const {
		return(x*x + y*y + z*z + w*w);
	}

	// Does Vector4f equal (0, 0, 0, 0)?
	bool isZero() const {
		return((x == 0.0F) && (y == 0.0F) && (z == 0.0F) && (w == 0.0F));
	}

	// Normalize a Vector4f
	CG221::Vector4f &normalize() {
		float m = length();
		if (m > 0.0F)
			m = 1.0F / m;
		else
			m = 0.0F;
		x *= m;
		y *= m;
		z *= m;
		w *= m;
		return *this;
	}

	// Dot product of two Vector4f's
	float DotProduct(const CG221::Vector4f &b) 
	{
		return x*b.x + y*b.y +  z*b.z + w*b.w;
	}
};

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

} // namespace CG221 {

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_VECTOR4F_H__F990EDCF_DA7F_44A7_8888_183A1B8B3544__INCLUDED_)

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
