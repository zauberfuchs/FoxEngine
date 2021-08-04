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

#include "AABox.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

AABox::AABox( CG221::Vector3f &corner,  float x, float y, float z) 
{
	setBox(corner,x,y,z);
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

AABox::AABox() 
{
	corner.x = 0; corner.y = 0; corner.z = 0;

	x = 1.0f;
	y = 1.0f;
	z = 1.0f;	
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

AABox::~AABox() 
{

}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

void AABox::setBox( CG221::Vector3f &corner,  float x, float y, float z) 
{
	this->corner = CG221::Vector3f(corner);

	if (x < 0.0) {
		x = -x;
		this->corner.x -= x;
	}
	if (y < 0.0) {
		y = -y;
		this->corner.y -= y;
	}
	if (z < 0.0) {
		z = -z;
		this->corner.z -= z;
	}
	this->x = x;
	this->y = y;
	this->z = z;
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

CG221::Vector3f AABox::getVertexP(CG221::Vector3f &normal) 
{

	CG221::Vector3f res = corner;

	if (normal.x > 0)
		res.x += x;

	if (normal.y > 0)
		res.y += y;

	if (normal.z > 0)
		res.z += z;

	return(res);
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

CG221::Vector3f AABox::getVertexN(CG221::Vector3f &normal) 
{

	CG221::Vector3f res = corner;

	if (normal.x < 0)
		res.x += x;

	if (normal.y < 0)
		res.y += y;

	if (normal.z < 0)
		res.z += z;

	return(res);
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

} // namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
