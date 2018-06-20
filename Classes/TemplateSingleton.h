#pragma once

template <class T>
class TemplateSingleton
{
protected:
	TemplateSingleton() {};
	~TemplateSingleton() {};

public:
	static T * getInstance()
	{
		if (_sharedInstance == nullptr)
			_sharedInstance = new (std::nothrow) T;

		return _sharedInstance;
	}

	static void destroyInstance()
	{
		if (_sharedInstance != nullptr)
		{
			delete _sharedInstance;
			_sharedInstance = nullptr;
		}
	}
private:
	static T * _sharedInstance;
};
template <class T>
T * TemplateSingleton<T>::_sharedInstance = nullptr;