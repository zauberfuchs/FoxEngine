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

#ifndef __Matrix4f_H__
#define __Matrix4f_H__

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
#include "Matrix3f.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

class CG221_API Matrix4f;

CG221::Matrix4f CG221_API IdentityMatrix4f();
CG221::Matrix4f CG221_API TransposeMatrix4f(const CG221::Matrix4f &m);
CG221::Matrix4f CG221_API InvertMatrix4f(const CG221::Matrix4f &m);
CG221::Matrix4f CG221_API RotateRadMatrix4f(char axis, float rad);
CG221::Matrix4f CG221_API RotateRadMatrix4f(const CG221::Vector3f &axis, float rad);
CG221::Matrix4f CG221_API TranslateMatrix4f(float x, float y, float z);
CG221::Matrix4f CG221_API ScaleMatrix4f(float x, float y, float z, float w = 1.0);
CG221::Matrix4f CG221_API LookAtMatrix4f(const CG221::Vector3f &camPos, const CG221::Vector3f &camUp, const CG221::Vector3f &target );
CG221::Matrix4f CG221_API FrustumMatrix4f(float l, float r, float b, float t, float n, float f);
CG221::Matrix4f CG221_API PerspectiveMatrix4f(float fovY, float aspect, float n, float f);
CG221::Matrix4f CG221_API OrthoMatrix4f(float l, float r, float b, float t, float n, float f);
CG221::Matrix4f CG221_API OrthoNormalMatrix4f(const CG221::Vector3f &xdir, const CG221::Vector3f &ydir, const CG221::Vector3f &zdir);

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

class CG221_API Matrix4f
{

public:
	CG221::Vector4f col[4];

	// Constructors
	Matrix4f() {};
	virtual ~Matrix4f();

	// Constructor with initializing value
	Matrix4f(float v) {
		col[0].set(v, v, v, v);
		col[1].set(v, v, v, v);
		col[2].set(v, v, v, v);
		col[3].set(v, v, v, v);
	}
	// Constructor with initializing Matrix4f
	Matrix4f(const CG221::Matrix4f &m) {
		col[0] = m[0];
		col[1] = m[1];
		col[2] = m[2];
		col[3] = m[3];
	}
	// Constructor with initializing Vector4f's
	Matrix4f(const CG221::Vector4f &v0, const CG221::Vector4f &v1, 
		const CG221::Vector4f &v2, const CG221::Vector4f &v3) {
			col[0] = v0;
			col[1] = v1;
			col[2] = v2;
			col[3] = v3;
	}
	// Constructor with initializing matrix33
	explicit Matrix4f(const CG221::Matrix3f &m) {
		col[0] = m[0];
		col[1] = m[1];
		col[2] = m[2];
		col[3].set(0.0, 0.0, 0.0, 1.0);
	}

public:
	// Operators
	// Array indexing
	CG221::Vector4f       &operator [] (unsigned int i) {
		assert (i<4);
		return col[i];
	}
	// Array indexing
	const CG221::Vector4f &operator [] (unsigned int i) const {
		assert (i<4);
		return col[i];
	}
	// Assign
	CG221::Matrix4f &operator =  (const CG221::Matrix4f &m) {
		col[0] = m[0];
		col[1] = m[1];
		col[2] = m[2];
		col[3] = m[3];
		return *this;
	}
	// Assign a matrix33 to the Matrix4f
	CG221::Matrix4f  &operator =  (const CG221::Matrix3f &m) {
		col[0] = m[0];
		col[1] = m[1];
		col[2] = m[2];
		col[3].set(0.0, 0.0, 0.0, 1.0);
		return *this;
	}
	// Add a Matrix4f to this one
	CG221::Matrix4f &operator += (const CG221::Matrix4f &m) {
		col[0] += m[0];
		col[1] += m[1];
		col[2] += m[2];
		col[3] += m[3];
		return *this;
	}
	// Subtract a Matrix4f from this one
	CG221::Matrix4f &operator -= (const CG221::Matrix4f &m) {
		col[0] -= m[0];
		col[1] -= m[1];
		col[2] -= m[2];
		col[3] -= m[3];
		return *this;
	}
	// Multiply the Matrix4f by another Matrix4f
	CG221::Matrix4f &operator *= (const CG221::Matrix4f &m);
	// Multiply the Matrix4f by a float
	CG221::Matrix4f &operator *= (float f) {
		col[0] *= f;
		col[1] *= f;
		col[2] *= f;
		col[3] *= f;
		return *this;
	}
	//Matrix4f      &operator /= (float f) {}
	// Are these two Matrix4f's equal?
	friend bool       operator == (const CG221::Matrix4f &a, const CG221:: Matrix4f &b) {
		return((a[0] == b[0]) && (a[1] == b[1]) &&
			(a[2] == b[2]) && (a[3] == b[3]));
	}
	// Are these two Matrix4f's not equal?
	friend bool operator != (const CG221::Matrix4f &a, const CG221::Matrix4f &b) {
		return((a[0] != b[0]) || (a[1] != b[1]) ||
			(a[2] != b[2]) || (a[3] != b[3]));
	}
	// Add two Matrix4f's
	friend CG221::Matrix4f operator + (const CG221::Matrix4f &a, const CG221::Matrix4f &b) {
		CG221::Matrix4f ret(a);
		ret += b;
		return ret;
	}
	// Subtract one Matrix4f from another
	friend CG221::Matrix4f operator - (const CG221::Matrix4f &a, const CG221::Matrix4f &b) {
		CG221::Matrix4f ret(a);
		ret -= b;
		return ret;
	}
	// Multiply Matrix4f by another Matrix4f
	friend CG221::Matrix4f operator * (const CG221::Matrix4f &a, const CG221::Matrix4f &b) {
		CG221::Matrix4f ret(a);
		ret *= b;
		return ret;
	}
	// Multiply a Vector3f by this Matrix4f
	friend Vector3f operator * (const CG221::Matrix4f &m, const CG221::Vector3f &v) {
		CG221::Vector4f ret(v);
		ret = m * ret;
		return CG221::Vector3f(ret.x, ret.y, ret.z);
	}
	// Multiply a Vector3f by this Matrix4f
	friend CG221::Vector3f operator * (const CG221::Vector3f &v, const CG221::Matrix4f &m) {
		CG221::Vector4f ret(v);
		ret = ret * m;
		return CG221::Vector3f(ret.x, ret.y, ret.z);
	}
	// Multiply a Vector4f by this Matrix4f
	friend CG221::Vector4f operator * (const CG221::Matrix4f &m, const CG221::Vector4f &v) {
		CG221::Vector4f ret;
		ret.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + v.w * m[3][0];
		ret.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + v.w * m[3][1];
		ret.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + v.w * m[3][2];
		ret.w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + v.w * m[3][3];
		return ret;
	}
	// Multiply a Vector4f by this Matrix4f
	friend CG221::Vector4f operator * (const CG221::Vector4f &v, const CG221::Matrix4f &m) {
		CG221::Vector4f ret;
		ret.x = DotProduct(m[0], v);
		ret.y = DotProduct(m[1], v);
		ret.z = DotProduct(m[2], v);
		ret.w = DotProduct(m[3], v);
		return ret;
	}
	// Multiply Matrix4f by a float
	friend CG221::Matrix4f operator * (const CG221::Matrix4f &m, float f) {
		CG221::Matrix4f ret(m);
		ret *= f;
		return ret;
	}
	// Set Matrix4f to the identity matrix
	friend CG221::Matrix4f operator * (float f, const CG221::Matrix4f &m) {
		CG221::Matrix4f ret(m);
		ret *= f;
		return ret;
	}

public:
	// Methods
	// Set Matrix4f to the identity matrix
	CG221::Matrix4f      &identity() {
		col[0].set(1.0, 0.0, 0.0, 0.0);
		col[1].set(0.0, 1.0, 0.0, 0.0);
		col[2].set(0.0, 0.0, 1.0, 0.0);
		col[3].set(0.0, 0.0, 0.0, 1.0);
		return *this;
	}
	// Transpose the Matrix4f
	CG221::Matrix4f &transpose();
	// Invert the Matrix4f
	CG221::Matrix4f &invert();

	// multply matrix with vector4f
	//Vector4f multiplyWithVector4f(Vector4f &v);


	inline CG221::Matrix4f &translation(float x, float y, float z)
	{	
		CG221::Matrix4f ret;
		ret.identity();
		
		ret[3][0] = x;
		ret[3][1] = y;
		ret[3][2] = z;

		*this = ret;
		return *this;
	}

	inline void getOpenGLfv(float m[]) 
	{
		m[ 0]=col[0].x; m[ 1]=col[1].x; m[ 2]=col[2].x; m[ 3]=col[3].x;
		m[ 4]=col[0].y; m[ 5]=col[1].y; m[ 6]=col[2].y; m[ 7]=col[3].y;
		m[ 8]=col[0].z; m[ 9]=col[1].z; m[10]=col[2].z; m[11]=col[3].z;
		m[12]=col[0].w; m[13]=col[1].w; m[14]=col[2].w; m[15]=col[3].w;		
	}
};

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

} // namespace GeVE

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#endif // __Matrix4f_H__
