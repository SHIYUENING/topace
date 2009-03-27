#include <fstream>
using namespace std;

typedef unsigned char BYTE;
typedef int INT32;
typedef unsigned int UINT32;

BYTE ReadByte(ifstream& ifs){
    BYTE o;
    ifs >> o;
    return o;
}

INT32 ReadInt32(ifstream& ifs){
    INT32 o;
    o = ReadByte(ifs);
    o = o | ((int)(ReadByte(ifs)) << 8);
    o = o | ((int)(ReadByte(ifs)) << 16);
    o = o | ((int)(ReadByte(ifs)) << 24);
    return o;
}

struct BomsSet{
	UINT32 Pnum;
	int RandomSizeMIN;//随机大小最小值
	int RandomSizeMAX;//随机大小最大值
	int RandomMoveMIN;//随机移动量最小值
	int RandomMoveMAX;//随机移动量最大值
	int ShowTimeStart;//开始时间
	int ShowTimeEnd;//结束时间
};
const int MAXBOMS = 200;

void ReadBomsSet(ifstream& ifs, BomsSet& b){
    b.Pnum = 0;
    ReadInt32(ifs);
    b.RandomSizeMIN = ReadInt32(ifs);
    b.RandomSizeMAX = ReadInt32(ifs);
    b.RandomMoveMIN = ReadInt32(ifs);
    b.RandomMoveMAX = ReadInt32(ifs);
    b.ShowTimeStart = ReadInt32(ifs);
    b.ShowTimeEnd = ReadInt32(ifs);
}

void main(){
    ifstream ifs("1.set");
    
    if (ReadInt32(ifs) != 0x00544553){
        return;
    }

    INT32 Count = ReadInt32(ifs);
    if (Count > MAXBOMS){
        Count = MAXBOMS;
    }

    BomsSet BomsSets[MAXBOMS];

    for (int i = 0; i < Count; i += 1){
        ReadBomsSet(ifs, BomsSets[i]);
    }
}