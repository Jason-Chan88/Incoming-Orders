#include "cqueue.h"
// default constructor setting all the objects
CQueue::CQueue(prifn_t priFn, HEAPTYPE heapType, STRUCTURE structure){
    m_size = 0;
    m_heap = nullptr;
    m_priorFunc = priFn;
    m_heapType = heapType;
    m_structure = structure;
}
// destructor calls clear and deallocates all memory
CQueue::~CQueue(){
     if(m_heap != nullptr) {
         clear();
     }
     m_heap = nullptr;
     m_size = 0;
}
//clear calls help clear
void CQueue::clear() {
    helpClear(m_heap);
}
// copy constructor copies another queue
CQueue::CQueue(const CQueue& rhs){ // copying for Rhs
        m_heap = helpCopy(rhs.m_heap);
        m_size = rhs.m_size;
        m_priorFunc = rhs.m_priorFunc;
        m_heapType = rhs.m_heapType;
        m_structure = rhs.m_structure;
}
CQueue& CQueue::operator=(const CQueue& rhs) { // calling clear and basically copying and pasting the copy constructor
    if (&rhs != this){
        clear();
        m_heap = helpCopy(rhs.m_heap);
        m_size = rhs.m_size;
        m_priorFunc = rhs.m_priorFunc;
        m_heapType = rhs.m_heapType;
        m_structure = rhs.m_structure;
    }
    return *this;
}
// merge two queues together with rhs
void CQueue::mergeWithQueue(CQueue& rhs) {
    // checks everything is the same between the two structure
    if (rhs.m_heap != nullptr && m_priorFunc == rhs.m_priorFunc && m_structure == rhs.m_structure) {
        if(m_heap != rhs.m_heap) { // checks against self merging
            m_heap = helpMerge(m_heap, rhs.m_heap); // calls help merge
            m_size = rhs.m_size + m_size;
            rhs.m_heap = nullptr; // rhs should be empty
            rhs.m_size = 0;
        }
    }
    else{
        throw domain_error("the priority function and the structure aren't the same"); // throw domainn error
    }

}
// insert all the orders
void CQueue::insertOrder(const Order& order) {
    if(order.m_customerID >= MINCUSTID && order.m_customerID <= MAXCUSTID) { // checks valid customer id
        if (order.m_orderID >= MINORDERID && order.m_orderID <= MAXORDERID) { // checks valid order id
            Node *curr = new Node(order);
            m_heap = helpMerge(m_heap, curr);
            m_size += 1; // increment size
        }
    }
}
// removes a node but returns it order
Order CQueue::getNextOrder() {
    if (m_heap == nullptr) { // if the heap is empty throw exception
        throw out_of_range("the queue is empty");
    }
    Node * temp = m_heap; // hold m heap
    Order order = temp->m_order; // hold the order
    m_heap = helpMerge(m_heap->m_left, m_heap->m_right); // merges
    m_size -= 1;
    delete temp;
    return order; // return order
}
// changing priority and heap type
void CQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
    m_priorFunc = priFn; // sets them
    m_heapType = heapType;
    Node * temp = m_heap;
    m_heap = nullptr;
    m_size = 0; // important to set size to 0
    helpRebuild(temp); // calls a function to rebuild it
}
// changing the structure
void CQueue::setStructure(STRUCTURE structure){
    m_structure = structure;
    Node * temp = m_heap;
    m_heap = nullptr;
    m_size = 0;
    helpRebuild(temp); // calls a function to rebuild it
}

STRUCTURE CQueue::getStructure() const {
    return m_structure;
}
HEAPTYPE CQueue::getHeapType() const {
    return m_heapType;
}
prifn_t CQueue::getPriorityFn() const {
    return m_priorFunc;
}
// prints the order in the queue with a helper
void CQueue::printOrdersQueue() const { //
    helpPrintOrders(m_heap, m_heap->m_order);
}
// returns the size
int CQueue::numOrders() const {
    return m_size;
}

void CQueue::dump() const {
    if (m_size == 0) {
        cout << "Empty heap.\n" ;
    } else {
        dump(m_heap);
    }
    cout << endl;
}
void CQueue::dump(Node *pos) const {
    if ( pos != nullptr ) {
        cout << "(";
        dump(pos->m_left);
        if (m_structure == SKEW)
            cout << m_priorFunc(pos->m_order) << ":" << pos->m_order.getOrderID();
        else
            cout << m_priorFunc(pos->m_order) << ":" << pos->m_order.getOrderID() << ":" << pos->m_npl;
        dump(pos->m_right);
        cout << ")";
    }
}
ostream& operator<<(ostream& sout, const Order& order) {
    sout << "Order ID: " << order.getOrderID()
         << ", customer ID: " << order.getCustomerID()
         << ", # of points: " << order.getPoints()
         << ", membership tier: " << order.getTierString()
         << ", item ordered: " << order.getItemString()
         << ", quantity: " << order.getCountString();
    return sout;
}
ostream& operator<<(ostream& sout, const Node& node) {
    sout << node.getOrder();
    return sout;
}
// helps clear the heap
void CQueue::helpClear(Node * curr) {

    if(curr != nullptr) { // recursively deletes them
        helpClear(curr->m_left);
        helpClear(curr->m_right);
        delete curr;
    }

}
// helps copy the entire heap
Node *CQueue::helpCopy(Node *curr) {
    Node * temp = nullptr;
    if (curr != nullptr) {
        temp = new Node(*curr);
        temp->m_left = helpCopy(curr->m_left);
        temp->m_right = helpCopy(curr->m_right);
    }
    return temp;
}
// prints out the orders in the queue
void CQueue::helpPrintOrders(Node *curr, const Order& order) const {
    if (curr != nullptr) {
        cout << "[" <<  m_priorFunc(curr->m_order) << "] "
             << "Order ID: " << curr->m_order.m_orderID
             << ", customer ID: " << curr->m_order.m_customerID
             << ", # of points: " << curr->m_order.m_points
             << ", membership tier: " << curr->m_order.m_membership
             << ", item ordered: " << curr->m_order.m_item
             << ", quantity: " << curr->m_order.m_count << endl;
        helpPrintOrders(curr->m_left, curr->m_order);
        helpPrintOrders(curr->m_right, curr->m_order);
    }
}
// this merges the two heap together
Node *CQueue::helpMerge(Node *curr, Node * temp) {
    if (m_structure == SKEW) { // checks if it's a skew
        if (curr != nullptr && temp != nullptr) {
            if (m_heapType == MINHEAP) { // checks the heap type
                if (m_priorFunc(curr->m_order) <= m_priorFunc(temp->m_order)) { // priority check
                    Node *test = curr->m_left;
                    // swaps
                    curr->m_left = curr->m_right;
                    curr->m_right = test;
                    curr->m_left = helpMerge(curr->m_left, temp);
                    return curr;
                } else {
                    Node *test = temp->m_left;
                    temp->m_left = temp->m_right;
                    temp->m_right = test;
                    temp->m_left = helpMerge(temp->m_left, curr);
                    return temp;
                }
            }
            else { // max heap
                if (m_priorFunc(curr->m_order) >= m_priorFunc(temp->m_order)) {
                    Node *test = curr->m_left;
                    curr->m_left = curr->m_right;
                    curr->m_right = test;
                    curr->m_left = helpMerge(curr->m_left, temp);
                    return curr;
                } else {
                    Node *test = temp->m_left;
                    temp->m_left = temp->m_right;
                    temp->m_right = test;
                    temp->m_left = helpMerge(temp->m_left, curr);
                    return temp;
                }
            }
        }
        else if(curr != nullptr && temp == nullptr) {
            return curr;
        }
        else if(curr == nullptr && temp != nullptr) {
            return temp;
        }

    }
    if (m_structure == LEFTIST) { // checks leftist
        if (curr != nullptr && temp != nullptr) {
            if (m_heapType == MINHEAP) {
                if (m_priorFunc(curr->m_order) <= m_priorFunc(temp->m_order)) { // min heap

                    if (curr->m_left == nullptr) {
                        curr->m_left = temp;
                    }
                    else {
                        curr->m_right = helpMerge(curr->m_right, temp);
                        if (curr->m_left->m_npl < curr->m_right->m_npl) { // does npl check before swap
                            Node *test = curr->m_left;
                            curr->m_left = curr->m_right;
                            curr->m_right = test;
                        }
                        curr->m_npl = curr->m_right->m_npl + 1; // hanges npl to correct value
                    }

                    return curr;
                } else {

                    return helpMerge(temp, curr);
                }
            }
            else { // max heap
                if (m_priorFunc(curr->m_order) >= m_priorFunc(temp->m_order)) {
                    if (curr->m_left == nullptr) {
                        curr->m_left = temp;
                    }

                    else {
                        curr->m_right = helpMerge(curr->m_right, temp);
                        if (curr->m_left->m_npl < curr->m_right->m_npl) {
                            Node *test = curr->m_left;
                            curr->m_left = curr->m_right;
                            curr->m_right = test;
                        }
                        curr->m_npl = curr->m_right->m_npl + 1;
                    }

                    return curr;
                } else {
                    return helpMerge(temp, curr);
                }
            }
        }
        else if(curr != nullptr && temp == nullptr) {
            return curr;
        }
        else if(curr == nullptr && temp != nullptr) {
            return temp;
        }
    }
    return nullptr;
}
// helps rebuild the heap after the setters
void CQueue::helpRebuild(Node *curr) {
    if (curr != nullptr) {
        helpRebuild(curr->m_left);
        helpRebuild(curr->m_right);
        insertOrder(curr->m_order);
        delete curr;
    }
}
// testing the heap property
bool CQueue::helpHeapProperty(Node * curr) {
    bool result = true;

    if (curr == nullptr) {
        return result;
    }

    if (m_heapType == MINHEAP) { // checks the Heap type
        // if the first order is greater than it's kids than return false as it should be the opposite
        if (curr->m_left != nullptr && m_priorFunc(curr->m_order) > m_priorFunc(curr->m_left->m_order)) {
            result = false;
        }
        if (curr->m_right != nullptr && m_priorFunc(curr->m_order) > m_priorFunc(curr->m_right->m_order)) {
            result = false;
        }
    }
    if (m_heapType == MAXHEAP) {
        // if the first order is less than it's kids than return false as it should be the opposite
        if (curr->m_left != nullptr && m_priorFunc(curr->m_order) < m_priorFunc(curr->m_left->m_order)) {
            result = false;
        }
        if (curr->m_right != nullptr && m_priorFunc(curr->m_order) < m_priorFunc(curr->m_right->m_order)) {
            result = false;
        }
    }
    result = result && helpHeapProperty(curr->m_left); // recurse through
    result = result && helpHeapProperty(curr->m_right);

    return result;
}
// checking the property of Leftist heap
bool CQueue::helpCheckLeftProperty(Node * curr) {
    bool result = true;
    if (curr != nullptr) {
        result = result && helpCheckLeftProperty(curr->m_left); // recursively go down the tree
        result = result && helpCheckLeftProperty(curr->m_right);
        if (curr->m_left == nullptr && curr->m_right != nullptr) { // should be something on the left of a Leftist heap
            result = false;
        }
        if(curr->m_left != nullptr && curr->m_right != nullptr && curr->m_left->m_npl < curr->m_right->m_npl) {
            result = false;
        }
        return result;
    }
    return result;
}
// returns a counter to calculate npl
int CQueue::helpCalcNpl1(Node * curr) {
    int counter = 0;
    while(curr != nullptr && curr->m_right != nullptr) {
        counter += 1;
        curr = curr->m_right;
    }
    return counter;
}
// second helper for npl that traverses and checks the value are correct
bool CQueue::helpCalcNpl2(Node * curr) {
    if (curr == nullptr) {
        return true;
    }
    int value = helpCalcNpl1(curr); // call function into a value to store than check
    if (value != curr->m_npl) {
        return false;
    }

    return helpCalcNpl2(curr->m_left) && helpCalcNpl2(curr->m_right); // recursive goes through
}
// checks that the nodes have created a deep copy
bool CQueue::helpDeepCopyCheck(Node * curr, Node * temp) {
    if (curr == nullptr) {
        return true;
    }
    // they can't equal each other or false
    if(curr == temp) {
        return false;
    }
    // checks that all their values aren't the same
    if(curr->m_order.m_orderID != temp->m_order.m_orderID || curr->m_order.m_customerID != temp->m_order.m_customerID || curr->m_order.m_count != temp->m_order.m_count || curr->m_order.m_points != temp->m_order.m_points || curr->m_order.m_item != temp->m_order.m_item || curr->m_order.m_membership != temp->m_order.m_membership ){
        return false;
    }
    return helpDeepCopyCheck(curr->m_left, temp->m_left) && helpDeepCopyCheck(curr->m_right, temp->m_right);
}