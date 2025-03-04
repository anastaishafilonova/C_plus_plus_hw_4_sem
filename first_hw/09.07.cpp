#include <iostream>
#include <memory>

template <typename T>
class Tree {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent;

        Node(T value) : data(value), left(nullptr), right(nullptr) {}

        ~Node() {
            std::cout << "Node with value " << data << " is destructed\n";
        }
    };

    std::shared_ptr<Node> root;

public:
    Tree() : root(nullptr) {}

    ~Tree() {
        std::cout << "Tree is destructed\n";
    }

    void insert(const T& value) {
        if (!root) {
            root = std::make_shared<Node>(value);
        } else {
            insertHelper(root, value);
        }
    }

    std::shared_ptr<Node> find(const T& value) const {
        return findHelper(root, value);
    }

    void remove(const T& value) {
        auto node = find(value);
        if (node) {
            removeHelper(node);
        }
    }

    int getMin() const {
        return getMin(root)->data;
    }

    void makeCycle() {
        
    }

private:
    
    void insertHelper(std::shared_ptr<Node> node, const T& value) {
        if (value < node->data) {
            if (node->left) {
                insertHelper(node->left, value);
            } else {
                node->left = std::make_shared<Node>(value);
                node->left->parent = node;
            }
        } else {
            if (node->right) {
                insertHelper(node->right, value);
            } else {
                node->right = std::make_shared<Node>(value);
                node->right->parent = node;
            }
        }
    }

    std::shared_ptr<Node> findHelper(std::shared_ptr<Node> node, const T& value) const {
        if (!node || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return findHelper(node->left, value);
        } else {
            return findHelper(node->right, value);
        }
    }

    void removeHelper(std::shared_ptr<Node> node) {
        if (!node->left && !node->right) {
            auto parent = node->parent.lock();
            if (parent) {
                if (parent->left == node) {
                    parent->left.reset();
                } else {
                    parent->right.reset();
                }
            } else {
                root.reset();
            }
        } else if (node->left && node->right) {
            auto successor = getMin(node->right);
            node->data = successor->data;
            removeHelper(successor);
        } else {
            auto child = node->left ? node->left : node->right;
            auto parent = node->parent.lock();
            if (parent) {
                if (parent->left == node) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
                child->parent = parent;
            } else {
                root = child;
                child->parent.reset();
            }
        }
    }

    std::shared_ptr<Node> getMin(std::shared_ptr<Node> node) const {
        while (node->left) {
            node = node->left;
        }
        return node;
    }
};


int main() {
    Tree<int> tree = Tree<int>();
    tree.insert(2);
    tree.insert(4);
    tree.insert(13);
    std::cout << tree.getMin() << "\n";
    tree.remove(2);
    std::cout << tree.getMin() << "\n";
    std::cout << tree.find(1) << "\n";
}
