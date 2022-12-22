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
template <class T>
class AVLNode
{
public:
    AVLNode(const T& value) : data(value), rank(1), left_node(NULL), right_node(NULL), parent_node(NULL) {}
    ~AVLNode() {}
    const T& getValue() const { return data; }
    void setLeft(AVLNode* left) { left_node = left; }
    AVLNode* getLeft() const { return left_node; }
    void setRight(AVLNode* right) { right_node = right; }
    AVLNode* getRight() const { return right_node; }
    void setParent(AVLNode* parent) { parent_node = parent; }
    AVLNode* getParent() const { return parent_node; }

    void print() const { std::cout << data; }

    AVLNode();

    T data;
    int rank;//will help us to find the index of a certain value
    AVLNode* left_node;
    AVLNode* right_node;
    AVLNode* parent_node;
};
///=====================================root_node======================================================
template <class T>
class RankTree
{
public:
    RankTree() : root_node(NULL) {}
    ~RankTree();
    void insert(const T& value);
    void remove(const T& value);
    AVLNode<T>* get_root() const { return root_node; }
    AVLNode<T>* find(AVLNode<T>* root, const T& value) const;
    int get_height(AVLNode<T>* root) const;
    int balance_factor(AVLNode<T>* root) const;
    void fix_parent(AVLNode<T>* root);
    void fix_node_parent(AVLNode<T>* node, const T& value) const;
    AVLNode<T>* rotateLeft(AVLNode<T>* root);
    AVLNode<T>* rotateRight(AVLNode<T>* root);
    void print_inOrder(AVLNode<T>* root) const; // Left, Parent, Right
    void deleteAVLNode(AVLNode<T>* node);
    AVLNode<T>* min_value_node(AVLNode<T>* node);
    void insertAVLNode(AVLNode<T>* root, AVLNode<T>* ins);
    AVLNode<T>* deleteNode(AVLNode<T>* root, const T key);
    T& select(int k);
    T& selectNode(AVLNode<T>* root, int k);
    AVLNode<T>* root_node;
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
template <class T>
void RankTree<T>::deleteAVLNode(AVLNode<T>* node)
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
template <class T>
RankTree<T>::~RankTree()
{
    if (root_node)
    {
        deleteAVLNode(root_node);
    }
}

///=====================================insert======================================================
//insert new node to the tree
template <class T>
void RankTree<T>::insert(const T& value)
{
    AVLNode<T>* new_node = new (std::nothrow) AVLNode<T>(value);

    if (!new_node)
        throw(RankTree<T>::ALLOC_ERROR()); // Out of memory
    if (!root_node)                        //
    {
        root_node = new_node;
    }
    else
    {
        if (find(root_node, new_node->getValue()))
            throw(ALREADY_EXIST());
        insertAVLNode(root_node, new_node);
    }
    fixNodeParent(root_node, value);
}

///=====================================rotateLeft======================================================
//rotating the tree left(as RR rotation) while keeping the balance in the nodes
template <class T>
AVLNode<T>* RankTree<T>::rotateLeft(AVLNode<T>* root)
{
    AVLNode<T>* new_root_after_rotation = root->getRight();
    root->setRight(new_root_after_rotation->getLeft());
    new_root_after_rotation->setLeft(root);
    new_root_after_rotation->setParent(root->getParent());
    if (root->getRight())
    {
        root->getRight()->setParent(root);
    }
    if (root->getParent() == NULL)
    {
        root_node = new_root_after_rotation;
        new_root_after_rotation->setParent(NULL);
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

    if ((new_root_after_rotation->getLeft()) != NULL)
    {
        if (((new_root_after_rotation->getLeft())->getLeft()) != NULL)
        {
            rank_al = ((new_root_after_rotation->getLeft())->getLeft())->rank;
        }
        if ((new_root_after_rotation->getLeft())->getRight() != NULL)
        {
            rank_bl = ((new_root_after_rotation->getLeft())->getRight())->rank;
        }
    }
    if ((new_root_after_rotation->getRight()) != NULL)
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
template <class T>
void RankTree<T>::insertAVLNode(AVLNode<T>* root, AVLNode<T>* node_to_insert)
{
    // Binary Search Tree insertion algorithm
    (root->rank)++;
    if (node_to_insert->getValue() <= root->getValue())
    {
        if (root->getLeft()) // If there is a left child, keep searching
            insertAVLNode(root->getLeft(), node_to_insert);
        else
        { // Found the right spot
            if (node_to_insert == root)
            {
                throw(RankTree<T>::ALREADY_EXIST());
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
                throw(RankTree<T>::ALREADY_EXIST());
            }
            root->setRight(node_to_insert);
            node_to_insert->setParent(root);
        }
    }

    // after we added the new node we might damaged the varient of the tree, so we must balance it again
    //(the varient is that for each node the balance factor is smaller then 2 or and bigger than -2 -1=<BF<=1)
    int balance = balanceFactor(root);
    if (balance > 1)
    { //unbalanced from the left
        if (balanceFactor(root->getLeft()) < 0)
        {                                //we have to much on the right in the left subtree
            rotateLeft(root->getLeft()); //preforming another roatioation to fix balance
        }
        rotateRight(root);
    }
    else if (balance < -1)
    { //  unbalanced from the right
        if (balanceFactor(root->getRight()) > 0)
        {                                  // we have to much on the left in the right subtree
            rotateRight(root->getRight()); //preforming another roatioation to fix balance
        }
        rotateLeft(root);
    }
}

///====================================print_inOrder======================================================
//prints the tree inorder(smallest to biggest)
template <class T>
void RankTree<T>::print_inOrder(AVLNode<T>* root) const
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
template <class T>
AVLNode<T>* RankTree<T>::find(AVLNode<T>* root, const T& value) const
{
    fixNodeParent(root, value);
    if (root != NULL)
    {
        if (root->getValue() == value)
        {
            return root; // Founds
        }
        else if (value < root->getValue())
        {
            return find(root->getLeft(), value);
        }
        else
        {
            return find(root->getRight(), value);
        }
    }
    return NULL;
}

///=====================================fix_node_parent======================================================
//fix the parents of the node that contains the value
template <class T>
void RankTree<T>::fix_node_parent(AVLNode<T>* root, const T& value) const
{
    if (root != NULL)
    {
        if (value < root->getValue())
        {
            if (root->getLeft())
            {
                if (root->getLeft()->getValue() == value)
                {
                    root->getLeft()->setParent(root);
                }
            }
            fixNodeParent(root->getLeft(), value);
        }
        else
        {
            if (root->getRight())
            {
                if (root->getRight()->getValue() == value)
                {
                    root->getRight()->setParent(root);
                }
            }
            fixNodeParent(root->getRight(), value);
        }
    }
}

//return the height of some node in the tree
template <class T>
int RankTree<T>::get_height(AVLNode<T>* root) const
{
    int height = 0;
    if (root != NULL)
    {
        int right = getHeight(root->getRight());
        int left = getHeight(root->getLeft());
        height = 1 + ((left > right) ? left : right);
    }
    return height;
}

///=====================================balance_factor======================================================
//return's the balance factor of some node in the tree
template <class T>
int RankTree<T>::balance_factor(AVLNode<T>* root) const
{
    int balance = 0;
    if (root != NULL)
    {
        balance = getHeight(root->getLeft()) - getHeight(root->getRight());
    }
    return balance;
}

///=====================================fix_parent======================================================
//sets the first node parent to be NULL
template <class T>
void RankTree<T>::fix_parent(AVLNode<T>* root)
{
    if (root != NULL)
    {
        if (root->getParent())
        {
            if (root->getParent()->getValue() == root->getValue())
            {
                root->setParent(NULL);
            }
        }
    }
}

///=====================================rotateRight======================================================
//rotating the tree right(as LL rotation) while keeping the tree balanced
template <class T>
AVLNode<T>* RankTree<T>::rotateRight(AVLNode<T>* root)
{
    // preforming the rotation of the nodes
    AVLNode<T>* new_root_after_rotation = root->getLeft();
    root->setLeft(new_root_after_rotation->getRight());
    new_root_after_rotation->setRight(root);
    new_root_after_rotation->setParent(root->getParent());
    if (root->getLeft())
    {
        root->getLeft()->setParent(root);
    }
    // orginanizing the tree
    if (root->getParent() == NULL)
    {
        root_node = new_root_after_rotation;
        new_root_after_rotation->setParent(NULL);
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

    if ((new_root_after_rotation->getRight()) != NULL)
    {
        if (((new_root_after_rotation->getRight())->getRight()) != NULL)
        {
            rank_br = ((new_root_after_rotation->getRight())->getRight())->rank;
        }
        if (((new_root_after_rotation->getRight())->getLeft()) != NULL)
        {
            rank_ar = ((new_root_after_rotation->getRight())->getLeft())->rank;
        }
    }
    if ((new_root_after_rotation->getLeft()) != NULL)
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
template <class T>
void RankTree<T>::remove(const T& value)
{
    fixParent(root_node);
    fixNodeParent(root_node, value);
    AVLNode<T>* node = find(root_node, value);
    if (node == NULL)
    {
        throw(RankTree<T>::NOT_EXIST());
    }
    if (!deleteNode(root_node, value))
        root_node = NULL;
}

///====================================min_value_node======================================================
//return's the smallest value node in a certain subTree
template <class T>
AVLNode<T>* RankTree<T>::min_value_node(AVLNode<T>* node)
{
    AVLNode<T>* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left_node != NULL)
        current = current->left_node;

    return current;
}

///====================================selectNode======================================================
template <class T>
T& RankTree<T>::selectNode(AVLNode<T>* root, int k)
{
    int left_rank = 0;
    if (root->getLeft() != NULL)
    {
        left_rank = (root->getLeft())->rank;
    }
    if (left_rank == k - 1)
    {
        return root->data;
    }
    if (left_rank > k - 1)//goLeft
    {
        return selectNode(root->getLeft(), k);
    }
    return selectNode(root->getRight(), k - 1 - left_rank);
}

///====================================deleteNode======================================================
//recursive function to delete a node from the tree
template <class T>
AVLNode<T>* RankTree<T>::deleteNode(AVLNode<T>* root, const T key)
{
    if (root == NULL)
        return root;
    (root->rank)--;
    if (key < root->data) //key is smaller, then search left
        root->left_node = deleteNode(root->left_node, key);
    else if (key > root->data) //key is bigger, then search right
        root->right_node = deleteNode(root->right_node, key);
    else
    {
        // split to options only child, only leftson or only rightson
        if ((root->right_node == NULL) || (root->left_node == NULL))
        {
            AVLNode<T>* node_temp = root->left_node; //if there is no left son the temp will be null
            if (node_temp == NULL)
            {
                node_temp = root->right_node; //if the there is no right son the temp will be null therefore there will be no sons
            }
            // got here there are no sons
            if (node_temp == NULL)
            {
                node_temp = root;
                root = NULL;
            }
            else //one of the sons was not null therefore we change the corrent node to be the son and delete the temp
            {
                AVLNode<T>* temp2 = root->getParent();
                *root = *node_temp;
                root->setParent(temp2);
            }
            free(node_temp);
        }
        else
        {
            // the corrent node has two sons, we will replace him, so we take only the data from the minimal value from the right sub tree
            AVLNode<T>* temp = minValueNode(root->right_node);
            root->data = temp->data;
            root->right_node = deleteNode(root->right_node, temp->data); // remove the node we took the data from

        }
    }
    //only one node in the tree, therefore we need to remove it and finish
    if (root == NULL)
    {
        return NULL;
    }
    //balance algorythem for AVL
    int balance = balanceFactor(root);
    if (balanceFactor(root->right_node) > 0 && balance < -1) //need to preform right the left  rotation on the tree
    {
        root->right_node = rotateRight(root->right_node);
        return rotateLeft(root);
    }
    if (balanceFactor(root->left_node) >= 0 && balance > 1) //need to preform right rotation on the tree
    {
        return rotateRight(root);
    }
    if (balanceFactor(root->right_node) <= 0 && balance < -1) //need to preform left rotation on the tree
    {
        return rotateLeft(root);
    }
    if (balanceFactor(root->left_node) < 0 && balance > 1) //need to preform left then right rotation on the tree
    {
        root->left_node = rotateLeft(root->left_node);
        return rotateRight(root);
    }
    return root;
}

///====================================select======================================================
template <class T>
T& RankTree<T>::select(int k)
{
    if (root_node == NULL || k > (root_node->rank))
        throw(NOT_EXIST());
    return selectNode(root_node, (root_node->rank) - k + 1);//sucsses for sure
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
