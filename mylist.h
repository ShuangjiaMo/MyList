#include<iostream>
using namespace std;

template<class T>
class MyList{
private:
	T *a;
	int size, top;
	
	void double_space()			//double the space when the list is not long enough
	{	T *tmp = a;
		size *= 2;
		
		a = new T [size];
		for (int i=0; i<size/2; ++i) a[i] = tmp[i];
		
		delete [] tmp;
	}
	
	void lessSort(int l, int r)  
	{   if (l< r)  
	    {        
	        int i = l, j = r, x = a[l];  
	        while (i < j)  
	        {  
	            while(i < j && a[j]>= x) j--;   
	            if(i < j) a[i++] = a[j];  
	            while(i < j && a[i]< x) i++;   
	            if(i < j) a[j--] = a[i];  
	        }  
	        a[i] = x;  
	        lessSort(l, i - 1); 
	        lessSort(i + 1, r);  
	    }  
	}  
	
	void greaterSort(int l, int r)  
	{   if (l< r)  
	    {        
	        int i = l, j = r, x = a[l];  
	        while (i < j)  
	        {  
	            while(i < j && a[j]< x) j--;   
	            if(i < j) a[i++] = a[j];  
	            while(i < j && a[i]>= x) i++;   
	            if(i < j) a[j--] = a[i];  
	        }  
	        a[i] = x;  
	        greaterSort(l, i - 1); 
	        greaterSort(i + 1, r);  
	    }  
	} 

public:
	MyList()
	{	size = 100;
		top = 0;
		a = new T [size];
	}
	
	MyList(int num, const T &item)			//put n items in the list
	{	size = 100;
		top = num;
				
		a = new T [size];
		while (top > size) double_space();
		for (int i=0; i<num; ++i) a[i] = item;
	}
	
	MyList(const MyList &l)			//copy another list
	{	size = 100;
		top = l.top;
				
		a = new T [size];
		while (top > size) double_space();
		for (int i=0; i<top; ++i) a[i] = l.a[i];
	}
	
	MyList(T* arr, int len)			//copy the fisrt n items of another list
	{	size = 100;
		top = len;
		
		a = new T [size];
		while (top > size) double_space();
		for (int i=0; i<top; ++i) a[i] = arr[i];
	}
	
	void push(const T &item)			//push an item to the end of the list
	{	++top;
		while (top > size) double_space();
		a[top-1] = item;
	} 
	
	T pop()			//delete the last item of the list and return its value
	{	--top; return a[top];}
	
	void insert(int index, const T &item)			//insert the item at the corresponding place 
	{	if (index > top) cout << "ERROR!" << endl;
		else{
			T *tmp = a;
			++top;
			
			a = new T [size];
			while (top > size) double_space();
			
			for (int i=0; i<index; ++i) a[i] = tmp[i];
			for (int i=index+1; i<top; ++i) a[i] = tmp[i-1];
			a[index] = item;
			
			delete [] tmp;
		}
	}
	
	void clean()			//clean the list
	{	top = 0;}
	
	int get_size() const		//return the size of the list
	{	return top;}
	
	void erase(int start, int end)			//delete the items from start to end
	{	if (start > end){
			cout << "ERROR!" << endl;
		} 
		else{
			T *tmp = a;
			a = new T [size];
			
			for (int i=0; i<start; ++i) a[i] = tmp[i];
			for (int i=end+1; i<top; ++i) a[i-end+start-1] = tmp[i];
			top = top-end+start-1;
			
			delete [] tmp;
		}
	}
	
	T get_item(int index)			//return a corresponding item
	{	if (index >= top) cout << "ERROR!" << endl;			
		else return a[index];
	}
	
	MyList get_item(int start, int end)			//return the items from start to end
	{	MyList temp;
		if (start < 0) start += top;
		if (end < 0) end += top;
		if (start<0 || end<0 || start>end || start>top-1 || end>top-1){
			cout << "ERROR!" << endl;			
		}
		else{
			for (int i=start; i<=end; ++i) temp.push(a[i]);
		}
		return temp;
	}
		
	int count(const T &item)			//return the number of the elements which are equal to item
	{	int cnt = 0;
		for (int i=0; i<top; ++i){
			if (a[i] == item) ++cnt; 
		}
		return cnt;
	}
	
	void remove(const T &item)			//remove the first element which is equal to item
	{	for (int i=0; i<top; ++i){
			if (a[i] == item){
				for (int j=i; j<top-1; ++j) a[j] = a[j+1];
				--top;
				break;
			}
		}
	}

	MyList &operator = (const MyList &l)			//set value
	{	if (this == &l) return *this;
		
		delete [] a;
		
		size = 100;
		top = l.top;
		
		a = new T [size];
		while (top > size) double_space();
		for (int i=0; i<top; ++i) a[i] = l.a[i];
		
		return *this;
	}
	
	MyList &operator += (const T &item)			//push item
	{	this->push(item);
		return *this;
	}
	
	MyList &operator += (const MyList &l)			//same as add
	{	for (int i=0; i<l.top; ++i) this->push(l.a[i]);
		return *this;
	}
	
	T &operator [](int index) const			//return the corresponding item
	{	if (index > top) cout << "ERROR!" << endl;			
		else return a[index];
	}
	
	friend MyList operator + (const MyList &l1, const MyList &l2)			//merge two lists
	{	T *tmp = new T [l1.top + l2.top];
		
		for (int i=0; i<l1.top; ++i) tmp[i] = l1[i];
		for (int i=l1.top; i<l1.top+l2.top; ++i) tmp[i] = l2[i-l1.top];
		
		MyList temp(tmp, l1.top+l2.top);
		delete [] tmp;
		
		return temp;
	}
	
	friend MyList operator + (const MyList &l1, const T &item)			//push item and return a new list
	{	MyList temp(const MyList &l1);
		temp.push(item);
		return temp;
	}
	
	friend ostream & operator<<(ostream &os, const MyList &obj)			//output the list like [1, 2, 5, 4, 1]
	{	os << "[";
		for (int i=0; i<obj.top-1; ++i) os << obj.a[i] << ", ";
		os << obj.a[obj.top-1] << "]";
		
		return os;
	}

	void sort(bool less=true)			//quick sort 
	{   if (less) lessSort(0, top-1);
		else greaterSort(0, top-1);
	}   
	
	void reverse()			//reverse the items 
	{	int tmp;
		for (int i=0; i<top/2; ++i){
			tmp = a[i];
			a[i] = a[top-i-1];
			a[top-i-1] = tmp;
		}
	}

	~MyList(void){ delete [] a;}
};


