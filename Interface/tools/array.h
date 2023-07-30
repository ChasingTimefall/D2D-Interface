#pragma once

#include "../core/core.h"

template <class T, size_t Size>
class TArray {
public:
	TArray() {

		if (!Memory)
			Memory = new T[Size];

		if (!ExchangeMemory)
			ExchangeMemory = new T[Size];

		Clear();
	}

	~TArray()
	{
		if (Memory)
			delete[] Memory;

		if (ExchangeMemory)
			delete[] ExchangeMemory;

	}
	TArray(const TArray<T, Size>& Other) {

		Clear();

		if (!Other.IsEmpty())
		{
			RtlCopyMemory(Base(), Other.Base(), sizeof T * Other.ArraySize());
			sizeCurrent = Other.sizeCurrent;
		}

	}

public:

	bool Find(const T& Data) {

		if (IsEmpty())
			return false;

		for (size_t Current = 0; Current < sizeCurrent; Current++)
		{
			if (Memory[Current] == Data)
				return true;

		}

		return false;
	}
	void CopyTo(TArray<T, Size>& Other) {

		Other.Clear();

		if (!sizeCurrent)
			return;

		Other.sizeCurrent = sizeCurrent;

		RtlCopyMemory(Other.Base(), Base(), sizeof(T) * sizeCurrent);
	}

	bool Contains(const T& Value) {

		if (IsEmpty())
			return false;

		for (int Current = 0; Current < sizeCurrent; Current++)
		{
			if (memcmp(&Memory[Current], &Value, sizeof(T)) == 0)
				return true;
		}

		return false;
	}

	void Swap(TArray<T, Size>& Other) {

		size_t SizeThis = sizeCurrent;
		size_t SizeOther = Other.sizeCurrent;

		if (!IsEmpty())
			RtlCopyMemory((void*)Other.ExchangeMemory, (void*)Memory, sizeof T * sizeCurrent);


		if (!Other.IsEmpty())
			RtlCopyMemory((void*)ExchangeMemory, (void*)Other.Memory, sizeof T * Other.sizeCurrent);

		Other.sizeCurrent = SizeThis;
		sizeCurrent = SizeOther;

		if (!IsEmpty())
			RtlCopyMemory((void*)Memory, (void*)ExchangeMemory, sizeof T * sizeCurrent);

		if (!Other.IsEmpty())
			RtlCopyMemory((void*)Other.Memory, (void*)Other.ExchangeMemory, sizeof T * Other.sizeCurrent);

	}

public:

	T* Base() {
		return Memory;
	}

	size_t ArraySize() {
		return sizeCurrent;
	}

	void Clear() {

		if (sizeCurrent)
		{
			RtlSecureZeroMemory(Memory, sizeof T * Size);
			RtlSecureZeroMemory(ExchangeMemory, sizeof T * Size);
			sizeCurrent = 0;
		}
	}

	bool IsEmpty() {
		return sizeCurrent <= 0;
	}

	bool IsFull() {
		return sizeCurrent >= Size;
	}

public:

	T* AddBack(const T& Value) {

		if (IsFull())
			return nullptr;

		RtlCopyMemory(&Memory[sizeCurrent], &Value, sizeof T);
		sizeCurrent++;

		return Back();
	}

	T* PopAt(const size_t Index) {

		if (Index >= sizeCurrent)
			return nullptr;

		if (sizeCurrent == 1 || sizeCurrent - 1 == Index)
			return PopBack();

		if (Index == 0)
			return PopFront();

		RtlCopyMemory(ExchangeMemory, &Memory[Index + 1], sizeof T * (sizeCurrent - Index));
		RtlCopyMemory(&Memory[Index], ExchangeMemory, sizeof T * (sizeCurrent - Index));

		sizeCurrent -= 1;

		return ObjectAt(Index);
	}

	T* PopBack() {

		if (IsEmpty())
			return nullptr;

		--sizeCurrent;
		RtlSecureZeroMemory(&Memory[sizeCurrent], sizeof T);

		return Back();
	}

	T* AddFront(const T& Value) {

		if (IsFull())
			return nullptr;

		if (!IsEmpty())
		{
			RtlCopyMemory(ExchangeMemory, Memory, sizeof T * sizeCurrent);
			RtlCopyMemory(&Memory[1], ExchangeMemory, sizeof T * sizeCurrent);
			RtlCopyMemory(&Memory[0], &Value, sizeof T);
		}

		RtlCopyMemory(&Memory[0], &Value, sizeof T);

		sizeCurrent++;
	}

	T* PopFront() {

		if (IsEmpty())
			return nullptr;

		if (sizeCurrent == 1)
			return PopBack();
		else {

			RtlCopyMemory(ExchangeMemory, Memory, sizeof T * sizeCurrent);
			RtlCopyMemory(&Memory[0], &ExchangeMemory[1], sizeof T * (sizeCurrent - 1));

			--sizeCurrent;

		}

		return Front();
	}

public:

	T* Back() {

		if (IsEmpty())
			return nullptr;

		return ObjectAt(sizeCurrent - 1);
	}

	T* Front() {

		if (IsEmpty())
			return nullptr;

		return ObjectAt(0);
	}

	T* ObjectAt(const int Index) {
		return &Memory[Index];
	}

	T* operator[](const int Index) {
		return ObjectAt(Index);
	}

private:
	T* Memory;
	T* ExchangeMemory;
	size_t sizeCurrent = 0;
};