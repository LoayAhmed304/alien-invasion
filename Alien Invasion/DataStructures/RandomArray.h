#ifndef RANDOM_ARRAY_H
#define RANDOM_ARRAY_H

#include "RandomArrayADT.h"
template <typename T>
class RandomArray : public RandomArrayADT<T> 
{
	enum { MAX_SIZE = 1000 };
private:
	T* arr;
	int count;
public:
	RandomArray() 
	{
		arr = new T[MAX_SIZE];
		count = 0;
		srand(time(0));
	}
	bool isEmpty()  const
	{
		return (count == 0);
	}

	bool insert(const T& item)
	{
		if (count < MAX_SIZE)
		{
			arr[count++] = item;
			return true;
		}
		return false;
	}

	bool peek(T& item) const
	{
		if (count)
		{
			int index = rand() % count;
			item = arr[index];
			return true;
		}
		return false;
	}

	bool remove(T& item) 
	{
		if (count)
		{
			int index = rand() % count;
			item = arr[index];
			arr[index] = arr[--count];
			return true;
		}
		return false;
	}

	int length() const
	{
		return count;
	}

	void printAll() const
	{
		if (isEmpty())
			return;
		cout << arr[0];
		for (int i = 1; i < count; i++)
		{
			cout << ", " << arr[i];
		}
	}

	~RandomArray() 
	{
		delete [] arr;
	}
};

#endif