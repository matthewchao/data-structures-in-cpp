// TODO NEXT: handle edge cases for BinaryTree:BFS()
// specifically what to do with nil leaves or empty trees

#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <unordered_map>

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
        curr = queue.front();
        if (curr->left)
        {
            queue.push_back(curr->left);
        }
        if (curr->right)
        {
            queue.push_back(curr->right);
        }
        visited.push_back(curr);
        queue.pop_front();
    }

    return visited;
}

// returns -1 for empty tree, 0 for the tree with single node, 1 for a tree with two nodes, etc.
int BinaryTree::treeHeight()
{
    if (!root) return -1;  

    // does a dfs, while maintaining a depths map
    std::unordered_map<TreeNode*,int> depths {{root,0}};
    std::vector<TreeNode*> to_be_visited_stack {root};
    TreeNode* curr_node;
    int curr_height,record_height=0;
    while (!to_be_visited_stack.empty())
    {
        curr_node=to_be_visited_stack.back();
        curr_height=depths[curr_node];
        to_be_visited_stack.pop_back();
        if (!curr_node->left && !curr_node->right) 
            // we are at a leaf; depth of leaf might be the tree height;
            record_height=std::max(record_height,curr_height);
        if (curr_node->right)
        {
            depths[curr_node->right]=curr_height+1;
            to_be_visited_stack.push_back(curr_node->right);
        }
        if (curr_node->left)
        {
            depths[curr_node->left]=curr_height+1;
            to_be_visited_stack.push_back(curr_node->left);
        }
    }
    return record_height;
}

void BinaryTree::rightRotate()
{
    if (!root) {std::cout<<"WARNING: empty tree; nothing to rotate"<<std::endl; return;}
    if (!root->left) {std::cout<<"not enough nodes to rightRotate!"<<std::endl; return;}
    TreeNode *x=root, *y=x->left, *z=y->right;
    x->left=z;
    y->right=x;
    root=y;
}

void BinaryTree::leftRotate()
{
    if (!root) {std::cout<<"WARNING: empty tree; nothing to rotate"<<std::endl; return;}
    if (!root->right) {std::cout<<"not enough nodes to leftRotate!"<<std::endl; return;}
    TreeNode *x=root, *y=x->right, *z=y->left;
    x->right=z;
    y->left=x;
    root=y;
}













