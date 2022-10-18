#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
	// two helper function - trickle up and trickle down
	void tr_up(int idx);
	void tr_down(int idx);
	std::vector<T> data;
	PComparator c;
	int m;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
{
	this->m=m;
	this->c=c;
}
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
	return data.size()==0;
}
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
	return data.size();
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
		throw std::underflow_error("Empty Heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
	return data[0];
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::tr_up(int idx)
{
	//get index for parents
	int p_idx=(idx-1)/m;
	while(p_idx>=0&& c(data[idx], data[p_idx]))
	{
		//swap if the functor retuns true
		T temp= data[idx];
		data[idx]=data[p_idx];
		data[p_idx]=temp;
		idx=p_idx;
		p_idx=(p_idx-1)/m;
	}
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
	//push_back and call trickle up
	data.push_back(item);
	tr_up(data.size()-1);
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::tr_down(int idx)
{
	int leaf_idx = 0;
	int prev = 0;
	//a stupid method to determine whether the idx is a leaf node
	while(1)
	{
		//find height of the tree
		if(leaf_idx*m+1>int(data.size()-1)) break;
		prev=leaf_idx;
		leaf_idx=leaf_idx*m+1;
	}
	//return if the index is at the bottom
	if(idx>=leaf_idx) return;
	else if(idx>=prev)
	{
		//return if the index is not at the bottom but is a leaf
		while(prev<leaf_idx)
		{
			bool flag = false;
			for(int i = 1; i<=m; i++)
			{
				if(prev*m+i<=int(data.size()-1))
				{
					flag=true;
					break;
				}
			}
			if(!flag)
			{
				if(idx==prev) return;
			}
			prev++;
		}
	}
	T maxChild = data[idx*m+1];
	int max_idx = idx*m+1;
	// find the max child using the functor
	for(int i = 2; i<=m; i++)
	{
		if(idx*m+i>int(data.size()-1)) break;
		if(c(data[idx*m+i], maxChild))
		{
			maxChild = data[idx*m+i];
			max_idx=idx*m+i;
		}
	}
	if(c(maxChild, data[idx])) 
	{
		data[max_idx] = data[idx];
		data[idx] = maxChild;
		tr_down(max_idx);
	}
	


}








// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
		throw std::underflow_error("Empty Heap");
  }
	data[0] = data[data.size()-1];
	data.pop_back();
	tr_down(0);



}



#endif

