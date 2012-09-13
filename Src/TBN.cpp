#include "TBN.h"
#include "Mathematics.h"

#include"EasyMatrix.h"
CTBN::CTBN(void)
{
}

CTBN::~CTBN(void)
{
}
void CTBN::TBN(void)
{
    Matrix44d UV;
    UV = TexCoordsInToTBN[0][0], TexCoordsInToTBN[1][0], TexCoordsInToTBN[2][0], 0,
         TexCoordsInToTBN[0][1], TexCoordsInToTBN[1][1], TexCoordsInToTBN[2][1], 0,
                              0,                      0,                      0, 1,
                              1,                      1,                      1, 0;
    Vector3d AB;
    AB = VerticesInToTBN[1][0] - VerticesInToTBN[0][0],
         VerticesInToTBN[1][1] - VerticesInToTBN[0][1],
         VerticesInToTBN[1][2] - VerticesInToTBN[0][2];

    Vector3d AC;
    AC = VerticesInToTBN[2][0] - VerticesInToTBN[0][0],
         VerticesInToTBN[2][1] - VerticesInToTBN[0][1],
         VerticesInToTBN[2][2] - VerticesInToTBN[0][2];
    
    Vector3d n;
    n = normalize(cross(AB, AC));

    Matrix44d XYZ;
    XYZ = VerticesInToTBN[0][0],  VerticesInToTBN[1][0],  VerticesInToTBN[2][0], n(0),
          VerticesInToTBN[0][1],  VerticesInToTBN[1][1],  VerticesInToTBN[2][1], n(1),
          VerticesInToTBN[0][2],  VerticesInToTBN[1][2],  VerticesInToTBN[2][2], n(2),
                              1,                      1,                      1,    0;

    Matrix44d M;
    M = XYZ * inverse(UV);
    
    Vector4d TInTex;
    TInTex = 1, 0, 0, 0;

    Vector4d T;
    T = M * TInTex;

    TBNout[0] = (float)T(0);
    TBNout[1] = (float)T(1);
    TBNout[2] = (float)T(2);
}
