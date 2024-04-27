#if !defined(n_list_h)
#define n_list_h


template<class T> class n_list_node {
public:
    T element;
    n_list_node* next;
    n_list_node* prev;

    n_list_node(T element, n_list_node* prev, n_list_node* next) : element(element) {
        this->next = next;
        this->prev = prev;
    }
};

template<class T> class n_list {
public:

   ~n_list();
    n_list();
    n_list(const n_list<T>&);

    T& curr();
    T& first();
    T& last();

    void append_item(T);
    int length();

private:
    int len;
    n_list_node<T>* head;
    n_list_node<T>* tail;
    n_list_node<T>* current;
};

template<class T> n_list<T>::n_list() {
    len = 0;
    head = nullptr;
    tail = nullptr;
    current = nullptr;
}
template<class T> n_list<T>::n_list(const n_list<T>& list) {
    len = 0;
    head = nullptr;
    tail = nullptr;
    current = nullptr;

    n_list_node<T> *temp = list.head;
    do {
        append_item(temp->element);
        temp = temp->next;
    } while (temp != nullptr);
}


#endif
