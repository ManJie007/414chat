#pragma once
#include<pthread.h>
template<typename T>
class Singleton
{
public:
	static T& Instance()
	{
		pthread_once(&ponce_, &Singleton::init);
		// if (nullptr == value_)
		// {
		// 	value_ = new T();
		// }
		return *value_;
	}
	Singleton()=delete;
private:
	~Singleton() = default;

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	//要写成静态方法的原因：类成员函数隐含传递this指针（第一个参数）
	//而pthread_once函数标签为int pthread_once(pthread_once_t once_control, void (init_routine) (void))；
	static void init()
	{
		value_ = new T();
		//::atexit(destroy);
	}

	static void destroy()
	{
		delete value_;
	}
	static pthread_once_t ponce_;
	static T*             value_;
};

//template<typename T>
//pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = nullptr;