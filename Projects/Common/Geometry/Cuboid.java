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

package users.CWolters.P2.Primitives;

import javax.vecmath.Color3f;
import javax.vecmath.Point3f;

import cgr.geometry.Face;
import cgr.geometry.Mesh;
import cgr.geometry.primitives.ICuboid;
import javax.vecmath.Vector3f;

/**
 * @author Christian Baeumer
 */
public class Cuboid extends Mesh implements ICuboid {

    /** The width of the cube */
    protected float width;
    /** The depth of the cube */
    protected float depth;
    /** The height of the cube */
    protected float height;

    /** Creates a new unit cube */
    public Cuboid(String name) {

        super(name);

        this.depth = 1.0f;
        this.width = 1.0f;
        this.height = 1.0f;
        update();
    }

    /** 
     * Creates a new instance of Cuboid
     * 
     * @param width the width of the cube
     */
    public Cuboid(String name, float length, float width, float height) {

        super(name);

        this.depth = length;
        this.width = width;
        this.height = height;
        update();
    }

    /** "Calculates" the cube */
    public void update() {

        /* clear the mesh buffer */
        clear();

        final float halfdepth = depth / 2;
        final float halfwidth = width / 2;
        final float halfheight = height / 2;
        Vector3f nn = new Vector3f();

        /* FRONT */
        nn = calcNormal(new Vector3f(-halfdepth, -halfheight, halfwidth),
                        new Vector3f(halfdepth, -halfheight, halfwidth),
                        new Vector3f(halfdepth, halfheight, halfwidth));
        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(-halfdepth, -halfheight, halfwidth),
                        new Point3f(halfdepth, -halfheight, halfwidth),
                        new Point3f(halfdepth, halfheight, halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(1.0f, 0.0f, 0.0f),
                        new Color3f(1.0f, 0.0f, 0.0f),
                        new Color3f(1.0f, 0.0f, 0.0f),},
                    new Vector3f[]{nn, nn, nn}
                    )
                );

        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(halfdepth, halfheight, halfwidth),
                        new Point3f(-halfdepth, halfheight, halfwidth),
                        new Point3f(-halfdepth, -halfheight, halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(1.0f, 0.0f, 0.0f),
                        new Color3f(1.0f, 0.0f, 0.0f),
                        new Color3f(1.0f, 0.0f, 0.0f),},
                        new Vector3f[]{nn, nn, nn}
                    )
                );




        /* RIGHT */
        nn = calcNormal(new Vector3f(halfdepth, -halfheight, halfwidth),
                        new Vector3f(halfdepth, -halfheight, -halfwidth),
                        new Vector3f(halfdepth, halfheight, -halfwidth));
        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(halfdepth, -halfheight, halfwidth),
                        new Point3f(halfdepth, -halfheight, -halfwidth),
                        new Point3f(halfdepth, halfheight, -halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(0.0f, 1.0f, 0.0f),
                        new Color3f(0.0f, 1.0f, 0.0f),
                        new Color3f(0.0f, 1.0f, 0.0f),},
                            new Vector3f[]{nn, nn, nn}
                    )
                );

        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(halfdepth, halfheight, -halfwidth),
                        new Point3f(halfdepth, halfheight, halfwidth),
                        new Point3f(halfdepth, -halfheight, halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(0.0f, 1.0f, 0.0f),
                        new Color3f(0.0f, 1.0f, 0.0f),
                        new Color3f(0.0f, 1.0f, 0.0f),},
                            new Vector3f[]{nn, nn, nn}
                    )
                );

        /* BACK */
        nn = calcNormal(new Vector3f(halfdepth, -halfheight, -halfwidth),
                        new Vector3f(-halfdepth, -halfheight, -halfwidth),
                        new Vector3f(-halfdepth, halfheight, -halfwidth));
        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(halfdepth, -halfheight, -halfwidth),
                        new Point3f(-halfdepth, -halfheight, -halfwidth),
                        new Point3f(-halfdepth, halfheight, -halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(0.0f, 0.0f, 1.0f),
                        new Color3f(0.0f, 0.0f, 1.0f),
                        new Color3f(0.0f, 0.0f, 1.0f),},
                                new Vector3f[]{nn, nn, nn}
                    )
                );

        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(-halfdepth, halfheight, -halfwidth),
                        new Point3f(halfdepth, halfheight, -halfwidth),
                        new Point3f(halfdepth, -halfheight, -halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(0.0f, 0.0f, 1.0f),
                        new Color3f(0.0f, 0.0f, 1.0f),
                        new Color3f(0.0f, 0.0f, 1.0f),},
                                new Vector3f[]{nn, nn, nn}
                    )
                );

        /* LEFT */
        nn = calcNormal(new Vector3f(-halfdepth, -halfheight, -halfwidth),
                        new Vector3f(-halfdepth, -halfheight, halfwidth),
                        new Vector3f(-halfdepth, halfheight, halfwidth));
        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(-halfdepth, -halfheight, -halfwidth),
                        new Point3f(-halfdepth, -halfheight, halfwidth),
                        new Point3f(-halfdepth, halfheight, halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(1.0f, 1.0f, 0.0f),
                        new Color3f(1.0f, 1.0f, 0.0f),
                        new Color3f(1.0f, 1.0f, 0.0f),},
                                    new Vector3f[]{nn, nn, nn}
                    )
                );

        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(-halfdepth, halfheight, halfwidth),
                        new Point3f(-halfdepth, halfheight, -halfwidth),
                        new Point3f(-halfdepth, -halfheight, -halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(1.0f, 1.0f, 0.0f),
                        new Color3f(1.0f, 1.0f, 0.0f),
                        new Color3f(1.0f, 1.0f, 0.0f),},
                                    new Vector3f[]{nn, nn, nn}
                    )
                );

        /* TOP */
        nn = calcNormal(new Vector3f(-halfdepth, halfheight, halfwidth),
                        new Vector3f(halfdepth, halfheight, halfwidth),
                        new Vector3f(halfdepth, halfheight, -halfwidth));
        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(-halfdepth, halfheight, halfwidth),
                        new Point3f(halfdepth, halfheight, halfwidth),
                        new Point3f(halfdepth, halfheight, -halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(1.0f, 0.0f, 1.0f),
                        new Color3f(1.0f, 0.0f, 1.0f),
                        new Color3f(1.0f, 0.0f, 1.0f),},
                                        new Vector3f[]{nn, nn, nn}
                    )
                );

        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(halfdepth, halfheight, -halfwidth),
                        new Point3f(-halfdepth, halfheight, -halfwidth),
                        new Point3f(-halfdepth, halfheight, halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(1.0f, 0.0f, 1.0f),
                        new Color3f(1.0f, 0.0f, 1.0f),
                        new Color3f(1.0f, 0.0f, 1.0f),},
                    
                    new Vector3f[]{nn, nn, nn}
                    )
                );

        /* Bottom */
        nn = calcNormal(new Vector3f(-halfdepth, -halfheight, halfwidth),
                        new Vector3f(-halfdepth, -halfheight, -halfwidth),
                        new Vector3f(halfdepth, -halfheight, -halfwidth));
        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(-halfdepth, -halfheight, halfwidth),
                        new Point3f(-halfdepth, -halfheight, -halfwidth),
                        new Point3f(halfdepth, -halfheight, -halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(0.0f, 1.0f, 1.0f),
                        new Color3f(0.0f, 1.0f, 1.0f),
                        new Color3f(0.0f, 1.0f, 1.0f),},

                        new Vector3f[]{nn, nn, nn}
                    )
                );

        addFace(new Face(
                    /* vertices */
                    new Point3f[]{
                        new Point3f(halfdepth, -halfheight, -halfwidth),
                        new Point3f(halfdepth, -halfheight, halfwidth),
                        new Point3f(-halfdepth, -halfheight, halfwidth),},
                    /* vertex colors */
                    new Color3f[]{
                        new Color3f(0.0f, 1.0f, 1.0f),
                        new Color3f(0.0f, 1.0f, 1.0f),
                        new Color3f(0.0f, 1.0f, 1.0f),},

                        new Vector3f[]{nn, nn, nn}
                    )
                );

    }

    private Vector3f calcNormal(final Vector3f p0, Vector3f p1, Vector3f p2) {

//        /* origin of the orthogonal ray */
//        Point3f q = new Point3f(0,0,0);
//
//        /* the vector directing from p1 to p2 */
//        Vector3f r = new Vector3f();
//        r.sub(p2, p1);
//        /* the vector directing from the origin to p1 */
//        Vector3f qp = new Vector3f();
//        qp.sub(p1,q);
//
//        /* determine the "lotfußpunkt" */
//        r.scale(qp.dot(r)/r.dot(r));
//        p1.sub(r);
//
//        p1.normalize();
//        return p1;

        Vector3f faceNormal = new Vector3f();
        p1.sub(p0);

        p2.sub(p0);

        faceNormal.cross(p1, p2);
        faceNormal.normalize();
        return faceNormal;
    }

    @Override
    public void setDimension(Vector3f p1, Vector3f p2) {
        this.setWidth(Math.abs(p1.x - p2.x));
        this.setHeight(Math.abs(p1.y - p2.y));
        this.setDepth(Math.abs(p1.z - p2.z));
    }

    @Override
    public void setDimension(float valueW, float valueH, float valueD) {
        this.setWidth(valueW);
        this.setHeight(valueH);
        this.setDepth(valueD);
    }

    /**
     * Sets the width of this Cuboid.
     * @param value  the width to be set.
     */
    @Override
    public void setWidth(float value) {
        this.width = value;
        update();
    }

    /**
     * Sets the height of this Cuboid.
     * @param value  the height to be set.
     */
    @Override
    public void setHeight(float value) {
        this.height = value;
        update();
    }

    /**
     * Sets the depth of this Cuboid.
     * @param value  the depth to be set.
     */
    @Override
    public void setDepth(float value) {
        this.depth = value;
        update();
    }

    /**
     * Gets the width of this cuboid.
     * @return  the actual width of this cuboid.
     */
    @Override
    public float getWidth() {
        return this.width;
    }

    /**
     * Gets the height of this cuboid.
     * @return  the actual height of this cuboid.
     */
    @Override
    public float getHeight() {
        return this.height;
    }

    /**
     * Gets the depth of this cuboid.
     * @return  the actual depth of this cuboid.
     */
    @Override
    public float getDepth() {
        return this.depth;
    }
}
