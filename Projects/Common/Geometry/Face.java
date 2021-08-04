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

package cgr.geometry;

import java.util.Arrays;

import javax.vecmath.Color3f;
import javax.vecmath.Point3f;
import javax.vecmath.TexCoord3f;
import javax.vecmath.Vector3f;

/**
 * @author Christian Baeumer
 */
public class Face {

	/** The vertices of this face */
	protected Point3f[] vertices;
	/** The vertex colors */
	protected Color3f[] vertexColors;
	/** The face normal */
	protected Vector3f faceNormal;
	/** The vertex normals of this face */
	protected Vector3f[] vertexNormals;
	/** The UVW-Coordinates of this face */
	protected TexCoord3f[] uvwCoords;
	
	
	/**
	 * Constructs a new Face.
	 *  
	 * Face normal will be calculated.
	 * Vertex-normals will be approximated by "normalizing" the vertices. 
	 * 
	 * @param vertices the vertices 
	 */
	public Face(final Point3f[] vertices) {
		
		this.vertices = vertices;
		
		final int vertCount = vertices.length;
				
		vertexNormals = new Vector3f[vertCount];
		
		for (int i = 0; i < vertCount; i++) {
			vertexNormals[i] = new Vector3f(vertices[i]);
			vertexNormals[i].normalize();
		}
		
		calculateFaceNormal();
	}
	
	/**
	 * Constructs a new Face.
	 *  
	 * Face normal will be calculated.
	 * Vertex-normals will be approximated by "normalizing" the vertices. 
	 * 
	 * @param vertices the vertices
	 * @param vertexColors the vertex colors 
	 */
	public Face(final Point3f[] vertices, final Color3f[] vertexColors) {
		
		this.vertices = vertices;
		this.vertexColors = vertexColors;
		
		final int vertCount = vertices.length;
				
		vertexNormals = new Vector3f[vertCount];
		
		for (int i = 0; i < vertCount; i++) {
			vertexNormals[i] = new Vector3f(vertices[i]);
			vertexNormals[i].normalize();
		}
		
		calculateFaceNormal();
	}
	
	/**
	 * Constructs a new Face.
	 * 
	 * Face normal will be calculated.
	 * 
	 * @param vertices the vertices
	 * @param vertexNormals the vertex normals
	 */
	public Face(final Point3f[] vertices, final Vector3f[] vertexNormals) {
		
		this.vertices = vertices;
		this.vertexNormals = vertexNormals;
		
		calculateFaceNormal();
	}
	
	/**
	 * Constructs a new Face.
	 * 
	 * Face normal will be calculated.
	 * 
	 * @param vertices the vertices
	 * @param vertexColors the vertex colors 
	 
	 * @param vertexNormals the vertex normals
	 */
	public Face(final Point3f[] vertices, final Color3f[] vertexColors,
			final Vector3f[] vertexNormals) {
		
		this.vertices = vertices;
		this.vertexColors = vertexColors;
		this.vertexNormals = vertexNormals;
		
		calculateFaceNormal();
	}
	
	/**
	 * Constructs a new Face.
	 * 
	 * @param vertices the vertices
	 * @param vertexNormals the vertex normals
	 * @param faceNormal the face normal
	 */
	public Face(final Point3f[] vertices, final Vector3f[] vertexNormals, 
			final Vector3f faceNormal) {
		
		this.vertices = vertices;
		this.vertexNormals = vertexNormals;
		this.faceNormal = faceNormal;
	}
	
	/**
	 * Constructs a new Face.
	 * 
	 * @param vertices the vertices
	 * @param vertexColors the vertex colors 
	 * @param vertexNormals the vertex normals
	 * @param faceNormal the face normal
	 */
	public Face(final Point3f[] vertices, final Color3f[] vertexColors, 
			final Vector3f[] vertexNormals, final Vector3f faceNormal) {
		
		this.vertices = vertices;
		this.vertexColors = vertexColors;
		this.vertexNormals = vertexNormals;
		this.faceNormal = faceNormal;
	}
	
	
	/** Calculates the face normal */
	private void calculateFaceNormal() {
		faceNormal = new Vector3f();
		final Point3f p0 = vertices[0];
		
		Vector3f v0 = new Vector3f(vertices[1]);
        v0.sub(p0);
        
        Vector3f v1 = new Vector3f(vertices[2]);
        v1.sub(p0);
        
        faceNormal.cross(v0, v1);
        faceNormal.normalize();
	}
	
	
	/**
	 * Returns the vertices of this face
	 * 
	 * @return the vertices of this face
	 */
	public Point3f[] getVertices() {
		return vertices;
	}

	/**
	 * Sets the vertices of this face.
	 * 
	 * !IF THE FACE WAS ADDED TO A MESH CHANGES MADE TO THE FACE WILL NOT
	 * AFFECT THE MESH! 
	 * 
	 * @param vertices the vertices to set 
	 */
	public void setVertices(Point3f[] vertices) {
		this.vertices = vertices;
	}
	
	/**
	 * Returns the vertex colors of this face 
	 * 
	 * @return the vertex colors of this face
	 */
	public Color3f[] getVertexColors() {
		return vertexColors;
	}

	/**
	 * Sets the vertex colors of this face.
	 * 
	 * !IF THE FACE WAS ADDED TO A MESH CHANGES MADE TO THE FACE WILL NOT
	 * AFFECT THE MESH! 
	 * 
	 * @param vertexColors the vertex colors to set 
	 */
	public void setVertexColors(Color3f[] vertexColors) {
		this.vertexColors = vertexColors;
	}

	/**
	 * Returns the face normal
	 * 
	 * @return the face normal
	 */
	public Vector3f getFaceNormal() {
		return faceNormal;
	}

	/**
	 * Sets the face normal.
	 * 
	 * !IF THE FACE WAS ADDED TO A MESH CHANGES MADE TO THE FACE WILL NOT
	 * AFFECT THE MESH! 
	 * 
	 * @param faceNormal the face normal to set
	 */
	public void setFaceNormal(Vector3f faceNormal) {
		this.faceNormal = faceNormal;
	}

	/**
	 * Returns the vertex normals
	 * 
	 * @return the vertex normals
	 */
	public Vector3f[] getVertexNormals() {
		return vertexNormals;
	}

	/**
	 * Sets the vertex normals of this face.
	 * 
	 * !IF THE FACE WAS ADDED TO A MESH CHANGES MADE TO THE FACE WILL NOT
	 * AFFECT THE MESH! 
	 * 
	 * @param vertexNormals the vertex normals to set
	 */
	public void setVertexNormals(Vector3f[] vertexNormals) {
		this.vertexNormals = vertexNormals;
	}
	
	/**
	 * Returns the UVW coordinates
	 * 
	 * @return the UVW coordinates
	 */
	public TexCoord3f[] getUVWCoordinates() {
		return uvwCoords;
	}

	/**
	 * Sets the UVW coordinates of this face.
	 * 
	 * !IF THE FACE WAS ADDED TO A MESH CHANGES MADE TO THE FACE WILL NOT
	 * AFFECT THE MESH! 
	 * 
	 * @param vertexNormals the UVW coordinates to set
	 */
	public void setUvwCoords(TexCoord3f[] uvwCoords) {
		this.uvwCoords = uvwCoords;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {		
		return "Vertices: " + Arrays.toString(vertices)
			+ "\nVertexNormals: " + Arrays.toString(vertexNormals)
			+ "\nFaceNormal: " + faceNormal;
	}
	
}
