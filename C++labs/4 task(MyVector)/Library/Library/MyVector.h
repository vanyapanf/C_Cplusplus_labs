#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
template<class T>
class VectorIt {
private:
	T* t;
public:
	VectorIt() :t(nullptr) {};
	VectorIt(T* tt) :t(tt) {};
	T& operator *() const;
	//T* operator ->() const;
	VectorIt& operator ++();
	VectorIt& operator =(const VectorIt& it) const;
	bool operator ==(const VectorIt& it) const;
	bool operator !=(const VectorIt& it) const;
};
template<class T>
T& VectorIt<T>::operator *()const {
	if (t == nullptr)
		throw std::exception("pointer is nullptr");
	return (*t);
}
template<class T>
T* VectorIt<T>::operator ->() const {//?
}
template<class T>
VectorIt& VectorIt<T>::operator =(const VectorIt& it) const {
	t = it;
	return t;
}
template<class T>
VectorIt& VectorIt<T>::operator ++() {
	if (t== nullptr)
		throw std::exception("pointer is nullptr");
	return(++t);
}
template<class T>
bool VectorIt<T>::operator ==(const VectorIt& it) const {
	if (t == it)
		return true
	else return false;
}
template<class T>
bool VectorIt<T>::operator !=(const VectorIt& it) const {
	if (t == it)
		return false
	else return true;
}
template<class T>
class Vector {
private:
	const int SZ=100;
	int kol;
	T* t;
public:
	friend class VectorIt<T>;
	typedef VectorIt<T> iterator;
	iterator begin();
	iterator end();
	void erase(iterator);
	void push_back(T*);
	~vector() { delete[] t; };
};
template<class T>
Vector<T>::iterator Vector<T>::begin() {
	Vector<T>::iterator it;
	it = t;
	return it;
}
template<class T>
Vector<T>::iterator Vector<T>::end() {
	Vector<T>::iterator it;
	int i = 0;
	for (it = begin(); i != kol; ++it, ++i);
	return it;
}
template<class T>
void Vector<T>::erase(Vector<T>::iterator it) {
	Vector<T>::iterator it1=it;
	Vector<T>::iterator it2 = it;
	delete it;
	if ((++it2) == end()) {
		--kol;
		return it;
	}
	for (; it2 != end(); ++it2) {
		*it1 = *it2;
		it1 = it2;
	}
	--kol;
	return it;
}
template<class T>
void Vector<T>::push_back(T* t) {
	Vector<T>::iterator it = end();
	*it = t;
	++kol;
	return t;
}
#endif VECTOR_H

