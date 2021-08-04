
#include "Matrix3f.h"

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

Matrix3f::Matrix3f()
{
	col[0].set(0, 0, 0);
	col[1].set(0, 0, 0);
	col[2].set(0, 0, 0);
}

Matrix3f::~Matrix3f()
{
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

// Multiply the Matrix3f by another Matrix3f
Matrix3f &Matrix3f::operator *= (const Matrix3f &m) 
{
	Matrix3f t;

	for (unsigned int r = 0; r < 3; r++)
	{
		for (unsigned int c = 0; c < 3; c++)
		{
			float f = 0;

			f += col[0][r] * m[c][0];
			f += col[1][r] * m[c][1];
			f += col[2][r] * m[c][2];

			t[c][r] = f;
		}
	}

	*this = t;

	return *this;
}

// Transpose the Matrix3f
Matrix3f &Matrix3f::transpose() 
{
	float t;

	for (unsigned int c = 0; c < 3; c++)
	{
		for (unsigned int r = c + 1; r < 3; r++)
		{
			t = col[c][r];
			col[c][r] = col[r][c];
			col[r][c] = t;
		} 
	}

	return *this;
}

// Invert the Matrix3f
Matrix3f &Matrix3f::invert() 
{
	Matrix3f a(*this);
	Matrix3f b(IdentityMatrix3f());

	unsigned int c, r;
	unsigned int cc;
	unsigned int rowMax; // Points to max abs value row in this column
	unsigned int row;
	float tmp;

	// Go through columns
	for (c=0; c<3; c++)
	{
		// Find the row with max value in this column
		rowMax = c;
		for (r=c+1; r<3; r++)
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
		for (cc=0; cc<3; cc++)
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
		for (cc=0; cc<3; cc++)
		{
			a[cc][c] /= tmp;
			b[cc][c] /= tmp;
		}

		// Now do the other rows, so that this column only has a 1 and 0's
		for (row = 0; row < 3; row++)
		{
			if (row != c)
			{
				tmp = a[c][row];
				for (cc=0; cc<3; cc++)
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

// Return a Matrix3f set to the identity matrix
Matrix3f IdentityMatrix3f() 
{
	Matrix3f ret;

	return ret.identity();
}

// Return the transpose of the Matrix3f
Matrix3f TransposeMatrix3f(const Matrix3f &m) 
{
	Matrix3f ret(m);

	return ret.transpose();
}

// Return the inverted Matrix3f
Matrix3f InvertMatrix3f(const Matrix3f &m) 
{
	Matrix3f ret(m);

	return ret.invert();
}

// Return a 2D rotation Matrix3f
Matrix3f RotateRadMatrix3f(float rad) 
{
	Matrix3f ret;
	float sinA, cosA;

	sinA = (float)sin(rad);
	cosA = (float)cos(rad);

	ret[0][0] = cosA; ret[1][0] = -sinA; ret[2][0] = 0.0F;
	ret[0][1] = sinA; ret[1][1] =  cosA; ret[2][1] = 0.0F;
	ret[0][2] = 0.0F; ret[1][2] =  0.0F; ret[2][2] = 1.0F;

	return ret;
}

// Return a 2D translation Matrix3f
Matrix3f TranslateMatrix3f(float x, float y) 
{
	Matrix3f ret;

	ret.identity();
	ret[2][0] = x;
	ret[2][1] = y;

	return ret;
}

// Return a 2D/3D scale Matrix3f
CG221::Matrix3f ScaleMatrix3f(float x, float y, float z) 
{
	CG221::Matrix3f ret;

	ret.identity();
	ret[0][0] = x;
	ret[1][1] = y;
	ret[2][2] = z;

	return ret;
}


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
