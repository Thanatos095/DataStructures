#include<iostream>
using namespace std;

template<class T>
class Node
{
    Node* n;
    T value;
    public:
    Node(T v): n(NULL), value(v){}
    void connect(Node *next)
    {
        n = next;
    }
    
    Node* getNext()
    {
        return n;
    }
    T& getValue()
    {
        return value;
    }
    void nullify()
    {
    	n = NULL;
	}
    ~Node()
    {
            delete n;
    }
};
template<class T>
class List
{
    mutable Node<T>* curr;
    Node<T>* head;
    int size;
    public:
    List(T val)
    {
        size = 1;
        head = new Node<T>(val);
        curr = head;
    }
    List(const List& ref)
    {
    	size = 1;
        head = new Node<T>(ref.head->getValue());
        curr = head;
    	for(int i = 1 ; i < ref.getSize() ; i++)
    	{
    		this->append(ref[i]);
		}
	}
    void append(T val)
    {
    	size++;
        Node<T> *temp = new Node<T>(val);
        curr->connect(temp);
        curr = temp;
    }
	void remove(int i)
	{
		Node<T> *temp;
		if(i == 0)
		{
			temp = head;
			head = head->getNext();
    		temp->nullify();
    		delete temp;
			size--;
    		return;
    	}	
	    else if(i == size - 1)
	    {
	    	pop();
		}
		else
		{
			Node<T> *after;
			Node<T> *before;
			curr = head;
			for(int j = 0 ; j <= i - 2  ; j++)
        {
            curr = curr->getNext();
        } 
			before = curr;
			temp = curr->getNext();  
        	after = temp->getNext();
			before->connect(after);
			temp->nullify();
			delete temp;
			size--;
			return;
		}
	}
	void pop()
	{
			Node<T> *temp;
			curr = head;
	    	while(curr->getNext()->getNext() != NULL)
	    	{
	    		curr = curr->getNext();
			}
			temp = curr->getNext();
			curr->nullify();
			delete temp;
			size--;
			return;
	}
    int getSize() const
    {
    	return size;
	}
	
    T& operator[](int i) const
	{
        curr = head;
        int j = 0;
        for(j = 0 ; j < i ; j++)
        {
            curr = curr->getNext();
        }
        return curr->getValue();
    }
    ~List()
    {
        delete head;
    }
	void print()
    {
    	for(int i = 0 ; i < this->getSize() ; i++)
    	{
    		cout<<(*this)[i]<<endl;
		}
	}
};

struct Student
{
	int id;
	string name;
	bool isBad;
	Student(int a, string b, bool c): id(a), name(b), isBad(c){
	}
	friend ostream& operator<<(ostream& os, const Student& s);
};

ostream& operator<<(ostream& os, const Student& s)
{
	os<<"Name: "<<s.name<<", id: "<<s.id<<endl;
	return os;
}
int main()
{
    List<Student> linky(Student(146, "Raahim", true));
	linky.append(Student(338, "Mahad", true));
	linky.append(Student(205, "Abbas", true));
	linky.remove(2);
	linky.print();	

}