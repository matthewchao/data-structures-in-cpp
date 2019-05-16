#include <cassert>
#include <algorithm>
#include <deque>
#include <unordered_map>


// extract_keys gets keys from a map
template<typename TK, typename TV>
std::deque<TK> extract_keys(std::unordered_map<TK, TV> const& input_map) {
  std::deque<TK> retval;
  for (auto const& element : input_map) {
    retval.push_back(element.first);
  }
  return retval;
} 


// Implements a max heap
class BinaryHeap {
    public:
    // Puts keys into a binary heap with priority equal to the key's value
    BinaryHeap(std::unordered_map<int,int> unsorted_priorities) :
    priorities(unsorted_priorities), indices({})
    {
        elements = extract_keys(unsorted_priorities);
        for (int i=0; i<elements.size(); i++) {
            indices[elements[i]]=i;
        }
        heapify();
    };

    std::deque<int> get_heap_elements() const {
        return elements;
    }

    bool empty() const {
        return (elements.size()==0);

    };

    int get_priority(int nodeName) const {
        return priorities.at(nodeName);
    }

    void insert_with_priority(int nodeName,int priority) {
        priorities[nodeName]=priority;
        elements.push_back(nodeName);
        indices[nodeName]=elements.size()-1;
        siftUp(elements.size()-1);
    };

    int peek_max_element() const {
        return elements[0];
    };

    int pop_max_element() {
        int max_element = elements.front(); 

        //erase max element
        priorities.erase(max_element);
        indices.erase(max_element);
        elements.pop_front();

        // edge case: heap had only one element
        if (elements.size()==0) {
            return max_element;
        }

        // put a leaf in root position, and correct:
        int temp_last_element = elements.back();
        elements.pop_back();
        indices[temp_last_element] = 0;
        elements.push_front(temp_last_element);
        siftDown(0);
        assert(priorities.size()==indices.size()&&priorities.size()==elements.size());
        return max_element;
    };


    void increase_priority_by(int nodeName,int amount_of_increase) {
        if (priorities.count(nodeName) ) {
            priorities[nodeName]+=amount_of_increase;
            siftUp(indices[nodeName]);
        }
    };


    private:
    /* The flattened binary tree sorted as an array. Will be kept in heap order.
    A deque is used instead of a vector because extract_max operation will pop_front from elements. */
    std::deque<int> elements;
    //holds current priority of each element    
    std::unordered_map<int,int> priorities; 
    /* while the existence of an indices map might seem extraneous,
    it is necessary since sifting operations use the index of the element being sifted */
    std::unordered_map<int,int> indices; 


    void siftUp(int index) {
        int parentIndex = (index-1)/2;
        while (parentIndex>=0) {
            auto currentPriority = priorities[elements[index]];
            auto parentPriority = priorities[elements[parentIndex]];

            bool isHeap = (currentPriority<=parentPriority);
            if (isHeap) break;
            heap_swap(index,parentIndex);
            index = parentIndex;
            parentIndex = (index-1)/2;
        }
    };
    
    void siftDown(int index) {
        /* swaps an element with bigger child until heap property is restored */
        int leftChildIndex = 2*index+1;
        int rightChildIndex = 2*index+2;
        while (leftChildIndex<elements.size()) {
            // i.e. while the current node has at least one child
            auto currentPriority = priorities[elements[index]];
            auto leftChildPriority = priorities[elements[leftChildIndex]];

            if (rightChildIndex<elements.size()) {
                // Case where current node has both left and right children
                auto rightChildPriority = priorities[elements[rightChildIndex]];
                bool isHeap = (currentPriority>=leftChildPriority) && (currentPriority>=rightChildPriority);                
                if (isHeap) break;
                if (leftChildPriority>=rightChildPriority) {
                    heap_swap(leftChildIndex,index);
                    index = leftChildIndex;
                } else {
                    heap_swap(rightChildIndex,index);
                    index = rightChildIndex;
                }
            } else {
                /* Case where current node has only a left child - e.g., a complete tree with 4 elements
                has an element with a left child but no right child. */
                bool isHeap = (currentPriority>=leftChildPriority); 
                if (isHeap) break;  
                heap_swap(leftChildIndex,index);
                index = leftChildIndex;
            }

            leftChildIndex = 2*index+1;
            rightChildIndex = 2*index+2;
        }


        


    };


    /*It is possible to turn a set into a heap by inserting one-by-one;
    but because of siftUp subroutine, this would take O(n log n) time.
    By putting everything into the tree at once, and sifting down, 
    we exploit the fact that most elements are in the bottom half of the tree
    and can only sift down so far.
    Note the reverse order in which we apply siftDown is due to the following property of siftDown: 
    If both subtrees beneath x satisfy the Heap property, then sifting x down will restore the Heap property
    to the subtree with root x. */
    void heapify() {
        for (int i=(elements.size()-1); i>=0; --i) {
            siftDown(i);
        }
    };

    void heap_swap(const int index1,const int index2) {

        assert (index1<elements.size() && index2<elements.size());
        // swap in the indices map:
        indices[elements[index1]]=index2;
        indices[elements[index2]]=index1;
        // then swap in the tree representation
        std::swap(elements[index1],elements[index2]) ;
    }

};



// int main() 
// {
//     std::unordered_map<int,int> m;
//     std::cout<<"enter some unique ints; their priorities will be their values: \n";
//     auto v = readVector<int>();
//     for (auto el: v) {
//         m[el]=el;
//     }

//     auto b = BinaryHeap(m);


//     std::cout<<"enter another node to insert:   \n";
//     int n;
//     std::cin>>n;
//     b.insert_with_priority(n,n);


//     std::cout<<"tree is now:  ";
//     for (auto x: b.display() ) {
//         std::cout<<x<<", ";
//     }
//     std::cout<<std::endl;

    



//     return 0;
// }