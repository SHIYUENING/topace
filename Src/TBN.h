//#pragma once
#ifndef CTBN_H
#define CTBN_H
class CTBN
{
public:
	CTBN(void);
	~CTBN(void);
	void TBN(void);
	float VerticesInToTBN[3][3];
	float NormalsInToTBN[3][3];
	float TexCoordsInToTBN[3][2];
	float TBNout[3];
};
#endif