///////////////////////////////////////////////////////////////////////////
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Library General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Library General Public License for more details.
//
//  You should have received a copy of the GNU Library General Public
//  License along with this library; if not, write to the
//  Free Software Foundation, Inc., 59 Temple Place - Suite 330,
//  Boston, MA  02111-1307, USA.
//
//  Or go to http://www.gnu.org/copyleft/lgpl.html
//
///////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <map>

#include "Utils/Color3f.h"
#include "Utils/Color4f.h"
#include "Utils/Vector3f.h"
#include "Utils/Vector4f.h"
#include "Utils/Matrix3f.h"
#include "Utils/Matrix3f.h"
#include "Utils/Matrix4f.h"

/**
 * @author 
 */
class Face 
{
public:
	///** The vertices of this face */	
	CG221::VectorVector3f vertices;
	///** The vertex colors */	
	CG221::VectorColor3f vertexColors;
	///** The face normal */	
	CG221::Vector3f * faceNormal;
	///** The vertex normals of this face */	
	CG221::VectorVector3f vertexNormals;
	///** The UVW-Coordinates of this face */	
	CG221::VectorVector3f uvwCoords;

	int vertCount;
	
	Face(CG221::VectorVector3f &_vertices) 
	{		
		std::copy(_vertices.begin(), _vertices.end(), vertices.begin());

		vertCount = vertices.size();

		vertexNormals.reserve(vertCount);
		for (int i = 0; i < vertCount; ++i) {			
			vertexNormals.push_back(new CG221::Vector3f(*vertices[i]));
			vertexNormals[i]->normalize();
		}

		calculateFaceNormal();
	}
	
	///**
	// * Constructs a new Face.
	// *  
	// * Face normal will be calculated.
	// * Vertex-normals will be approximated by "normalizing" the vertices. 
	// * 
	// * @param vertices the vertices
	// * @param vertexColors the vertex colors 
	// */
	//public Face(final Point3f[] vertices, final Color3f[] vertexColors) {
	//	
	//	this.vertices = vertices;
	//	this.vertexColors = vertexColors;
	//	
	//	final int vertCount = vertices.length;
	//			
	//	vertexNormals = new Vector3f[vertCount];
	//	
	//	for (int i = 0; i < vertCount; i++) {
	//		vertexNormals[i] = new Vector3f(vertices[i]);
	//		vertexNormals[i].normalize();
	//	}
	//	
	//	calculateFaceNormal();
	//}
	//
	///**
	// * Constructs a new Face.
	// * 
	// * Face normal will be calculated.
	// * 
	// * @param vertices the vertices
	// * @param vertexNormals the vertex normals
	// */
	//public Face(final Point3f[] vertices, final Vector3f[] vertexNormals) {
	//	
	//	this.vertices = vertices;
	//	this.vertexNormals = vertexNormals;
	//	
	//	calculateFaceNormal();
	//}
	
	///**
	// * Constructs a new Face.
	// * 
	// * Face normal will be calculated.
	// * 
	// * @param vertices the vertices
	// * @param vertexColors the vertex colors 
	// 
	// * @param vertexNormals the vertex normals
	// */
	//Face(CG221::VectorVector3f *_vertices, CG221::VectorVector3f *_vertexColors, CG221::VectorVector3f *_vertexNormals) 
	//{	
	//	std::copy(_vertices->begin(), _vertices->end(), vertices.begin());
	//	std::copy(_vertexColors->begin(), _vertexColors->end(), vertexColors.begin());
	//	std::copy(_vertexNormals->begin(), _vertexNormals->end(), vertexNormals.begin());
	//
	//	calculateFaceNormal();
	//}
	
	///**
	// * Constructs a new Face.
	// * 
	// * @param vertices the vertices
	// * @param vertexNormals the vertex normals
	// * @param faceNormal the face normal
	// */
	//public Face(final Point3f[] vertices, final Vector3f[] vertexNormals, 
	//		final Vector3f faceNormal) {
	//	
	//	this.vertices = vertices;
	//	this.vertexNormals = vertexNormals;
	//	this.faceNormal = faceNormal;
	//}
	
	/**
	 * 
	 * @param vertices the vertices
	 * @param vertexColors the vertex colors 
	 * @param vertexNormals the vertex normals
	 * @param faceNormal the face normal
	 */
	Face(CG221::Vector3f &v0, CG221::Vector3f &v1, CG221::Vector3f &v2, 
			CG221::Color3f &c0, CG221::Color3f &c1, CG221::Color3f &c2,
			CG221::Vector3f &n0, CG221::Vector3f &n1, CG221::Vector3f &n2)
	{
		vertices.push_back(new CG221::Vector3f(v0));
		vertices.push_back(new CG221::Vector3f(v1));
		vertices.push_back(new CG221::Vector3f(v2));

		vertexColors.push_back(new CG221::Color3f(c0));
		vertexColors.push_back(new CG221::Color3f(c1));
		vertexColors.push_back(new CG221::Color3f(c2));

		vertexNormals.push_back(new CG221::Vector3f(n0));
		vertexNormals.push_back(new CG221::Vector3f(n1));
		vertexNormals.push_back(new CG221::Vector3f(n2));
	}
	
	
	/** Calculates the face normal */
	void calculateFaceNormal() 
	{
		faceNormal = new CG221::Vector3f();
		CG221::Vector3f* p0 = vertices[0];
		
		CG221::Vector3f* v0 = new CG221::Vector3f(*vertices[1]);
        *v0 = *v0 - *p0;
        
		CG221::Vector3f* v1 = new CG221::Vector3f(*vertices[2]);
        *v1 = *v1 - *p0;
        
        faceNormal->cross(*v0, *v1);
        faceNormal->normalize();
	}
	
	
	///**
	// * Returns the vertices of this face
	// * 
	// * @return the vertices of this face
	// */
	//public Point3f[] getVertices() {
	//	return vertices;
	//}

	///**
	// * Sets the vertices of this face.
	// * 
	// * !IF THE FACE WAS ADDED TO A MESH CHANGES MADE TO THE FACE WILL NOT
	// * AFFECT THE MESH! 
	// * 
	// * @param vertices the vertices to set 
	// */
	//public void setVertices(Point3f[] vertices) {
	//	this.vertices = vertices;
	//}
	//
	///**
	// * Returns the vertex colors of this face 
	// * 
	// * @return the vertex colors of this face
	// */
	//public Color3f[] getVertexColors() {
	//	return vertexColors;
	//}

	///**
	// * Sets the vertex colors of this face.
	// * 
	// * !IF THE FACE WAS ADDED TO A MESH CHANGES MADE TO THE FACE WILL NOT
	// * AFFECT THE MESH! 
	// * 
	// * @param vertexColors the vertex colors to set 
	// */
	//public void setVertexColors(Color3f[] vertexColors) {
	//	this.vertexColors = vertexColors;
	//}

	///**
	// * Returns the face normal
	// * 
	// * @return the face normal
	// */
	//public Vector3f getFaceNormal() {
	//	return faceNormal;
	//}

	///**
	// * Sets the face normal.
	// * 
	// * !IF THE FACE WAS ADDED TO A MESH CHANGES MADE TO THE FACE WILL NOT
	// * AFFECT THE MESH! 
	// * 
	// * @param faceNormal the face normal to set
	// */
	//public void setFaceNormal(Vector3f faceNormal) {
	//	this.faceNormal = faceNormal;
	//}

	///**
	// * Returns the vertex normals
	// * 
	// * @return the vertex normals
	// */
	//public Vector3f[] getVertexNormals() {
	//	return vertexNormals;
	//}

	///**
	// * Sets the vertex normals of this face.
	// * 
	// * !IF THE FACE WAS ADDED TO A MESH CHANGES MADE TO THE FACE WILL NOT
	// * AFFECT THE MESH! 
	// * 
	// * @param vertexNormals the vertex normals to set
	// */
	//public void setVertexNormals(Vector3f[] vertexNormals) {
	//	this.vertexNormals = vertexNormals;
	//}
	//
	///**
	// * Returns the UVW coordinates
	// * 
	// * @return the UVW coordinates
	// */
	//public TexCoord3f[] getUVWCoordinates() {
	//	return uvwCoords;
	//}

	///**
	// * Sets the UVW coordinates of this face.
	// * 
	// * !IF THE FACE WAS ADDED TO A MESH CHANGES MADE TO THE FACE WILL NOT
	// * AFFECT THE MESH! 
	// * 
	// * @param vertexNormals the UVW coordinates to set
	// */
	//public void setUvwCoords(TexCoord3f[] uvwCoords) {
	//	this.uvwCoords = uvwCoords;
	//}
	//
	///* (non-Javadoc)
	// * @see java.lang.Object#toString()
	// */
	//@Override
	//public String toString() {		
	//	return "Vertices: " + Arrays.toString(vertices)
	//		+ "\nVertexNormals: " + Arrays.toString(vertexNormals)
	//		+ "\nFaceNormal: " + faceNormal;
	//}
	//
};
