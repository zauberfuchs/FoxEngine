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

#ifndef __Matrix3f_H__
#define __Matrix3f_H__

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
#include "Vector4f.h"
#include "Quat4f.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

class CG221_API Matrix3f;

CG221::Matrix3f CG221_API IdentityMatrix3f();
CG221::Matrix3f CG221_API TransposeMatrix3f(const CG221::Matrix3f &m);
CG221::Matrix3f CG221_API InvertMatrix3f(const CG221::Matrix3f &m);
CG221::Matrix3f CG221_API RotateRadMatrix3f(float rad);
CG221::Matrix3f CG221_API TranslateMatrix3f(float x, float y);
CG221::Matrix3f CG221_API ScaleMatrix3f(float x, float y, float z);

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

class CG221_API Matrix3f
{

public:
	CG221::Vector3f col[3];

	Matrix3f();
	virtual ~Matrix3f();
	
	// Constructor with initializing value
	Matrix3f(float v) {
		col[0].set(v, v, v);
		col[1].set(v, v, v);
		col[2].set(v, v, v);
	}
	// Constructor with initializing Matrix3f
	Matrix3f(const CG221::Matrix3f &m) {
		col[0] = m[0];
		col[1] = m[1];
		col[2] = m[2];
	}
	// Constructor with initializing Vector3f's
	Matrix3f(const CG221::Vector3f &v0, const CG221::Vector3f &v1, const CG221::Vector3f &v2) {
		col[0] = v0;
		col[1] = v1;
		col[2] = v2;
	}

public:
	// Operators
	// Array indexing
	CG221::Vector3f       &operator [] (unsigned int i) {
		assert (i<3);
		return(Vector3f&)col[i];
	}
	// Array indexing
	const CG221::Vector3f     &operator [] (unsigned int i) const {
		assert (i<3);
		return(CG221::Vector3f&)col[i];
	}
	// Assign
	CG221::Matrix3f      &operator =  (const CG221::Matrix3f &m) {
		col[0] = m[0];
		col[1] = m[1];
		col[2] = m[2];
		return *this;
	}
	// Add a Matrix3f to this one
	CG221::Matrix3f      &operator += (const CG221::Matrix3f &m) {
		col[0] += m[0];
		col[1] += m[1];
		col[2] += m[2];
		return *this;
	}
	// Subtract a Matrix3f from this one
	CG221::Matrix3f      &operator -= (const CG221::Matrix3f &m) {
		col[0] -= m[0];
		col[1] -= m[1];
		col[2] -= m[2];
		return *this;
	}
	// Multiply the Matrix3f by another Matrix3f
	CG221::Matrix3f      &operator *= (const CG221::Matrix3f &m);
	// Multiply the Matrix3f by a float
	CG221::Matrix3f      &operator *= (float f) {
		col[0] *= f;
		col[1] *= f;
		col[2] *= f;
		return *this;
	}
	// Are these two Matrix3f's equal?
	friend bool       operator == (const CG221::Matrix3f &a, const CG221::Matrix3f &b) {
		return((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]));
	}
	// Are these two Matrix3f's not equal?
	friend bool       operator != (const CG221::Matrix3f &a, const CG221::Matrix3f &b) {
		return((a[0] != b[0]) || (a[1] != b[1]) || (a[2] != b[2]));
	}
	// Add two Matrix3f's
	friend CG221::Matrix3f   operator + (const CG221::Matrix3f &a, const CG221::Matrix3f &b) {
		Matrix3f ret(a);
		ret += b;
		return ret;
	}
	// Subtract one Matrix3f from another
	friend CG221::Matrix3f   operator - (const CG221::Matrix3f &a, const CG221::Matrix3f &b) {
		CG221::Matrix3f ret(a);
		ret -= b;
		return ret;
	}
	// Multiply Matrix3f by another Matrix3f
	friend CG221::Matrix3f   operator * (const CG221::Matrix3f &a, const CG221::Matrix3f &b) {
		CG221::Matrix3f ret(a);
		ret *= b;
		return ret;
	}
	// Multiply a Vector3f by this Matrix3f
	friend CG221::Vector3f    operator * (const CG221::Matrix3f &m, const CG221::Vector3f &v) {
		CG221::Vector3f ret;
		ret.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0];
		ret.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1];
		ret.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2];
		return ret;
	}
	// Multiply a Vector3f by this Matrix3f
	friend CG221::Vector3f    operator * (const CG221::Vector3f &v, const CG221::Matrix3f &m) {
		CG221::Vector3f ret;
		ret.x = DotProduct(m[0], v);
		ret.y = DotProduct(m[1], v);
		ret.z = DotProduct(m[2], v);
		return ret;
	}
	// Multiply Matrix3f by a float
	friend CG221::Matrix3f   operator * (const CG221::Matrix3f &m, float f) {
		CG221::Matrix3f ret(m);
		ret *= f;
		return ret;
	}
	// Multiply Matrix3f by a float
	friend CG221::Matrix3f   operator * (float f, const CG221::Matrix3f &m) {
		CG221::Matrix3f ret(m);
		ret *= f;
		return ret;
	}

public:
	// Methods
	// Set Matrix3f to the identity matrix
	CG221::Matrix3f      &identity() {
		col[0].set(1.0, 0.0, 0.0);
		col[1].set(0.0, 1.0, 0.0);
		col[2].set(0.0, 0.0, 1.0);
		return *this;
	}
	// Transpose the Matrix3f
	CG221::Matrix3f      &transpose();
	// Invert the Matrix3f
	CG221::Matrix3f      &invert();
};

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

} // namespace GeVE

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#endif // __Matrix3f_H__
