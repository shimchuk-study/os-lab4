template<typename T>
BTree<T>::Node::Node(T _data) : data(_data), height(1)  {}

template<typename T>
BTree<T>::Iterator::Iterator(BTree<T>::NodePtr _ptr) : ptr(_ptr) {}

template<typename T>
auto BTree<T>::Iterator::left() const -> Iterator
{
    return Iterator(ptr->left);
}

template<typename T>
auto BTree<T>::Iterator::right() const -> Iterator
{
    return Iterator(ptr->right);
}

template<typename T>
const T& BTree<T>::Iterator::operator*() const
{
    return ptr->data;
}

template<typename T>
const T* BTree<T>::Iterator::operator->() const
{
    return &ptr->data;
}

template<typename T>
bool BTree<T>::insert(T data)
{
    this->m_insertion_flag = true;
    m_root = insert(m_root, data);
    return this->m_insertion_flag;
}

template<typename T>
auto BTree<T>::insert(NodePtr node, T data) -> NodePtr
{
    if (node) {
        if (node->data == data)
            m_insertion_flag = false;
        else if (data < node->data)
            node->left = insert(node->left, data);
        else
            node->right = insert(node->right, data);

        return balance(node);
    }

    m_size++;

    return std::make_shared<Node>(data);
}

template<typename T>
auto BTree<T>::balance(NodePtr node) -> NodePtr
{
    fixheight(node);

    int bf = bfactor(node);
    if (bf == 2) {
        if (node->right)
            if (bfactor(node->right) < 0)
                node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    else if (bf == -2) {
        if (node->left)
            if (bfactor(node->left) > 0)
                node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    return node;
}

template<typename T>
auto BTree<T>::rotateRight(NodePtr node) -> NodePtr
{
    NodePtr q = node->left;
    node->left = q->right;
    q->right = node;
    fixheight(node);
    fixheight(q);

    return q;
}

template<typename T>
auto BTree<T>::rotateLeft(NodePtr node) -> NodePtr
{
    NodePtr q = node->right;
    node->right = q->left;
    q->left = node;
    fixheight(node);
    fixheight(q);

    return q;
}

template<typename T>
void BTree<T>::fixheight(NodePtr node)
{

    int hl = 0, hr = 0;
    if (node->left)
        hl = node->left->height;
    if (node->right)
        hr = node->right->height;
    node->height = std::max<int>(hl, hr) + 1;
}

template<typename T>
int BTree<T>::bfactor(NodePtr node)
{
    int fr = 0, fl = 0;
    if (node->left)
        fl = node->left->height;
    if (node->right)
        fr = node->right->height;
    return fr - fl;
}

template<typename T>
auto BTree<T>::root() const -> Iterator
{
    return m_root;
}

template<typename T>
auto BTree<T>::end() const -> Iterator
{
    static NodePtr empty;
    return empty;
}

template<typename T>
unsigned BTree<T>::depth() const
{
    std::function<int(NodePtr)> fd;
    fd = [&fd](NodePtr p) -> int {
        if (p) {
            return std::max<int>(fd(p->left), fd(p->right)) + 1;
        }
        return 0;
    };
    return fd(m_root);

    int depth = 0;
    int elCount = size();

    for (int i = 1; i <= elCount; i *= 2) {
        ++depth;
        elCount -= i;
    }

    if (elCount)
        ++depth;

    return depth;
}

template<typename T>
bool BTree<T>::remove(T data)
{
    m_insertion_flag = false;
    m_root = remove(m_root, data);
    return m_insertion_flag;
}

template<typename T>
auto BTree<T>::remove(NodePtr n, T data) -> NodePtr
{
    if (!n)
        return n;
    if (data < n->data)
        n->left = remove(n->left, data);
    else if (data == n->data) {
        m_insertion_flag = true;
        m_size--;

        auto q = n->left;
        auto r = n->right;
        if (!r)
            return q;

        auto min = findmin(r);
        min->right = removeMin(r);
        min->left = q;


        return balance(min);
    }
    else
        n->right = remove(n->right, data);

    return balance(n);
}

template<typename T>
auto BTree<T>::findmin(NodePtr n) -> NodePtr
{
    return n->left ? findmin(n->left) : n;
}

template<typename T>
auto BTree<T>::removeMin(NodePtr n) -> NodePtr
{
    if (!n->left)
        return n->right;
    n->left = removeMin(n->left);
    return balance(n);
}

