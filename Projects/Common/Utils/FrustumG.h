
#ifndef _FRUSTUMG_
#define _FRUSTUMG_

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#include "CompilerPre.h"

#include "Vector3f.h"
#include "Plane.h"
#include "AABox.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

namespace CG221 {

#ifndef _FRUSTUM_RESULT
#define _FRUSTUM_RESULT

    enum eFrustumResult {
        OUTSIDE, INTERSECT, INSIDE
    };
#endif


    //////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////

    class CG221_API FrustumG {
    private:

        enum {
            TOP = 0,
            BOTTOM,
            LEFT,
            RIGHT,
            NEARP,
            FARP
        };


    public:

        //	enum {OUTSIDE, INTERSECT, INSIDE};

        Plane pl[6];


        CG221::Vector3f ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
        float nearD, farD, ratio, angle, tang;
        float nw, nh, fw, fh;

        FrustumG();
        ~FrustumG();

        void setCamInternals(float angle, float ratio, float nearD, float farD);
        void setCamDef(CG221::Vector3f &p, CG221::Vector3f &l, CG221::Vector3f &u);
        int pointInFrustum(CG221::Vector3f &p);
        int sphereInFrustum(CG221::Vector3f &p, float raio);
        int boxInFrustum(AABox &b);

        //void FrustumG::drawPoints();
        //void FrustumG::drawLines();
        //void FrustumG::drawPlanes();
        //void FrustumG::drawNormals();
    };

    //////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////

} // namespace CG221 {

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#endif