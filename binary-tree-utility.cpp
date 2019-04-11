#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <math.h>
#include <numeric>
#include <algorithm>
#include <vector>
#include <deque>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <float.h>
#include <tuple>
#include <stdexcept>
#include <iterator>
#include <sstream>
#include "binary-tree.cpp"

template <typename T> 
std::vector<T> parseToVector(std::string input_string)
{
    std::istringstream string_as_stream;
    std::vector<T> v;
    string_as_stream.str(input_string);

    std::copy(std::istream_iterator<T>(string_as_stream),
        std::istream_iterator<T>(),
        std::back_inserter(v));

    return v;        
}

template <typename T> 
std::deque<T> parseToDeque(std::string input_string)
{
    std::istringstream string_as_stream;
    std::deque<T> v;
    string_as_stream.str(input_string);

    std::copy(std::istream_iterator<T>(string_as_stream),
        std::istream_iterator<T>(),
        std::back_inserter(v));

    return v;        
}


template <typename T> 
std::vector<T> readVector() 
{

    std::string temp_line;

    std::vector<T> v;

    std::istringstream line_as_stream;

    std::getline(std::cin, temp_line);
    line_as_stream.str(temp_line);
    std::copy(std::istream_iterator<T>(line_as_stream),
        std::istream_iterator<T>(),
        std::back_inserter(v));

    return v;    
}

template <typename T>
std::vector<std::vector<T>> readGroupedVectors(char delim)
{

    std::string whole_line;
    std::getline(std::cin, whole_line);
    std::istringstream line_as_stream;
    line_as_stream.str(whole_line);
    std::string group;
    std::vector<T> v;
    std::vector<std::vector<T>> vect_of_vects;
    
    while (std::getline(line_as_stream,group,delim))
    {
        v = parseToVector<int>(group);  
        vect_of_vects.push_back(v);
    }      
    return vect_of_vects;

}

template <typename T>
std::vector<std::deque<T>> readGroupedDeques(char delim)
{

    std::string whole_line;
    std::getline(std::cin, whole_line);
    std::istringstream line_as_stream;
    line_as_stream.str(whole_line);
    std::string group;
    std::deque<T> v;
    std::vector<std::deque<T>> vect_of_vects;
    
    while (std::getline(line_as_stream,group,delim))
    {
        v = parseToDeque<int>(group);  
        vect_of_vects.push_back(v);
    }      
    return vect_of_vects;

}


template <typename T> 
void printVector(T &v) 
{ 
    for (const auto& x : v) {
        std::cout << x << " ";  
    }
    std::cout << "\n";
} 

void printNodes(std::vector<TreeNode*> nodes)
{
    for (TreeNode* node: nodes)
    {
        if (node) {std::cout<<node->data<<" ";}
        else {std::cout<<"x ";}
    }
    std::cout<<std::endl;
}

void printNodes(std::deque<TreeNode*> nodes)
{
    for (TreeNode* node: nodes)
    {
        if (node) {std::cout<<node->data<<" ";}
        else {std::cout<<"x ";}
    }
    std::cout<<std::endl;
}


void displayTree(BinaryTree&b)
{
    // does modified BFS
    std::string output;
    TreeNode* curr;
    std::deque<TreeNode*> fifo_queue = {b.root};
    std::cout<< "queue before starting is:  ";
    printNodes(fifo_queue);    

    while (!fifo_queue.empty())
    {
        curr=fifo_queue[0];
        if (curr)
        {
            output.append(std::to_string(curr->data));
            output.append(" ");
            fifo_queue.push_back(curr->left);
            fifo_queue.push_back(curr->right);

        } else
        {
            output.append("x ");
        }
        fifo_queue.pop_front();
    }

    std::cout<<"Tree contents:  "<<output<<std::endl;
}

void displayCompleteTree(BinaryTree& b)
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

    BinaryTree b;
    std::vector<std::deque<int>> grouped_nodes;
    std::cout<<"enter in the node values row by row, left to right, starting from the root"
    "using 'x' (without quotes) to represent all nil nodes:  "<<std::endl;
    
    grouped_nodes=readGroupedDeques<int>('x');

    if (grouped_nodes[0].empty())
    {
        std::cout<<"Warning: you entered an empty or invalid tree!"<<std::endl;
        return b;
    }

    TreeNode* rootNode = new TreeNode(grouped_nodes[0].front());
    b.root=rootNode;
    std::deque<TreeNode*> parents = {rootNode};
    bool needs_left_child=true;
    grouped_nodes[0].pop_front();
    TreeNode* parent;
        // for each i in I
            // let parent = parents[0];
            // if flag = true:
                // set flag to false
                // set parent->left=i
                // parents.push(i)
            // if flag = false:
                // set flag to true
                // set parent->right=i
                // parents.push(i)
                // parents.pop_front()
        // endfor
        // in between I's, we take into account the 'x'
        // by running the "advance" subroutine:
            // if flag = true:
                // set flag = false
            // if flag = false:
                // set flag = true
                // parents.pop_front()
    // endfor    
    for (std::deque<int> group: grouped_nodes)
    {
        for (int nodeValue : group)
        {
            parent = parents.front();
            TreeNode* currNode = new TreeNode(nodeValue);
            if (needs_left_child)
            {
                parent->left=currNode;

            } else
            {
                parent->right=currNode;
                parents.pop_front();
            }
            parents.push_back(currNode);
            needs_left_child=!needs_left_child;
        }

        // in between groups are 'x' i.e., NULLs,
        // which mean the next slot should be skipped over
        if (needs_left_child) {} 
        else {parents.pop_front();}
        needs_left_child=!needs_left_child;
    }

    return b;

}


BinaryTree readCompleteTree() {


    auto v = readVector<int>();
    std::vector<TreeNode*> nodes;
    for (int j = 0; j<v.size(); j++)
    {
        TreeNode* node_j = new TreeNode(v[j]);
        nodes.push_back(node_j);
    }

    int n = nodes.size();
    for (int j=0; 2*j+1<n; j++)
    {
        nodes[j]->left = nodes[2*j+1];

        if (2*j+2<n)  nodes[j]->right = nodes[2*j+2];
    }
    
    // std::cout<<"made a tree of size:  "<<n<<std::endl;
    BinaryTree b(nodes[0]);
    return b;
    
}

int main() 
{


    BinaryTree b = readTree();

    // std::cout<<"b's root is:  "<<b.root->data<<"!"<<std::endl;
    // std::cout<<"b has left child? "<<(!!b.root->left)<<std::endl;
    // std::cout<<"b has right child? "<<(!!b.root->right)<<std::endl;
    // std::cout<<"b's right child is:  "<<b.root->right->data<<std::endl;


    displayTree(b);

    // // b.rightRotate();
    // // std::cout<<"after right rotation:  "<<std::endl;
    // // displayTree(b);


    b.leftRotate();
    std::cout<<"after left rotation:  "<<std::endl;
    displayTree(b);



     return 0;
}