#ifndef SINGLETON_H
#define SINGLETON_H

/*==============================================================================================#
|                                                                                               |
| Copyright (c) 2019 Karsten Vermeulen. All rights reserved.                                    |
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade Lite' game engine,    |
| for the purposes of educating other fellow programmers, programming students and anyone else  |
| wishing to learn about game development, C++ and OOP. The structure of the engine, class      |
| design and overall code is constantly under development.                                      |
|                                                                                               |
| Designed to teach. Made from scratch. Built by hand.  						                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade Lite' and wish to show your support, if you have any questions about    |
| the project, or if you just want to reach out, please find me on the following channels:      |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Singleton' source files last updated in June 2019 									        |
#==============================================================================================*/

template <class T>
class Singleton
{

public:

	static T* Instance();	

private:

	Singleton() {}
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

};

//------------------------------------------------------------------------------------------------------
//template function that will create an instance of any type and return its address
//------------------------------------------------------------------------------------------------------
template <class T> T* Singleton<T>::Instance()
{

	//declare a pointer to the object and assign it a NULL value
	//this will happen only once, ie the first iteration of this function
	static T* s_singletonObject = nullptr;

	//check if pointer is NULL, and if it is, instantiate the object
	if (!s_singletonObject)
	{
		s_singletonObject = new T();
	}

	//alternatively just return the address
	return s_singletonObject;

}

#endif