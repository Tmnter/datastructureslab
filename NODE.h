#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
template <typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> prev; // Для однозв'язного просто ігноруємо це поле

    Node(T val) : data(val), next(nullptr) {}
};
#endif // NODE_H_INCLUDED
