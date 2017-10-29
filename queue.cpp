#include <iostream>

using namespace std;

template <typename T>
class queue {
    struct node{
        T data;
        node *next;

        node(){
            data = 0;
            next = nullptr;
        }

        node(T const& data, node* next){
            this->data = data;
            this->next = next;
        }
    };

    int Size = 0;
    node *head = nullptr;
    node *tail = nullptr;

public:

    ~queue();
    bool empty();
    int size();
    T& front();
    T& back();
    void push(T const& data);
    void swap (queue& x);
    void pop();
};

template <typename T>
queue<T>::~queue(){
    node *curr = new node();
    while(head) {
        curr = head;
        head = head->next;
        delete curr;
    }
    delete tail;
}

template <typename T>
bool queue<T>::empty(){
    return Size == 0;
}

template <typename T>
int queue<T>::size(){
    return Size;
}

template <typename T>
T& queue<T>::front(){
    return head->data;
}

template <typename T>
T&  queue<T>::back(){
    return tail->data;
}

template <typename T>
void  queue<T>::push(T const& data){
    node *newNode = new node(data, nullptr);
    if(!Size) head = newNode;
    else tail->next = newNode;
    tail = newNode;
    ++Size;
}
template <typename T>
void  queue<T>::pop(){
    node *tmp = new node();
    if(Size != 0) tmp = head;
    head = head->next;
    --Size;
    delete tmp;
}

template <typename T>
void queue<T>::swap (queue& x){
    std::swap(Size, x.Size);
    std::swap(head, x.head);
    std::swap(tail, x.tail);
}


int main(){

queue<int> q,q1;
q.push(1);
q.push(2);
q.push(3);
q.push(4);
q.push(5);
q.push(11);
q.push(21);
q.push(31);
q.push(41);
q.push(51);

/*while(!q.empty()){
    cout<<q.front()<<" ";
    q.pop();
}*/
q.front()=9;q.back()=0;
while(!q.empty()){
    cout<<q.front()<<" ";
    q.pop();
}



return 0;}
