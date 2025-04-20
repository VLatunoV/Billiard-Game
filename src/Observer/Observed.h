#pragma once
#include <vector>

template <typename T>
class Observed {
protected:
	template<typename... MArgs, typename... Args>
	void Notify(void (T::*method)(MArgs...), Args&&... args) const {
		for (const auto& o : observers) {
			(o->*method)(std::forward<Args>(args)...);
		}
	}

	void RegisterObserver(T* o) {
		observers.push_back(o);
	}

private:
	std::vector<T*> observers;
};

using MouseObserved = Observed<class MouseObserver>;
using KeyboardObserved = Observed<class KeyboardObserver>;
