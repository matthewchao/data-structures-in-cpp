// TODO NEXT: modify displayTree so that it doesn't display all trailing nil leaves
// but only those nil leaves which would be required as input

#include "binary-tree.cpp"
#include "input-utils.cpp"


// REPLACING BELOW TWO FUNCTIONS WITH ONE WHICH TAKES A BEGIN AND END ITERATOR:
// void printNodes(std::vector<TreeNode*> nodes)
// {
//     for (TreeNode* node: nodes)
//     {
//         if (node) {std::cout<<node->data<<" ";}
//         else {std::cout<<"x ";}
//     }
//     std::cout<<std::endl;
// }

template <class RandomAccessIterator>
void printNodes( RandomAccessIterator first, RandomAccessIterator last )
{
    while( first != last ) {
        if (*first)  std::cout<< (*first)->data<< " ";
        else std::cout << "x ";
        ++first;
    }
    std::cout<<std::endl;
}



void displayTree(BinaryTree&b)
{
    // does modified BFS
    std::string output;
    TreeNode* curr;
    std::deque<TreeNode*> fifo_queue = {b.get_root()};

    while (!fifo_queue.empty())
    {
        curr=fifo_queue.front();
        if (curr)
        {
            output.append(std::to_string(curr->data));
            output.append(" ");
            fifo_queue.push_back(curr->left);
            fifo_queue.push_back(curr->right);

        } else { output.append("x "); }
        fifo_queue.pop_front();
        // std::cout<<"queue is now:  ";
        // printNodes(fifo_queue.begin(),fifo_queue.end());
    }

    /* Find the index of the last node data and trim after that;
    Otherwise we have a bunch of trailing x's representing leaves' null children,
    which do not tell us anything new about the tree structure*/
    int last_meaningful_index = output.find_last_not_of(" x");
    output.resize(last_meaningful_index+1);
    std::cout<<output<<std::endl;
}

void displayCompleteTree(BinaryTree& b)
{
    std::vector<TreeNode*> nodes = b.BFS();
    for (TreeNode* n: nodes){ std::cout<<n->data<<" "; }
    std::cout<<std::endl;
}



/* Creates and fills a tree based on user input.
Subsequent nodes are assigned as children to the front of a "parents" queue
where any nil node, inputted as 'x', results in the queue being advanced */
BinaryTree readTree() {    

    std::vector<std::deque<int>> grouped_nodes;
    grouped_nodes=readGroupedDeques<int>('x');

    // bad input yields an tree with NULL root
    if (grouped_nodes[0].empty())
    {
        std::cout<<"Warning: you entered an empty or invalid tree!"<<std::endl;
        BinaryTree b;
    }

    TreeNode* rootNode = new TreeNode(grouped_nodes[0].front());
    BinaryTree b{rootNode};

    std::deque<TreeNode*> parents = {rootNode};
    grouped_nodes[0].pop_front();

    bool needs_left_child=true; /* Becomes false after a left child is assigned
     or when a left child is due but a nil leaf is encountered.
     Becomes true after a right child is assigned.*/
    TreeNode* currParent;
    TreeNode* currNode;

    for (std::deque<int> group: grouped_nodes)
    {
        for (int nodeValue : group)
        {
            currParent = parents.front();
            currNode = new TreeNode(nodeValue);
            if (needs_left_child) currParent->left=currNode;
            else
            {
                currParent->right=currNode;
                parents.pop_front();
            }
            parents.push_back(currNode);
            needs_left_child=!needs_left_child;
        }
        /* inner loops are demarcated with 'x' i.e., nil leaves,
        which means the next available slot should be skipped over */
        if (!needs_left_child) parents.pop_front();
        needs_left_child=!needs_left_child;
    }
    return b;
}

// This is subsumed by readTree, but is preserved here to show how show the code is when
// the tree is complete
BinaryTree readCompleteTree() {


    std::vector<int> v = readVector<int>();
    std::vector<TreeNode*> nodes;
    for (int j = 0; j<v.size(); j++)
    {
        TreeNode* node_j = new TreeNode(v[j]);
        nodes.push_back(node_j);
    }

    int j, n = nodes.size();
    for (j=0; 2*j+1<n; j++)  {
        nodes[j]->left = nodes[2*j+1];
        // the condition below is necessary in case the last node is a right child
        if (2*j+2<n)  nodes[j]->right = nodes[2*j+2];
    }

    BinaryTree b(nodes[0]);
    return b;
    
}

int main() 
{


    std::cout<<"Enter in space-separated node values row by row, "
    "left to right, starting from the root"<<std::endl;

    // sample trees:
    // x
    // (an empty tree)
    // 1 x 2 x 3 x 4 x 5 x 6 
    // (a path of right children)
    // 1 2 3 4 5 6 7
    // (a complete tree)
    BinaryTree b = readTree();

    displayTree(b);
    // b.leftRotate();
    // std::cout<<"after rotation:  "<<std::endl;
    // displayTree(b);
    std::cout<<"tree height is:  "<<b.treeHeight()<<".\n";
    std::cout<<"now enter two nodes to find a path between; the ancestor node first:  "<<std::endl;
    int from_val, to_val;
    std::cin>>from_val>>to_val;
    auto path_from_to = b.path(from_val,to_val);
    printNodes( path_from_to.begin(),path_from_to.end() );


    // b.rightRotate();
    // std::cout<<"after second rotation:  "<<std::endl;
    // displayTree(b);




     return 0;
}
