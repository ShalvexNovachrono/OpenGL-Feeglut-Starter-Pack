#ifndef KeyValue
#define KeyValue
#include "main.h"
#include "Array.h"

template <typename K, typename V>
struct Entry {
    K key;
    V value;

    bool operator==(const Entry& other) const {
        return key == other.key;
    }
};

template <typename K, typename V>
struct TreeNode {
    Entry<K, V> entry;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int height = 1;
};

template <typename K, typename V>
class CKeyValue {
private:
    TreeNode<K, V>* root = nullptr;
    int size = 0;

    int Height(TreeNode<K, V>* n) const {
        return n ? n->height : 0;
    }

    void UpdateHeight(TreeNode<K, V>* n) {
        n->height = 1 + max(Height(n->left), Height(n->right));
    }

    int BalanceFactor(TreeNode<K, V>* n) const {
        return n ? Height(n->left) - Height(n->right) : 0;
    }

    TreeNode<K, V>* RotateRight(TreeNode<K, V>* y) {
        TreeNode<K, V>* x = y->left;
        y->left = x->right;
        x->right = y;
        UpdateHeight(y);
        UpdateHeight(x);
        return x;
    }

    TreeNode<K, V>* RotateLeft(TreeNode<K, V>* x) {
        TreeNode<K, V>* y = x->right;
        x->right = y->left;
        y->left = x;
        UpdateHeight(x);
        UpdateHeight(y);
        return y;
    }

    TreeNode<K, V>* Rebalance(TreeNode<K, V>* n) {
        UpdateHeight(n);
        int bf = BalanceFactor(n);
        if (bf > 1) {
            if (BalanceFactor(n->left) < 0)
                n->left = RotateLeft(n->left);
            return RotateRight(n);
        }
        if (bf < -1) {
            if (BalanceFactor(n->right) > 0)
                n->right = RotateRight(n->right);
            return RotateLeft(n);
        }
        return n;
    }

    TreeNode<K, V>* Insert(TreeNode<K, V>* n, const K& key, const V& value) {
        if (!n) {
            ++size;
            return new TreeNode<K, V>{ {key, value}, nullptr, nullptr, 1 };
        }
        if (key < n->entry.key)
            n->left = Insert(n->left, key, value);
        else if (n->entry.key < key)
            n->right = Insert(n->right, key, value);
        else
            n->entry.value = value;
        return Rebalance(n);
    }

    TreeNode<K, V>* InsertDefault(TreeNode<K, V>* n, const K& key) {
        if (!n) {
            ++size;
            return new TreeNode<K, V>{ {key, V()}, nullptr, nullptr, 1 };
        }
        if (key < n->entry.key)
            n->left = InsertDefault(n->left, key);
        else if (n->entry.key < key)
            n->right = InsertDefault(n->right, key);
        return Rebalance(n);
    }

    TreeNode<K, V>* FindMin(TreeNode<K, V>* n) const {
        while (n->left) n = n->left;
        return n;
    }

    TreeNode<K, V>* RemoveMin(TreeNode<K, V>* n) {
        if (!n->left) return n->right;
        n->left = RemoveMin(n->left);
        return Rebalance(n);
    }

    TreeNode<K, V>* Remove(TreeNode<K, V>* n, const K& key) {
        if (!n) return nullptr;
        if (key < n->entry.key) {
            n->left = Remove(n->left, key);
        } else if (n->entry.key < key) {
            n->right = Remove(n->right, key);
        } else {
            --size;
            TreeNode<K, V>* left = n->left;
            TreeNode<K, V>* right = n->right;
            delete n;
            if (!right) return left;
            TreeNode<K, V>* min = FindMin(right);
            min->right = RemoveMin(right);
            min->left = left;
            return Rebalance(min);
        }
        return Rebalance(n);
    }

    TreeNode<K, V>* Find(TreeNode<K, V>* n, const K& key) const {
        if (!n) return nullptr;
        if (key < n->entry.key) return Find(n->left, key);
        if (n->entry.key < key) return Find(n->right, key);
        return n;
    }

    void DestroyTree(TreeNode<K, V>* n) {
        if (!n) return;
        DestroyTree(n->left);
        DestroyTree(n->right);
        delete n;
    }

    void CopyTree(TreeNode<K, V>*& dest, TreeNode<K, V>* src) {
        if (!src) { dest = nullptr; return; }
        dest = new TreeNode<K, V>{ src->entry, nullptr, nullptr, src->height };
        CopyTree(dest->left, src->left);
        CopyTree(dest->right, src->right);
    }

public:
    CKeyValue() = default;

    ~CKeyValue() {
        DestroyTree(root);
    }

    CKeyValue(const CKeyValue& other) : size(other.size) {
        CopyTree(root, other.root);
    }

    CKeyValue& operator=(const CKeyValue& other) {
        if (this != &other) {
            DestroyTree(root);
            size = other.size;
            CopyTree(root, other.root);
        }
        return *this;
    }

    void Add(const K& key, const V& value) {
        root = Insert(root, key, value);
    }

    void Remove(const K& key) {
        root = Remove(root, key);
    }

    void Clear() {
        DestroyTree(root);
        root = nullptr;
        size = 0;
    }

    V Get(const K& key) const {
        TreeNode<K, V>* n = Find(root, key);
        return n ? n->entry.value : V();
    }

    V* GetPtr(const K& key) {
        TreeNode<K, V>* n = Find(root, key);
        return n ? &n->entry.value : nullptr;
    }

    bool Has(const K& key) const {
        return Find(root, key) != nullptr;
    }

    int GetSize() const {
        return size;
    }
    
    CArray<Entry<K, V>>& GetEntries() {
        CArray<Entry<K, V>> result;
        for (const auto& entry : *this) {
            result.Append(entry);
        }
        return result;
    }
    
    const CArray<Entry<K, V>>& GetEntries() const {
        CArray<Entry<K, V>> result;
        for (const auto& entry : *this) {
            result.Append(entry);
        }
        return result;
    }

    bool operator==(const CKeyValue& other) const {
        if (size != other.size) return false;
        auto it1 = begin();
        auto it2 = other.begin();
        while (it1 != end()) {
            if (!(*it1 == *it2)) return false;
            ++it1;
            ++it2;
        }
        return true;
    }

    V& operator[](const K& key) {
        root = InsertDefault(root, key);
        return Find(root, key)->entry.value;
    }

    struct iterator {
        std::stack<TreeNode<K, V>*> stack;

        iterator() = default;

        explicit iterator(TreeNode<K, V>* root) {
            PushLeft(root);
        }

        void PushLeft(TreeNode<K, V>* n) {
            while (n) { stack.push(n); n = n->left; }
        }

        Entry<K, V>& operator*() { return stack.top()->entry; }
        Entry<K, V>* operator->() { return &stack.top()->entry; }

        iterator& operator++() {
            TreeNode<K, V>* n = stack.top();
            stack.pop();
            PushLeft(n->right);
            return *this;
        }

        bool operator==(const iterator& other) const {
            if (stack.empty() && other.stack.empty()) return true;
            if (stack.empty() != other.stack.empty()) return false;
            return stack.top() == other.stack.top();
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    struct const_iterator {
        std::stack<const TreeNode<K, V>*> stack;

        const_iterator() = default;

        explicit const_iterator(const TreeNode<K, V>* root) {
            PushLeft(root);
        }

        void PushLeft(const TreeNode<K, V>* n) {
            while (n) { stack.push(n); n = n->left; }
        }

        const Entry<K, V>& operator*() const { return stack.top()->entry; }
        const Entry<K, V>* operator->() const { return &stack.top()->entry; }

        const_iterator& operator++() {
            const TreeNode<K, V>* n = stack.top();
            stack.pop();
            PushLeft(n->right);
            return *this;
        }

        bool operator==(const const_iterator& other) const {
            if (stack.empty() && other.stack.empty()) return true;
            if (stack.empty() != other.stack.empty()) return false;
            return stack.top() == other.stack.top();
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }
    };

    iterator begin() { return iterator(root); }
    iterator end() { return iterator(); }
    const_iterator begin() const { return const_iterator(root); }
    const_iterator end() const { return const_iterator(); }

    iterator find(const K& key) {
        iterator it;
        TreeNode<K, V>* n = root;
        while (n) {
            if (key < n->entry.key) {
                it.stack.push(n);
                n = n->left;
            } else if (n->entry.key < key) {
                n = n->right;
            } else {
                it.stack.push(n);
                return it;
            }
        }
        return end();
    }

    const_iterator find(const K& key) const {
        const_iterator it;
        const TreeNode<K, V>* n = root;
        while (n) {
            if (key < n->entry.key) {
                it.stack.push(n);
                n = n->left;
            } else if (n->entry.key < key) {
                n = n->right;
            } else {
                it.stack.push(n);
                return it;
            }
        }
        return end();
    }
};

#endif