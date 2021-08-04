
#include "Matrix4f.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Matrix4f::~Matrix4f()
{
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

// Multiply the Matrix4f by another Matrix4f
CG221::Matrix4f &Matrix4f::operator *= (const CG221::Matrix4f &m) 
{
	CG221::Matrix4f t;
	for (unsigned int r = 0; r < 4; r++)
	{
		for (unsigned int c = 0; c < 4; c++)
		{
			float f = 0;

			f += (col[0][r] * m[c][0]);
			f += (col[1][r] * m[c][1]);
			f += (col[2][r] * m[c][2]);
			f += (col[3][r] * m[c][3]);

			t[c][r] = f;
		}
	}
	*this = t;
	return *this;
}


// Transpose the Matrix4f
CG221::Matrix4f &Matrix4f::transpose() 
{
	float t;

	for (unsigned int c = 0; c < 4; c++)
	{
		for (unsigned int r = c + 1; r < 4; r++)
		{
			t = col[c][r];
			col[c][r] = col[r][c];
			col[r][c] = t;
		} 
	} 

	return *this;
}

// Invert the Matrix4f
CG221::Matrix4f &Matrix4f::invert() 
{
	CG221::Matrix4f a(*this);
	CG221::Matrix4f b(IdentityMatrix4f());

	unsigned int r, c;
	unsigned int cc;
	unsigned int rowMax; // Points to max abs value row in this column
	unsigned int row;
	float tmp;

	// Go through columns
	for (c=0; c<4; c++)
	{

		// Find the row with max value in this column
		rowMax = c;
		for (r=c+1; r<4; r++)
		{
			if (fabs(a[c][r]) > fabs(a[c][rowMax]))
			{
				rowMax = r;
			}
		}

		// If the max value here is 0, we can't invert.  Return identity.
		if (a[rowMax][c] == 0.0F)
			return(identity());

		// Swap row "rowMax" with row "c"
		for (cc=0; cc<4; cc++)
		{
			tmp = a[cc][c];
			a[cc][c] = a[cc][rowMax];
			a[cc][rowMax] = tmp;
			tmp = b[cc][c];
			b[cc][c] = b[cc][rowMax];
			b[cc][rowMax] = tmp;
		}

		// Now everything we do is on row "c".
		// Set the max cell to 1 by dividing the entire row by that value
		tmp = a[c][c];
		for (cc=0; cc<4; cc++)
		{
			a[cc][c] /= tmp;
			b[cc][c] /= tmp;
		}

		// Now do the other rows, so that this column only has a 1 and 0's
		for (row = 0; row < 4; row++)
		{
			if (row != c)
			{
				tmp = a[c][row];
				for (cc=0; cc<4; cc++)
				{
					a[cc][row] -= a[cc][c] * tmp;
					b[cc][row] -= b[cc][c] * tmp;
				}
			}
		}

	}

	*this = b;

	return *this;
}

// Return a Matrix4f set to the identity matrix
CG221::Matrix4f IdentityMatrix4f() 
{
	CG221::Matrix4f ret;

	return ret.identity();
}

// Return the transpose of the Matrix4f
CG221::Matrix4f TransposeMatrix4f(const CG221::Matrix4f &m) 
{
	CG221::Matrix4f ret(m);

	return ret.transpose();
}

// Return the inverted Matrix4f
CG221::Matrix4f InvertMatrix4f(const CG221::Matrix4f &m) 
{
	CG221::Matrix4f ret(m);

	return ret.invert();
}

// Return a 3D axis-rotation Matrix4f
// Pass in 'x', 'y', or 'z' for the axis.
CG221::Matrix4f RotateRadMatrix4f(char axis, float rad) 
{
	CG221::Matrix4f ret;
	float sinA, cosA;

	sinA = (float)sin(rad);
	cosA = (float)cos(rad);

	switch (axis)
	{
	case 'x':
	case 'X':
		ret[0][0] =  1.0F; ret[1][0] =  0.0F; ret[2][0] =  0.0F;
		ret[0][1] =  0.0F; ret[1][1] =  cosA; ret[2][1] = -sinA;
		ret[0][2] =  0.0F; ret[1][2] =  sinA; ret[2][2] =  cosA;
		break;

	case 'y':
	case 'Y':
		ret[0][0] =  cosA; ret[1][0] =  0.0F; ret[2][0] =  sinA;
		ret[0][1] =  0.0F; ret[1][1] =  1.0F; ret[2][1] =  0.0F;
		ret[0][2] = -sinA; ret[1][2] =  0.0F; ret[2][2] =  cosA;
		break;

	case 'z':
	case 'Z':
		ret[0][0] =  cosA; ret[1][0] = -sinA; ret[2][0] =  0.0F;
		ret[0][1] =  sinA; ret[1][1] =  cosA; ret[2][1] =  0.0F;
		ret[0][2] =  0.0F; ret[1][2] =  0.0F; ret[2][2] =  1.0F;
		break;
	}

	ret[0][3] = 0.0F; ret[1][3] = 0.0F; ret[2][3] = 0.0F;
	ret[3][0] = 0.0F;
	ret[3][1] = 0.0F;
	ret[3][2] = 0.0F;
	ret[3][3] = 1.0F;

	return ret;
}

// Return a 3D axis-rotation Matrix4f
// Pass in an arbitrary Vector3f axis.
CG221::Matrix4f RotateRadMatrix4f(const CG221::Vector3f &axis, float rad) 
{
	CG221::Matrix4f ret;
	float sinA, cosA;
	float invCosA;
	CG221::Vector3f nrm = axis;
	float x, y, z;
	float xSq, ySq, zSq;

	nrm.normalize();
	sinA = (float)sin(rad);
	cosA = (float)cos(rad);
	invCosA = 1.0F - cosA;

	x = nrm.x;
	y = nrm.y;
	z = nrm.z;

	xSq = x * x;
	ySq = y * y;
	zSq = z * z;

	ret[0][0] = (invCosA * xSq) + (cosA);
	ret[1][0] = (invCosA * x * y) - (sinA * z );
	ret[2][0] = (invCosA * x * z) + (sinA * y );
	ret[3][0] = 0.0F;

	ret[0][1] = (invCosA * x * y) + (sinA * z);
	ret[1][1] = (invCosA * ySq) + (cosA);
	ret[2][1] = (invCosA * y * z) - (sinA * x);
	ret[3][1] = 0.0F;

	ret[0][2] = (invCosA * x * z) - (sinA * y);
	ret[1][2] = (invCosA * y * z) + (sinA * x);
	ret[2][2] = (invCosA * zSq) + (cosA);
	ret[3][2] = 0.0F;

	ret[0][3] = 0.0F;
	ret[1][3] = 0.0F;
	ret[2][3] = 0.0F;
	ret[3][3] = 1.0F;

	return ret;
}

// Return a 3D translation Matrix4f
CG221::Matrix4f TranslateMatrix4f(float x, float y, float z) 
{
	CG221::Matrix4f ret;

	ret.identity();
	ret[3][0] = x;
	ret[3][1] = y;
	ret[3][2] = z;

	return ret;
}

// Return a 3D/4D scale Matrix4f
CG221::Matrix4f ScaleMatrix4f(float x, float y, float z, float w) 
{
	CG221::Matrix4f ret;

	ret.identity();
	ret[0][0] = x;
	ret[1][1] = y;
	ret[2][2] = z;
	ret[3][3] = w;

	return ret;
}

// Return a "lookat" Matrix4f given the current camera position (Vector3f),
//   camera-up Vector3f, and camera-target Vector3f.
CG221::Matrix4f LookAtMatrix4f(const CG221::Vector3f &camPos, const CG221::Vector3f &target, const CG221::Vector3f &camUp ) 
{
	CG221::Matrix4f ret;

	CG221::Vector3f F = target - camPos;
	F.normalize();

	CG221::Vector3f S = CrossProduct(F, Normalized(camUp));
	S.normalize();

	CG221::Vector3f U = CrossProduct(S, F);
	U.normalize();

	ret[0][0] = S.x;
	ret[1][0] = S.y;
	ret[2][0] = S.z;
	ret[3][0] = 0.0;

	ret[0][1] = U.x;
	ret[1][1] = U.y;
	ret[2][1] = U.z;
	ret[3][1] = 0.0;

	ret[0][2] = -F.x;
	ret[1][2] = -F.y;
	ret[2][2] = -F.z;
	ret[3][2] = 0.0;

	ret[0][3] = 0.0F;
	ret[1][3] = 0.0F;
	ret[2][3] = 0.0F;
	ret[3][3] = 1.0F;

	ret *= TranslateMatrix4f(-camPos.x, -camPos.y, -camPos.z);

	return ret;
}

// Return a frustum Matrix4f given the left, right, bottom, top,
//   near, and far values for the frustum boundaries.
CG221::Matrix4f FrustumMatrix4f(float l, float r, 
						 float b, float t, float n, float f) 
{
	Matrix4f ret;
	float width = r-l;
	float height = t-b;
	float depth = f-n;

	ret[0][0] = (2*n) / width;
	ret[0][1] = 0.0F;
	ret[0][2] = 0.0F;
	ret[0][3] = 0.0F;

	ret[1][0] = 0.0F;
	ret[1][1] = (2*n) / height;
	ret[1][2] = 0.0F;
	ret[1][3] = 0.0F;

	ret[2][0] = (r + l) / width;
	ret[2][1] = (t + b) / height;
	ret[2][2] = -(f + n) / depth;
	ret[2][3] = -1.0F;

	ret[3][0] = 0.0F;
	ret[3][1] = 0.0F;
	ret[3][2] = -(2*f*n) / depth;
	ret[3][3] = 0.0F;

	return ret;
}

// Return a perspective Matrix4f given the field-of-view in the Y
//   direction in degrees, the aspect ratio of Y/X, and near and
//   far plane distances.
CG221::Matrix4f PerspectiveMatrix4f(float fovY, float aspect, float n, float f) 
{
	CG221::Matrix4f ret;
	float angle;
	float cot;

	angle = fovY / 2.0F;
	angle = deg2Rad( angle );

	cot = (float) cos(angle) / (float) sin(angle);

	ret[0][0] = cot / aspect;
	ret[0][1] = 0.0F;
	ret[0][2] = 0.0F;
	ret[0][3] = 0.0F;

	ret[1][0] = 0.0F;
	ret[1][1] = cot;
	ret[1][2] = 0.0F;
	ret[1][3] = 0.0F;

	ret[2][0] = 0.0F;
	ret[2][1] = 0.0F;
	ret[2][2] = -(f + n) / (f - n);
	ret[2][3] = -1.0F;


	ret[3][0] = 0.0F;
	ret[3][1] = 0.0F;
	ret[3][2] = -(2*f*n) / (f - n);
	ret[3][3] = 0.0F;

	return ret;
}

// Return an orthographic Matrix4f given the left, right, bottom, top,
//   near, and far values for the frustum boundaries.
CG221::Matrix4f OrthoMatrix4f(float l, float r, 
					   float b, float t, float n, float f) 
{
	CG221::Matrix4f ret;
	float width = r-l;
	float height = t-b;
	float depth = f-n;

	ret[0][0] = 2.0F / width;
	ret[0][1] = 0.0F;
	ret[0][2] = 0.0F;
	ret[0][3] = 0.0F;

	ret[1][0] = 0.0F;
	ret[1][1] = 2.0F / height;
	ret[1][2] = 0.0F;
	ret[1][3] = 0.0F;

	ret[2][0] = 0.0F;
	ret[2][1] = 0.0F;
	ret[2][2] = -(2.0F) / depth;
	ret[2][3] = 0.0F;

	ret[3][0] = -(r + l) / width;
	ret[1][3] = -(t + b) / height;
	ret[3][2] = -(f + n) / depth;
	ret[3][3] = 1.0F;

	return ret;
}

// Return an orientation matrix using 3 basis normalized vectors
CG221::Matrix4f OrthoNormalMatrix4f(const CG221::Vector3f &xdir, const CG221::Vector3f &ydir, const CG221::Vector3f &zdir)
{
	CG221::Matrix4f ret;

	ret[0] = (CG221::Vector4f)xdir;
	ret[1] = (CG221::Vector4f)ydir;
	ret[2] = (CG221::Vector4f)zdir;
	ret[3].set(0.0, 0.0, 0.0, 1.0);

	return ret;
}

//// Multiply matrix with vector
//Vector4f Matrix4f::multiplyWithVector4f(Vector4f &v)
//{
//	Vector4f vResult;
//	vResult.x = col[0].x * v.x + col[1].x * v.y + col[2].x * v.z;
//	vResult.y = col[0].y * v.x + col[1].y * v.y + col[2].y * v.z;
//	vResult.z = col[0].z * v.x + col[1].z * v.y + col[2].z * v.z;
//	return vResult;
//}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

} // namespace GeVE

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
