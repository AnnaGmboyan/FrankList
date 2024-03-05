#ifndef FRANKLIST_HPP
#define FRANKLIST_HPP

template <typename T>
FrankList<T>::Node::Node(T val, Node* next, Node* prev, Node* asc, Node* desc) :
			val(val), next(next), prev(prev), asc(asc), desc(desc) { }

template <typename T>
FrankList<T>::FrankList()
{
		head = nullptr;
		tail = nullptr;
		ahead = nullptr;
		atail = nullptr;
}
template <typename T>
FrankList<T>::~FrankList()
{
	clear();
}

template <typename T>
FrankList<T>::FrankList(size_type size) : FrankList() //
{
		for(std::size_t i = 0; i < size; ++i)
		{
				push_back(T());
		}
}
template <typename T>
FrankList<T>::FrankList(size_type size, const_reference init) : FrankList() //
{
		for(size_type i = 0; i < size; ++i)
		{
				push_back(init);
		}
}
template <typename T>
FrankList<T>::FrankList(const FrankList<value_type>& rhv) : FrankList() //
{
	Node* tmp = rhv.head;
	while(tmp)
	{
		push_back(tmp ->val);
		tmp = tmp -> next;
	}
}
template <typename T>
FrankList<T>::FrankList(FrankList<value_type>&& rhv) //chstugvac
{
		if(this != &rhv)
		{
				head = rhv.head;
				tail = rhv.tail;
				ahead = rhv.ahead;
				atail = rhv.atail;
				
				rhv.head = nullptr;
				rhv.tail= nullptr;
				rhv.ahead = nullptr;
				rhv.atail = nullptr;
		}
}
template <typename T>
FrankList<T>::FrankList(std::initializer_list<T> init) : FrankList() //
{
		for(auto it = init.begin(); it != init.end(); ++it)
		{
				push_back(*it);
		}
}

template <typename T>
typename FrankList<T>::size_type FrankList<T>::size() const //
{
	size_t count = 0;
	Node* ptr = head;
	while(ptr)
	{
			++count;
			ptr = ptr -> next;
	}
	return count;
		
}

template <typename T>
bool FrankList<T>::empty() const //
{
			return size() == 0;
}

template <typename T>
void FrankList<T>::resize(size_type s, const_reference init) //
{
	size_type current_size = size();
	if(current_size == s) {
			return;
	} else if (current_size < s) {
			while(current_size != s)
			{
					push_back(init);
					++current_size;
			}
	} else if (s == 0){
			clear();		
	}else {
			while(current_size != s)
			{
					pop_back();
					--current_size;
			}
	}	
}
template <typename T>
void FrankList<T>::pop_back()  //
{

	size_type size = this -> size();
	if(!size) {
			return;
	} else if(size == 1) {
			clear();
			return;
	}
	else {
			if(ahead == tail) {
				ahead = tail -> asc;	
			} else if(atail == tail) {
				 atail = tail -> desc; 
			}
			if(tail -> desc)
			{		
				tail -> desc -> asc = tail -> asc;		
			}	
			if(tail -> asc)
			{
				tail -> asc -> desc = tail -> desc;
			}
			tail = tail -> prev;
			delete tail -> next;
			tail-> next = nullptr;
	}
	
}
template <typename T>
void FrankList<T>::pop_front()
{
		if(!size()){
			return;	
		} else if (size() == 1) {
				clear();
		} else {
			if(ahead == head) {
				ahead = head -> asc;	
			} else if(atail == head) {
				 atail = head -> desc; 
			}

			if(head -> desc)
			{		
				head -> desc -> asc = head -> asc;		
			}	
			if(head -> asc)
			{
				head -> asc -> desc = head -> desc;
			}
			head = head -> next;
			delete head -> prev;
			head -> prev = nullptr;
				
		}
}

template <typename T>
void FrankList<T>::push_back(const_reference elem)
{
		Node* curr = new Node(elem);
		if(tail == nullptr)
		{
			head = curr;
			tail = head;
			atail = head;
			ahead = head;

		} else {

			tail -> next = curr;
			curr -> prev = tail;
			tail = curr;
		}
		put_in_sorted_order(tail);

}

template <typename T>
void FrankList<T>::push_front(const_reference elem)
{
		Node* curr = new Node(elem);
		if(head == nullptr)
		{
			head = curr;
			tail = head;
			atail = head;
			ahead = head;
		} else {
			curr -> next = head;
			head -> prev = curr;
			head = curr;
		}
		put_in_sorted_order(head);

}

template <typename T>
void FrankList<T>::clear() noexcept //
{
		while(head)
		{
				Node* tmp = head;
				head = head -> next;
				delete tmp;
		}
		head = nullptr;
		tail = nullptr;
		ahead = nullptr;
		atail = nullptr;
		
}
template <typename T>
void FrankList<T>::swap(FrankList<value_type>& rhv)
{
	std::swap(*this, rhv);
}
template <typename T>
typename FrankList<T>::const_reference FrankList<T>::front() const
{
	if(!head)
	{
        throw std::runtime_error("Invalid reference encountered");
	}
	return head -> val;

}

template <typename T>
typename FrankList<T>::reference FrankList<T>::front() 
{
	if(!head)
	{
        throw std::runtime_error("Invalid reference encountered");
	}
	return head -> val;

}
template <typename T>
typename FrankList<T>::const_reference FrankList<T>::back() const
{
	if(!tail)
	{
        throw std::runtime_error("Invalid reference encountered");
	}
	return tail -> val;

}
template <typename T>
typename FrankList<T>::reference FrankList<T>::back() 
{
	if(!tail)
	{
        throw std::runtime_error("Invalid reference encountered");
	}
	return tail -> val;

}
template <typename T>
typename FrankList<T>::const_reference FrankList<T>::min() const
{
	if(!ahead)
	{		
        throw std::runtime_error("Invalid reference encountered");
	}
	return ahead -> val;
}
template <typename T>
typename FrankList<T>::reference FrankList<T>::min() 
{
	if(!ahead)
	{		
        throw std::runtime_error("Invalid reference encountered");
	}
	return ahead -> val;
}
template <typename T>
typename FrankList<T>::const_reference FrankList<T>::max() const
{
	if(!atail)
	{		
        throw std::runtime_error("Invalid reference encountered");
	}
	return atail -> val;
}

template <typename T>
typename FrankList<T>::reference FrankList<T>::max()
{
	if(!atail)
	{		
        throw std::runtime_error("Invalid reference encountered");
	}
	return atail -> val;
}
/*
	const FrankList<value_type>& operator=(const FrankList<value_type>& rhv); //O(n)
    const FrankList<value_type>& operator=(FrankList<value_type>&& rhv); //O(n)
    const FrankList<value_type>& operator=(std::initializer_list<value_type> init); //O(n)

    bool operator==(const FrankList<value_type>& rhv) const; //O(n)
    bool operator!=(const FrankList<value_type>& rhv) const; //O(n)
    bool operator<(const FrankList<value_type>& rhv) const; //O(n)
    bool operator<=(const FrankList<value_type>& rhv) const; //O(n)
    bool operator>(const FrankList<value_type>& rhv) const; //O(n)
    bool operator>=(const FrankList<value_type>& rhv) const; //O(n)

*/

template <typename T>
void FrankList<T>::print(bool sorted, bool reversed)
{
/*
   Node* ptr = nullptr;
	if(!sorted && !reversed) {
		ptr = head;
		while(ptr)
		{
				std::cout << ptr -> val << " ";
				ptr = ptr -> next;
		}
	} else if(sorted && !reversed) {
			ptr = ahead;
			while(ptr)
			{
					std::cout << ptr-> val << " ";
					ptr = ptr -> asc;
			}
	} else if(!sorted && reversed) {
			ptr = tail;
			while(ptr)
			{
					std::cout << ptr-> val << " ";
					ptr = ptr -> prev;
			}
	} else { //sorted and reversed
			int counter = 0;
			ptr = atail;
				std::cout << ptr -> val << std::endl;
				ptr = ptr -> desc;
				std::cout << ptr -> val << std::endl;
				ptr = ptr -> desc;
				std::cout << ptr -> val << std::endl;
				ptr = ptr -> desc;
				std::cout << ptr -> val << std::endl;
				ptr = ptr -> desc;
				std::cout << ptr -> val << std::endl;
				ptr = ptr -> desc;
				std::cout << ptr -> val << std::endl;
			//	ptr = ptr -> desc;
			//	std::cout << ptr -> val << std::endl;
				ptr = ptr -> desc;
				std::cout <<  ptr << std::endl;
			}
		while(ptr -> desc)
			{
					if (ptr->desc != nullptr)
					{
						if (counter != 8)
						{
							std::cout << ptr -> val << std::endl;
							++counter;
						}else
						{ 
							exit(1);
						}
					}
					//std::cout << ptr-> val << " ";
					ptr = ptr -> desc;

			}
	}	
*/
 Node* tmp = nullptr;

    if (sorted && reversed) {
        tmp = atail;
        while (tmp)
        {
            std::cout << tmp->val << " ";
            tmp = tmp->desc;
        }
    } else if (sorted && !reversed) {
        tmp = ahead;
        while (tmp)
        {
            std::cout << tmp->val << " ";
            tmp = tmp->asc;
        }
    } else if (!sorted && reversed) {
        tmp = tail;
        while (tmp)
        {
            std::cout << tmp->val << " ";
            tmp = tmp->prev;
        }
    } else {
        tmp = head;
        while (tmp)
        {
			std::cout << 1 << " ";
            std::cout << tmp->val << " ";
            tmp = tmp->next;
        }
    }

    std::cout << std::endl;
}
template <typename T>
void FrankList<T>::put_in_sorted_order(Node* ptr) //
{
	//if the value is smaller than the smallest value in list
	if(ptr -> val <= ahead -> val)
	{
			ahead -> desc = ptr;
			ptr -> asc = ahead;
			ahead = ptr;

	 } //if the value is greater than the greatest value in list
	 else if (ptr -> val > atail -> val) {
			atail -> asc = ptr;
			ptr -> desc = atail;
			atail = ptr;
	} 
	else {
	 //if the value is in the range of smallesot and the greates elements
		Node* curr = ahead;
		while (curr -> val < ptr -> val) 
		{
			curr = curr -> asc;
		}
		curr -> desc -> asc = ptr;
		curr -> desc = ptr;
		ptr -> desc = curr -> desc;
		ptr -> asc = curr;
	}
}

/*
//ctor
    template <typename input_iterator>
    FrankList(input_iterator f, input_iterator l); //O(n)
*/


#endif //FRANKLIST_HPP


