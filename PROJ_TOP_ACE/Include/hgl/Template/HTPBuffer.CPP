#ifndef HGL_HTP_BUFFER_CPP
#define HGL_HTP_BUFFER_CPP

#include<hgl/TileLibrary.H>
#include<hgl/ObjectBuffer.H>
#include<hgl/ResManage.H>
namespace hgl
{
    class HTPBuffer:public FinUseData<String,HTP *>
    {
		typedef FinUseData<String,HTP *> fud_class;

        HAC *hac;
        TileLibrary *lib;

    private:

        bool Create(const String &filename,HTP *&htp)
        {
            htp=new HTP(lib,hac,filename);

            return(true);
        }

    	void Clear(const String &filename,HTP *&htp)
        {
            delete htp;
        }

    public:

        HTPBuffer(HAC *hac_pack,const wchar_t *lib_name,int memory_limit,int max_count):FinUseData<String,HTP *>(max_count)
        {
            hac=hac_pack;

            lib=new TileLibrary;

            if(!lib->Open(hac,lib_name,memory_limit))
            {
                delete lib;
                lib=NULL;
            }
        }

        ~HTPBuffer()
        {
            SAFE_CLEAR(lib);

		    fud_class::Clear();
        }
    };//class HTPBuffer

    class HTPResManage:public ResManage<String,HTP>
    {
        HAC *hac;
        TileLibrary *lib;

    private:

		HTP *Create(const String &filename)
        {
            return(new HTP(lib,hac,filename));
        }

		void Clear(HTP *htp)
        {
            delete htp;
        }

    public:

        HTPResManage(HAC *hac_pack,const wchar_t *lib_name,int memory_limit)
        {
            hac=hac_pack;

            lib=new TileLibrary;

            if(!lib->Open(hac,lib_name,memory_limit))
            {
                delete lib;
                lib=NULL;
            }
        }

        ~HTPResManage()
        {
            SAFE_CLEAR(lib);
        }
    };//class HTPResManage
}//namespace hgl
#endif//HGL_HTP_BUFFER_CPP

