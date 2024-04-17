#ifndef RANDOM_ARRAY_H
#define RANDOM_ARRAY_H

#include "ArrayADT.h"
template <typename T>
class RandomArray : public ArrayADT<T> 
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

	bool peek(T& item, int rand) const
	{
		if (count)
		{
			item = arr[rand];
			return true;
		}
		return false;
	}

	bool remove(T& item, int rand) 
	{
		if (count)
		{
			item = arr[rand];
			arr[rand] = arr[--count];
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
};

#endif