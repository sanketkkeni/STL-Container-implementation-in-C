#include <iostream>
#include <vector>

using namespace std;

template <class T> class multiset;
template <class T> class Node_Iterator;

template<class T>
struct Node
{
    T value;
    Node *left;
    Node *right;
    Node *next;
	int height;

    Node(const T& data){
        value = data;
        left = nullptr;
        right = nullptr;
        next = nullptr;
		height = 1;
    }

    ~Node(){
        delete left;
        delete right;
    }

};

template<class T>
class multiset
{
private :

    unsigned int Size;
    Node<T> *Root;
    Node<T> *startIterator;

    void build_iterators(const Node<T> *root);
	void clearUtil(Node<T>* &root);
    void build_iterators_imp(std::vector<Node<T>*> &iterators, const Node<T> *root);
    Node_Iterator<T> findUtil(const T& t, Node<T>*&root);
	Node<T>* minValueNode(Node<T>* node);
	Node<T>* deleteNodeUtil(Node<T>* root, const T& value);
	Node<T>* insertUtil(Node<T>* root, const T& value);
	unsigned int height(Node<T>* root);
	int getBalance(Node<T> *N);
	Node<T>* leftRotate(Node<T>* x);
	Node<T>* rightRotate(Node<T>* y);

public :


    typedef Node_Iterator<T> iterator;
    multiset();
    ~multiset();
    multiset(multiset &s);
    multiset& operator =(multiset &s);
    void clear();
    unsigned int size();
    bool empty();
    void insert(const T& t);
    void erase(const T& t);
	void erase(Node_Iterator<T> it);
	void erase(Node_Iterator<T> it1, Node_Iterator<T> it2);
    iterator begin();
    iterator end();
	iterator find(const T& t);
	void swap(multiset<T> &s);

};

template <typename T>
multiset<T>:: multiset(){
        Size = 0;
        Root = nullptr;
}

template <typename T>
multiset<T>:: ~multiset(){
        clear();
}

template <typename T>
multiset<T>:: multiset(multiset &s){
        Size = 0;
        Root = nullptr;
        for(iterator it = s.begin(); it != s.end(); it++){
            insert(*it);
        }
}

template <typename T>
multiset<T>& multiset<T>:: operator =(multiset<T> &s){
        if(&s == this) return *this;
        clear();
        for(iterator it = s.begin(); it != s.end(); it++){
            insert(*it);
        }
        return *this;
    }

template <typename T>
void multiset<T>:: clear(){
        clearUtil(Root);
        Size = 0;
}

template <typename T>
void multiset<T>:: clearUtil(Node<T>* &root){
	if(root == nullptr) return;
	clearUtil(root->left);
	clearUtil(root->right);
	delete root;
	root = nullptr;
	return;
}

template <typename T>
unsigned int multiset<T>:: size(){
        return Size;
}

template <typename T>
Node<T>* multiset<T>:: rightRotate(Node<T>* y){
    Node<T> *x = y->left;
    Node<T> *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

template <typename T>
Node<T>* multiset<T>:: leftRotate(Node<T>* x){
    Node<T> *y = x->right;
    Node<T> *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

template <typename T>
int multiset<T>:: getBalance(Node<T> *N){
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

template <typename T>
unsigned int multiset<T>:: height(Node<T>* root){
        if (root == nullptr)
			return 0;
		return root->height;
}

template <typename T>
bool multiset<T>:: empty(){
        return Size == 0;
}

template <typename T>
void multiset<T>:: insert(const T& value){
        Root = insertUtil(Root, value);
}

template <typename T>
Node<T>* multiset<T>:: insertUtil(Node<T>* root, const T& value){

	if (root == nullptr){
        Size++;
        return(new Node<T>(value));
	}

    if (value <= root->value)
        root->left  = insertUtil(root->left, value);
    else
        root->right = insertUtil(root->right, value);

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && value < root->left->value)
        return rightRotate(root);

    if (balance < -1 && value > root->right->value)
        return leftRotate(root);

    if (balance > 1 && value > root->left->value){
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && value < root->right->value){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

template <typename T>
void multiset<T>:: erase(Node_Iterator<T> it1, Node_Iterator<T> it2){

        do{
            Root = deleteNodeUtil(Root, *it1++);

        }
        while(it1!=it2);
}

template <typename T>
void multiset<T>:: erase(Node_Iterator<T> it){

		Root = deleteNodeUtil(Root, *it);
}

template <typename T>
void multiset<T>:: erase(const T& value){
		iterator found = find(value);
		do{
			Root = deleteNodeUtil(Root, value);
		}
		while(found != end());
}

template <typename T>
Node<T>* multiset<T>:: deleteNodeUtil(Node<T>* root, const T& value){
    if (root == nullptr)
		return root;

    if (value < root->value )
        root->left = deleteNodeUtil(root->left, value);

    else if( value > root->value )
        root->right = deleteNodeUtil(root->right, value);

    else{
        if((root->left == nullptr) || (root->right == nullptr)){
            Node<T> *temp = root->left ? root->left :root->right;

            if (temp == nullptr){
                temp = root;
                root = nullptr;
            }
            else
             *root = *temp;

			delete temp;
			Size--;
        }
        else{
            Node<T>* temp = minValueNode(root->right);

            root->value = temp->value;

            root->right = deleteNodeUtil(root->right, temp->value);
        }
    }

    if (root == nullptr)
		return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0){
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

template <typename T>
Node<T>* multiset<T>:: minValueNode(Node<T>* root){
    Node<T>* current = root;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

template <typename T>
Node_Iterator<T> multiset<T>:: begin(){
        if(Root == nullptr) return iterator(0);
        build_iterators(Root);
        return iterator(startIterator);
}

template <typename T>
Node_Iterator<T> multiset<T>:: end(){
        return iterator(0);
}

template <typename T>
void multiset<T>:: build_iterators(const Node<T> *root){
        unsigned int i;
        std::vector<Node<T>*> iterators;
        build_iterators_imp(iterators, root);

        if(empty()){
            startIterator = nullptr;
            return;
        }

        startIterator = iterators[0];
        for(i = 0; i < iterators.size() - 1; i++){
            iterators[i]->next = iterators[i + 1];
        }
        iterators[i]->next = nullptr;
}

template <typename T>
void multiset<T>:: build_iterators_imp(std::vector<Node<T>*> &iterators, const Node<T> *root){
        if(root == nullptr) {
            return;
        }

        build_iterators_imp(iterators, root->left);

        iterators.push_back((Node<T>*)root);

        build_iterators_imp(iterators, root->right);
}


template <typename T>
Node_Iterator<T> multiset<T>:: findUtil(const T& t, Node<T>*&root){
		if(!root){
            return iterator(0);
        }

        if(t == root->value){
            return iterator(root);
        }
        else if(t < root->value){
            return findUtil(t, root->left);
        }
        else{
            return findUtil(t, root->right);
        }
}

template <typename T>
Node_Iterator<T> multiset<T>:: find(const T& t){
        Node<T>* temp = Root;
        return findUtil(t,temp);
}


template <typename T>
void multiset<T>:: swap(multiset<T> &s){
    std::swap(Root, s.Root);
    std::swap(Size,s.Size);
}



template <class T>
class Node_Iterator{
   Node<T> * n;
   typedef Node<T> node;
public:
   Node_Iterator() { n = 0;}
   Node_Iterator(node * newNode){ n = newNode; }
   bool operator== (Node_Iterator it) { return n == it.n; }
   bool operator != (Node_Iterator it) { return n != it.n; }
   Node_Iterator& operator++();
   Node_Iterator operator++(int);
   T& operator*() { return n->value; }
   T* operator->() { return &n->value; }
   Node_Iterator& operator=(Node_Iterator<T> it) { n = it.n; return *this; }

   friend class multiset<T>;
};

template <class T>
Node_Iterator<T>& Node_Iterator<T>::operator ++(){
   n = n->next;
   return *this;
}

template <class T>
Node_Iterator<T> Node_Iterator<T>::operator ++(int){
   Node_Iterator<T> it(*this); ++(*this);

   return it;
}



int main()
{
    multiset<int> set;
    set.insert(4); set.insert(0);
    set.insert(2); set.insert(7);
    set.insert(0); set.insert(2);
    set.insert(6); set.insert(4);
    set.insert(12); set.insert(11);
    set.insert(8); set.insert(1);
    set.insert(5); set.insert(0);
    set.insert(3); set.insert(2);
    set.insert(7); set.insert(1);

    multiset<int>::iterator it;

    multiset<int> set2;
    set2 = set;/*
    //set2.insert(88888);set2.insert(8848);
    it = set2.find(8);
    cout<<*it;

    for(multiset<int>::iterator it = set2.begin(); it != set2.end(); it++)
    {
        cout << *it << ' ';
    }*/
    cout<<endl;cout<<set.size();
    //set.clear();
    for(multiset<int>::iterator it = set.begin(); it != set.end(); it++)
    {
        cout << *it << ' ';
    }
}
