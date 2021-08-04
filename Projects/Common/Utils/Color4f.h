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

#ifndef __Color4f_H__
#define __Color4f_H__
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#include "CompilerPre.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <new>

#include <deque>
#include <queue>
#include <list>
#include <map>
#include <vector>
#include <iostream>
#include <string>

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#include "Vector3f.h"

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

namespace CG221 {

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

class CG221_API Color4f;

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

class CG221_API Color4f
{
public:
	float x, y, z, w;

	Color4f() : x(0), y(0), z(0), w(0) {};
	virtual ~Color4f();

	// Constructor with initializing float values
	Color4f(float inX, float inY, float inZ, float inW): x(inX), y(inY), z(inZ), w(inW) {};

	// Constructor with initializing Color4f
	Color4f(const Color4f &v): x(v.x), y(v.y), z(v.z), w(v.w) {};

	// Constructor with initializing Vector3f
	explicit Color4f(const Vector3f &v): x(v.x), y(v.y), z(v.z), w(0.0F) {};
	
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
	Color4f &operator = (const Vector3f &v) { 
		x = v.x;
		y = v.y;
		z = v.z;
		w = 0.0F;
		return *this;
	}

	// Add a Color4f to this one
	Color4f &operator += (const Color4f &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	// Subtract a Color4f from this one
	Color4f  &operator -= (const Color4f &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	// Multiply the Color4f by a float
	Color4f &operator *= (float f) {
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}

	// Divide the Color4f by a float
	Color4f &operator /= (float f) {
		x /= f;
		y /= f;
		z /= f;
		w /= f;
		return *this;
	}

	// Are these two Color4f's equal?
	friend bool operator == (const Color4f &a, const Color4f &b) {
		return((a.x == b.x) && (a.y == b.y) &&
			(a.z == b.z) && (a.w == b.w));
	}

	// Are these two Color4f's not equal?
	friend bool operator != (const Color4f &a, const Color4f &b) {
		return((a.x != b.x) || (a.y != b.y) ||
			(a.z != b.z) || (a.w != b.w));
	}

	// Negate a Color4f
	friend Color4f operator - (const Color4f &a) {
		return Color4f(-a.x, -a.y, -a.z, -a.w);
	}

	// Add two Color4f's
	friend Color4f operator + (const Color4f &a, const Color4f &b) {
		Color4f ret(a);
		ret += b;
		return ret;
	}

	// Subtract one Color4f from another
	friend Color4f operator - (const Color4f &a, const Color4f &b) {
		Color4f ret(a);
		ret -= b;
		return ret;
	}

	// Multiply Color4f by a float
	friend Color4f operator * (const Color4f &v, float f) {
		return Color4f(f * v.x, f * v.y, f * v.z, f * v.w);
	}

	// Multiply Color4f by a float
	friend Color4f operator * (float f, const Color4f &v) {
		return Color4f(f * v.x, f * v.y, f * v.z, f * v.w);
	}

	// Divide Color4f by a float
	friend Color4f operator / (const Color4f &v, float f) {
		return Color4f(v.x / f, v.y / f, v.z / f, v.w / f);
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

	// Does Color4f equal (0, 0, 0, 0)?
	bool isZero() const {
		return((x == 0.0F) && (y == 0.0F) && (z == 0.0F) && (w == 0.0F));
	}
	
};

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

} // namespace CG221 {

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_Color4f_H__F990EDCF_DA7F_44A7_8888_183A1B8B3544__INCLUDED_)

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
