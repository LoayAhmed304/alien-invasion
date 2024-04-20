#ifndef ARRAY_ADT_H
#define ARRAY_ADT_H

template <typename T>
class ArrayADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool insert(const T&) = 0;
	virtual bool peek(T&, int) const = 0;
	virtual bool remove(T&, int) = 0;
	virtual int length() const = 0;
	virtual void printAll() const = 0;
	virtual ~ArrayADT() {}
};

#endif