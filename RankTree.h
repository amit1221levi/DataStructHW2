//
// Created by amit levi on 21/12/2022.
///=============================================================================================
///=============================================================================================
//                         ##########    ###########
//                         ##      ##        ##
//                         ##########        ##
//                         ##       ##       ##
//                         ##        ##      ##
///=============================================================================================
///=============================================================================================
#ifndef DATASTRUCTHW2_RANKTREE_H
#define DATASTRUCTHW2_RANKTREE_H
#include <iostream>
template <class K,class V>
class AVLNode
{
public:
    AVLNode(K key,V& value) : key(key), data(&value), rank(1), left_node(nullptr), right_node(nullptr), parent_node(nullptr) {}
    ~AVLNode() {}
    V& getValue() const { return *data; }
    const K getKey() const { return key; }
    void setLeft(AVLNode* left) { left_node = left; }
    AVLNode* getLeft() const { return left_node; }
    void setRight(AVLNode* right) { right_node = right; }
    AVLNode* getRight() const { return right_node; }
    void setParent(AVLNode* parent) { parent_node = parent; }
    AVLNode* getParent() const { return parent_node; }

    void print() const { std::cout << data; }

    AVLNode();

    K key;
    V* data;
    int rank;//will help us to find the index of a certain value
    AVLNode* left_node;
    AVLNode* right_node;
    AVLNode* parent_node;
};
///=====================================root_node======================================================
template <class K,class V>
class RankTree
{
public:
    RankTree() : root_node(nullptr),numberOfNodes(0) {}
    ~RankTree();
    void insert(K key,V& value);
    void remove(const K key);
    AVLNode<K,V>* get_root() const { return root_node; }
    AVLNode<K,V>* find(AVLNode<K,V>* root, const K key) const;
    int get_height(AVLNode<K,V>* root) const;
    int balance_factor(AVLNode<K,V>* root) const;
    void fix_parent(AVLNode<K,V>* root);
    void fixNodeParent(AVLNode<K,V>* node, K key) const;
    AVLNode<K,V>* rotateLeft(AVLNode<K,V>* root);
    AVLNode<K,V>* rotateRight(AVLNode<K,V>* root);
    void print_inOrder(AVLNode<K,V>* root) const; // Left, Parent, Right
    void deleteAVLNode(AVLNode<K,V>* node);
    AVLNode<K,V>* min_value_node(AVLNode<K,V>* node);
    void insertAVLNode(AVLNode<K,V>* root, AVLNode<K,V>* ins);
    AVLNode<K,V>* deleteNode(AVLNode<K,V>* root, K key);
    V& select(int k);
    V& selectNode(AVLNode<K,V>* root, int k);

    AVLNode<K,V>* root_node;
    int numberOfNodes;
    class ALREADY_EXIST
    {
    };
    class ALLOC_ERROR
    {
    };
    class NOT_EXIST
    {
    };
};

//=============================================================================================
///=====================================FUNCTIONS======================================================
//=============================================================================================

///=====================================deleteAVLNode======================================================
//deletes all nodes in postorder
template <class K,class V>
void RankTree<K,V>::deleteAVLNode(AVLNode<K,V>* node)
{
    if (node)
    {
        if (node->getRight() != nullptr)
            deleteAVLNode(node->getRight());
        if (node->getLeft() != nullptr)
            deleteAVLNode(node->getLeft());

        delete node; // Post Order Deletion
    }
}

///=====================================~RankTree======================================================
template <class K,class V>
RankTree<K,V>::~RankTree()
{
    if (root_node)
    {
        deleteAVLNode(root_node);
    }
}

///=====================================insert======================================================
//insert new node to the tree
template <class K,class V>
void RankTree<K,V>::insert(K key,V& value)
{
    AVLNode<K,V>* new_node = new (std::nothrow) AVLNode<K,V>(key,value);

    if (!new_node)
        throw(RankTree<K,V>::ALLOC_ERROR()); // Out of memory
    if (!root_node)                        //
    {
        root_node = new_node;
    }
    else
    {
        insertAVLNode(root_node, new_node);
    }
    fixNodeParent(root_node, key);
    numberOfNodes++;
}

///=====================================rotateLeft======================================================
//rotating the tree left(as RR rotation) while keeping the balance in the nodes
template <class K,class V>
AVLNode<K,V>* RankTree<K,V>::rotateLeft(AVLNode<K,V>* root)
{
    AVLNode<K,V>* new_root_after_rotation = root->getRight();
    root->setRight(new_root_after_rotation->getLeft());
    new_root_after_rotation->setLeft(root);
    new_root_after_rotation->setParent(root->getParent());
    if (root->getRight())
    {
        root->getRight()->setParent(root);
    }
    if (root->getParent() == nullptr)
    {
        root_node = new_root_after_rotation;
        new_root_after_rotation->setParent(nullptr);
    }
    else
    {
        if (root->getParent()->getLeft() == root)
        {
            root->getParent()->setLeft(new_root_after_rotation);
        }
        else
        {
            root->getParent()->setRight(new_root_after_rotation);
        }
        new_root_after_rotation->setParent(root->getParent());
    }
    root->setParent(new_root_after_rotation);
    int rank_bl = 0;
    int rank_br = 0;
    int rank_al = 0;

    if ((new_root_after_rotation->getLeft()) != nullptr)
    {
        if (((new_root_after_rotation->getLeft())->getLeft()) != nullptr)
        {
            rank_al = ((new_root_after_rotation->getLeft())->getLeft())->rank;
        }
        if ((new_root_after_rotation->getLeft())->getRight() != nullptr)
        {
            rank_bl = ((new_root_after_rotation->getLeft())->getRight())->rank;
        }
    }
    if ((new_root_after_rotation->getRight()) != nullptr)
    {
        rank_br = (new_root_after_rotation->getRight())->rank;
    }
    (new_root_after_rotation->getLeft())->rank = 1 + rank_bl + rank_al;
    (new_root_after_rotation->rank) = 2 + rank_br + rank_al + rank_bl;
    return new_root_after_rotation;
}

///=====================================insertAVLNode======================================================
//recursive function to insert a new node to the tree, then balancing the tree to
//keep him AVL tree
template <class K,class V>
void RankTree<K,V>::insertAVLNode(AVLNode<K,V>* root, AVLNode<K,V>* node_to_insert)
{
    // Binary Search Tree insertion algorithm
    (root->rank)++;
    if (node_to_insert->getKey() <= root->getKey())
    {
        if (root->getLeft()) // If there is a left child, keep searching
            insertAVLNode(root->getLeft(), node_to_insert);
        else
        { // Found the right spot
            if (node_to_insert == root)
            {
                throw(RankTree<K,V>::ALREADY_EXIST());
            }
            root->setLeft(node_to_insert);
            node_to_insert->setParent(root);
        }
    }
    else
    {
        if (root->getRight()) // If there is a right child, keep searching
            insertAVLNode(root->getRight(), node_to_insert);
        else
        { // Found the right spot
            if (node_to_insert == root)
            {
                throw(RankTree<K,V>::ALREADY_EXIST());
            }
            root->setRight(node_to_insert);
            node_to_insert->setParent(root);
        }
    }

    // after we added the new node we might damaged the varient of the tree, so we must balance it again
    //(the varient is that for each node the balance factor is smaller then 2 or and bigger than -2 -1=<BF<=1)
    int balance = balance_factor(root);
    if (balance > 1)
    { //unbalanced from the left
        if (balance_factor(root->getLeft()) < 0)
        {                                //we have to much on the right in the left subtree
            rotateLeft(root->getLeft()); //preforming another roatioation to fix balance
        }
        rotateRight(root);
    }
    else if (balance < -1)
    { //  unbalanced from the right
        if (balance_factor(root->getRight()) > 0)
        {                                  // we have to much on the left in the right subtree
            rotateRight(root->getRight()); //preforming another roatioation to fix balance
        }
        rotateLeft(root);
    }
}

///====================================print_inOrder======================================================
//prints the tree inorder(smallest to biggest)
template <class K,class V>
void RankTree<K,V>::print_inOrder(AVLNode<K,V>* root) const
{
    if (root)
    {
        printInOrder(root->getLeft()); // Left
        root->print();                 // Parent
        std::cout << "rank: " << root->rank << " , ";
        printInOrder(root->getRight()); // Right
    }
}

///=====================================find======================================================
//finding the requested value in the tree, recursive function until we get to the value
//log(n)
template <class K,class V>
AVLNode<K,V>* RankTree<K,V>::find(AVLNode<K,V>* root, K key) const
{
    fixNodeParent(root, key);
    if (root != nullptr)
    {
        if (root->getKey() == key)
        {
            return root; // Founds
        }
        else if (key < root->getKey())
        {
            return find(root->getLeft(), key);
        }
        else
        {
            return find(root->getRight(), key);
        }
    }
    return nullptr;
}

///=====================================fix_node_parent======================================================
//fix the parents of the node that contains the value
template <class K,class V>
void RankTree<K,V>::fixNodeParent(AVLNode<K,V>* root, K key) const
{
    if (root != nullptr)
    {
        if (key < root->getKey())
        {
            if (root->getLeft())
            {
                if (root->getLeft()->getKey() == key)
                {
                    root->getLeft()->setParent(root);
                }
            }
            fixNodeParent(root->getLeft(), key);
        }
        else
        {
            if (root->getRight())
            {
                if (root->getRight()->getKey() == key)
                {
                    root->getRight()->setParent(root);
                }
            }
            fixNodeParent(root->getRight(), key);
        }
    }
}

//return the height of some node in the tree
template <class K,class V>
int RankTree<K,V>::get_height(AVLNode<K,V>* root) const
{
    int height = 0;
    if (root != nullptr)
    {
        int right = get_height(root->getRight());
        int left = get_height(root->getLeft());
        height = 1 + ((left > right) ? left : right);
    }
    return height;
}

///=====================================balance_factor======================================================
//return's the balance factor of some node in the tree
template <class K,class V>
int RankTree<K,V>::balance_factor(AVLNode<K,V>* root) const
{
    int balance = 0;
    if (root != nullptr)
    {
        balance = get_height(root->getLeft()) - get_height(root->getRight());
    }
    return balance;
}

///=====================================fix_parent======================================================
//sets the first node parent to be nullptr
template <class K,class V>
void RankTree<K,V>::fix_parent(AVLNode<K,V>* root)
{
    if (root != nullptr)
    {
        if (root->getParent())
        {
            if (root->getParent()->getKey() == root->getKey())
            {
                root->setParent(nullptr);
            }
        }
    }
}

///=====================================rotateRight======================================================
//rotating the tree right(as LL rotation) while keeping the tree balanced
template <class K,class V>
AVLNode<K,V>* RankTree<K,V>::rotateRight(AVLNode<K,V>* root)
{
    // preforming the rotation of the nodes
    AVLNode<K,V>* new_root_after_rotation = root->getLeft();
    root->setLeft(new_root_after_rotation->getRight());
    new_root_after_rotation->setRight(root);
    new_root_after_rotation->setParent(root->getParent());
    if (root->getLeft())
    {
        root->getLeft()->setParent(root);
    }
    // orginanizing the tree
    if (root->getParent() == nullptr)
    {
        root_node = new_root_after_rotation;
        new_root_after_rotation->setParent(nullptr);
    }
    else
    {
        if (root->getParent()->getLeft() == root)
        {
            root->getParent()->setLeft(new_root_after_rotation);
        }
        else
        {
            root->getParent()->setRight(new_root_after_rotation);
        }
        new_root_after_rotation->setParent(root->getParent());
    }
    root->setParent(new_root_after_rotation);
    int rank_br = 0;
    int rank_ar = 0;
    int rank_al = 0;

    if ((new_root_after_rotation->getRight()) != nullptr)
    {
        if (((new_root_after_rotation->getRight())->getRight()) != nullptr)
        {
            rank_br = ((new_root_after_rotation->getRight())->getRight())->rank;
        }
        if (((new_root_after_rotation->getRight())->getLeft()) != nullptr)
        {
            rank_ar = ((new_root_after_rotation->getRight())->getLeft())->rank;
        }
    }
    if ((new_root_after_rotation->getLeft()) != nullptr)
    {
        rank_al = (new_root_after_rotation->getLeft())->rank;
    }
    (new_root_after_rotation->getRight())->rank = 1 + rank_br + rank_ar;
    (new_root_after_rotation->rank) = 2 + rank_br + rank_ar + rank_al;
    return new_root_after_rotation;
}


///=====================================remove======================================================
//remove's node that contain value from the tree, while keeping the tree balanced
//o(log(n))
template <class K,class V>
void RankTree<K,V>::remove(const K key)
{
    fix_parent(root_node);
    fixNodeParent(root_node, key);
    AVLNode<K,V>* node = find(root_node, key);
    if (node == nullptr)
    {
        throw(RankTree<K,V>::NOT_EXIST());
    }
    if (!deleteNode(root_node, key)){
        root_node = nullptr;
    }
    numberOfNodes--;
}

///====================================min_value_node======================================================
//return's the smallest value node in a certain subTree
template <class K,class V>
AVLNode<K,V>* RankTree<K,V>::min_value_node(AVLNode<K,V>* node)
{
    AVLNode<K,V>* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left_node != nullptr)
        current = current->left_node;

    return current;
}

///====================================selectNode======================================================
template <class K,class V>
V& RankTree<K,V>::selectNode(AVLNode<K,V>* root, int k)
{
    int left_rank = 0;
    if (root->getLeft() != nullptr)
    {
        left_rank = (root->getLeft())->rank;
    }
    if (left_rank == k - 1)
    {
        return root->getValue();
    }
    if (left_rank > k - 1)//goLeft
    {
        return selectNode(root->getLeft(), k);
    }
    return selectNode(root->getRight(), k - 1 - left_rank);
}

///====================================deleteNode======================================================
//recursive function to delete a node from the tree
template <class K,class V>
AVLNode<K,V>* RankTree<K,V>::deleteNode(AVLNode<K,V>* root, K key)
{
    if (root == nullptr)
        return root;
    (root->rank)--;
    if (key < root->key) //key is smaller, then search left
    { 
        root->left_node = deleteNode(root->left_node, key);
    }
    else if (key > root->getKey()) //key is bigger, then search right
    { 
        root->right_node = deleteNode(root->right_node, key);
    }
    else
    {
        // split to options only child, only leftson or only rightson
        if ((root->right_node == nullptr) || (root->left_node == nullptr))
        {
            AVLNode<K,V>* node_temp = root->left_node; //if there is no left son the temp will be nullptr
            if (node_temp == nullptr)
            {
                node_temp = root->right_node; //if the there is no right son the temp will be nullptr therefore there will be no sons
            }
            // got here there are no sons
            if (node_temp == nullptr)
            {
                node_temp = root;
                root = nullptr;
            }
            else //one of the sons was not nullptr therefore we change the corrent node to be the son and delete the temp
            {
                AVLNode<K,V>* temp2 = root->getParent();
                *root = *node_temp;
                root->setParent(temp2);
            }
            free(node_temp);
        }
        else
        {
            // the corrent node has two sons, we will replace him, so we take only the data from the minimal value from the right sub tree
            AVLNode<K,V>* temp = min_value_node(root->right_node);
            root->data = temp->data;
            root->key = temp->key;
            root->right_node = deleteNode(root->right_node, temp->key); // remove the node we took the data from
        }
    }
    //only one node in the tree, therefore we need to remove it and finish
    if (root == nullptr)
    {
        return nullptr;
    }
    //balance algorythem for AVL
    int balance = balance_factor(root);
    if (balance_factor(root->right_node) > 0 && balance < -1) //need to preform right the left  rotation on the tree
    {
        root->right_node = rotateRight(root->right_node);
        return rotateLeft(root);
    }
    if (balance_factor(root->left_node) >= 0 && balance > 1) //need to preform right rotation on the tree
    {
        return rotateRight(root);
    }
    if (balance_factor(root->right_node) <= 0 && balance < -1) //need to preform left rotation on the tree
    {
        return rotateLeft(root);
    }
    if (balance_factor(root->left_node) < 0 && balance > 1) //need to preform left then right rotation on the tree
    {
        root->left_node = rotateLeft(root->left_node);
        return rotateRight(root);
    }
    return root;
}

///====================================select======================================================
template <class K,class V>
V& RankTree<K,V>::select(int k)
{
    if (root_node == nullptr || k > (root_node->rank))
        throw(NOT_EXIST());
    return selectNode(root_node, (k));//sucsses for sure
}

#endif //DATASTRUCTHW2_RANKTREE_H
///=============================================================================================
///=============================================================================================
//                         ##########    ###########
//                         ##      ##        ##
//                         ##########        ##
//                         ##       ##       ##
//                         ##        ##      ##
///=============================================================================================
///=============================================================================================
