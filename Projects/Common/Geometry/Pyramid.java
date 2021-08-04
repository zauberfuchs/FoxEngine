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

import cgr.geometry.primitives.IPyramid;

/**
 *
 * @author Carsten Wolters
 * @since 23. Maerz 2007, 03:06
 * @version 0.1
 */
public class Pyramid extends Cylinder implements IPyramid {

    /** Erzeugt eine neue Instanz der Klasse Pyramid */
    public Pyramid(String name) {
    	super(name);
        super.radiusTop = 0.0f;
        super.segments = 4;
        update();
    }

    /** Erzeugt eine neue Instanz der Klasse Pyramid
     * und setzt den uebergebenen Namen. */
    public Pyramid(String name, float radius, float height) {
    	super(name);
        super.radiusTop = 0.0f;
        super.radiusBottom = radius;
        super.height = height;
        super.segments = 4;
        update();
    }

    /**
     * Diese Methode setzt die Hoehe dieser Pyramide.
     *
     * @param value  die Hoehe dieser Pyramide.
     */
    @Override
    public void setHeight(float value) {
        this.height = value;
        update();
    }

    /**
     * Diese Methode gibt die Hoehe dieser Pyramide zurueck.
     *
     * @return float  die Hoehe dieser Pyramide.
     */
    @Override
    public float getHeight() {
        return this.height;
    }

    /**
     * Diese Methode setzt die Groesse der Grundflaeche dieser Pyramide.
     *
     * @param float  value die Groesse der Grundflaeche dieser Pyramide.
     */
    @Override
    public void setSize(float value) {
        this.radiusBottom = ((float)((value / 2) * Math.sqrt(2f)));
        update();
    }

    /**
     * Diese Methode gibt die Groesse der Grundflaeche dieser Pyramide zurueck.
     *
     * @return float  die Groesse der Grundflaeche dieser Pyramide.
     */
    @Override
    public float getSize() {
        return ((float)((2 * this.radiusBottom) / Math.sqrt(2f)));
    }

}
