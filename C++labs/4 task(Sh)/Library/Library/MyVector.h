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
	T* operator ->() const;
	VectorIt& operator ++();
	VectorIt& operator =(const VectorIt& it);
	bool operator ==(const VectorIt& it)const;
	bool operator !=(const VectorIt& it)const;
};
template<class T>
T& VectorIt<T>::operator *()const {
	if (t == nullptr)
		throw std::exception("pointer is nullptr");
	return (*t);
}
template<class T>
T* VectorIt<T>::operator ->() const {//?
	return t;
}
template<class T>
VectorIt<T>& VectorIt<T>::operator =(const VectorIt& it)  {
	t = it.t;
	return *this;
}
template<class T>
VectorIt<T>& VectorIt<T>::operator ++() {
	if (t == nullptr)
		throw std::exception("pointer is nullptr");
	++t;
	return(*this);
}
template<class T>
bool VectorIt<T>::operator ==(const VectorIt& it)const {
	if (t == it.t)
		return true;
	else return false;
}
template<class T>
bool VectorIt<T>::operator !=(const VectorIt& it)const {
	if (t == it.t)
		return false;
	else return true;
}
template<class T>
class Vector {
private:
	const int SZ = 100;
	int kol;
	T *t;
public:
	friend class VectorIt<T>;
	typedef VectorIt<T> iterator;
	Vector();
	iterator begin();
	iterator end();
	iterator erase(iterator);
	iterator push_back(const T&);
	~Vector(){ delete[] t; };
};
template<class T>
Vector<T>::Vector() {
	kol = 0;
	t = new T[ SZ ];
}
template<class T>
typename Vector<T>::iterator Vector<T>::begin() {
	Vector<T>::iterator it(t);
	return it;
}
template<class T>
typename Vector<T>::iterator Vector<T>::end() {
	Vector<T>::iterator it(t+kol);
//	int i = 0;
//	for (it =/*(*this)->*/begin(); i != kol; ++it, ++i);
	return it;
}
template<class T>
typename Vector<T>::iterator Vector<T>::erase(typename Vector<T>::iterator it) {
	typename Vector<T>::iterator it1 = it;
	typename Vector<T>::iterator it2 = it;
	//delete *it;
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
typename Vector<T>::iterator Vector<T>::push_back(const T& p) {
	typename Vector<T>::iterator it =end();
	t[kol] = p;
	++kol;
	return it;
}
#endif VECTOR_H
