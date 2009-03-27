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
	int RandomSizeMIN;//�����С��Сֵ
	int RandomSizeMAX;//�����С���ֵ
	int RandomMoveMIN;//����ƶ�����Сֵ
	int RandomMoveMAX;//����ƶ������ֵ
	int ShowTimeStart;//��ʼʱ��
	int ShowTimeEnd;//����ʱ��
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