#ifndef HGL_WINDOWS_RWLOCK_INCLUDE
#define HGL_WINDOWS_RWLOCK_INCLUDE
namespace hgl
{
    /**
    * Windows版共享锁
    */
    class WinRWLock                                                                                 ///共享锁(只有一个可写，但可以有多个在读)
    {
        void *write_mutex;
        void *read_event;
        volatile int readers;

        bool ReadLock(unsigned int);
        bool WriteLock(unsigned int);

    public:

        WinRWLock();
        ~WinRWLock();

        bool ReadLock(){return ReadLock(0xFFFFFFFF);}                                               ///<读锁定
        bool TryReadLock(){return ReadLock(0);}                                                     ///<尝试读锁定

        bool WriteLock(){return WriteLock(0xFFFFFFFF);}                                             ///<写锁定
        bool TryWriteLock(){return WriteLock(0);}                                                   ///<尝试写锁定

        bool Unlock();                                                                              ///<解锁
    };

    #define RWLock WinRWLock
}//namespace hgl
#endif//HGL_WINDOWS_RWLOCK_INCLUDE

