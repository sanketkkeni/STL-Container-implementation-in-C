#include<iostream>
#include<math.h>

template <class T>
class  Vector {
private:
    unsigned int size;
    unsigned int capacity;
    unsigned int Log;
    T* buffer;
public:
    typedef T* Iterator;
    Vector();
    Vector(unsigned int size);
    Vector(unsigned int size, const T & initial);
    Vector(const Vector<T>& v);
    ~Vector();
    unsigned int Capacity();
    unsigned int Size();
    bool empty();
    Iterator begin();
    Iterator end();
    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();
    void erase(Iterator it);
    void erase(Iterator it1, Iterator it2);
	void emplace(Iterator it, const T& value);
    void reserve(unsigned int capacity);
    void resize(unsigned int size);
    void swap(Vector<T>& v);
    T & operator[](unsigned int index);
    Vector<T> & operator = (const Vector<T> &);
    void clear();

};


template<class T>
Vector<T>::Vector(){
    capacity = 0;
    size = 0;
    buffer = 0;
    Log = 0;
}

template<class T>
Vector<T>::Vector(const Vector<T> & v){
    size = v.size;
    Log = v.Log;
    capacity = v.capacity;
    buffer = new T[size];
    for (unsigned int i = 0; i < size; i++)
        buffer[i] = v.buffer[i];
}

template<class T>
Vector<T>::Vector(unsigned int size){
    size = size;
    Log = ceil(log((double) size) / log(2.0));
    capacity = 1 << Log;
    buffer = new T[capacity];
}

template <class T>
bool Vector<T>:: empty(){
    return size == 0;
}

template<class T>
Vector<T>::Vector(unsigned int size, const T& initial){
    size = size;
    Log = ceil(log((double) size) / log(2.0));
    capacity = 1 << Log;
    buffer = new T [capacity];
    for (unsigned int i = 0; i < size; i++)
        buffer[i] = initial;
}

template<class T>
Vector<T>& Vector<T>::operator = (const Vector<T> & v){
    delete[] buffer;
    size = v.size;
    Log = v.Log;
    capacity = v.capacity;
    buffer = new T [capacity];
    for (unsigned int i = 0; i < size; i++)
        buffer[i] = v.buffer[i];
    return *this;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::begin(){
    return buffer;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::end(){
    return buffer + Size();
}

template<class T>
T& Vector<T>::front(){
    return buffer[0];
}

template<class T>
T& Vector<T>::back(){
    return buffer[size - 1];
}

template<class T>
void Vector<T>::push_back(const T & v){
    if (size >= capacity) {
        reserve(1 << Log);
        Log++;
    }
    buffer [size++] = v;
}

template<class T>
void Vector<T>::pop_back(){
    size--;
}

template<class T>
void Vector<T>::swap(Vector<T>& v){
    unsigned int size1 = v.Size();
    unsigned int capacity1 = v.Capacity();
    unsigned int log1 = ceil(log((double) size1) / log(2.0));
    T* buffer1 = v.begin();

    v = *this;

    size = size1;
    capacity = capacity1;
    Log = log1;
    buffer = buffer1;
}

template<class T>
void Vector<T>::erase(Iterator it){
    unsigned int pos = it-buffer;
    while(pos!=size-1){
        buffer[pos] = buffer[pos+1];pos++;
    }
    size--;
}

template<class T>
void Vector<T>::erase(Iterator it1, Iterator it2){
    unsigned int pos1 = it1-buffer;
    unsigned int pos2 = it2-buffer;
    while(pos2!=size){
        buffer[pos1] = buffer[pos2];pos2++;pos1++;
    }
    size-=pos2-pos1;
}

template<class T>
void Vector<T>::emplace(Iterator it, const T& value){
    unsigned int pos = it-buffer;
	if (size >= capacity) {
        reserve(1 << Log);
        Log++;
    }
	for(unsigned int i=size;i>pos;i--){
		buffer[i]=buffer[i-1];
	}
	buffer[pos] = value;
    size++;
}


template<class T>
void Vector<T>::reserve(unsigned int capacity){
    T * newBuffer = new T[capacity];

    for (unsigned int i = 0; i < size; i++)
        newBuffer[i] = buffer[i];

    capacity = capacity;
    delete[] buffer;
    buffer = newBuffer;
}

template<class T>
 unsigned int Vector<T>::Size(){
    return size;
}

template<class T>
void Vector<T>::resize(unsigned int size){
    Log = ceil(log((double) size) / log(2.0));
    reserve(1 << Log);
    size = size;
}

template<class T>
T& Vector<T>::operator[](unsigned int index){
    return buffer[index];
}

template<class T>
unsigned int Vector<T>::Capacity(){
    return capacity;
}

template<class T>
Vector<T>::~Vector(){
    delete[] buffer;
}

template <class T>
void Vector<T>::clear(){
    capacity = 0;
    size = 0;
    buffer = 0;
    Log = 0;
}

using namespace std;

int main(){

    Vector<int> v; Vector<int> v1;
    v.push_back(1);v1.push_back(11);
    v.push_back(2);v1.push_back(12);
    v.push_back(3);v1.push_back(13);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    Vector<int> :: Iterator it;

    for(it=v.begin();it!=v.end();it++){
        cout<<*it<<" ";
    } cout<<endl<<v.Size()<<endl;
    for(it=v1.begin();it!=v1.end();it++){
        cout<<*it<<" ";
    } cout<<endl<<v1.Size()<<endl;
    v.swap(v1);

    for(it=v.begin();it!=v.end();it++){
        cout<<*it<<" ";
    } cout<<endl<<v.Size()<<endl;
    for(it=v1.begin();it!=v1.end();it++){
        cout<<*it<<" ";
    } cout<<endl<<v1.Size()<<endl;
cout<<"ewfd";
return 0;}


