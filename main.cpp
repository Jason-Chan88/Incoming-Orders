#include "cqueue.h"
#include <random>
int priorityFn1(const Order &order);// works with a MAXHEAP
int priorityFn2(const Order &order);// works with a MINHEAP

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }

private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

class Tester{
public:

    bool testInsertNormalMinSkew();
    bool testInsertNormalMinLeft();
    bool testInsertNormalMaxSkew();
    bool testInsertNormalMaxLeft();
    bool testRemoveNormalMinSkew();
    bool testRemoveNormalMinLeft();
    bool testRemoveNormalMaxSkew();
    bool testRemoveNormalMaxLeft();
    bool testLeftHeapNPL();
    bool testMinLeftHeapNPLNHeapProperty();
    bool testMaxLeftHeapNPLNHeapProperty();
    bool testChangingPriorityNHeapTypeToMinLeft();
    bool testChangingPriorityNHeapTypeToMinSkew();
    bool testChangingPriorityNHeapTypeToMaxLeft();
    bool testChangingPriorityNHeapTypeToMaxSkew();
    bool testMergeEmptyQueue();
    bool testCopyConstructorNormal();
    bool testCopyConstructorEdge();
    bool testAssignmentOperatorNormal();
    bool testAssignmentOperatorEdge();
    bool testDequeueException();
    bool testMergeException();

};

int main(){
    Tester tester;

    if (tester.testInsertNormalMinLeft()) // should return true
        cout << "\ttestInsertNormalMinLeft() returned true." << endl;
    else
        cout << "\ttestInsertNormalMinLeft() returned false." << endl;

    if (tester.testInsertNormalMinSkew()) // should return true
        cout << "\ttestInsertNormalMinSkew() returned true." << endl;
    else
        cout << "\ttestInsertNormalMinSkew() returned false." << endl;

    if (tester.testInsertNormalMaxLeft()) // should return true
        cout << "\ttestInsertNormalMaxLeft() returned true." << endl;
    else
        cout << "\ttestInsertNormalMaxLeft() returned false." << endl;

    if (tester.testInsertNormalMaxSkew()) // should return true
        cout << "\ttestInsertNormalMaxSkew() returned true." << endl;
    else
        cout << "\ttestInsertNormalMaxSkew() returned false." << endl;

    if (tester.testRemoveNormalMinLeft()) // should return true
        cout << "\ttestRemoveNormalMinLeft() returned true." << endl;
    else
        cout << "\ttestRemoveNormalMinLeft() returned false." << endl;

    if (tester.testRemoveNormalMinSkew()) // should return true
        cout << "\ttestRemoveNormalMinSkew() returned true." << endl;
    else
        cout << "\ttestRemoveNormalMinSkew() returned false." << endl;

    if (tester.testRemoveNormalMaxLeft()) // should return true
        cout << "\ttestRemoveNormalMaxLeft() returned true." << endl;
    else
        cout << "\ttestRemoveNormalMaxLeft() returned false." << endl;

    if (tester.testRemoveNormalMaxSkew()) // should return true
        cout << "\ttestRemoveNormalMaxSkew() returned true." << endl;
    else
        cout << "\ttestRemoveNormalMaxSkew() returned false." << endl;

    if (tester.testLeftHeapNPL()) // should return true
        cout << "\ttestLeftHeapNPL() returned true." << endl;
    else
        cout << "\ttestLeftHeapNPL() returned false." << endl;

    if (tester.testMinLeftHeapNPLNHeapProperty()) // should return true
        cout << "\ttestMinLeftHeapNPLNHeapProperty() returned true." << endl;
    else
        cout << "\ttestMinLeftHeapNPLNHeapProperty() returned false." << endl;

    if (tester.testMaxLeftHeapNPLNHeapProperty()) // should return true
        cout << "\ttestMaxLeftHeapNPLNHeapProperty() returned true." << endl;
    else
        cout << "\ttestMaxLeftHeapNPLNHeapProperty() returned false." << endl;

    if (tester.testChangingPriorityNHeapTypeToMinLeft()) // should return true
        cout << "\ttestChangingPriorityNHeapTypeToMinLeft() returned true." << endl;
    else
        cout << "\ttestChangingPriorityNHeapTypeToMinLeft() returned false." << endl;

    if (tester.testChangingPriorityNHeapTypeToMinSkew()) // should return true
        cout << "\ttestChangingPriorityNHeapTypeToMinSkew() returned true." << endl;
    else
        cout << "\ttestChangingPriorityNHeapTypeToMinSkew() returned false." << endl;

    if (tester.testChangingPriorityNHeapTypeToMaxLeft()) // should return true
        cout << "\ttestChangingPriorityNHeapTypeToMaxLeft() returned true." << endl;
    else
        cout << "\ttestChangingPriorityNHeapTypeToMaxLeft() returned false." << endl;

    if (tester.testChangingPriorityNHeapTypeToMaxSkew()) // should return true
        cout << "\ttestChangingPriorityNHeapTypeToMaxSkew() returned true." << endl;
    else
        cout << "\ttestChangingPriorityNHeapTypeToMaxSkew() returned false." << endl;

    if (tester.testMergeEmptyQueue()) // should return true
        cout << "\ttestMergeEmptyQueue() returned true." << endl;
    else
        cout << "\ttestMergeEmptyQueue() returned false." << endl;

    if (tester.testCopyConstructorNormal()) // should return true
        cout << "\ttestCopyConstructorNormal() returned true." << endl;
    else
        cout << "\ttestCopyConstructorNormal() returned false." << endl;

    if (tester.testCopyConstructorEdge()) // should return true
        cout << "\ttestCopyConstructorEdge() returned true." << endl;
    else
        cout << "\ttestCopyConstructorEdge() returned false." << endl;

    if (tester.testAssignmentOperatorNormal()) // should return true
        cout << "\ttestAssignmentOperatorNormal() returned true." << endl;
    else
        cout << "\ttestAssignmentOperatorNormal() returned false." << endl;

    if (tester.testAssignmentOperatorEdge()) // should return true
        cout << "\ttestAssignmentOperatorEdge() returned true." << endl;
    else
        cout << "\ttestAssignmentOperatorEdge() returned false." << endl;

    if (tester.testDequeueException()) // should return true
        cout << "\ttestDequeueException() returned true." << endl;
    else
        cout << "\ttestDequeueException() returned false." << endl;

    if (tester.testMergeException()) // should return true
        cout << "\ttestMergeException() returned true." << endl;
    else
        cout << "\ttestMergeException() returned false." << endl;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<10;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    cout << "\nDump of the leftist heap queue with priorityFn2 (MINHEAP):\n";
    aQueue.dump();
    aQueue.setStructure(SKEW);
    cout << "\nDump of the skew heap queue with priorityFn2 (MINHEAP):\n";
    aQueue.dump();
    cout << "\nPreorder traversal of the nodes in the queue with priorityFn2 (MINHEAP):\n";
    aQueue.printOrdersQueue();
    aQueue.setPriorityFn(priorityFn1, MAXHEAP);
    cout << "\nDump of the skew queue with priorityFn1 (MAXHEAP):\n";
    aQueue.dump();
    return 0;
}

int priorityFn1(const Order &order) {
    //this function works with a MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-5003]
    //the highest priority would be 3+5000 = 5003
    //the lowest priority would be 0+0 = 0
    //the larger value means the higher priority
    int priority = static_cast<int>(order.getCount()) + order.getPoints();
    return priority;
}

int priorityFn2(const Order &order) {
    //this funcction works with a MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-10]
    //the highest priority would be 0+0 = 0
    //the lowest priority would be 5+5 =10
    //the smaller value means the higher priority
    int priority = static_cast<int>(order.getItem()) + static_cast<int>(order.getMemebership());
    return priority;
}

//Function: Tester::testInsertNormalMinLeft
//Case: Insert 300 nodes and test that it follows the min heap property for leftist heap
//Expected result: we expect this to return true as it should past the test case
bool Tester::testInsertNormalMinLeft() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    result = result && aQueue.helpHeapProperty(aQueue.m_heap); // checks the property of with a helper

    return result;
}
//Function: Tester::testInsertNormalMinSkew
//Case: Insert 300 nodes and test that it follows the min heap property for skew heap
//Expected result: we expect this to return true as it should past the test case
bool Tester::testInsertNormalMinSkew() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    result = result && aQueue.helpHeapProperty(aQueue.m_heap); // checks the heap property

    return result;

}
//Function: Tester::testInsertNormalMaxLeft
//Case: Insert 300 nodes and test that it follows the max heap property for leftist heap
//Expected result: we expect this to return true as it should past the test case
bool Tester::testInsertNormalMaxLeft() {
    bool result = true;


    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    result = result && aQueue.helpHeapProperty(aQueue.m_heap); // checks the heap property

    return result;

}
//Function: Tester::testInsertNormalMaxSkew
//Case: Insert 300 nodes and test that it follows the max heap property for skew heap
//Expected result: we expect this to return true as it should past the test case
bool Tester::testInsertNormalMaxSkew() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, SKEW);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    result = result && aQueue.helpHeapProperty(aQueue.m_heap); // checks the heap property

    return result;

}
//Function: Tester::testRemoveNormalMinLeft
//Case: Insert 300 nodes and test that the nodes are being remove in order aka by the root
//Expected result: we expect this to return true as it should past the test case
bool Tester::testRemoveNormalMinLeft() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    // this test that the prev order priority is less or equal than the next order priority, it's a min heap
    Order order = aQueue.getNextOrder();
    Order order2 = aQueue.getNextOrder();
    result = result && (priorityFn2(order) <= priorityFn2(order2));
    Order order3 = aQueue.getNextOrder();
    result = result && (priorityFn2(order2) <= priorityFn2(order3));
    Order order4 = aQueue.getNextOrder();
    result = result && (priorityFn2(order3) <= priorityFn2(order4));
    Order order5 = aQueue.getNextOrder();
    result = result && (priorityFn2(order4) <= priorityFn2(order5));
    Order order6 = aQueue.getNextOrder();
    result = result && (priorityFn2(order5) <= priorityFn2(order6));
    Order order7 = aQueue.getNextOrder();
    result = result && (priorityFn2(order6) <= priorityFn2(order7));
    Order order8 = aQueue.getNextOrder();
    result = result && (priorityFn2(order7) <= priorityFn2(order8));
    Order order9 = aQueue.getNextOrder();
    result = result && (priorityFn2(order8) <= priorityFn2(order9));
    Order order10 = aQueue.getNextOrder();
    result = result && (priorityFn2(order9) <= priorityFn2(order10));
    Order order11 = aQueue.getNextOrder();
    result = result && (priorityFn2(order10) <= priorityFn2(order11));

    return result;
}
//Function: Tester::testRemoveNormalMinSkew
//Case: Insert 300 nodes and test that the nodes are being remove in order aka by the root
//Expected result: we expect this to return true as it should past the test case
bool Tester::testRemoveNormalMinSkew() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    // this test that the prev order priority is less or equal than the next order priority, it's a min heap
    Order order = aQueue.getNextOrder();
    Order order2 = aQueue.getNextOrder();
    result = result && (priorityFn2(order) <= priorityFn2(order2));
    Order order3 = aQueue.getNextOrder();
    result = result && (priorityFn2(order2) <= priorityFn2(order3));
    Order order4 = aQueue.getNextOrder();
    result = result && (priorityFn2(order3) <= priorityFn2(order4));
    Order order5 = aQueue.getNextOrder();
    result = result && (priorityFn2(order4) <= priorityFn2(order5));
    Order order6 = aQueue.getNextOrder();
    result = result && (priorityFn2(order5) <= priorityFn2(order6));
    Order order7 = aQueue.getNextOrder();
    result = result && (priorityFn2(order6) <= priorityFn2(order7));
    Order order8 = aQueue.getNextOrder();
    result = result && (priorityFn2(order7) <= priorityFn2(order8));
    Order order9 = aQueue.getNextOrder();
    result = result && (priorityFn2(order8) <= priorityFn2(order9));
    Order order10 = aQueue.getNextOrder();
    result = result && (priorityFn2(order9) <= priorityFn2(order10));
    Order order11 = aQueue.getNextOrder();
    result = result && (priorityFn2(order10) <= priorityFn2(order11));

    return result;
}
//Function: Tester::testRemoveNormalMaxLeft
//Case: Insert 300 nodes and test that the nodes are being remove in order aka by the root
//Expected result: we expect this to return true as it should past the test case
bool Tester::testRemoveNormalMaxLeft() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    // this test that the prev order priority is greater or equal than the next order priority, it's a max heap
    Order order = aQueue.getNextOrder();
    Order order2 = aQueue.getNextOrder();
    result = result && (priorityFn1(order) >= priorityFn1(order2));
    Order order3 = aQueue.getNextOrder();
    result = result && (priorityFn1(order2) >= priorityFn1(order3));
    Order order4 = aQueue.getNextOrder();
    result = result && (priorityFn1(order3) >= priorityFn1(order4));
    Order order5 = aQueue.getNextOrder();
    result = result && (priorityFn1(order4) >= priorityFn1(order5));
    Order order6 = aQueue.getNextOrder();
    result = result && (priorityFn1(order5) >= priorityFn1(order6));
    Order order7 = aQueue.getNextOrder();
    result = result && (priorityFn1(order6) >= priorityFn1(order7));
    Order order8 = aQueue.getNextOrder();
    result = result && (priorityFn1(order7) >= priorityFn1(order8));
    Order order9 = aQueue.getNextOrder();
    result = result && (priorityFn1(order8) >= priorityFn1(order9));
    Order order10 = aQueue.getNextOrder();
    result = result && (priorityFn1(order9) >= priorityFn1(order10));
    Order order11 = aQueue.getNextOrder();
    result = result && (priorityFn1(order10) >= priorityFn1(order11));

    return result;
}
//Function: Tester::testRemoveNormalMaxSkew
//Case: Insert 300 nodes and test that the nodes are being remove in order aka by the root
//Expected result: we expect this to return true as it should past the test case
bool Tester::testRemoveNormalMaxSkew() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, SKEW);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    // this test that the prev order priority is greater or equal than the next order priority, it's a max heap
    Order order = aQueue.getNextOrder();
    Order order2 = aQueue.getNextOrder();
    result = result && (priorityFn1(order) >= priorityFn1(order2));
    Order order3 = aQueue.getNextOrder();
    result = result && (priorityFn1(order2) >= priorityFn1(order3));
    Order order4 = aQueue.getNextOrder();
    result = result && (priorityFn1(order3) >= priorityFn1(order4));
    Order order5 = aQueue.getNextOrder();
    result = result && (priorityFn1(order4) >= priorityFn1(order5));
    Order order6 = aQueue.getNextOrder();
    result = result && (priorityFn1(order5) >= priorityFn1(order6));
    Order order7 = aQueue.getNextOrder();
    result = result && (priorityFn1(order6) >= priorityFn1(order7));
    Order order8 = aQueue.getNextOrder();
    result = result && (priorityFn1(order7) >= priorityFn1(order8));
    Order order9 = aQueue.getNextOrder();
    result = result && (priorityFn1(order8) >= priorityFn1(order9));
    Order order10 = aQueue.getNextOrder();
    result = result && (priorityFn1(order9) >= priorityFn1(order10));
    Order order11 = aQueue.getNextOrder();
    result = result && (priorityFn1(order10) >= priorityFn1(order11));

    return result;
}
//Function: Tester::testLeftHeapNPL
//Case: Insert 300 nodes and test all nodes in a leftist heap have the correct NPL value.
//Expected result: we expect this to return true as it should past the test case
bool Tester::testLeftHeapNPL() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    result = result && aQueue.helpHeapProperty(aQueue.m_heap); // checks heap property

    result = result && aQueue.helpCalcNpl2(aQueue.m_heap); // checks that the NPL is correct

    return result;
}
//Function: Tester::testMinLeftHeapNPLNHeapProperty
//Case: Insert 300 nodes and test a leftist heap preserves the property of such a heap, min heap
//Expected result: we expect this to return true as it should past the test case
bool Tester::testMinLeftHeapNPLNHeapProperty() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    result = result && aQueue.helpHeapProperty(aQueue.m_heap); // check property

    result = result && aQueue.helpCheckLeftProperty(aQueue.m_heap); // checks that left npl is greater or equal to right npl


    return result;
}
//Function: Tester::testMaxLeftHeapNPLNHeapProperty
//Case: Insert 300 nodes and test a leftist heap preserves the property of such a heap, max heap
//Expected result: we expect this to return true as it should past the test case
bool Tester::testMaxLeftHeapNPLNHeapProperty() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    result = result && aQueue.helpHeapProperty(aQueue.m_heap); // checks heap property

    result = result && aQueue.helpCheckLeftProperty(aQueue.m_heap); // checks that left npl is greater or equal to right npl

    return result;
}
//Function: Tester::testChangingPriorityNHeapTypeToMinLeft
//Case: Insert 300 nodes and test Max Leftist Heap changes to Min Leftist Heap
//Expected result: we expect this to return true as it should past the test case
bool Tester::testChangingPriorityNHeapTypeToMinLeft() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);
    for (int i=100002;i<100302;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      i);
        aQueue.insertOrder(anOrder);
    }
    aQueue.setPriorityFn(priorityFn2, MINHEAP); // changes the priority and heap type

    result = result && (aQueue.m_priorFunc == priorityFn2); // checks priority

    result = result && (aQueue.m_heapType == MINHEAP); // checks heap type

    result = result && (aQueue.m_size == 300); // checks the size

    result = result && aQueue.helpHeapProperty(aQueue.m_heap); // checks property

    return result;
}
//Function: Tester::testChangingPriorityNHeapTypeToMinSkew
//Case: Insert 300 nodes and test Max Skew Heap changes to Min Skew Heap
//Expected result: we expect this to return true as it should past the test case
bool Tester::testChangingPriorityNHeapTypeToMinSkew() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, SKEW);
    for (int i=100002;i<100302;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      i);
        aQueue.insertOrder(anOrder);
    }
    aQueue.setPriorityFn(priorityFn2, MINHEAP);

    result = result && (aQueue.m_priorFunc == priorityFn2);

    result = result && (aQueue.m_heapType == MINHEAP);

    result = result && (aQueue.m_size == 300);

    result = result && aQueue.helpHeapProperty(aQueue.m_heap);

    return result;
}
//Function: Tester::testChangingPriorityNHeapTypeToMaxLeft
//Case: Insert 300 nodes and test Min Leftist Heap changes to Max Leftist Heap
//Expected result: we expect this to return true as it should past the test case
bool Tester::testChangingPriorityNHeapTypeToMaxLeft() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=100002;i<100302;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      i);
        aQueue.insertOrder(anOrder);
    }
    aQueue.setPriorityFn(priorityFn1, MAXHEAP);

    result = result && (aQueue.m_priorFunc == priorityFn1);

    result = result && (aQueue.m_heapType == MAXHEAP);

    result = result && (aQueue.m_size == 300);

    result = result && aQueue.helpHeapProperty(aQueue.m_heap);

    return result;
}
//Function: Tester::testChangingPriorityNHeapTypeToMaxSkew
//Case: Insert 300 nodes and test Min Skew Heap changes to Max Skew Heap
//Expected result: we expect this to return true as it should past the test case
bool Tester::testChangingPriorityNHeapTypeToMaxSkew() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);
    for (int i=100002;i<100302;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      i);
        aQueue.insertOrder(anOrder);
    }
    aQueue.setPriorityFn(priorityFn1, MAXHEAP);

    result = result && (aQueue.m_priorFunc == priorityFn1);

    result = result && (aQueue.m_heapType == MAXHEAP);

    result = result && (aQueue.m_size == 300);

    result = result && aQueue.helpHeapProperty(aQueue.m_heap);

    return result;
}
//Function: Tester::testMergeEmptyQueue
//Case: Insert 300 nodes and test merge of an empty queue (an edge case) with a normal queue
//Expected result: we expect this to return true as it should past the test case
bool Tester::testMergeEmptyQueue() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW); // filled queue
    CQueue aQueue2(priorityFn2, MINHEAP, SKEW); // empty queue
    for (int i=100002;i<100302;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      i);
        aQueue.insertOrder(anOrder);
    }

    aQueue2.mergeWithQueue(aQueue); // trying to merge them

    result = result && (aQueue2.m_heap != nullptr); // checks that queue 2 isn't empty
    result = result && (aQueue.m_heap == nullptr); // checks that queue 1 s empty

    return result;
}
//Function: Tester::testCopyConstructorNormal
//Case: Insert 300 nodes and test C2 takes on what C1 had
//Expected result: we expect this to return true as it should past the test case
bool Tester::testCopyConstructorNormal() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);
    //CQueue aQueue2(priorityFn2, MINHEAP, SKEW);
    for (int i=100002;i<100302;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      i);
        aQueue.insertOrder(anOrder);
    }

    CQueue aQueue2(aQueue);

    result = result && aQueue.helpDeepCopyCheck(aQueue.m_heap, aQueue2.m_heap); // use this to check deep copy

    return result;
}
//Function: Tester::testCopyConstructorEdge
//Case: Insert 1 nodes and test empty C2 going into empty C2
//Expected result: we expect this to return true as it should past the test case
bool Tester::testCopyConstructorEdge() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);
    //CQueue aQueue2(priorityFn2, MINHEAP, SKEW);

    CQueue aQueue2(aQueue);

    result = result && aQueue.helpDeepCopyCheck(aQueue.m_heap, aQueue2.m_heap); // use this to check deep copy

    return result;
}
//Function: Tester::testAssignmentOperatorNormal
//Case: Insert 300 nodes and test copying C1 to C2 while both have nodes
//Expected result: we expect this to return true as it should past the test case
bool Tester::testAssignmentOperatorNormal() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);
    CQueue aQueue2(priorityFn2, MINHEAP, SKEW);
    for (int i=100002;i<100302;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      i);
        aQueue.insertOrder(anOrder);
        Order anOrder1(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      i);
        aQueue2.insertOrder(anOrder1);
    }
    aQueue2 = aQueue;

    result = result && aQueue.helpDeepCopyCheck(aQueue.m_heap, aQueue2.m_heap); // use this to check deep copy

    return result;
}
//Function: Tester::testAssignmentOperatorEdge
//Case: Insert 300 nodes and test Copying one empty and one with Orders
//Expected result: we expect this to return true as it should past the test case
bool Tester::testAssignmentOperatorEdge() {
    bool result = true;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);
    CQueue aQueue2(priorityFn2, MINHEAP, SKEW);
    for (int i=100002;i<100302;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      i);
        aQueue.insertOrder(anOrder);
    }
    aQueue2 = aQueue;

    result = result && aQueue.helpDeepCopyCheck(aQueue.m_heap, aQueue2.m_heap); // use this to check deep copy

    return result;
}
//Function: Tester::testDequeueException
//Case: testing deleting an empty heap, should throw a error so it should be try than caught
//Expected result: we expect this to return true as it should past the test case
bool Tester::testDequeueException() {
    bool result = false;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);

    try { // try to remove
        aQueue.getNextOrder();
    }
    catch(out_of_range const&) { // should catch out or range error
        result = true; // change result to true
    }

    return result;
}
//Function: Tester::testMergeException
//Case: test merging with different priorities and heap type, should throw a error so it should be try than caught
//Expected result: we expect this to return true as it should past the test case
bool Tester::testMergeException() {
    bool result = false;

    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen( 0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);
    CQueue aQueue2(priorityFn1, MAXHEAP, LEFTIST);
    for (int i=100002;i<100302;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      i);
        aQueue.insertOrder(anOrder);
    }
    try { // try to merge
        aQueue2.mergeWithQueue(aQueue);
    }
    catch(domain_error const&) { // catch domain error
        result = true; // change result to true
    }

    return result;
}




