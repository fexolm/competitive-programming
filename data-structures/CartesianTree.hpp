#pragma once
#include <random>
namespace ds {
template<typename TValue>
class CartesianTree {
public:
  struct Node {
    TValue value;
    long priority;
    Node *left;
    Node *right;

    Node()
        : priority(random()),
          left(nullptr),
          right(nullptr) {}
  };
  Node *root;
  CartesianTree()
      : root(nullptr) {}

  CartesianTree(Node *node)
      : root(node) {}

  CartesianTree(const CartesianTree &) = default;
  CartesianTree &operator=(const CartesianTree &) = default;
  CartesianTree(CartesianTree &&) = default;
  CartesianTree &operator=(CartesianTree &&) = default;

  void insert(TValue val);

  void erase(TValue val);
};

template<typename T>
using node_t = typename CartesianTree<T>::Node *;

template<typename T>
inline void merge(node_t<T> &res, node_t<T> lhs, node_t<T> rhs) {
  if (!lhs || !rhs) {
    res = lhs ? lhs : rhs;
    return;
  }
  if (lhs->priority > rhs->priority) {
    merge(lhs->right, lhs->right, rhs);
    res = lhs;
  } else {
    merge(rhs->left, lhs, rhs->left);
    res = rhs;
  }
}

template<typename T>
inline void split(node_t<T> cur, T key, node_t<T> &lhs, node_t<T> &rhs) {
  if (!cur) {
    lhs = rhs = nullptr;
    return;
  }
  if (key < cur->value) {
    split(cur->left, key, lhs, cur->left);
    rhs = cur;
  } else {
    split(cur->right, key, cur->right, rhs);
    lhs = cur;
  }
}

template<typename T>
inline void insert(node_t<T> &root, node_t<T> node) {
  if (!root) {
    root = node;
    return;
  }
  if (root->priority < node->priority) {
    split<T>(root, node->value, node->left, node->right);
    root = node;
  } else {
    insert<T>(root->value > node->value ? root->left : root->right, node);
  }
}

template<typename T>
inline void erase(node_t<T> root, T key) {
  if (root->value > key) {
    erase(root->right, key);
  } else if (root->value < key) {
    erase(root->left, key);
  } else {
    merge(root, root->left, root->right);
  }
}

template<typename TValue>
void CartesianTree<TValue>::insert(TValue val) {
  Node *node = new Node;
  node->value = val;
  ds::insert<TValue>(root, node);
}
template<typename TValue>
void CartesianTree<TValue>::erase(TValue val) {
  ds::erase<TValue>(root, val);
}
}