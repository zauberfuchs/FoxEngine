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
import javax.vecmath.Vector3f;

import cgr.geometry.Face;
import cgr.geometry.Mesh;
import cgr.geometry.primitives.ISphere;


/**
 * @author Carsten Wolters
 * @since 23. Maerz 2007, 03:06
 * @version 0.1
 */
public class Sphere extends Mesh implements ISphere {

    /** The radius of the sphere */
    private float radius;
    
    /** The segments of the sphere */
    private int segments;
    
    /** definition of the color red */
    private static final Color3f RED = new Color3f(1.0f, 0.0f, 0.0f);
    
    /** definition of the color yellow */
    private static final Color3f YELLOW = new Color3f(1.0f, 1.0f, 0.0f);
    
    /** definition of the color green */
    private static final Color3f GREEN = new Color3f(0.0f, 1.0f, 0.0f);
    
    /** Creates a new unit sphere */
    public Sphere(String name) {
        this(name, 1, 16);
//        this.getDefaultMaterial().setMaterialMode(
//                Material.MaterialMode.USE_VERTEX_COLORS_ONLY);
    }

    /** 
     * Creates a new instance of Cube
     * 
     * @param size the size of the cube
     */
    public Sphere(String name, float radius, int segments) {
    	super(name);
//        this.getDefaultMaterial().setMaterialMode(
//                Material.MaterialMode.USE_VERTEX_COLORS_ONLY);
    	setRadius(radius);
        setSegments(segments);
    }
    
    /** "Calculates" the cube */
    public void update() {

    	/* clear the mesh buffer */
    	clear();
    	
        /* Die Buffer fuer diese Sphere erzeugen.
         * Eine Sphere besteht aus insgesamt (segments * segments / 2) 
         * quadratischen Flaechen. Fuer die Erstellung mit Dreiecksflächen
         * werden (segments * segments / 2) * 2 Flaechen benoetigt.
         */
        final int numFaces = segments * segments;
        Point3f[] lvertices = new Point3f[numFaces];
        Point3f[] normals = new Point3f[numFaces];
        
        /* Die Vertices erstellen und dem Mesh hinzufuegen.
         * Alle Vertices werden ausgehend vom Mittelpunkt der Sphere angeordnet.
         */
        
        final float radiusDelta = 180.0f / (segments / 2);  // Winkelscritte pro Ebene
        float angle = 0.0f;         // Startwert fuer den Drehwinkel einer Ebene
        float angleStep = 360.0f / segments;        // Winkelschritt pro Segment
        float angleEbene = 90.0f;                      // Startwinkel der Ebene
        
        int vertexindex = 0;                             // Vertex Index-Counter
        
        Vector3f normal;
        for (int ebene = 0; ebene < (segments / 2 + 1); ebene++) {
            
            final float radiusEbene = this.radius * (float)Math.cos(Math.toRadians(angleEbene));
            
            final float y = radius * (float)Math.sin(Math.toRadians(angleEbene));
            
            for (int i = 0; i < segments; i++) {
                final float x = radiusEbene * (float)Math.cos(Math.toRadians(angle));
                final float z = radiusEbene * (float)Math.sin(Math.toRadians(angle));
                normal = new Vector3f(x, y, z);
                normal.normalize();
                Point3f vertex = new Point3f(x, y, z);
                
                lvertices[vertexindex++] = vertex;
//                System.out.println("Vertex: " + vertex);
                angle += angleStep;
            }
            angleEbene += radiusDelta;
        }
        
        /* Die Faces dieser Sphere erstellen und dem Mesh hinzufuegen. */
        int faceindex = 0;
        final int tsegments = segments - 1;  //
        
        for (int j = 0; j < (segments / 2); j++) {
            
            for (int i = 0; i < tsegments; i++) {
                int p0 = (j + 1) * tsegments + (j + i + 1);
                int p1 = ((j * tsegments) + i + j);
                int p2 = ((j * tsegments) + (j + i +1));
                int p3 = ((j + 1) * tsegments + (j + i + 2));
                
                addFace(new Face(
                        new Point3f[] {lvertices[p0], lvertices[p1], lvertices[p2]},
                        new Color3f[] {YELLOW, GREEN, YELLOW}
                ));
                addFace(new Face(
                        new Point3f[] {lvertices[p2], lvertices[p3], lvertices[p0]},
                        new Color3f[] {YELLOW, RED, YELLOW}
                ));
                
                
            }
            int p0 = ((j + 2) * tsegments + (j + 1));
            int p1 = ((j + 1) * tsegments) + j;
            int p2 = ((j * tsegments) + j);
            int p3 = (j + 1) * tsegments + (j + 1);
            addFace(new Face(new Point3f[] {lvertices[p0], lvertices[p1], lvertices[p2]},
                    new Color3f[] {GREEN, YELLOW, GREEN}
            ));
            addFace(new Face(new Point3f[] {lvertices[p2], lvertices[p3], lvertices[p0]},
                    new Color3f[] {RED, YELLOW, RED}
            ));
            
        }
    }
    

    
    /**
     * Sets the radius of this sphere.
     * 
     * @param radius the radius to be set.
     */
    public final void setRadius(float radius) {
        this.radius = radius;
        update();
    }

    /**
     * Returns the radius of this sphere.
     * 
     * @return the radius of this sphere.
     */
    public float getRadius() {
        return this.radius;
    }
    
    /**
     * Returns the number od segments of this sphere.
     * @return the number of segments of this sphere.
     */
    public int getSegments() {
        return segments;
    }

    /**
     * Sets the number of segments of this sphere.
     * @param segments  the number of segments to be set.
     */
    public final void setSegments(int segments) {
        this.segments = segments;
        update();
    }
}
