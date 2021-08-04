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

import cgr.geometry.primitives.ICone;

/**
 *
 * @author Carsten Wolters
 * @since 23. Maerz 2007, 03:06
 * @version 0.1
 */
public class Cone extends Cylinder implements ICone {
    
    /** Erzeugt einen neuen Cylinder */
    public Cone(String name) {
    	super(name);
        super.radiusTop = 0.0f;
        update();
    }
    
    /** Erzeugt einen neuen Cylinder mit dem uebergebenen Namen. */
    public Cone(String name, float radius, float height, int segments) {
    	super(name);
        super.radiusBottom = radius;
        super.radiusTop = 0.0f;
        super.height = height;
        super.segments = segments;
        update();
    }
    
    @Override
    public void setRadius(float value) {
        super.radiusBottom = value;
        update();
    }
}