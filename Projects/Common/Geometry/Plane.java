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
import cgr.geometry.primitives.IPlane;
import javax.vecmath.Color3f;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;


/**
 *
 * @author Carsten Wolters
 * @since 23. Maerz 2007, 03:06
 * @version 0.1
 */
public class Plane extends Mesh implements IPlane {

    /** Die Breite dieser Plane. */
    private float width;
    
    /** Die Laenge dieser Plane. */
    private float length;
    
    /** Anzahl der Segmente entlang der x-Achse. */
    private int segX;
    
    /** Anzahl der Segmente entlang der y-Achse. */
    private int segZ;
    
    /** definition of the color red */
    private static final Color3f RED = new Color3f(1.0f, 0.0f, 0.0f);
    
    /** definition of the color yellow */
    private static final Color3f YELLOW = new Color3f(1.0f, 1.0f, 0.0f);
    
    /** definition of the color green */
    private static final Color3f GREEN = new Color3f(0.0f, 1.0f, 0.0f);
    
    /** definition of the color blue */
    private static final Color3f BLUE = new Color3f(0.0f, 0.0f, 1.0f);
        
    /** Erzeugt eine neue Plane */
    public Plane(String name) {
    	super(name);
        this.width = 2.0f;
        this.length = 2.0f;
        this.segX = 2;
        this.segZ = 2;
        update();
    }
    
    /**
     * Erzeugt eine neue Plane mit dem uebergebenen Namen.
     * @param name  der Name der zu erzeugenen Plane.
     */
    public Plane(String name, float width, float length, int segX, int segZ) {
    	super(name);
        this.width = width;
        this.length = length;
        this.segX = segX;
        this.segZ = segZ;
        update();
    }
    
    /**
     * Diese Methode berechnet die Vertices und deren Zuordnung zu den Faces
     * dieser Plane.
     */
    public void update() {

        super.clear();
        
        Point3f[] lvertices = new Point3f[(segX + 1) * (segZ + 1)];
        /* Die Vertices erstellen und dem Mesh hinzufuegen.
         * Alle Vertices werden ausgehend vom Mittelpunkt der Plane angeordnet.
         */
        final float segmentWidth = (width / segX);
        final float segmentLength = (length / segZ);
        final float widthOffset = -width / 2;
        final float lengthOffset = -length / 2;
        Vector3f normal;
        normal = new Vector3f(0, 1, 0);
        normal.normalize();
        for (int j = 0; j <= segZ; j ++) {
            int segmentOffset = j * (segX + 1);
            for (int i = 0; i <= segX; i++) {
                int vertexIndex = segmentOffset + i;
                float vx = widthOffset + segmentWidth * i;
                float vy = 0.0f;
                float vz = lengthOffset + segmentLength * j;
                
//                System.out.println("Vertex: " + vertexIndex + "\tKoords: " + vx + " " + vy + " " + vz);
                lvertices[vertexIndex] = new Point3f(vx, vy, vz);
            }
        }
        
        
        
        /* Die Faces dieser Plane erstellen und dem Mesh hinzufuegen. */
        for (int j = 0; j < segZ; j++) {
            
            for (int i = 0; i < segX; i++) {
                int p3 = (j + 1) * segX + (j + i + 1);
                int p2 = ((j * segX) + i + j);
                int p1 = ((j * segX) + (j + i +1));
                int p0 = ((j + 1) * segX + (j + i + 2));

                addFace(new Face(new Point3f[] {lvertices[p0], lvertices[p1], lvertices[p2]},
                        new Color3f[] {GREEN, YELLOW, RED},
                        new Vector3f[] {normal, normal, normal}));
                addFace(new Face(new Point3f[] {lvertices[p2], lvertices[p3], lvertices[p0]},
                        new Color3f[] {BLUE, GREEN, RED},
                        new Vector3f[] {normal, normal, normal}));
            }
        }
    }

    /**
     * sets the width of this plane.
     * @param value  the width of this plane.
     */
    @Override
    public void setWidth(float value) {
        width = value;
        update();
    }

    /**
     * gets the width of this plane.
     * @return  the width of this plane.
     */
    @Override
    public float getWidth() {
        return width;
    }
    
    /**
     * sets the height of this plane.
     * @param value  the height of this plane.
     */
    @Override
    public void setHeight(float value) {
        length = value;
        update();
    }

    /**
     * gets the height of this plane.
     * @return  the height of this plane
     */
    @Override
    public float getHeight() {
        return length;
    }
    
    /**
     * sets the number of segments in x-direction.
     * @param value  number of segments in x-direction.
     */
    @Override
    public void setSegX(int value) {
        this.segX = value;
        update();
    }
    
    /**
     * gets the number of segments in x-direction.
     * @return  number of segments in x-direction
     */
    @Override
    public int getSegX() {
        return this.segX;
    }
    
    /**
     * sets the number of segments in y-direction.
     * @param value  number of segments in x-direction.
     */
    @Override
    public void setSegZ(int value) {
        this.segZ = value;
        update();
    }
    
    /**
     * gets the number of segments in y-direction.
     * @return  number of segments in y-direction
     */
    @Override
    public int getSegZ() {
        return this.segZ;
    }
}
