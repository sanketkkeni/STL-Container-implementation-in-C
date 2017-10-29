#include <iostream>


template <typename T>
class Forward_list;

template <typename TNode>
class ForwardListIterator
{
    friend class Forward_list<typename TNode::value_type>;
    TNode* p;
public:
    ForwardListIterator() {}
    ForwardListIterator(TNode* p){ this->p = p; }
    ForwardListIterator(const ForwardListIterator& other) {p = other.p; }
    ForwardListIterator& operator=(ForwardListIterator other) { std::swap(p, other.p); return *this; }
    void operator++() { p = p->next; }
    void operator++(int) { p = p->next; }
    bool operator==(const ForwardListIterator& other) { return p == other.p; }
    bool operator!=(const ForwardListIterator& other) { return p != other.p; }
    const int& operator*() { return p->data; }
    ForwardListIterator<TNode> operator+(int i)
    {
        ForwardListIterator<TNode> iter = *this;
        while (i-- > 0 && iter.p)
        {
            ++iter;
        }
        return iter;
    }
};

template <typename T>
class Node
{
    friend class Forward_list<T>;
    friend class ForwardListIterator<Node<T>>;
    T data;
    Node<T> *next;
    Node() { next = nullptr;}


public:
    Node(const T &data){
        this->data = data;
        next = nullptr;
    }
    typedef T value_type;
};

template <typename T>
class Forward_list
{
private:
    typedef Node<T> node;
    int Size;
    node* head;
    node* tail;
    void FrontBackSplit(node* source, node** frontRef, node** backRef);
    void mergesort(node** head);

public:

    typedef ForwardListIterator<node> iterator;
    Forward_list();
    ~Forward_list();
    const int size();
    void push_front(T const& data);
    void pop_front();
    void assign(int times, T const & data);
    void clear();
    bool empty();
    T& front();
    Node<T>* merge(node* a, node* b);
    void sort();
    void remove(T data);
    ForwardListIterator<node> begin();
    ForwardListIterator<node> end();
    void swap(Forward_list& first);
    void operator=(T const & other);
    void reverse ();



};


template <typename T>
Forward_list<T>::Forward_list(){
        Size = 0;
        head = new node();
        tail = new node();
        head->next = tail;
}

template <typename T>
Forward_list<T>::~Forward_list(){
        node* t;
        while (head->next != tail){
            t = head->next;
            head->next = head->next->next;
            delete t;
        }
}

template <typename T>
const int Forward_list<T>::size(){
        return Size;
}

template <typename T>
void Forward_list<T>::push_front(T const& data){
        node* newNode = new node(data);
        if(head->next == tail){
            head->next = newNode;
            newNode->next = tail;
        }
        else{
            newNode->next = head->next;
            head->next = newNode;
        }
        Size++;
}

template <typename T>
void Forward_list<T>::pop_front(){
    node *tmp = head->next;
    head->next = head->next->next;
    Size--;
    delete tmp;
}

template <typename T>
void Forward_list<T>::assign(int times, T const & data){
        for(int i=0;i<times;i++){
            push_front(data);
        }
        Size+=times;
}

template <typename T>
void Forward_list<T>::clear(){
    node* curr;
    while(head->next != tail){
        curr = head->next;
        head->next = head->next->next;
        delete curr;
    }
    Size = 0;
}

template <typename T>
bool Forward_list<T>::empty(){
        return Size==0;
}

template <typename T>
T& Forward_list<T>::front(){
        return head->next->data;
}

template <typename T>
void Forward_list<T>::FrontBackSplit(node* source, node** frontRef, node** backRef){
        node* fast;
        node* slow;
        if (source==tail || source->next==tail){
            *frontRef = source;
            *backRef = tail;
        }

        else{
            slow = source;
            fast = source->next;

            while (fast != tail){
                fast = fast->next;
                if (fast != tail){
                    slow = slow->next;
                    fast = fast->next;
                }
            }

            *frontRef = source;
            *backRef = slow->next;
            slow->next = tail;
        }
}

template <typename T>
Node<T>* Forward_list<T>::merge(node* a, node* b){
        node* result = tail;

        if (a == tail)
            return(b);
        else if (b==tail)
            return(a);

        if (a->data <= b->data){
            result = a;
            result->next = merge(a->next, b);
        }

        else{
            result = b;
            result->next = merge(a, b->next);
        }
        return(result);
}

template <typename T>
void Forward_list<T>::mergesort(node** head){
        node* temphead = *head;
        node* a;
        node* b;

        if ((temphead == tail) || (temphead->next == tail)){
            return;
        }

        FrontBackSplit(temphead, &a, &b);

        mergesort(&a);
        mergesort(&b);

        *head = merge(a, b);
}

template <typename T>
void Forward_list<T>::sort(){
        node* temphead = head->next;
        mergesort(&temphead);
        head->next = temphead;
}

template <typename T>
void Forward_list<T>::remove(T data){
        node* temp = head->next, *delnode,*prev = head;
        while(temp!=tail){
            if(temp->data == data){
                delnode = temp;
                prev->next = temp->next;
                temp = temp->next;
                Size--;
                delete delnode;
            }
            else{
                prev = temp;
                temp = temp->next;
            }
        }
}

template <typename T>
ForwardListIterator<Node<T>> Forward_list<T>::begin(){
        return iterator(head->next);
}

template <typename T>
ForwardListIterator<Node<T>> Forward_list<T>::end(){
        return iterator(tail);
}

template <typename T>
void Forward_list<T>::swap(Forward_list& first){
        std::swap(first.Size, Size);
        std::swap(first.head, head);
        std::swap(first.tail, tail);
}

template <typename T>
void Forward_list<T>::operator=(T const & other){
        clear();
        Size = other.size();
        iterator it;
        node* temp = head;
        for(it=other.begin(); it!=other.end();it++){
            temp->next = new node(*it);
            temp = temp->next;
        }
        temp->next = tail;
}

template <typename T>
void Forward_list<T>::reverse (){
        node *current, *prev, *next;
        current = head->next;
        prev = tail;
        while(current != tail){
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head->next = prev;
}

using namespace std;
int main(){

Forward_list<int> l,l2;

l.push_front(1);l.push_front(2);l.push_front(3);l.push_front(4);l.push_front(5);l.push_front(-1);l.push_front(17);l.push_front(8);
l.remove(17);
Forward_list<int> :: iterator it;
for(it = l.begin();it!=l.end();it++){
    cout<<*it<<" ";
}cout<<endl;

l.reverse();
for(it = l.begin();it!=l.end();it++){
    cout<<*it<<" ";
}cout<<endl;

cout<<endl<<l.size();


return 0;}
