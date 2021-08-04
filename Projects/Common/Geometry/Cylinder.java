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

import cgr.geometry.Face;
import cgr.geometry.Mesh;
import cgr.geometry.primitives.ICylinder;
import javax.vecmath.Color3f;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;

/**
 *
 * @author Carsten Wolters
 * @since 23. Maerz 2007, 03:06
 * @version 0.1
 */
public class Cylinder extends Mesh implements ICylinder {
    
    /** The radius at the bottom of the cylinder */
    protected float radiusBottom;
    
    /** The radius at the top of the cylinder */
    protected float radiusTop;
    
    /** The height of the cylinder */
    protected float height;
    
    /** The segments of the cylinder */
    protected int segments;
    
    /** the number of height segments. */
    protected int heightSegments;
    
    /** definition of the color red */
    private static final Color3f RED = new Color3f(1.0f, 0.0f, 0.0f);
    
    /** definition of the color yellow */
    private static final Color3f YELLOW = new Color3f(1.0f, 1.0f, 0.0f);
    
    /** definition of the color green */
    private static final Color3f GREEN = new Color3f(0.0f, 1.0f, 0.0f);
    
    /** definition of the color blue */
    private static final Color3f BLUE = new Color3f(0.0f, 0.0f, 1.0f);
    
    /** Creates a new unit cylinder */
    public Cylinder(String name) {    	
        this(name, 1, 3, 16);
    }
    
    public Cylinder(String name, float radius, float height, int segments) {
    	super(name);
        this.radiusBottom = radius;
        this.radiusTop = radius;
        this.height = height;
        this.segments = segments;
        update();
    }
    
    /**
     * Diese Methode berechnet die Vertices und deren Zuordnung zu den Faces
     * dieses Cylinders.
     */
    @Override
    public final void update() {
        
        super.clear();
        
        /* Die Vertices erstellen und dem Mesh hinzufuegen.
         * Alle Vertices werden ausgehend vom Mittelpunkt des Cylinder angeordnet.
         */
        
        float angle = 0.0f;         // Startwert fuer den Drehwinkel einer Ebene
        final float angleStep = 360.0f / segments;        // Winkelschritt pro Segment
        
        Vector3f normaltop;                           // Die Normalen der TopCap
        Vector3f normalbottom;                     // Die Normalen der BottomCap
        
        final int numVertices = segments * 2;
        Point3f[] lvertices = new Point3f[numVertices + 2];
        Vector3f[] normals = new Vector3f[numVertices + 2];
        
        Point3f vertex = null;
        
        for (int i = 0; i < segments; i++) {
            final float xBottom = radiusBottom * (float)Math.cos(Math.toRadians(angle));
            final float zBottom = radiusBottom * (float)Math.sin(Math.toRadians(angle));
            
            final float xTop = radiusTop * (float)Math.cos(Math.toRadians(angle));
            final float zTop = radiusTop * (float)Math.sin(Math.toRadians(angle));
            
            /* Die Normalen berechenen */
            normalbottom = new Vector3f(xBottom, -height / 2, zBottom);
//            normalbottom = new Vector3f(0f, -1f, 0f);
//            normalbottom.normalize();
            normaltop = new Vector3f(xTop, height / 2, zTop);
//            normaltop = new Vector3f(0f, 1f, 0f);
//            normaltop.normalize();

            /* bottom cap -> bottom ring */
            vertex = new Point3f(xBottom, -height / 2, zBottom);
            lvertices[i] = vertex;
            normals[i] = calcNormal(normalbottom, normaltop);//normalbottom;
            
            /* top cap -> top ring */
            vertex = new Point3f(xTop, height / 2, zTop);
            lvertices[segments + i] = vertex;
            normals[segments + i] = calcNormal(normalbottom, normaltop);//normaltop;

            angle += angleStep;
        }
        /* center bottom */
        vertex = new Point3f(0.0f, -height / 2, 0.0f);
        lvertices[numVertices] = vertex;
        normals[numVertices] = new Vector3f(0.0f, -1.0f, 0.0f);
        
        /* center top */
        vertex = new Point3f(0.0f, height / 2, 0.0f);
        lvertices[numVertices + 1] = vertex;
        normals[numVertices + 1] = new Vector3f(0.0f, 1.0f, 0.0f);
        
        
        /* Die Faces dieses Cylinder erstellen */
        int p0, p1, p2, p3 = 0;
        Vector3f n0, n1, n2, n3 = null;
        
        /* Das TopCap erstellen und dem Mesh als Faces hinzufuegen. */
        for (int i = 0; i < segments - 1; i++) {
            p0 = numVertices + 1;  // top center
            p2 = segments + i;
            p1 = segments + i + 1;
//            System.out.println("Inner p0:" + p0 + "\tp1: " + p1 + "\tp2: " + p2);
            addFace(new Face(new Point3f[] {lvertices[p0], lvertices[p1], lvertices[p2]},
                    new Color3f[] {RED, RED, RED},
                    new Vector3f[] {normals[p0], normals[p1], normals[p2]}));
        }
        p0 = numVertices + 1;  // top center
        p2 = numVertices - 1;
        p1 = segments;
//        System.out.println("Outer p0:" + p0 + "\tp1: " + p1 + "\tp2: " + p2);
        addFace(new Face(new Point3f[] {lvertices[p0], lvertices[p1], lvertices[p2]},
                new Color3f[] {GREEN, GREEN, GREEN},
                new Vector3f[] {normals[p0], normals[p1], normals[p2]}));
        
        /* Das BottomCap erstellen und dem Mesh als Faces hinzufuegen. */
        for (int i = 0; i < segments - 1; i++) {
            p0 = numVertices;
            p1 = i;
            p2 = i + 1;
//            System.out.println("Inner p0:" + p0 + "\tp1: " + p1 + "\tp2: " + p2);
            addFace(new Face(new Point3f[] {lvertices[p0], lvertices[p1], lvertices[p2]},
                    new Color3f[] {YELLOW, YELLOW, YELLOW},
                    new Vector3f[] {normals[p0], normals[p1], normals[p2]}));
        }
        p0 = numVertices;   //bottom center
        p1 = segments - 1;
        p2 = 0;
//        System.out.println("Outer p0:" + p0 + "\tp1: " + p1 + "\tp2: " + p2);
        addFace(new Face(new Point3f[] {lvertices[p0], lvertices[p1], lvertices[p2]},
                    new Color3f[] {GREEN, GREEN, GREEN},
                    new Vector3f[] {normals[p0], normals[p1], normals[p2]}));


        /* Die Mantelflaechen dieses Cylinders erstellen und dem Mesh hinzufuegen. */
        for (int i = 0; i < segments - 1; i++) {
            p0 = i + segments+ 1;
            p1 = i + 1;
            p2 = i;
            p3 = i + segments;
//            System.out.println("Inner p0:" + p0 + "\tp1: " + p1 + "\tp2: " + p2);
//            System.out.println("Inner p2:" + p2 + "\tp3: " + p3 + "\tp0: " + p0);

            n0 = new Vector3f(lvertices[p0]);
            n0.sub(lvertices[numVertices + 1]);
            n0.normalize();
            n1 = new Vector3f(lvertices[p1]);
            n1.sub(lvertices[numVertices]);
            n1.normalize();
            n2 = new Vector3f(lvertices[p2]);
            n2.sub(lvertices[numVertices]);
            n2.normalize();
            n3 = new Vector3f(lvertices[p3]);
            n3.sub(lvertices[numVertices + 1]);
            n3.normalize();
            
            addFace(new Face(new Point3f[] {lvertices[p0], lvertices[p1], lvertices[p2]},
                    new Color3f[] {BLUE, BLUE, BLUE},
                    new Vector3f[] {n0, n1, n2}));
            addFace(new Face(new Point3f[] {lvertices[p2], lvertices[p3], lvertices[p0]},
                    new Color3f[] {BLUE, BLUE, BLUE},
                    new Vector3f[] {n2, n3, n0}));
        }
        p0 = segments;
        p1 = 0;
        p2 = segments - 1;
        p3 = numVertices - 1;
        n0 = new Vector3f(lvertices[p0]);
        n0.sub(lvertices[numVertices + 1]);
        n0.normalize();
        n1 = new Vector3f(lvertices[p1]);
        n1.sub(lvertices[numVertices]);
        n1.normalize();
        n2 = new Vector3f(lvertices[p2]);
        n2.sub(lvertices[numVertices]);
        n2.normalize();
        n3 = new Vector3f(lvertices[p3]);
        n3.sub(lvertices[numVertices + 1]);
        n3.normalize();
        addFace(new Face(new Point3f[] {lvertices[p0], lvertices[p1], lvertices[p2]},
                new Color3f[] {GREEN, GREEN, GREEN},
                new Vector3f[] {n0, n1, n2}));
        addFace(new Face(new Point3f[] {lvertices[p2], lvertices[p3], lvertices[p0]},
                new Color3f[] {GREEN, GREEN, GREEN},
                new Vector3f[] {n2, n3, n0}));
    }
    
    private Vector3f calcNormal(Vector3f p1, Vector3f p2) {

        /* origin of the orthogonal ray */
        Point3f q = new Point3f(0,0,0);

        /* the vector directing from p1 to p2 */
        Vector3f r = new Vector3f();
        r.sub(p2, p1);
        /* the vector directing from the origin to p1 */
        Vector3f qp = new Vector3f();
        qp.sub(p1,q);

        /* determine the "lotfußpunkt" */
        r.scale(qp.dot(r)/r.dot(r));
        p1.sub(r);

        p1.normalize();
        return p1;
    }

    @Override
    public void setHeight(float value) {
        this.height = value;
        update();
    }
    
    @Override
    public void setRadius(float value) {
        this.radiusBottom = value;
        this.radiusTop = value;
        update();
    }
    
    @Override
    public void setSegments(int value) {
        this.segments = value;
        update();
    }
    
    @Override
    public float getHeight() {
        return this.height;
    }
    
    @Override
    public float getRadius() {
        return this.radiusBottom;
    }
    
    @Override
    public int getSegments() {
        return (int)this.segments;
    }
}