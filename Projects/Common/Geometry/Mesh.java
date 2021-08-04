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

import CG221.core.data.Entity;
import java.nio.FloatBuffer;
import java.util.Arrays;

import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;

import cgr.material.Material;
import cgr.rendering.IRenderStrategy;
import cgr.util.BufferUtil;

/**
 * A MESH ONLY SUPPORT TRIANGLE FACES!
 * 
 * @author Christian Baeumer
 */
public class Mesh extends Entity
{

    /**
     * The Normal mode enumeration is used to specify which normals should be
     * used for rendering. */
    public enum NormalMode
    {

        VERTEX_NORMALS, FACE_NORMALS;
    }
    /** Direct float buffer for vertices */
    protected FloatBuffer vertices;
    /** Direct float buffer for vertex colors */
    protected FloatBuffer vertexColors;
    /** Direct float buffer for vertex normals */
    protected FloatBuffer vertexNormals;
    /** Direct float buffer for face normals */
    protected FloatBuffer faceNormals;
    /** Direct float buffer for texture coordinates */
    protected FloatBuffer uvwCoords;
    /** The normal mode indicate which normals (vertex normals or face normals)
     * are used for rendering */
    protected NormalMode currentNormalMode;
    /** Number of mesh faces */
    protected int faceCount;
    /** The default material of this mesh */
    private Material defaultMaterial;
    /** Cached render strategy */
    protected IRenderStrategy<MeshInstance> cachedRenderStrategy;

    /**
     * Constructs a new Mesh
     *
     * @param name the name of the mesh
     */
    protected Mesh(final String name)
    {
        super(name);

        currentNormalMode = NormalMode.VERTEX_NORMALS;

        clear();

        MeshManager.getInstance().add(this);
    }

    /**
     * Copy constructor.
     * @param orig
     */
    public Mesh(Mesh orig)
    {
        super(orig.getName());

        currentNormalMode = orig.currentNormalMode;
        defaultMaterial = orig.defaultMaterial;

        vertices = BufferUtil.copyFloatBuffer(orig.vertices);
        vertexColors = BufferUtil.copyFloatBuffer(orig.vertexColors);
        vertexNormals = BufferUtil.copyFloatBuffer(orig.vertexNormals);
        faceNormals = BufferUtil.copyFloatBuffer(orig.faceNormals);
        uvwCoords = BufferUtil.copyFloatBuffer(orig.uvwCoords);

        faceCount = orig.faceCount;
    }

    /** Clears all buffers. */
    public final void clear()
    {
        /* setup mesh buffer */
        vertices = BufferUtil.newFloatBuffer(0);
        vertexColors = BufferUtil.newFloatBuffer(0);
        vertexNormals = BufferUtil.newFloatBuffer(0);
        faceNormals = BufferUtil.newFloatBuffer(0);
        uvwCoords = BufferUtil.newFloatBuffer(0);

        /* no faces added yet */
        faceCount = 0;

        super.changed();
    }

    /**
     * Adds a new face to this mesh. ONLY TRIANGLE-FACES ARE SUPPORTED!
     *
     * @param newFace the new face
     * @return the faceID of the new face
     */
    public int addFace(final Face newFace)
    {

        /* add vertices */
        if (newFace.vertices != null) {
            vertices = BufferUtil.put(vertices, newFace.vertices);
        }

        /* add vertex colors */
        if (newFace.vertexColors != null) {
            vertexColors = BufferUtil.put(vertexColors, newFace.vertexColors);
        }

        /* add vertex normals */
        if (newFace.vertexNormals != null) {
            vertexNormals = BufferUtil.put(vertexNormals, newFace.vertexNormals);
        }

        /* add face normals */
        if (newFace.faceNormal != null) {
            final Vector3f[] fns = new Vector3f[3];
            Arrays.fill(fns, newFace.faceNormal);
            faceNormals = BufferUtil.put(faceNormals, fns);
        }

        /* add UVW coordinates */
        if (newFace.uvwCoords != null) {
            uvwCoords = BufferUtil.put(uvwCoords, newFace.uvwCoords);
        }

        /* increment face count */
        faceCount++;

        /* mesh has changed! */
        super.changed();

        return faceCount;
    }

    /**
     * Returns a face of this mesh
     *
     * @param faceID the face-id of the face
     * @return a face of this mesh
     */
    public Face getFace(int faceID)
    {

        /* 9 = 3 vertices * 3 components per vertex */
        int v_idx = 9 * faceID;
        int n_idx = v_idx;
        int f_idx = v_idx;

        /* only for fast and easy access */
        final FloatBuffer vertexBuffer = this.vertices;
        final FloatBuffer vertexNormalBuffer = this.vertexNormals;
        final FloatBuffer faceNormalBuffer = this.faceNormals;

        /* some data container */
        final Point3f[] _vertices = new Point3f[3];
        final Vector3f[] _vertexNormals = new Vector3f[3];
        /* the face normal can be set immediately  */
        final Vector3f faceNormal = new Vector3f(faceNormalBuffer.get(f_idx++),
                faceNormalBuffer.get(f_idx++),
                faceNormalBuffer.get(f_idx++));

        /* fill the data container
         * 3 = 3 vertices = 1 Triangle */
        for (int i = 0; i < 3; i++) {
            _vertices[i] = new Point3f(vertexBuffer.get(v_idx++),
                    vertexBuffer.get(v_idx++),
                    vertexBuffer.get(v_idx++));

            _vertexNormals[i] = new Vector3f(vertexNormalBuffer.get(n_idx++),
                    vertexNormalBuffer.get(n_idx++),
                    vertexNormalBuffer.get(n_idx++));
        }

        /* return a new(!) face object */
        return new Face(_vertices, _vertexNormals, faceNormal);
    }

    /**
     * Sets the normal mode of this mesh.
     *
     * @param mode the normal mode to set
     */
    public void setNormalMode(NormalMode mode)
    {
        currentNormalMode = mode;
        /* mesh has changed! */
        super.changed();
    }

    /**
     * Returns the currently used normal mode of this mesh
     *
     * @return the currently used normal mode
     */
    public NormalMode getCurrentNormalMode()
    {
        return currentNormalMode;
    }

    /**
     * Returns the number of faces
     *
     * @return the number of faces
     */
    public int getFaceCount()
    {
        return faceCount;
    }

    /**
     * Returns the number of vertices
     *
     * @return the number of vertices
     */
    public int getVertexCount()
    {
        return vertices.capacity() / 3;
    }

    /**
     *
     * @return number coords for uvw mapping
     */
    public int getUVWCoordsCount()
    {
        return uvwCoords.capacity();
    }

    /**
     *
     * @return number of vertex colors
     */
    public int getVertexColorsCount()
    {
        return this.vertexColors.capacity();
    }

    /**
     * Returns the default material, which will be used for rendering a
     * MeshInstance, if no other material is attached to the instance.
     *
     * @return the defaultMaterial
     */
    public Material getDefaultMaterial()
    {
        return defaultMaterial;
    }

    /**
     * Sets the default material, which will be used for rendering a
     * MeshInstance, if no other material is attached to the instance.
     *
     * @param defaultMaterial the defaultMaterial to set
     */
    public void setDefaultMaterial(Material defaultMaterial)
    {
        this.defaultMaterial = defaultMaterial;
    }

    public void setVertices(FloatBuffer verticies)
    {
        this.vertices = verticies;
    }

    public void setVertexNormals(FloatBuffer vertexNormals)
    {
        this.vertexNormals = vertexNormals;
    }

    public void setFaceNormals(FloatBuffer faceNormals)
    {
        this.faceNormals = faceNormals;
    }

    public void setUVWCoords(FloatBuffer uvwCoords)
    {
        this.uvwCoords = uvwCoords;
    }

    /**
     * Gets the calculated min and max vector of all vertices of this mesh.
     * @return 
     */
    public Point3f[] getMinMaxVector()
    {

        Point3f min = new Point3f();
        Point3f max = new Point3f();
        Point3f[] minMax = new Point3f[2];
        float value;
        int limit = vertices.limit();
       
        min.x = -1.0f;
        min.y = -1.0f;
        min.z = -1.0f;
        max.x = 1.0f;
        max.y = 1.0f;
        max.z = 1.0f;

//        if ((limit < 3) || (limit % 3 != 0)) {
//            throw new IllegalArgumentException("The vertices list must have " +
//                    "3 or more values. And it must be divided by 3 without " +
//                    "rest.");
//        } else {

        if (limit > 0) {
            min.x = vertices.get(0);
            min.y = vertices.get(1);
            min.z = vertices.get(2);
            max.x = min.x;
            max.y = min.y;
            max.z = min.z;

            for (int i = 1; i < limit / 3; i++) {

                value = vertices.get(i * 3 + 0);
                if (min.x > value) {
                    min.x = value;
                }
                if (max.x < value) {
                    max.x = value;
                }

                value = vertices.get(i * 3 + 1);
                if (min.y > value) {
                    min.y = value;
                }
                if (max.y < value) {
                    max.y = value;
                }

                value = vertices.get(i * 3 + 2);
                if (min.z > value) {
                    min.z = value;
                }
                if (max.z < value) {
                    max.z = value;
                }
            }
        }

        minMax[0] = min;
        minMax[1] = max;

        return minMax;
    }
}
