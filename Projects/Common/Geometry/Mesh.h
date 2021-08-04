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
#include <vector>
#include <list>
#include <map>

#include "Utils/Vector3f.h"
#include "Utils/Vector4f.h"
#include "Utils/Matrix3f.h"
#include "Utils/Matrix3f.h"
#include "Utils/Matrix4f.h"

#include "Geometry/Face.h"

/**
 * 
 * 
 * @author
 */
class Mesh
{
public:

//    /**
//     * The Normal mode enumeration is used to specify which normals should be
//     * used for rendering. */
//    public enum NormalMode
//    {
//
//        VERTEX_NORMALS, FACE_NORMALS;
//    }

//    /** Direct float buffer for vertices */
//    protected FloatBuffer vertices;
	std::vector<float> vertices;
//    /** Direct float buffer for vertex colors */
//    protected FloatBuffer vertexColors;
	std::vector<float> vertexColors;
//    /** Direct float buffer for vertex normals */
//    protected FloatBuffer vertexNormals;
	std::vector<float> vertexNormals;
//    /** Direct float buffer for face normals */
//    protected FloatBuffer faceNormals;
	std::vector<float> faceNormals;
//    /** Direct float buffer for texture coordinates */
//    protected FloatBuffer uvwCoords;
	std::vector<float> uvwCoords;
//    /** The normal mode indicate which normals (vertex normals or face normals)
//     * are used for rendering */
//    protected NormalMode currentNormalMode;
//    /** Number of mesh faces */
//    protected int faceCount;
	int faceCount;
//    /** The default material of this mesh */
//    private Material defaultMaterial;
//    /** Cached render strategy */
//    protected IRenderStrategy<MeshInstance> cachedRenderStrategy;

   /**
     * Constructs a new Mesh
     *
     * @param name the name of the mesh
     */
    Mesh()
    {

    }

//    /**
//     * Copy constructor.
//     * @param orig
//     */
//    public Mesh(Mesh orig)
//    {
//        super(orig.getName());
//
//        currentNormalMode = orig.currentNormalMode;
//        defaultMaterial = orig.defaultMaterial;
//
//        vertices = BufferUtil.copyFloatBuffer(orig.vertices);
//        vertexColors = BufferUtil.copyFloatBuffer(orig.vertexColors);
//        vertexNormals = BufferUtil.copyFloatBuffer(orig.vertexNormals);
//        faceNormals = BufferUtil.copyFloatBuffer(orig.faceNormals);
//        uvwCoords = BufferUtil.copyFloatBuffer(orig.uvwCoords);
//
//        faceCount = orig.faceCount;
//    }
//
    /** Clears all buffers. 
	 */
    void clear()
    {
        /* setup mesh buffer */
		vertices.clear();
		vertexColors.clear();
		vertexNormals.clear();
        faceNormals.clear();
		uvwCoords.clear();

        /* no faces added yet */
        faceCount = 0;
    }

	int addFace(CG221::Vector3f &v0, CG221::Vector3f &v1, CG221::Vector3f &v2,
		CG221::Color3f &c0, CG221::Color3f &c1, CG221::Color3f &c2,
		CG221::Vector3f &n0, CG221::Vector3f &n1, CG221::Vector3f &n2)
	{
		Face *face = new Face(v0, v1, v2, c0, c1, c2, n0, n1, n2);
		int result = addFace(face);
		delete face;

		return result;
	}

    /**
     * Adds a new face to this mesh. ONLY TRIANGLE-FACES ARE SUPPORTED!
     *
     * @param newFace the new face
     * @return the faceID of the new face
     */
    int addFace(Face *_newFace)
    {
        /* add vertices */
        if (!_newFace->vertices.empty()) {
			for (int iv = 0; iv < _newFace->vertices.size(); ++iv) {
				vertices.push_back(_newFace->vertices[iv]->x);
				vertices.push_back(_newFace->vertices[iv]->y);
				vertices.push_back(_newFace->vertices[iv]->z);
			}
        }

        /* add vertex colors */
        if (!_newFace->vertexColors.empty()) {            
			for (int iv = 0; iv < _newFace->vertexColors.size(); ++iv) {
				vertexColors.push_back(_newFace->vertexColors[iv]->x);
				vertexColors.push_back(_newFace->vertexColors[iv]->y);
				vertexColors.push_back(_newFace->vertexColors[iv]->z);
			}
        }

   //     /* add vertex normals */
   //     if (!_newFace->vertexNormals.empty()) {            
			//for (int iv = 0; iv < _newFace->vertexNormals.size(); ++iv) {
			//	vertexNormals.push_back(_newFace->vertexNormals[iv]->x);
			//	vertexNormals.push_back(_newFace->vertexNormals[iv]->y);
			//	vertexNormals.push_back(_newFace->vertexNormals[iv]->z);
			//}
   //     }

        /* add face normals */
   //     if (_newFace->faceNormal != NULL) {           
			//faceNormals.push_back(_newFace->faceNormal->x);
			//faceNormals.push_back(_newFace->faceNormal->y);
			//faceNormals.push_back(_newFace->faceNormal->z);
   //     }

   //     /* add UVW coordinates */
   //     if (!_newFace->uvwCoords.empty()) {
			//for (int iv = 0; iv < _newFace->uvwCoords.size(); ++iv) {
			//	uvwCoords.push_back(_newFace->uvwCoords[iv]->x);
			//	uvwCoords.push_back(_newFace->uvwCoords[iv]->y);
			//	uvwCoords.push_back(_newFace->uvwCoords[iv]->z);
			//}
   //     }

        /* increment face count */
        faceCount++;

        /* mesh has changed! */
        //super.changed();

        return faceCount;
    }

//    /**
//     * Returns a face of this mesh
//     *
//     * @param faceID the face-id of the face
//     * @return a face of this mesh
//     */
//    public Face getFace(int faceID)
//    {
//
//        /* 9 = 3 vertices * 3 components per vertex */
//        int v_idx = 9 * faceID;
//        int n_idx = v_idx;
//        int f_idx = v_idx;
//
//        /* only for fast and easy access */
//        final FloatBuffer vertexBuffer = this.vertices;
//        final FloatBuffer vertexNormalBuffer = this.vertexNormals;
//        final FloatBuffer faceNormalBuffer = this.faceNormals;
//
//        /* some data container */
//        final Point3f[] _vertices = new Point3f[3];
//        final Vector3f[] _vertexNormals = new Vector3f[3];
//        /* the face normal can be set immediately  */
//        final Vector3f faceNormal = new Vector3f(faceNormalBuffer.get(f_idx++),
//                faceNormalBuffer.get(f_idx++),
//                faceNormalBuffer.get(f_idx++));
//
//        /* fill the data container
//         * 3 = 3 vertices = 1 Triangle */
//        for (int i = 0; i < 3; i++) {
//            _vertices[i] = new Point3f(vertexBuffer.get(v_idx++),
//                    vertexBuffer.get(v_idx++),
//                    vertexBuffer.get(v_idx++));
//
//            _vertexNormals[i] = new Vector3f(vertexNormalBuffer.get(n_idx++),
//                    vertexNormalBuffer.get(n_idx++),
//                    vertexNormalBuffer.get(n_idx++));
//        }
//
//        /* return a new(!) face object */
//        return new Face(_vertices, _vertexNormals, faceNormal);
//    }
//
//    /**
//     * Sets the normal mode of this mesh.
//     *
//     * @param mode the normal mode to set
//     */
//    public void setNormalMode(NormalMode mode)
//    {
//        currentNormalMode = mode;
//        /* mesh has changed! */
//        super.changed();
//    }
//
//    /**
//     * Returns the currently used normal mode of this mesh
//     *
//     * @return the currently used normal mode
//     */
//    public NormalMode getCurrentNormalMode()
//    {
//        return currentNormalMode;
//    }
//
//    /**
//     * Returns the number of faces
//     *
//     * @return the number of faces
//     */
//    public int getFaceCount()
//    {
//        return faceCount;
//    }
//
//    /**
//     * Returns the number of vertices
//     *
//     * @return the number of vertices
//     */
//    public int getVertexCount()
//    {
//        return vertices.capacity() / 3;
//    }
//
//    /**
//     *
//     * @return number coords for uvw mapping
//     */
//    public int getUVWCoordsCount()
//    {
//        return uvwCoords.capacity();
//    }
//
//    /**
//     *
//     * @return number of vertex colors
//     */
//    public int getVertexColorsCount()
//    {
//        return this.vertexColors.capacity();
//    }
//
//    /**
//     * Returns the default material, which will be used for rendering a
//     * MeshInstance, if no other material is attached to the instance.
//     *
//     * @return the defaultMaterial
//     */
//    public Material getDefaultMaterial()
//    {
//        return defaultMaterial;
//    }
//
//    /**
//     * Sets the default material, which will be used for rendering a
//     * MeshInstance, if no other material is attached to the instance.
//     *
//     * @param defaultMaterial the defaultMaterial to set
//     */
//    public void setDefaultMaterial(Material defaultMaterial)
//    {
//        this.defaultMaterial = defaultMaterial;
//    }
//
//    public void setVertices(FloatBuffer verticies)
//    {
//        this.vertices = verticies;
//    }
//
//    public void setVertexNormals(FloatBuffer vertexNormals)
//    {
//        this.vertexNormals = vertexNormals;
//    }
//
//    public void setFaceNormals(FloatBuffer faceNormals)
//    {
//        this.faceNormals = faceNormals;
//    }
//
//    public void setUVWCoords(FloatBuffer uvwCoords)
//    {
//        this.uvwCoords = uvwCoords;
//    }
//
//    /**
//     * Gets the calculated min and max vector of all vertices of this mesh.
//     * @return 
//     */
//    public Point3f[] getMinMaxVector()
//    {
//
//        Point3f min = new Point3f();
//        Point3f max = new Point3f();
//        Point3f[] minMax = new Point3f[2];
//        float value;
//        int limit = vertices.limit();
//       
//        min.x = -1.0f;
//        min.y = -1.0f;
//        min.z = -1.0f;
//        max.x = 1.0f;
//        max.y = 1.0f;
//        max.z = 1.0f;
//
////        if ((limit < 3) || (limit % 3 != 0)) {
////            throw new IllegalArgumentException("The vertices list must have " +
////                    "3 or more values. And it must be divided by 3 without " +
////                    "rest.");
////        } else {
//
//        if (limit > 0) {
//            min.x = vertices.get(0);
//            min.y = vertices.get(1);
//            min.z = vertices.get(2);
//            max.x = min.x;
//            max.y = min.y;
//            max.z = min.z;
//
//            for (int i = 1; i < limit / 3; i++) {
//
//                value = vertices.get(i * 3 + 0);
//                if (min.x > value) {
//                    min.x = value;
//                }
//                if (max.x < value) {
//                    max.x = value;
//                }
//
//                value = vertices.get(i * 3 + 1);
//                if (min.y > value) {
//                    min.y = value;
//                }
//                if (max.y < value) {
//                    max.y = value;
//                }
//
//                value = vertices.get(i * 3 + 2);
//                if (min.z > value) {
//                    min.z = value;
//                }
//                if (max.z < value) {
//                    max.z = value;
//                }
//            }
//        }
//
//        minMax[0] = min;
//        minMax[1] = max;
//
//        return minMax;
//    }
};