// TODO NEXT: handle edge cases for BinaryTree:BFS()
// specifically what to do with nil leaves or empty trees

#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <iostream>
#include <unordered_map>
#include <cassert>

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



class BinaryTree
{
private:
    TreeNode* root;

public:
    BinaryTree()
    {
        root = nullptr;
    }

    BinaryTree(TreeNode* rt)
    {
        root = rt;
    }

    TreeNode* get_root() {return root;}
    std::vector<TreeNode*> leaves();

    // gives a row-by-row, left-to-right traversal of the tree
    std::vector<TreeNode*> BFS();
    std::vector<TreeNode*> LNR();
    std::vector<TreeNode*> NLR();
    std::vector<TreeNode*> RNL();
    /* Returns the (unique) path from root to node with data=node_value:
    {root, intermediate1, intermediate2, ... , node}.
    E.g., If node is root itself, returns {root}; If node is root's child, returns {root,node}
    Returns empty vector if "to" is not a descendant of "from" */
    std::vector<TreeNode*> path(int from_value,int to_value);
    std::vector<TreeNode*> path(int node_value);
    TreeNode* nodeWith(int value);
    int treeHeight();
    int treeHeight(TreeNode* root);
    void deleteLeaf(int value);
    void rightRotate();
    void leftRotate();

private:
    /* First version (1) pops the top node from the stack and
    (2) pushes its children, if any. 
    Second version (1) marks the top node visited XOR pops the top node if already visited, and 
    (2) pushes its children, if any.
    Both return the next top node, or nullptr if the stack is now empty.
    Second version doesn't necessarily remove a node, but it at least discovers children,
    or lack of chidren. */
    TreeNode* advanceDFS(std::stack<TreeNode*>& visit_stack);
    TreeNode* advanceDFS(    std::stack<TreeNode*>& visit_stack,
                        std::unordered_map<TreeNode*,bool>& visited);
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

TreeNode* BinaryTree::advanceDFS(std::stack<TreeNode*>& visit_stack)
{
    if ( visit_stack.empty() ) return nullptr;

    TreeNode* curr_node = visit_stack.top();
    visit_stack.pop();
    
    if (curr_node->right) visit_stack.push(curr_node->right);
    if (curr_node->left) visit_stack.push(curr_node->left);

    if ( visit_stack.empty() ) return nullptr;
    
    return visit_stack.top();
}

TreeNode* BinaryTree::advanceDFS(   std::stack<TreeNode*>& visit_stack,
                                    std::unordered_map<TreeNode*,bool>& visited)
{
    if ( visit_stack.empty() ) return nullptr;

    TreeNode* curr_node = visit_stack.top();
    if ( visited[curr_node] ) 
    {
        // Must have already seen this node and added its children earlier
        visit_stack.pop();
    } else {
        // First time visiting this node, so we never added its children before
        visited[curr_node] = true;
        if (curr_node->right) visit_stack.push(curr_node->right);
        if (curr_node->left) visit_stack.push(curr_node->left);
    }

    if ( visit_stack.empty() ) return nullptr;
    return visit_stack.top();    
}


std::vector<TreeNode*> BinaryTree::path(int from_value, int to_value)
{
    std::unordered_map<TreeNode*,bool> visited{};
    std::stack<TreeNode*> visit_stack = {};
    visit_stack.push(root);

// first locate the from_node: 
    TreeNode* from_node = visit_stack.top();
    while ( !visit_stack.empty() )
    {
        if (from_node->data==from_value) {
            break;
        }
        from_node = advanceDFS(visit_stack,visited);
    }

    // in from_value is not in the tree, the whole tree would have been traversed:
    if ( visit_stack.empty() ) return std::vector<TreeNode*>{};
// after having found from_node, find to_node; it should not require backtracking past from_node
// since to_node has to be a descendant of from_node;
    if (to_value==from_value) return std::vector<TreeNode*>{from_node};


    TreeNode* to_node = advanceDFS(visit_stack,visited);
    while ( to_node!=from_node )
    {
        if (to_node->data==to_value) {
            break;
        }
        to_node = advanceDFS(visit_stack,visited);
    }    

    if (to_node==from_node) return std::vector<TreeNode*>{};
    std::cout<<"found to node!"<<std::endl;


    // Path = sequence of nodes from to_node down to from_node in the stack,
    // which have been marked visited.
    std::vector<TreeNode*> result_in_reverse {to_node};


    for (TreeNode* curr_node = visit_stack.top(); curr_node!= from_node; curr_node = visit_stack.top() )
    {
        if (visited[curr_node]) result_in_reverse.push_back(curr_node);
        visit_stack.pop();
    }
    result_in_reverse.push_back(from_node);

    return std::vector<TreeNode*>(result_in_reverse.rbegin(),result_in_reverse.rend());
}

std::vector<TreeNode*> BinaryTree::path(int node_value)
{
    TreeNode* fromNode = root;
    return path(root->data, node_value);
}













