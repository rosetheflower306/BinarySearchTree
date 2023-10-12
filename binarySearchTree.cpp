//RoseTran - CS 310
//Lab Assignment: Binary Search Tree
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <class T>
class BinarySearchTree
{
  public: 
    int size, level;
    T *array;
    const int NULLVALUE = 2147483647;

    //constructor
    BinarySearchTree(int level)
    {
      this->level = level;
      this->size = extendSize(level); // 2^(level+1) - 1
      this->array = new T[this->size];
      for (int x = 0; x < this->size; x++)
      {
        array[x] = NULLVALUE;
      }
    }

    //copy constructor
    BinarySearchTree(const BinarySearchTree & obj)
    {
      this->size = obj.size;
      this->level = obj.level;
      this->array = new T[obj.size];
      for (int i = 0; i < obj.size; i++)
      {
        this->array[i] = obj.array[i];
      }
    }

    //Destructor
    ~BinarySearchTree()
    {
      delete [] (this->array);
    }

    /**
     * This function extend or determine the size up the BST
     * @param level An integer value represent the number of levels in the BST
     * @return the most updated size of BST
    */
    int extendSize(int level)
    {
      size = pow(2,level+1) - 1;
      return size;
    }
    
    /**
     * This function add more level/ space when the BST is full
    */
    void reAllocate()
    {
      cout << endl << "Increasing the level of the tree " << endl;
      int oldSize = size;
      this->level = (this->level) + 1;
      int tempSize = extendSize(this->level); // returns 2^(level+1) -1
      T *tempArray = new T[tempSize];
      // copy the elements of the previous array
      for (int i = 0; i < oldSize; i++)
      {
        tempArray[i] = this->array[i];
      }

      // all the remaining nodes should be empty
      for(int i = oldSize; i < tempSize; i++)
      {
        tempArray[i] = NULLVALUE;
      }

      // remove the memory of previous array
      delete [] (this->array);
      this->array = nullptr;
      // point to the newly created array
      this->array = tempArray;
      // update the new size information
      size = tempSize;
    }
    
    /**
     * This function insert element to the BST
     * @param item A T type element
    */
    void insert(T item)
    {
      int currentIndex = 0;
      cout << "Adding: " << item;
      while (true)
      {
        if (currentIndex >= size) 
        {
          reAllocate();
        }
        // a valid position has been found to add the item
        if (array[currentIndex] == NULLVALUE)
        {
          array[currentIndex] = item;
          cout << "\nInserted at index: " << currentIndex << endl << endl;
          break;
        }
        else if (array[currentIndex] < item || array[currentIndex] == item)
        {
        // duplicates not allowed in the BST
          if (array[currentIndex] == item)
          {
            cout << "ERROR!-- Repeating element" << endl;
            break;
          }
          currentIndex = (2 * currentIndex + 2);
        }
        else if (array[currentIndex] > item || array[currentIndex] == item)
        {
          if (array[currentIndex] == item)
          {
            cout << "ERROR!-- Repeating element" << endl;
            break;
          }
          currentIndex = (2 * currentIndex + 1);
        }
      }  
    }
    
    /**
     * This function deletes an element T from the binary search tree
     * @param data A T type element
     * @return true if element is deleted
    */
    bool deteleElement(T data)
    {
      // start from the root of the tree
      return deleteSetup(0, data);
    }
    
    /**
     * This function deletes an element T from the binary search tree
     * @param data A T type element
     * @param index The index of the element that is needed to delete
     * @return true if element is found
    */
    bool deleteSetup(int index, T data)
    {
      // nothing to delete
      if (elementAt(index) == NULLVALUE) 
      {
        return false;
      }
      // otherwise
      if (data < array[index])
      {
        return deleteSetup(2 * index + 1, data);
      }
      else if (data > array[index])
      {
        return deleteSetup(2 * index + 2, data);
      }
      else return deleteNode(index); // element found
    }

    /**
     * This function find and return an element T at index position from the binary search tree
     * @param index An index of the item
     * @return a T type element at index position
    */
    T elementAt(int index)
    {
      if(index >= size) 
      {
        return NULLVALUE;
      }
      else return array[index];
    }

    /**
     * This function deletes an element T from the binary search tree
     * @param index An index of the element that is needed to delete
     * @return true if element is deleted
    */
    bool deleteNode(int index)
    {
      // calculate the index of left and right children
      int left = 2 * index + 1;
      int right = 2 * index + 2;
      // case 0: the node has no children
      if ((elementAt(left) == NULLVALUE) && (elementAt(right) == NULLVALUE))
      {
        array[index] = NULLVALUE;
        return true;
      } // case 1: one children (or one subtree)
      else if (elementAt(left) == NULLVALUE)
      {
        // copy the value from the right child
        array[index] = elementAt(right);
        // delete the right child
        return deleteNode(right);
      }
      else if (elementAt(right) == NULLVALUE)
      {
        // copy the value from the left child
        array[index] = elementAt(left);
        // delete the left child
        return deleteNode(left);
      }
      else //case 2: two nodes
      {
        int preIndex = predecessor(left);
        // copy the value of the predecessor
        array[index] = elementAt(preIndex);
        // Now, delete the predecessor node: case 0 or case 1
        return deleteNode(preIndex);
      }
      return false; //not possible
    }

    /**
     * This function displays the elements of the binary search tree in order
     * @param currentIndex An integer index
    */
    void inOrderTraverse(int currentIndex)
    {
      if (currentIndex >= size)
      {
        return;
      }
      if (array[currentIndex] != NULLVALUE)
      {
        inOrderTraverse(2 * currentIndex + 1);//left
        cout << array[currentIndex] << endl;//root
        inOrderTraverse(2 * currentIndex + 2);//right
      }
    }

    /**
     * This function displays the elements of the binary search tree in order
     * start at the root, index = 0
    */
    void inOrder()
    {
      inOrderTraverse(0);
    }

    /**
     * This function displays the elements of the binary search tree pre order
     * @param currentIndex An integer index
    */
    void preOrderTraverse(int currentIndex)
    {
      if (currentIndex >= size)
      {
        return;
      }
      if (array[currentIndex] != NULLVALUE)
      {
        cout << array[currentIndex] << endl;//root
        preOrderTraverse(2 * currentIndex + 1);//left
        preOrderTraverse(2 * currentIndex + 2);//right
      }
    }

    /**
     * This function displays the elements of the binary search tree pre order
     * start at the root, index = 0
    */
    void preOrder()
    {
        preOrderTraverse(0);
    }

    /**
     * This function displays the elements of the binary search tree post order
     * @param currentIndex An integer index
    */
    void postOrderTraverse(int currentIndex)
    {
      if (currentIndex >= size)
      {
        return;
      }
      if (array[currentIndex] != NULLVALUE)
      {
        postOrderTraverse(2 * currentIndex + 1);//left
        postOrderTraverse(2 * currentIndex + 2);//right
        cout << array[currentIndex] << endl;//root
      }
    }

    /**
     * This function displays the elements of the binary search tree post order
     * start at the root, index = 0
    */
    void postOrder()
    {
      postOrderTraverse(0);
    }

    /**
     * This function displays the elements of the binary search tree descedent order
     * @param currentIndex An integer index
    */
    void descendentOrder(int currentIndex)
    {
      if (currentIndex >= size)
      {
        return;
      }
      if (array[currentIndex] != NULLVALUE)
      {
        descendentOrder(2 * currentIndex + 2);//right
        cout << array[currentIndex] << endl;//root
        descendentOrder(2 * currentIndex + 1);//left
      }
    }

    /**
     * This function searches the binary search tree for the element T 
     * and returns true/false accordingly
     * @param searchVal an T type element
     * @return true if found and false for otherwise
    */
    bool search(T searchVal)
    {
      int currentIndex = 0;
      while (true)
      {
        // anchor
        if (currentIndex >= size || array[currentIndex] == NULLVALUE)
        {
          cout << "Not Found" << endl;
          return false;
        } // base case
        if (array[currentIndex] == searchVal)
        {
          cout << "Found at index: " << currentIndex << endl;
          return true;
        } // general case
        else if (array[currentIndex] < searchVal)
        {
          currentIndex = (2 * currentIndex + 2);
        }
        else if (array[currentIndex] > searchVal)
        {
          currentIndex = (2 * currentIndex + 1);
        }
      }
    }

    /**
     * This function returns the predecessor of the node at index position
     * @param index An integer value represents the indext of the node
     * @return the index of the predescessor
    */
    int predecessor(int index) //go to the right most element in the left subtree
    {
      int left = 2 * index + 1;
      // if the right of the current node is not NULLVALUE
      // move to that node
      if (elementAt(left) != NULLVALUE)
      {
        index = left;
        // index of the right child
        int right = 2 * index + 2;
        while (elementAt(right) != NULLVALUE) 
        {
          index = right;
          right = 2 * index + 2;
        }
      }
      return index;
    }

    /**
     * This function returns the successor of the node at index position
     * @param index An integer value represents the indext of the node
     * @return the index of the successor
    */
    int successor(int index)  //go to the left most element in the right subtree
    {
      int right = 2 * index + 2;
      // if the right of the current node is not NULLVALUE
      // move to that node
      if (elementAt(right) != NULLVALUE)
      {
        index = right;
        // index of the right child
        int left = 2 * index + 1;
        while (elementAt(left) != NULLVALUE) 
        {
          index = left;
          left = 2 * index + 1;
        }
      }
      return index;
    }

    /**
     * This function returns the number of nodes in the binary search tree
     * @return The number of nodes in BST
    */
    int countNodes()
    {
      cout << "\nThere are " << size << " nodes.\n";
      return size;
    }

    /**
     * This function returns the maximum value of the binary search tree
     * @return a T type max value 
    */ 
    T maximum() //rightmost element of the right subtree
    {
      int currentIndex = 0;
      int right = 2 * currentIndex + 2;
      while (elementAt(right) != NULLVALUE)
      {
        currentIndex = right;
        right = 2 * currentIndex + 2;
      }
      return elementAt(currentIndex);
    }

    /**
     * This function returns the minimum value of the binary search tree
     * @return a T type min value 
    */ 
    T minimum() 
    {
      int currentIndex = 0;
      int left = 2 * currentIndex + 1;
      while (elementAt(left) != NULLVALUE)
      {
        currentIndex = left;
        left = 2 * currentIndex + 1;
      }
      return elementAt(currentIndex);
    }

    /**
     * This function returns the current size (array size) of the binary search tree
     * @return a int type value 
    */ 
    int arraySize()
    {
      int count = 0;
      for (int i = 0; i < size; i++)
      {
        if (array[i] != NULLVALUE)
        {
          count++;
        } 
      }
      return count;
    }

    /**
     * This function returns true/false to indicate whether the binary search tree is empty methods in the class.
     * @return a boolean type 
    */
    bool isEmpty()
    {
      for (int i = 0; i < size; i++)
      {
        if (array[i] != NULLVALUE)
        {
          cout << "\nThe tree is not empty...\n";
          return false; //the tree is not empty
        }
      }
      cout << "\nThe tree is empty...\n";
      return true; //is empty
    }
};

class Point
{
  private:
    int x, y;
  public:
    //constructor
    Point(int a = 0, int b = 0)
    {
      this->x = a;
      this->y = b;
    }

    //copy constructor
    Point(const Point & obj)
    {
      this->x = obj.x;
      this->y = obj.y;
    }
    
    //overload assignment operator
    Point operator =(const Point & obj)
    {
      x = obj.x;
      y = obj.y;
    }

    //overload < operator
    bool operator <(const Point & obj) const
    {
      if (x < obj.x) return true;
      else if (x == obj.x)
      {
        return y < obj.y;
      }
      else return false;
    }

    //overload > operator
    bool operator >(const Point & obj) const
    {
      if (x > obj.x) return true;
      else if (x == obj.x)
      {
        return y > obj.y;
      }
      else return false;
    }

    //overload == operator
    bool operator ==(const Point & obj) const
    {
      if ((x == obj.x) && (y == obj.y))
      {
        return true;
      } 
      else return false;
    }

    //overload != operator
    bool operator !=(const Point & obj) const
    {
      if ((x != obj.x) && (y != obj.y))
      {
        return true;
      } 
      else return false;
    }

    operator std::string() const
    {
      return "x = " + std::to_string(x) + ", y = " + std::to_string(y);
    }

    // Overloaded << operator to display a Movie
    friend ostream & operator << (ostream &out, const Point &point) 
    {
      out << std::string(point);
      return out;
    }
};


int main()
{
  BinarySearchTree<Point> pointCollection(7);
  //a) Declare 7 Point objects 
  //and add them to the pointCollection variable by using insert method.
  Point obj1 = Point(150,2);
  Point obj2 = Point(3,5);
  Point obj3 = Point(30,6);
  Point obj4 = Point(4,9);
  Point obj5 = Point(11,12);
  Point obj6 = Point(7,88);
  Point obj7 = Point(100,50);

  pointCollection.insert(obj1);
  pointCollection.insert(obj2);
  pointCollection.insert(obj3);
  pointCollection.insert(obj4);
  pointCollection.insert(obj5);
  pointCollection.insert(obj6);
  pointCollection.insert(obj7);

  //b) Display all the Point objects (assign the object T in a string variable 
  //and display the string variable by using cout object) 
  //by using inOrder/preOrder/ postOrder methods.
  cout << "Display by using string variables:\n";
  std::string s1 = obj1;
  std::string s2 = obj2;
  std::string s3 = obj3;
  std::string s4 = obj4;
  std::string s5 = obj5;
  std::string s6 = obj6;
  std::string s7 = obj7;
  cout << s1 << endl << s2 << endl << s3 << endl 
       << s4 << endl << s5 << endl << s6 << endl << s7;
  
  cout << "\n\nDisplay by inOder:\n";
  pointCollection.inOrder();
  cout << "\nDisplay by preOder:\n";
  pointCollection.preOrder();
  cout << "\nDisplay by postOder:\n";
  pointCollection.postOrder();

  //c) Create a copy of the pointCollection variable named myPointCollection 
  //(utilize the copy constructor) and 
  //display the content of the myPointCollection variable (inOrder only).
  BinarySearchTree<Point> myPointCollection(pointCollection);
  cout << "\nCopy constructor display:\n";
  myPointCollection.inOrder();

  //d) Declare a Point object and demonstrate the search(pointObj) function.
  Point pointObj = Point(1,2);
  cout << endl;
  pointCollection.search(pointObj);
  cout << endl;

  //e) Declare a Point object and demonstrate the delete(pointObj) function. 
  //Display the contents of the pointCollection variable to ensure that the delete operation has taken place.
  pointCollection.insert(pointObj);
  cout << "The collection after adding point Object:\n";
  pointCollection.inOrder();
  cout << "\nThe collection after delete point Object:\n";
  pointCollection.deteleElement(pointObj);
  pointCollection.inOrder();

  //f) Display the predecessor and successor of the root node
  cout << "\nThe predecessor and successor of the root node respectively are: ";
  int x = pointCollection.predecessor(0);
  int y = pointCollection.successor(0);
  cout << pointCollection.array[x] << " at index " << x << endl << "and " 
       << pointCollection.array[y] << " at index " << y << endl;

  //g) Display the node count, size, maximum, and minimum of the BinarySearchTree
  pointCollection.countNodes();
  cout << "There are " << pointCollection.arraySize() << " elements in the BST\n";
  cout << "Maximum: " << pointCollection.maximum() << endl;
  cout << "Minimum: " << pointCollection.minimum() << endl;

  //h) Display the elements of the BinarySearchTree in ascending and descending sorted order
  //(implement additional method in the BinarySearchTree if needed).
  cout << "\nDisplay in ascendent order:\n";
  pointCollection.inOrder();
  cout << "\nDisplay in descendent order:\n";
  pointCollection.descendentOrder(0);

  return 0;
}