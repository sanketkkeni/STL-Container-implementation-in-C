#include <iostream>

template <typename T>
class Stack {

    struct node{
        T data;
        node* next;
        node(){
            data = 0;
            next = nullptr;
        }
        node(T const& data, node* next){
            this->data = data;
            this->next = next;
        }
    };

    node* root = nullptr;
    int Size = 0;

    public:
        ~Stack();
        void push(T const& data);
        bool empty();
        int size();
        void swap (Stack& s);
        T& top();
        void pop();
};

template<typename T>
Stack<T>::~Stack(){
    node* next;
    for(node* loop = root; loop != nullptr; loop = next)
    {
        next = loop->next;
        delete loop;
    }
}

template<typename T>
void Stack<T>::push(T const& data){
    root = new node(data, root);
    ++Size;
}

template<typename T>
bool Stack<T>::empty(){
    return root == nullptr;
}

template<typename T>
int Stack<T>::size(){
    return Size;
}

template <typename T>
void Stack<T>::swap (Stack& s){
    std::swap(Size, s.Size);
    std::swap(root, s.root);
}

template<typename T>
T& Stack<T>::top(){
    return root->data;
}

template<typename T>
void Stack<T>::pop(){
    node*   tmp = root;
    root    = root->next;
    --Size;
    delete tmp;
}

using namespace std;
int main(){

Stack<int> s,s1;
s.push(1);s1.push(34);
s1.push(29);
s.push(2);
s.push(3);
s.push(4);
s.swap(s1);
while(!s.empty()){
    cout<<s.top();
    s.pop();
}cout<<endl;
while(!s1.empty()){
    cout<<s1.top();
    s1.pop();
}

return 0;}
