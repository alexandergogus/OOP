#include <iostream>
using namespace std;

class BST {
private:
    struct subset_node {
        int key;
        subset_node *left;
        subset_node *right;
        subset_node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    subset_node *root;

    bool insert(subset_node **sn, int k) {
        if (*sn == nullptr) {
            *sn = new subset_node(k);
            return true;
        }
        if (k < (*sn)->key) {
            return insert(&(*sn)->left, k);
        } else if (k > (*sn)->key) {
            return insert(&(*sn)->right, k);
        }
        return false;
    }

    subset_node* find(subset_node *sn, int k) const {
        if (sn == nullptr) return nullptr;
        if (k < sn->key) return find(sn->left, k);
        if (k > sn->key) return find(sn->right, k);
        return sn;
    }

    bool remove(subset_node **sn, int k) {
        if (*sn == nullptr) return false;
        if (k < (*sn)->key) return remove(&(*sn)->left, k);
        if (k > (*sn)->key) return remove(&(*sn)->right, k);

        if ((*sn)->left == nullptr) {
            subset_node *temp = (*sn)->right;
            delete *sn;
            *sn = temp;
        } else if ((*sn)->right == nullptr) {
            subset_node *temp = (*sn)->left;
            delete *sn;
            *sn = temp;
        } else {
            subset_node *temp = (*sn)->right;
            while (temp && temp->left != nullptr) {
                temp = temp->left;
            }
            (*sn)->key = temp->key;
            remove(&(*sn)->right, temp->key);
        }
        return true;
    }

    unsigned int size(subset_node *sn) const {
        if (sn == nullptr) return 0;
        return 1 + size(sn->left) + size(sn->right);
    }

    unsigned int height(subset_node *sn) const {
        if (sn == nullptr) return 0;
        unsigned int leftHeight = height(sn->left);
        unsigned int rightHeight = height(sn->right);
        return 1 + max(leftHeight, rightHeight);
    }

    void destructor(subset_node *sn) {
        if (sn == nullptr) return;
        destructor(sn->left);
        destructor(sn->right);
        delete sn;
    }

    void DFSHelper(subset_node *sn, int* arr, int &index) const {
        if (sn == nullptr) return;
        DFSHelper(sn->left, arr, index);
        arr[index++] = sn->key;
        DFSHelper(sn->right, arr, index);
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        destructor(root);
    }

    bool insert(int k) {
        return insert(&root, k);
    }

    bool find(int k) const {
        return find(root, k) != nullptr;
    }

    bool remove(int k) {
        return remove(&root, k);
    }

    unsigned int size() const {
        return size(root);
    }

    unsigned int height() const {
        return height(root);
    }

    int* DFS() const {
        unsigned int tree_size = size();
        int* arr = new int[tree_size];
        int index = 0;
        DFSHelper(root, arr, index);
        return arr;
    }
};

int main() {
    BST bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);

    cout << "Size of the tree: " << bst.size() << endl;
    cout << "Height of the tree: " << bst.height() << endl;

    cout << "DFS traversal: ";
    int* dfs_result = bst.DFS();
    for (unsigned int i = 0; i < bst.size(); ++i) {
        cout << dfs_result[i] << " ";
    }
    cout << endl;
    delete[] dfs_result;

    cout << "Removing 5..." << endl;
    bst.remove(5);
    cout << "Size after removal: " << bst.size() << endl;

    cout << "DFS traversal after removal: ";
    dfs_result = bst.DFS();
    for (unsigned int i = 0; i < bst.size(); ++i) {
        cout << dfs_result[i] << " ";
    }
    cout << endl;
    delete[] dfs_result;

    bst.~BST();

    return 0;
}
