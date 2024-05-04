#ifndef RANDOM_ARRAY_ADT_H
#define RANDOM_ARRAY_ADT_H

template <typename T>
class RandomArrayADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool insert(const T&) = 0;
	virtual bool peek(T&) const = 0;
	virtual bool remove(T&) = 0;
	virtual int length() const = 0;
	virtual void printAll() const = 0;
	virtual ~RandomArrayADT() {}
};

#endif