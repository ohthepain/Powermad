// Vector.h

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "myassert.h"

namespace Atomic
{
	template<class T> class Vector
	{
	public:
		Vector();
		~Vector();

		void Add(T value);
		void Remove(T value);
		T& operator[](int index);
		const T& operator[](int index) const;
		void Clear();
		size_t GetSize() const { return mSize; }

	private:
		T* mNodes;
		size_t mSize;
		size_t mCapacity;
	};
}


namespace Atomic
{
  template<class T> Vector<T>::Vector()
  : mNodes(nullptr)
  , mSize(0)
  , mCapacity(0)
  {
  }

  template<class T> Vector<T>::~Vector()
  {
    delete [] mNodes;
    mNodes = nullptr;
  }

  template<class T> void Vector<T>::Add(T value)
  {
    if (mSize == mCapacity)
    {
      int newsize = mCapacity * 2 + 2;
      T* newNodes = new T[newsize];
      for (size_t i=0; i<mCapacity; i++)
      {
        newNodes[i] = mNodes[i];
      }
      delete [] mNodes;
      mNodes = newNodes;
      mCapacity = newsize;
    }
    mNodes[mSize++] = value;
  }
  
  template<class T> void Vector<T>::Remove(T value)
  {
    bool found = false;
    for (size_t i=0; i<mSize; i++)
    {
      found = found || mNodes[i] == value;
      if (found && i < mSize - 1)
      {
        mNodes[i] = mNodes[i+1];
      }
    }
    myassert(found);
    if (found)
    {
      --mSize;
    }
  }
  
  template <class T> T& Vector<T>::operator[](int index)
  {
    myassert((size_t)index < mSize);
    return mNodes[index];
  }
 
  template <class T> const T& Vector<T>::operator[](int index) const
  {
    myassert((size_t)index < mSize);
    return mNodes[index];
  }

  template<class T> void Vector<T>::Clear()
  {
    mSize = 0;
  }
}