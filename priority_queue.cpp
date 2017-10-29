#include<iostream>
#include<math.h>

template <class T>
class  priority_queue {

private:
    unsigned int size;
    unsigned int capacity;
    unsigned int Log;
    T* buffer;
    int parent(int i) { return (i-1)/2; }
    void swap(int &a, int &b) { std::swap(a,b); }
    void MinHeapify(unsigned int i);
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }
    void reserve(unsigned int capacity);
    void resize(unsigned int size);

public:
    priority_queue();
    priority_queue(const priority_queue<T>& v);
    ~priority_queue();

    unsigned int Capacity();
    unsigned int Size();
    bool empty();
    T& top();
    void push(const T& value);
    void pop();
    void swap(priority_queue<T>& v);

};

template<class T>
priority_queue<T>::priority_queue(){
    capacity = 0;
    size = 0;
    buffer = 0;
    Log = 0;
}

template<class T>
priority_queue<T>::priority_queue(const priority_queue<T> & v){
    size = v.size;
    Log = v.Log;
    capacity = v.capacity;
    buffer = new T[size];
    for (unsigned int i = 0; i < size; i++)
        buffer[i] = v.buffer[i];
}

template <class T>
bool priority_queue<T>::empty(){
    return size == 0;
}

template<class T>
T& priority_queue<T>::top(){
    return buffer[0];
}

template<class T>
void priority_queue<T>::MinHeapify(unsigned int i){
    unsigned int l = left(i);
    unsigned int r = right(i);
    unsigned int largest = i;
    if (l < size && buffer[l] > buffer[i])
        largest = l;
    if (r < size && buffer[r] > buffer[largest])
        largest = r;
    if (largest != i)
    {
        swap(buffer[i], buffer[largest]);
        MinHeapify(largest);
    }
}

template<class T>
void priority_queue<T>::push(const T & v){
    if (size >= capacity) {
        reserve(1 << Log);
        Log++;
    }

    buffer [size++] = v;
    int i = size - 1;

    while (i != 0 && buffer[parent(i)] < buffer[i])
    {
       swap(buffer[i], buffer[parent(i)]);
       i = parent(i);
    }
}

template<class T>
void priority_queue<T>::pop(){
    if (size == 0)
        std::cout<<"Priority queue is empty";
    if (size == 1){
        size--;
        return;
    }

    buffer[0] = buffer[size-1];
    size--;
    MinHeapify(0);
}

template<class T>
void priority_queue<T>::swap(priority_queue<T>& v){
    std::swap(buffer,v.buffer);
    std::swap(size,v.size);
    std::swap(capacity,v.capacity);
    std::swap(Log,v.Log);
}

template<class T>
void priority_queue<T>::reserve(unsigned int capacity){
    T * newBuffer = new T[capacity];

    for (unsigned int i = 0; i < size; i++)
        newBuffer[i] = buffer[i];

    capacity = capacity;
    delete[] buffer;
    buffer = newBuffer;
}

template<class T>
 unsigned int priority_queue<T>::Size(){
    return size;
}

template<class T>
void priority_queue<T>::resize(unsigned int size){
    Log = ceil(log((double) size) / log(2.0));
    reserve(1 << Log);
    size = size;
}

template<class T>
unsigned int priority_queue<T>::Capacity(){
    return capacity;
}

template<class T>
priority_queue<T>::~priority_queue(){
    delete[] buffer;
}


using namespace std;

int main(){

    priority_queue<int> v; priority_queue<int> v1;
    v.push(10);v1.push(88);
    v.push(5);
    v.push(3);
    v.push(11);
    v.push(2);v.swap(v1);
    while (!v.empty())
  {
     cout << ' ' << v.top();
     v.pop();
  }
  while (!v1.empty())
  {
     cout << ' ' << v1.top();
     v1.pop();
  }
return 0;}


