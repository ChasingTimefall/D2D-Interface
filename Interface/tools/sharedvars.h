#pragma once
#include "../core/core.h"
#include <shared_mutex>

template <class T>
class CSharedVariable {
public:

	CSharedVariable() {
		RtlZeroMemory(&Var,sizeof T);
	}

	void operator=(const T& Other)
	{
		SetLocked(Other);
	}

	T GetLocked() {

		std::unique_lock<std::shared_mutex> LockGuard(Mutex);
		T VarMove;
		RtlCopyMemory(&VarMove,&Var,sizeof(T));
		return VarMove;
	}

private:
	void SetLocked(const T& Other)
	{
		std::unique_lock<std::shared_mutex> LockGuard(Mutex);
		RtlCopyMemory(&Var, &Other, sizeof(T));
	}

private:
	T Var;
	std::shared_mutex Mutex;
};