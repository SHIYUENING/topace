#ifndef HGL_UNIX_RWLOCK_INCLUDE
#define HGL_UNIX_RWLOCK_INCLUDE

namespace hgl
{
	struct unix_rwlock;
	
    /**
    * UNIX版共享锁
    */
    class UnixRWLock                                                                                 ///共享锁(只有一个可写，但可以有多个在读)
    {
        unix_rwlock *rwlock

    public:

        UnixRWLock();
        ~UnixRWLock();

        bool ReadLock();                                               								///<读锁定
        bool TryReadLock();																			///<尝试读锁定

        bool WriteLock();                                             								///<写锁定
        bool TryWriteLock();                                                   						///<尝试写锁定

        bool Unlock();                                                                              ///<解锁
    };

    #define RWLock UnixRWLock
}//namespace hgl
#endif//HGL_UNIX_RWLOCK_INCLUDE
