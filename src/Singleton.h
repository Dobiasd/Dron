#ifndef SINGLETON_H_
#define SINGLETON_H_

/*
 * Scott Meyer's singleton
 */
template<typename C>
class Singleton
{
public:
	static C& Instance()
	{
		static C singleton;
		return singleton;
	}
protected:
	Singleton()
	{
	}
};

#endif /* SINGLETON_H_ */
