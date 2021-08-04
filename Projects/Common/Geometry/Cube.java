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

import cgr.geometry.primitives.ICube;

/**
 *
 * @author Carsten Wolters <carsten.wolters at ca-wo.de>
 * @since 23. Maerz 2007, 03:06
 * @version 0.1
 */
public class Cube extends Cuboid implements ICube {
    
    private float size;

    public Cube(String name) {
    	super(name);
        this.size = 1.0f;
        update();
    }
    
    public Cube(String name, float size) {
    	super(name);
        this.size = size;
        update();
    }
    
    @Override
    public final void update() {
        super.width = size / 2;
        super.depth = size / 2;
        super.height = size / 2;
        super.update();
    }
    /**
     * Sets the width of this cube
     * 
     * @param width the width to set
     */
    @Override
    public void setSize(float size) {
        this.size = size;
        update();
    }

    /**
     * Returns the width of this cube
     * 
     * @return the width of this cube
     */
    @Override
    public float getSize() {
        return this.size;
    }
}
