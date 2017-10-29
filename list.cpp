#include <iostream>


template <typename T>
class List;

template <typename TNode>
class ListIterator
{
    friend class List<typename TNode::value_type>;
    TNode* p;
public:
    ListIterator() {}
    ListIterator(TNode* p){ this->p = p; }
    ListIterator(const ListIterator& other) {p = other.p; }
    ListIterator& operator=(ListIterator other) { std::swap(p, other.p); return *this; }
    void operator++() { p = p->next; }
    void operator++(int) { p = p->next; }
    bool operator==(const ListIterator& other) { return p == other.p; }
    bool operator!=(const ListIterator& other) { return p != other.p; }
    const int& operator*() { return p->data; }
    ListIterator<TNode> operator+(int i)
    {
        ListIterator<TNode> iter = *this;
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
    friend class List<T>;
    friend class ListIterator<Node<T>>;
    T data;
    Node<T> *next,*prev;
    Node() { next = nullptr; prev = nullptr;}


public:
    Node(const T &data){
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
    typedef T value_type;
};

template <typename T>
class List
{
private:
    typedef Node<T> node;
    int Size;
    node* head;
    node* tail;
    Node<T>* Split(node* head);
    Node<T>* mergesort(node* head);

public:

    typedef ListIterator<node> iterator;
    List();
    ~List();
    const int size();
    void push_front(T const& data);
    void pop_front();
    void push_back(T const& data);
    void pop_back();
    void assign(int times, T const & data);
    void clear();
    bool empty();
    T& front();
    T& back();
    Node<T>* merge(node* a, node* b);
    void sort();
    void remove(T data);
    ListIterator<node> begin();
    ListIterator<node> end();
    void swap(List& first);
    void operator=(T const & other);
    void reverse ();
    void unique();


};


template <typename T>
List<T>::List(){
        Size = 0;
        head = new node();
        tail = new node();
        head->next = tail;
        head->prev = head;
}

template <typename T>
List<T>::~List(){
        node* t;
        while (head->next != tail){
            t = head->next;
            head->next = head->next->next;
            delete t;
        }
}

template <typename T>
const int List<T>::size(){
        return Size;
}

template <typename T>
void List<T>::push_front(T const& data){
        node* newNode = new node(data);
        if(head->next == tail){
            newNode->prev = head;
            head->next = newNode;
            newNode->next = tail;
            tail->prev = newNode;
        }
        else{
            newNode->prev = head;
            head->next->prev = newNode;
            newNode->next = head->next;
            head->next = newNode;
        }
        Size++;
}

template <typename T>
void List<T>::pop_front(){
    node *tmp = head->next;
    tmp->next->prev = head;
    head->next = head->next->next;
    Size--;
    delete tmp;
}

template <typename T>
void List<T>::push_back(T const& data) {
    node* newNode = new node(data);
    if(head->next == tail){ //list is empty
        newNode->prev = head;
        head->next = newNode;
        newNode->next = tail;
        }
    else{
        newNode->prev = tail->prev;
        newNode->next = tail;
        tail->prev->next = newNode;
        tail->prev = newNode;

    }
    Size++;
}

template <typename T>
void List<T>::pop_back() {
    node *tmp = tail->prev;
    tail->prev = tail->prev->prev;
    if(tmp != head)
        tmp->prev->next = tail;
    Size--;
    delete tmp;
}

template <typename T>
void List<T>::assign(int times, T const & data){
        for(int i=0;i<times;i++){
            push_front(data);
        }
        Size+=times;
}

template <typename T>
void List<T>::clear(){
    node* curr;
    while(head->next != tail){
        curr = head->next;
        head->next = head->next->next;
        delete curr;
    }
    Size = 0;
}

template <typename T>
bool List<T>::empty(){
        return Size==0;
}

template <typename T>
T& List<T>::front(){
        return head->next->data;
}

template <typename T>
T& List<T>::back(){
        return tail->prev->data;
}

template <typename T>
Node<T>* List<T>::Split(node* head){
        node *fast = head, *slow = head;
        while (fast->next && fast->next->next){
            fast = fast->next->next;
            slow = slow->next;
        }
        node *temp = slow->next;
        slow->next = nullptr;
        return temp;
}

template <typename T>
Node<T>* List<T>::merge(node* a, node* b){

        if (a == nullptr)
            return b;
        else if (b==nullptr)
            return a;

        if (a->data < b->data){
            a->next = merge(a->next,b);
            a->next->prev = a;
            a->prev = nullptr;
            return a;
        }

        else{
            b->next = merge(a,b->next);
            b->next->prev = b;
            b->prev = nullptr;
            return b;
        }
}

template <typename T>
Node<T>* List<T>::mergesort(node* head){

        if ((head == nullptr) || (head->next == nullptr)){
            return head;
        }

        node * second = Split(head);

        head = mergesort(head);
        second = mergesort(second);

        return merge(head, second);
}

template <typename T>
void List<T>::sort(){
        node* temphead = head->next;
        tail->prev->next = nullptr;
        temphead = mergesort(temphead);
        head->next = temphead;
        ///attach tail at the end
        node* temp = temphead;
        while(temp->next!=nullptr){
            temp = temp->next;
        }
        temp->next = tail;
        tail->prev = temp;

}

template <typename T>
void List<T>::remove(T data){
        node* temp = head->next, *delnode,*prev1 = head;
        while(temp!=tail){
            if(temp->data == data){
                delnode = temp;
                delnode->next->prev = prev1;
                prev1->next = temp->next;
                temp = temp->next;
                Size--;
                if(delnode==tail->prev) tail->prev = tail->prev->prev;
                delete delnode;

            }
            else{
                prev1 = temp;
                temp = temp->next;
            }
        }
}

template <typename T>
ListIterator<Node<T>> List<T>::begin(){
        return iterator(head->next);
}

template <typename T>
ListIterator<Node<T>> List<T>::end(){
        return iterator(tail);
}

template <typename T>
void List<T>::swap(List& first){
        std::swap(first.Size, Size);
        std::swap(first.head, head);
        std::swap(first.tail, tail);
}

template <typename T>
void List<T>::operator=(T const & other){
        clear();
        Size = other.size();
        iterator it;
        node* temp = head, *prev1 = head;
        for(it=other.begin(); it!=other.end();it++){
            temp->next = new node(*it);
            temp->next->prev = prev1;
            temp = temp->next;
            prev1 = temp;
        }
        temp->next = tail;
        tail->prev = prev1;
}

template <typename T>
void List<T>::reverse (){
    if(size() == 0) return;
     node *temp;
     node *current = head->next;
     node *first = current, *last = tail->prev;
     while (current !=  tail)
     {
        temp = current->next;
        std::swap(current->prev, current->next);
        current = temp;
     }
        head->next = last;
        last->prev = head;
        tail->prev = first;
        first->next = tail;

}


template <typename T>
void List<T>::unique (){
    sort();
    node* current = head->next;

    node* next_next;

    /* do nothing if the list is empty */
    if (current == tail)
       return;

    /* Traverse the list till last node */
    while (current->next != tail){

       if (current->data == current->next->data){
           next_next = current->next->next;
           Size--;
           delete current->next;
           current->next = next_next;
       }

       else{
          current = current->next;
       }
    }
}

using namespace std;
int main(){

List<int> l,l2;

l.push_front(5);l.push_front(5);l.push_front(5);l.push_front(4);l.push_front(5);
l.push_front(-1);l.push_front(17);l.push_front(8);
l.push_back(14);
List<int> :: iterator it;
for(it = l.begin();it!=l.end();it++){
    cout<<*it<<" ";
}cout<<endl;

l.unique();

for(it = l.begin();it!=l.end();it++){
    cout<<*it<<" ";
}cout<<endl;
cout<<endl<<l.size();


return 0;}
