#ifndef Array_H
#define Array_H

#include <cstdio>
#include <exception>

// ----------------------------------------------------------------------------
// Templated dynamic array
// ----------------------------------------------------------------------------

#include <cassert>

template<typename T>
class Array
{
private:
	T* mData;
	int mSize;
	int mCapacity;

	static const int MIN_CAPACITY = 32;

public:
	Array()
		: mData(nullptr)
		, mSize(0)
		, mCapacity(0)
	{
	}

	virtual ~Array()
	{
		if (mData && mSize > 0)
			delete[] mData;
	}

	Array(const Array<T>& copyFrom)
	{
		this->operator=(copyFrom);
	}

	inline Array<T>& operator = (const Array<T>& rhs)
	{
		if (mData && mSize > 0)
			delete[] mData;

		mSize = rhs.mSize;
		mCapacity = rhs.mCapacity;

		mData = new T[mCapacity];

		for (int i = 0; i < mSize; i++)
		{
			mData[i] = rhs[i];
		}

		// For supporting things like a = b = c;
		return *this;
	}

	void Add(const T& item)
	{
		// Reallocate memory if current capacity is exceeded
		if (mSize + 1 >= mCapacity)
			ResizeGrow(2 * mCapacity);

		mData[mSize] = item;
		mSize++;
	}

	void ResizeGrow(int newSize)
	{
		if (newSize < MIN_CAPACITY)
			newSize = MIN_CAPACITY;

		if (newSize > mCapacity)
		{
			T* pNewDataBuf = new T[newSize];
			if (mSize > 0)
			{
				for (int i = 0; i < mSize; i++)
				{
					pNewDataBuf[i] = mData[i];
				}
			}

			if (mData)
				delete[] mData;

			mData = pNewDataBuf;
			mCapacity = newSize;
		}
	}

	template <typename Compare>
	void Sort(Compare cmp)
	{
		// Bubble sort
		for (int i = 0; i < Size(); i++)
		{
			for (int j = i + 1; j < Size(); j++)
			{
				if (cmp(mData[i], mData[j]))
				{
					T tmp = mData[i];
					mData[i] = mData[j];
					mData[j] = tmp;
				}
			}
		}
	}

	inline const T& operator [] (const int index) const
	{
		assert(index < mSize);

		return mData[index];
	}

	inline T& operator [] (const int index)
	{
		assert(index < mSize);

		return mData[index];
	}

	int Size() const
	{
		return mSize;
	}

	const T& Last() const
	{
		return mData[mSize - 1];
	}

	T& Last()
	{
		return mData[mSize - 1];
	}

	// Data buffer accessor
	const T* Data() const
	{
		return mData;
	}

	T* Data()
	{
		return mData;
	}
};
#endif