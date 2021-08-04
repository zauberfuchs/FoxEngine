
#include "Vector3f.h"

namespace CG221 {

	CG221::Vector3f * Vector3f::create()
	{
		return new Vector3f();
	}

	CG221::Vector3f * Vector3f::create(float _x, float _y, float _z)		
	{
		return new Vector3f(_x, _y, _z);
	}

	CG221::Vector3f * Vector3f::create(const CG221::Vector3f &v)		
	{
		return new Vector3f(v);
	}

	void Vector3f::destroy(CG221::Vector3f *v)
	{
		delete v;
		v = NULL;
	}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Vector3f::~Vector3f()
{

}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// Return Normal of vector3's
CG221::Vector3f Normalized(const CG221::Vector3f &a)
{
	CG221::Vector3f ret(a);
	return ret.normalize();
}

// Dot product of two Vector3f's
float DotProduct(const CG221::Vector3f &a, const CG221::Vector3f &b) 
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

// Swap two Vector3f's
void SwapVec(CG221::Vector3f &a, CG221::Vector3f &b) 
{
	CG221::Vector3f tmp(a);

	a = b;
	b = tmp;
}

// Cross product of two Vector3f's
CG221::Vector3f CrossProduct(const CG221::Vector3f &a, const CG221::Vector3f &b) 
{
	return CG221::Vector3f(a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x);
}

// Are these two Vector3f's nearly equal?
bool NearlyEquals( const CG221::Vector3f& a, const CG221::Vector3f& b, float r ) 
{
	CG221::Vector3f diff = a - b;  // difference

	return(DotProduct(diff, diff) < r*r);  // radius
}

bool CG221::Vector3f::doMaxCheck(const CG221::Vector3f& refVec) const
{
	return (refVec.x > x) ||
		(refVec.y > y) ||
		(refVec.z > z);
}

bool CG221::Vector3f::doMinCheck(const CG221::Vector3f& refVec) const
{
	return (refVec.x < x) ||
		(refVec.y < y) ||
		(refVec.z < z);
}

void CG221::Vector3f::getMax(const CG221::Vector3f& refVec)
{
	if (refVec.x > x) x = refVec.x;
	if (refVec.y > y) y = refVec.y;
	if (refVec.z > z) z = refVec.z;
}

void CG221::Vector3f::getMin(const CG221::Vector3f& refVec)
{
	if (refVec.x < x) x = refVec.x;
	if (refVec.y < y) y = refVec.y;
	if (refVec.z < z) z = refVec.z;
}

const CG221::Vector3f& CG221::Vector3f::invert()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

CG221::Vector3f CG221::Vector3f::getOrthogonal(const CG221::Vector3f& refVector) const
{
	CG221::Vector3f vecReturn(
		y * refVector.z - z * refVector.y,
		-(x * refVector.z - z * refVector.x),
		x * refVector.y - y * refVector.x);
	vecReturn.normalize();
	return vecReturn;
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

} // namespace CG221 {
