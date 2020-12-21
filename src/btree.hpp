#pragma once

#ifndef BTREE_HPP
#define BTREE_HPP

#include <memory>
#include <iostream>
#include <string>
#include <cstdint>
#include <functional>
#include <algorithm>

template<typename T>
class BTree {
private:

    struct Node {
        T data;
        int height = 1;

        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node() = default;
        Node(T _data);
    };

    using NodePtr = std::shared_ptr<Node>;

public:

    class Iterator {
        friend class BTree<T>;
    private:
        NodePtr ptr;
        Iterator(NodePtr _ptr);
    public:
        Iterator left() const;
        Iterator right() const;
        const T& operator*() const;
        const T* operator->() const;

        inline bool operator==(const Iterator& it) const { return ptr == it.ptr; }
        inline bool operator!=(const Iterator& it) const { return ptr != it.ptr; }
    };

private:

    NodePtr m_root;
    unsigned int m_size = 0;
    bool m_insertion_flag;

public:
    BTree() = default;
    BTree(const BTree&) = delete;
    
    BTree& operator=(const BTree&) = delete;

    bool insert(T data);
    bool remove(T data);

    unsigned depth() const;

    Iterator root() const;
    Iterator end()  const;

    inline unsigned size() const { return m_size; }

private:
    NodePtr insert(NodePtr node, T data);
    NodePtr balance(NodePtr node);
    void fixheight(NodePtr node);
    int bfactor(NodePtr node);
    NodePtr rotateRight(NodePtr node);
    NodePtr rotateLeft(NodePtr node);

    NodePtr remove(NodePtr n, T data);
    NodePtr findmin(NodePtr n);
    NodePtr removeMin(NodePtr n);
};

#include "btree.tcc"

#endif // BTEE_HPP
