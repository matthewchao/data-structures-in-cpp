// NEXT TASK: MODIFY READBINARYTREE TO interpret "X" or "x" as nullpointer
// e.g., 0 x 1 x 2 should be a path consisting of 3 nodes
// NOTE we should accept both
// the verbose 0 x 1 x x x 2
// as well as 0 x 1 x 2; here, the first "x" means the first 2 nodes on row 2 (root=row 0)
// must also be "x" since null can't have any children

// #include <cassert>
#include <iostream>
// #include <memory>
#include <string>
// #include <math.h>
// #include <numeric>
// #include <algorithm>
#include <vector>
#include <deque>
// #include <array>
// #include <map>
// #include <unordered_map>
// #include <set>
// #include <float.h>
// #include <tuple>
// #include <stdexcept>
#include <iterator>
#include <sstream>






struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    };
    ~TreeNode() {
        std::cout<<"tree node with data = "<<data<<" destroyed!"<<std::endl;
    };
};



struct BinaryTree
{
    TreeNode* root;

    BinaryTree() {
        root = nullptr;
    }
    BinaryTree(TreeNode* rt) {
        root = rt;
    }

    
    std::vector<TreeNode*> leaves();

    // gives a row-by-row, left-to-right traversal of the tree
    std::vector<TreeNode*> BFS();
    std::vector<TreeNode*> LNR();
    std::vector<TreeNode*> NLR();
    std::vector<TreeNode*> RNL();
    TreeNode* nodeWith(int value);
    int treeHeight();
    int treeHeight(TreeNode* root);
    void deleteLeaf(int value);
    void rightRotate();
    void leftRotate();
};

// BFS returns nodes row by row, from left to right
std::vector<TreeNode*> BinaryTree::BFS()
{
    // first-in-first-out queue
    std::deque<TreeNode*> queue(1,root);
    std::vector<TreeNode*> visited(0);
    TreeNode* curr;
    while (!queue.empty())
    {
        // std::cout<<"queue is:  ";
        // printNodes(queue);
        curr = queue.front();
        if (curr->left)
        {
            // std::cout<<curr->data<<" has a left child! adding to queue..."<<std::endl;
            queue.push_back(curr->left);
        }
        if (curr->right)
        {
            // std::cout<<curr->data<<" has a right child! adding to queue..."<<std::endl;
            queue.push_back(curr->right);
        }
        visited.push_back(curr);
        queue.pop_front();
    }

    // std::cout<<"visited nodes:  ";
    // printNodes(visited);
    return visited;
}

int BinaryTree::treeHeight()
{
}

void BinaryTree::rightRotate()
{
    if (!root->left) {std::cout<<"not enough nodes to rightRotate!"<<std::endl; return;}
    TreeNode *x=root, *y=x->left, *z=y->right;
    x->left=z;
    y->right=x;
    root=y;
}

void BinaryTree::leftRotate()
{
    if (!root->right) {std::cout<<"not enough nodes to leftRotate!"<<std::endl; return;}
    TreeNode *x=root, *y=x->right, *z=y->left;
    x->right=z;
    y->left=x;
    root=y;
}













