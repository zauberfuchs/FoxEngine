
#include "Plane.h"
#include <stdio.h>


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

namespace CG221 {

    //////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////

    Plane::Plane(CG221::Vector3f &v1, CG221::Vector3f &v2, CG221::Vector3f &v3) {

        set3Points(v1, v2, v3);
    }

    Plane::Plane() {
    }

    Plane::~Plane() {
    }

    void Plane::set3Points(CG221::Vector3f &v1, CG221::Vector3f &v2, CG221::Vector3f &v3) {


        CG221::Vector3f aux1, aux2;

        aux1 = v1 - v2;
        aux2 = v3 - v2;

        //normal = aux2 * aux1;
        normal = CG221::CrossProduct(aux2, aux1);

        normal.normalize();
        point.copy(v2);
        //d = -(normal.innerProduct(point));
        d = -(normal.DotProduct(point));
    }

    void Plane::setNormalAndPoint(CG221::Vector3f &normal, CG221::Vector3f &point) {

        this->normal.copy(normal);
        this->normal.normalize();
        //d = -(this->normal.innerProduct(point));
        d = -(this->normal.DotProduct(point));
    }

    void Plane::setCoefficients(float a, float b, float c, float d) {

        // set the normal vector
        normal.set(a, b, c);
        //compute the lenght of the vector
        float l = normal.length();
        // normalize the vector
        normal.set(a / l, b / l, c / l);
        // and divide d by th length as well
        this->d = d / l;
    }

    float Plane::distance(CG221::Vector3f &p) {
        //return (d + normal.innerProduct(p));
        return (d + normal.DotProduct(p));
    }

    //void Plane::print()
    //{
    //	printf("Plane(");normal.print();printf("# %f)",d);
    //}


    //////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////

} // namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
