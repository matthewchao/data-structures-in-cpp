// NEXT TASK: MODIFY READBINARYTREE TO interpret "X" or "x" as nullpointer
// e.g., 0 x 1 x 2 should be a path consisting of 3 nodes
// NOTE we should accept both
// 0 x 1 x x x 2
// and 0 x 1 x 2; the first "x" means the first 2 nodes on row 2 (root=row 0)
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

// reads a row of ints
std::vector<int>  readVector() {

    std::string temp_line;

    std::vector<int> v;

    std::istringstream line_as_stream;

    std::getline(std::cin, temp_line);
    line_as_stream.str(temp_line);
    std::copy(std::istream_iterator<int>(line_as_stream),
        std::istream_iterator<int>(),
        std::back_inserter(v));

    return v;    
}


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

void printNodes(std::vector<TreeNode*> nodes)
{
    for (TreeNode* x: nodes)
    {
        std::cout<<x->data<<" ";
    }
    std::cout<<std::endl;
}

void printNodes(std::deque<TreeNode*> nodes)
{
    for (TreeNode* x: nodes)
    {
        std::cout<<x->data<<" ";
    }
    std::cout<<std::endl;
}


struct BinaryTree {
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

// i.e., returns nodes row by row, from left to right
std::vector<TreeNode*> BinaryTree::BFS() {
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





void displayTree(BinaryTree& b)
{

    // std::cout<<"about to display tree..."<<std::endl;
    std::vector<TreeNode*> nodes = b.BFS();
    // std::cout<<"the size of the tree is:  "<<nodes.size()<<", and flattened it looks like:  "<<std::endl;
    
    for (TreeNode* n: nodes)
    {
        std::cout<<n->data<<" ";
    }
    std::cout<<std::endl;
}



// Reads a binary tree from a row of ints entered row-by-row, left-to-right starting from the root
BinaryTree readTree() {

    auto v = readVector();
    int n = v.size();
    TreeNode* curr;
    std::vector<TreeNode*> nodes;
    for (int j = 0; j<n; j++)
    {
        TreeNode* node_j = new TreeNode(v[j]);
        nodes.push_back(node_j);
    }

    for (int j=0; 2*j+1<n; j++)
    {
        if (2*j+1<n)  nodes[j]->left = nodes[2*j+1];

        if (2*j+2<n)  nodes[j]->right = nodes[2*j+2];
    }
    
    // std::cout<<"made a tree of size:  "<<n<<std::endl;
    BinaryTree b(nodes[0]);
    return b;
    
}







int main() 
{

    BinaryTree b = readTree();

    std::cout<<"b's root is:  "<<b.root->data<<"!"<<std::endl;
    displayTree(b);


    b.leftRotate();
    std::cout<<"after left rotation:  "<<std::endl;
    displayTree(b);

    b.rightRotate();
    std::cout<<"after right rotation:  "<<std::endl;
    displayTree(b);

    return 0;
}