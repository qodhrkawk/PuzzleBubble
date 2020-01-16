#pragma once

template<typename T, int N>
class VectorN
{
public:
	VectorN() {
		for (int i = 0; i < N; i++)
			value[i] = 0;

	}

	VectorN<T, N>& operator=(const VectorN<T, N>& vec) {
		for (int i = 0; i < N; i++) {
			value[i] = vec.value[i];
		}
		return (*this);
	}

	T& operator[](const int i) {
		return value[i];
	}
	T operator[](const int i) const {
		return value[i];
	}

private:
	T value[N];
};

/* Implement */
template<typename T, int N>
VectorN<T, N> operator+(const VectorN<T, N>& v1, const VectorN<T, N>& v2) {
	VectorN<T, N> v;

	for (int i = 0; i < N; i++)
		v[i] = v1[i] + v2[i];
	return v;


}

template<typename T, int N>
VectorN<T, N> operator-(const VectorN<T, N>& v1, const VectorN<T, N>& v2) {
	VectorN<T, N> v;
	for (int i = 0; i < N; i++)
		v[i] = v1[i] - v2[i];
	return v;
}

template<typename T, int N>
VectorN<T, N> operator-(const VectorN<T, N>& v) {
	VectorN<T, N> tmp;
	for (int i = 0; i < N; i++)
		tmp[i] = -v[i];
	return tmp;
}

template<typename T, int N>
VectorN<T, N> operator*(const T s, const VectorN<T, N>& vec3) {
	VectorN<T, N> v;
	for (int i = 0; i < N; i++)
		v[i] = s * vec3[i];
	return v;
}

template<typename T, int N>
T dotProduct(const VectorN<T,N>& v1,const VectorN<T,N>& v2){
	T sum = 0.0;
	for (int i = 0; i < N; i++) {
		sum += (v1[i] * v2[i]);

	}
	return sum;

}

