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

#ifndef __Color3f_H__
#define __Color3f_H__

/////////////////////////////////////////////////////////////////////////////
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

namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

class CG221_API Color3f
{
public:
	float x, y, z;

	Color3f() { x = 0; y = 0; z = 0; }	;
	Color3f(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
	Color3f(const Color3f &v) { x = v.x; y = v.y; z = v.z; }
	virtual ~Color3f();

	Color3f& operator=(const Color3f& that) 
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

	// Add a Color3f to this one
	Color3f &operator += (const Color3f &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	// Subtract a Color3f from this one
	Color3f &operator -= (const Color3f &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	// Multiply the Color3f by a float
	Color3f &operator *= (float f) {
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	// Divide the Color3f by a float
	Color3f &operator /= (float f) {
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	// Are these two Color3f's equal?
	friend bool operator == (const Color3f &a, const Color3f &b) {
		return((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
	}

	// Are these two Color3f's not equal?
	friend bool operator != (const Color3f &a, const Color3f &b) {
		return((a.x != b.x) || (a.y != b.y) || (a.z != b.z));
	}

	// Negate a Color3f
	friend Color3f operator - (const Color3f &a) {
		return Color3f(-a.x, -a.y, -a.z);
	}

	// Add two Color3f's
	friend Color3f operator + (const Color3f &a, const Color3f &b) {
		Color3f ret(a);
		ret += b;
		return ret;
	}

	// Subtract one Color3f from another
	friend Color3f operator - (const Color3f &a, const Color3f &b) {
		Color3f ret(a);
		ret -= b;
		return ret;
	}

	// Multiply Color3f by a float
	friend Color3f operator * (const Color3f &v, float f) {
		return Color3f(f * v.x, f * v.y, f * v.z);
	}

	// Multiply Color3f by a float
	friend Color3f operator * (float f, const Color3f &v) {
		return Color3f(f * v.x, f * v.y, f * v.z);
	}
	// Divide Color3f by a float
	friend Color3f operator / (const Color3f &v, float f) {
		return Color3f(v.x / f, v.y / f, v.z / f);
	}

	// Set Values
	void set(float xIn, float yIn, float zIn) {
		x = xIn;
		y = yIn;
		z = zIn;
	}	

	// Does Color3f equal (0, 0, 0)?
	bool isZero() const {
		return((x == 0.0F) && (y == 0.0F) && (z == 0.0F));
	}
	
};

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

typedef std::vector<CG221::Color3f *> VectorColor3f;

extern Color3f RED;
extern Color3f GREEN;
extern Color3f BLUE;
extern Color3f YELLOW;
extern Color3f MAGENTA;


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

} // namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
#endif // __Color3f_H__
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
