#include <iostream>


struct ListNode {
    int data;
    ListNode* next;

    ListNode(int d) {
        next=nullptr;
        data=d;
    }

    ~ListNode() {
        std::cout<<"node with data = "<<data<<" destroyed!\n";
    }
};

struct LinkedList {
    
    ListNode* head;

    
    LinkedList() { head=nullptr; };

    int listLength();
    ListNode* tail();
    ListNode* node_at(int pos);
    void append(int data);
    // delete_at(0) deletes the root, delete_at(-1) deletes the tail
    void delete_at(int pos);
    // deletes the node with given data value
    void delete_data(int data);
    void insert_at(int pos, int data);
    void cycle(int times);
    void reverse();
    void peek_at(int pos);

};



int LinkedList::listLength() {
    ListNode* curr=head;
    int count=0;
    while (curr) {
        ++count;
        curr=curr->next;
    }
    return count;
}


ListNode* LinkedList::tail()
{
    if (!head) return nullptr;
    return node_at(  this->listLength() - 1  );
}




// Alternative 1 for append:
void LinkedList::append(int data) {
    ListNode* newTail = new ListNode(data);

    if (head==nullptr) 
    {
        head=newTail;
    } else 
    {
        // std::cout<<"appending to nonempty list..."<<std::endl;
        this->tail() -> next = newTail;
    }
}

// Alternative 2:
// void LinkedList::append(int data) {
//     ListNode* newTail = new ListNode;
//     newTail->data=data;
//     newTail->next=nullptr;

//     if (head==nullptr) {
//         head=newTail;
//     } else {
//         ListNode* iterNode;
//         iterNode=head;
//         while (iterNode->next!=nullptr) {
//             iterNode=iterNode->next;
//         }
//         iterNode->next=newTail;
//     }    
// }

ListNode* LinkedList::node_at(int pos)
{
    if (pos==0) return head;

    ListNode* curr = head;
    if (pos>0)
    {
        for (int i=0; i<pos; i++) 
        {
            if (curr) 
            {
                curr=curr->next;
            } else
            {
                std::cout<<"node_at is returning a nullptr!"<<std::endl;
                return nullptr;
            }
        }
        return curr;
    }
    if (pos<0)
    {
        int numNodes = this->listLength();
        if (std::abs(pos)>numNodes)
        {
            std::cout<<"no node at position:  "<<pos<<"!"<<std::endl;
            return nullptr;
        } 
        return this->node_at(numNodes+pos);
    }

}


void LinkedList::delete_at(int pos) {
    
    // trivial case where list is empty
    if (!head) {std::cout<<"nothing to delete from empty list!"<<std::endl;}

    ListNode *pre, *post, *toDelete;
    if (pos==0) 
    {
        post=head->next;
        // the below is necessary because every node was originally
        // allocated with "new";
        delete head;
        this->head=post;
        return;
    }

    if (pos>0) {
        pre = this->node_at(pos-1);

        if (!pre) {std::cout<<"nothing to delete at index:  "<<pos<<std::endl; return;}
        if (!pre->next) {std::cout<<"the tail is already null!"<<std::endl; return;}

        toDelete = pre->next;
        post = toDelete->next;
        pre->next=post;
        delete toDelete;
        return;
    }

    if (pos<0) {
        if (!this->node_at(pos)) {std::cout<<"no node at position:  "<<pos<<std::endl; return;}

        this->delete_at(this->listLength()+pos);
    }


    
}

void LinkedList::insert_at(int pos,int data) {
    ListNode *pre, *post;
    // trivial case where list is empty

    ListNode *toInsert;
    if (!this->head) {return;}

    if (pos==0) 
    {
        post=head->next;
        // the below is necessary because every node was originally
        // allocated with "new";
        delete head;
        head=post;
    }

    if (pos>0) {
        
        ListNode *toDelete=pre->next;
        if (toDelete) {
            post = toDelete->next;
        } else {
            std::cout<<"tried to delete null after tail"<<std::endl;
            return;
        }
        delete toDelete;
        pre->next=post;
    }    
}


void displayList(LinkedList& l) {
    ListNode* iterNode;
    iterNode=l.head;
    while(iterNode!=nullptr) {
        std::cout<<iterNode->data<<"\t";
        iterNode=iterNode->next;
    }
    std::cout<<std::endl;
}



// DRIVER CODE
int main() 
{

    LinkedList l;
    for (int i=0; i< 10; i++) {
        l.append(i);
    }
    displayList(l);
    // l.delete_at(-11);
    // displayList(l);
    std::cout<<"length is:  "<<l.listLength()<<std::endl;
    return 0;
}

