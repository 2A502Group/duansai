// SingletonObject.h: interface for the CSingletonObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SINGLETONOBJECT_H__6DC9BB6D_46B9_4C24_9E6F_D9859BE58A49__INCLUDED_)
#define AFX_SINGLETONOBJECT_H__6DC9BB6D_46B9_4C24_9E6F_D9859BE58A49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CLASS_UNCOPYABLE(classname) \
	private:\
		classname##(const classname##&);\
		classname##& operator=(const classname##&);

class Mutex
{
	CLASS_UNCOPYABLE(Mutex)
public:
	Mutex() :_cs()	{ ::InitializeCriticalSection(&_cs); }
	~Mutex()		{ ::DeleteCriticalSection(&_cs); }
	void Lock()		{ ::EnterCriticalSection(&_cs); }
	void Unlock()	{ ::LeaveCriticalSection(&_cs); }
private:
	CRITICAL_SECTION _cs;
};

class Lock
{
	CLASS_UNCOPYABLE(Lock)
public:
	Lock(Mutex& cs) :_cs(cs) { _cs.Lock(); }
	~Lock() { _cs.Unlock(); }
private:
	Mutex& _cs;
};


template<class T>
class CSingletonObject  
{
	CLASS_UNCOPYABLE(CSingletonObject)
public:
	static T& Instance()
	{
		if (NULL == _instance)
		{
			Lock lock(_mutex);
			if (NULL == _instance)
			{
				_instance = new T();
				atexit(Destroy);
			}
		}

		return *_instance;
	}
protected:
	CSingletonObject() {}
	virtual ~CSingletonObject() {}

private:
	static void Destroy()
	{
		if (NULL != _instance)
		{
			delete _instance;
			_instance = NULL;
		}
	}

	static Mutex _mutex;
	static T * volatile _instance;
};


template<class T>
Mutex CSingletonObject<T>::_mutex;

template<class T>
T * volatile CSingletonObject<T>::_instance = NULL;


#endif // !defined(AFX_SINGLETONOBJECT_H__6DC9BB6D_46B9_4C24_9E6F_D9859BE58A49__INCLUDED_)
