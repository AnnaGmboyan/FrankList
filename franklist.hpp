#ifndef FRANKLIST_HPP
#define FRANKLIST_HPP

template <typename T>
FrankList<T>::Node::Node(T val, Node* next, Node* prev, Node* asc, Node* desc) :
			val(val), 
			next(next),
			prev(prev),
			asc(asc), 
			desc(desc)
{ }

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
			return;
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
			return;
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
template <typename T>
const FrankList<T>& FrankList<T>::operator=(const FrankList<value_type>& rhv)
{
	if(this != &rhv)
	{
		clear();
		Node* tmp = rhv.head;
		while(tmp)
		{
				push_back(tmp -> val);
				tmp = tmp -> next;
		}
	}
}
template <typename T>
const FrankList<T>& FrankList<T>::operator=(FrankList<value_type>&& rhv)
{
	if(this != &rhv)
	{
			clear();
			head = rhv.head;
			tail = rhv.tail;
			ahead = rhv.atail;
			atail = rhv.atail;
	}
		
}
template <typename T>
const FrankList<T>& FrankList<T>::operator=(std::initializer_list<value_type> init)
{
		clear();
		for(auto it = init.begin(); it != init.end(); ++it)
		{
				push_back(*it);
		}
}
template <typename T>
bool FrankList<T>::operator==(const FrankList<value_type>& rhv) const
{
	if (size() != rhv.size()) {
        return false;
    }
    Node* n1 = head;
    Node* n2 = rhv.head;
    for (n1, n2; n1; n1 = n1 -> next, n2 = n2 -> next) {
        if (n1 -> val != n2 -> val) {
            return false;
        }
    }
    return true;
}
template <typename T>
bool FrankList<T>::operator!=(const FrankList<value_type>& rhv) const
{
		return !(operator==(rhv));
}
template <typename T>
bool FrankList<T>::operator<(const FrankList<value_type>& rhv) const
{
		//
}
template <typename T>
bool FrankList<T>::operator>(const FrankList<value_type>& rhv) const
{
		//
}
template <typename T>
bool FrankList<T>::operator<=(const FrankList<value_type>& rhv) const
{
		return !(operator>(rhv));
}
template <typename T>
bool FrankList<T>::operator>=(const FrankList<value_type>& rhv) const
{
		return !(operator<(rhv));
}
//////////////////////////////////////////////////////////////////////////////////////// Base_iterator ////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
FrankList<T>::base_iterator::base_iterator(Node* ptr)
{
		this -> ptr = ptr;
}
template <typename T>
FrankList<T>::base_iterator::~base_iterator()
{
		this -> ptr = nullptr;
}
template <typename T>
bool FrankList<T>::base_iterator::operator==(const base_iterator& rhv) const
{
		return (this -> ptr == rhv -> ptr);
}
template <typename T>
bool FrankList<T>::base_iterator::operator!=(const base_iterator& rhv) const
{
		return !(operator==(rhv)); //ardyoq kkanchi franklist == te ir
}

/*

  class base_iterator
    {
        friend FrankList<value_type>;
    public:
        ~base_iterator();
        bool operator==(const base_iterator& rhv) const; //O(1)
        bool operator!=(const base_iterator& rhv) const; //O(1)
    protected:
        explicit base_iterator(Node* ptr); //O(1)
    protected:
        Node* ptr = nullptr;
    }
*/
///////////////////////////////////////////////////////////////////////////////////// const_itertor /////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
FrankList<T>::const_iterator::const_iterator(Node* ptr)
{
		this -> ptr = ptr;
}

template <typename T>
FrankList<T>::const_iterator::const_iterator(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;		
}
template <typename T>
FrankList<T>::const_iterator::const_iterator(base_iterator&& rhv)
{
	if (this -> ptr != rhv.ptr) 
	{
		this -> ptr = rhv.ptr;	
		rhv.ptr = nullptr;
	}
}

template <typename T>
const typename FrankList<T>::const_iterator& FrankList<T>::const_iterator::operator=(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
		return *this;
}
template <typename T>
const typename FrankList<T>::const_iterator& FrankList<T>::const_iterator::operator=(base_iterator&& rhv)
{
		if(this -> ptr != rhv.ptr)
		{
				this -> ptr = rhv.ptr;
				rhv.ptr = nullptr;
		}
		return *this;
}
template <typename T>
typename FrankList<T>::const_reference FrankList<T>::const_iterator::operator*() const
{
		return this -> ptr -> val;		
}
template <typename T>
typename FrankList<T>::const_pointer FrankList<T>::const_iterator::operator->() const
{
		return &(this -> ptr -> val);
}
template <typename T>
const typename FrankList<T>::const_iterator& FrankList<T>::const_iterator::operator++()
{
		this -> ptr = this -> ptr -> next;
		return *this;
}
template <typename T>
const typename FrankList<T>::const_iterator FrankList<T>::const_iterator::operator++(int)
{
		const_iterator it(this -> ptr);
		this -> ptr = this -> ptr -> next;
		return it;
}
template <typename T>
const typename FrankList<T>::const_iterator& FrankList<T>::const_iterator::operator--()
{
		this -> ptr = this -> ptr -> prev;
		return *this;
}
template <typename T>
const typename FrankList<T>::const_iterator FrankList<T>::const_iterator::operator--(int)
{
		const_iterator it(this -> ptr);
		this -> ptr = this -> ptr -> prev;;
		return it;
}
/*
public:
    class const_iterator : public base_iterator
    {
        friend FrankList<value_type>;
    public:
        const_iterator(const base_iterator& rhv); //O(1)
        const_iterator(base_iterator&& rhv); //O(1)
        
        const const_iterator& operator=(const base_iterator& rhv); //O(1)
        const const_iterator& operator=(base_iterator&& rhv); //O(1)
        const_reference operator*() const; //O(1)
        const_pointer operator->() const; //O(1)

        const const_iterator& operator++(); //O(1)
        const const_iterator operator++(value_type); //O(1)
        const const_iterator& operator--(); //O(1)
        const const_iterator operator--(value_type); //O(1)

    protected:
        explicit const_iterator(Node* ptr); //O(1)
    };
*/

//////////////////////////////////////////////////////////////////////////////////////////  iterator //////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
FrankList<T>::iterator::iterator(Node* ptr) : const_iterator(ptr)
{
		this -> ptr = ptr;
}
template <typename T>
FrankList<T>::iterator::iterator(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
}

template <typename T>
FrankList<T>::iterator::iterator(base_iterator&& rhv)
{
	if(this -> ptr != rhv.ptr)
	{
		this -> ptr = rhv.ptr;
		rhv.ptr = nullptr;
	}
}
template <typename T>
typename FrankList<T>::reference FrankList<T>::iterator::operator*()
{
		return (this -> ptr -> val);
}
template <typename T>
typename FrankList<T>::pointer FrankList<T>::iterator::operator->()
{
		return &(this -> ptr -> val);
}
template <typename T>
const typename FrankList<T>::iterator& FrankList<T>::iterator::operator=(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
		return *this;
}
template <typename T>
const typename FrankList<T>::iterator& FrankList<T>::iterator::operator=(FrankList<T>::base_iteartor&& rhv)
{
	if(this -> ptr != rhv.ptr)
	{
			this -> ptr = rhv.ptr;
			rhv.ptr = nullptr;
	}
	return *this;
}
/*
   public:
    class iterator : public const_iterator
    {
        friend FrankList<value_type>;
    public:
        iterator(const base_iterator& rhv); //O(1)
        iterator(base_iterator&& rhv); //O(1)

        reference operator*(); //O(1)
        pointer operator->(); //O(1)

        const iterator& operator=(const base_iterator& rhv); //O(1)
        const iterator& operator=(base_iterator&& rhv); //O(1)
    protected:
        explicit iterator(Node* ptr); //O(1)
    };
*/
//////////////////////////////////////////////////////////////////////// const_reverse_iterator ////////////////////////////////////////////////////////////////////////////////

template <typename T>
FrankList<T>::const_reference_iterator::const_reference_iterator(Node* ptr) : base_iterator(ptr)
{
		this -> ptr = ptr;
}
template <typename T>
FrankList<T>::const_reference_iterator::const_reference_iterator(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
}
template <typename T>
FrankList<T>::const_reference_iterator::const_reference_iterator(base_iterator&& rhv)
{
		this -> ptr = rhv.ptr;
		rhv.ptr = nullptr;
}
template <typename T>
const typename FrankList<T>::const_reverse_iterator& FrankList<T>::const_reverese_iterator::operator=(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
		return *this;
}
template <typename T>
const typename FrankList<T>::const_reverse_iterator& FrankList<T>::const_reverese_iterator::operator=(base_iterator&& rhv)
{
	if(this -> ptr != rhv.ptr)
	{			
		this -> ptr = rhv.ptr;
		rhv.ptr = nullptr;
	}
		return *this;
}

template <typename T>
const typename FrankList<T>::const_reference FrankList<T>::const_reverse_iterator::operator*() const
{
	return this -> ptr -> val;		
}

template <typename T>
const typename FrankList<T>::const_pointer FrankList<T>::const_reverse_iterator::operator->() const
{
	return &(this -> ptr -> val);		
}
template <typename T>
const typename FrankList<T>::const_reverse_iterator& FrankList<T>::const_reverse_iterator::operator++()
{
	this -> ptr = this -> ptr -> prev;
	return *this;
}
template <typename T>
const typename FrankList<T>::const_reverse_iterator FrankList<T>::const_reverse_iterator::operator++(int)
{
	const_reverse_iterator tmp(this -> ptr);
	this -> ptr = this -> ptr -> prev;
	return tmp;
}
template <typename T>
const typename FrankList<T>::const_reverse_iterator& FrankList<T>::const_reverse_iterator::operator--()
{
	this -> ptr = this -> ptr -> next;
	return *this;
}
template <typename T>
const typename FrankList<T>::const_reverse_iterator FrankList<T>::const_reverse_iterator::operator--(int)
{
	const_reverse_iterator tmp(this -> ptr);
	this -> ptr = this -> ptr -> next;
	return tmp;
}
/*
public:
    class const_reverse_iterator : public base_iterator
    {
        friend FrankList<value_type>;
    public:
        const_reverse_iterator(const base_iterator& rhv); //O(1)
        const_reverse_iterator(base_iterator&& rhv); //O(1)

        const const_reverse_iterator& operator=(const base_iterator& rhv); //O(1)
        const const_reverse_iterator& operator=(base_iterator&& rhv); //O(1)
        const_reference operator*() const; //O(1)
        const_pointer operator->() const; //O(1)

        const const_reverse_iterator& operator++(); //O(1)
        const const_reverse_iterator operator++(value_type); //O(1)
        const const_reverse_iterator& operator--(); //O(1)
        const const_reverse_iterator operator--(value_type); //O(1)

    protected:
        explicit const_reverse_iterator(Node* ptr); //O(1)
    };
  */ 
/////////////////////////////////////////////////////////////// reverse_iterator  ////////////////////////////////////////////////////////////////////////////////
template <typename T>
FrankList<T>::reverse_iterator::reverse_iterator(Node* ptr) : const_reverse_iterator(ptr)
{
		this -> ptr = ptr;
}
template <typename T>
FrankList<T>::reverse_iterator::reverse_iterator(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
}

template <typename T>
FrankList<T>::reverse_iterator::reverse_iterator(base_iterator&& rhv)
{
	if(this -> ptr != rhv.ptr)
	{
		this -> ptr = rhv.ptr;
		rhv.ptr = nullptr;
	}
}
template <typename T>
typename FrankList<T>::reference FrankList<T>::reverse_iterator::operator*()
{
		return	this -> ptr -> val;
}
template <typename T>
typename FrankList<T>::pointer FrankList<T>::reverese_iterator::operator->()
{
		return &(this -> ptr -> val);
}
template <typename T>
const typename FrankList<T>::reverse_iterator& FrankList<T>::reverse_iterator::operator=(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
		return *this;
}
template <typename T>
const typename FrankList<T>::reverse_iterator& FrankList<T>::reverse_iterator::operator=(base_iteartor&& rhv)
{
	if(this -> ptr != rhv.ptr)
	{
			this -> ptr = rhv.ptr;
			rhv.ptr = nullptr;
	}
	return *this;
}
/*
    class reverse_iterator : public const_reverse_iterator
    {
        friend FrankList<value_type>;
    public:
        reverse_iterator(const base_iterator& rhv); //O(1)
        reverse_iterator(base_iterator&& rhv); //O(1)

        reference operator*(); //O(1)
        pointer operator->(); //O(1)

        const reverse_iterator& operator=(const base_iterator& rhv); //O(1)
        const reverse_iterator& operator=(base_iterator&& rhv); //O(1)

    protected:
        explicit reverse_iterator(Node* ptr); //O(1)
    };
*/
///////////////////////////////////////////////////////////////////////// const_asc_iterator /////////////////////////////////////////////////////////////
template <typename T>
FrankList<T>::const_asc_iterator::const_asc_iterator(Node* ptr) : base_iterator(ptr)
{
		this -> ptr = ptr;
}
template <typename T>
FrankList<T>::const_asc_iterator::const_asc_iterator(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
}
template <typename T>
FrankList<T>::const_asc_iterator::const_asc_iterator(base_iterator&& rhv)
{
		this -> ptr = rhv.ptr;
		rhv.ptr = nullptr;
}
template <typename T>
const typename FrankList<T>::const_asc_iterator& FrankList<T>::const_asc_iterator::operator=(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
		return *this;
}
template <typename T>
const typename FrankList<T>::const_asc_iterator& FrankList<T>::const_asc_iterator::operator=(base_iterator&& rhv)
{
	if(this -> ptr != rhv.ptr)
	{			
		this -> ptr = rhv.ptr;
		rhv.ptr = nullptr;
	}
		return *this;
}

template <typename T>
const typename FrankList<T>::const_reference FrankList<T>::const_asc_iterator::operator*() const
{
	return this -> ptr -> val;		
}

template <typename T>
const typename FrankList<T>::const_pointer FrankList<T>::const_asc_iterator::operator->() const
{
	return &(this -> ptr -> val);		
}
template <typename T>
const typename FrankList<T>::const_asc_iterator& FrankList<T>::const_asc_iterator::operator++()
{
	this -> ptr = this -> ptr -> asc;
	return *this;
}
template <typename T>
const typename FrankList<T>::const_asc_iterator FrankList<T>::const_asc_iterator::operator++(int)
{
	const_asc_iterator tmp(this -> ptr);
	this -> ptr = this -> ptr -> asc;
	return tmp;
}
template <typename T>
const typename FrankList<T>::const_asc_iterator& FrankList<T>::const_asc_iterator::operator--()
{
	this -> ptr = this -> ptr -> desc;
	return *this;
}
template <typename T>
const typename FrankList<T>::const_asc_iterator FrankList<T>::const_asc_iterator::operator--(int)
{
	const_asc_iterator tmp(this -> ptr);
	this -> ptr = this -> ptr -> desc;
	return tmp;
}
/*
public:
    class const_asc_iterator :public base_iterator
    {
        friend FrankList<value_type>;
    public:
        const_asc_iterator(const base_iterator& rhv); //O(1)
        const_asc_iterator(base_iterator&& rhv); //O(1)

        const const_asc_iterator& operator=(const base_iterator& rhv); //O(1)
        const const_asc_iterator& operator=(base_iterator&& rhv); //O(1)
        const_reference operator*() const; //O(1)
        const_pointer operator->() const; //O(1)

        const const_asc_iterator& operator++(); //O(1)
        const const_asc_iterator operator++(value_type); //O(1)
        const const_asc_iterator& operator--(); //O(1)
        const const_asc_iterator operator--(value_type); //O(1)

    protected:
        explicit const_asc_iterator(Node* ptr); //O(1)
    };
*/
////////////////////////////////////////////////////////////////////////// asc_iterator ////////////////////////////////////////////////////////////////////////////////	
template <typename T>
FrankList<T>::asc_iterator::asc_iterator(Node* ptr) : const_asc_iterator(ptr)
{
		this -> ptr = ptr;
}
template <typename T>
FrankList<T>::asc_iterator::asc_iterator(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
}

template <typename T>
FrankList<T>::asc_iterator::asc_iterator(base_iterator&& rhv)
{
	if(this -> ptr != rhv.ptr)
	{
		this -> ptr = rhv.ptr;
		rhv.ptr = nullptr;
	}
}
template <typename T>
typename FrankList<T>::reference FrankList<T>::reverse_iterator::operator*()
{
		return	this -> ptr -> val;
}
template <typename T>
typename FrankList<T>::pointer FrankList<T>::reverese_iterator::operator->()
{
		return &(this -> ptr -> val);
}
template <typename T>
const typename FrankList<T>::reverse_iterator& FrankList<T>::reverse_iterator::operator=(const base_iterator& rhv)
{
		this -> ptr = rhv.ptr;
		return *this;
}
template <typename T>
const typename FrankList<T>::reverse_iterator& FrankList<T>::reverse_iterator::operator=(base_iteartor&& rhv)
{
	if(this -> ptr != rhv.ptr)
	{
			this -> ptr = rhv.ptr;
			rhv.ptr = nullptr;
	}
	return *this;
	/*
public:
    class asc_iterator : public const_asc_iterator
    {
        friend FrankList<value_type>;
    public:
        asc_iterator(const base_iterator& rhv); //O(1)
        asc_iterator(base_iterator&& rhv); //O(1)

        reference operator*(); //O(1)
        pointer operator->(); //O(1)

        const asc_iterator& operator=(const base_iterator& rhv); //O(1)
        const asc_iterator& operator=(base_iterator&& rhv); //O(1)

    protected:
        explicit asc_iterator(Node* ptr); //O(1)
    };
public:
    class const_desc_iterator : public base_iterator
    {
        friend FrankList<value_type>;
    public:
        const_desc_iterator(const base_iterator& rhv); //O(1)
        const_desc_iterator(base_iterator&& rhv); //O(1)

        const const_desc_iterator& operator=(const base_iterator& rhv); //O(1)
        const const_desc_iterator& operator=(base_iterator&& rhv); //O(1)
        const_reference operator*() const; //O(1)
        const_pointer operator->() const; //O(1)

        const const_desc_iterator& operator++(); //O(1)
        const const_desc_iterator operator++(value_type); //O(1)
        const const_desc_iterator& operator--(); //O(1)
        const const_desc_iterator operator--(value_type); //O(1)

    protected:
        explicit const_desc_iterator(Node* ptr); //O(1)
    };
public:
    class desc_iterator : public const_desc_iterator
    {
        friend FrankList<value_type>;
    public:
        desc_iterator(const base_iterator& rhv); //O(1)
        desc_iterator(base_iterator&& rhv); //O(1)

        reference operator*(); //O(1)
        pointer operator->(); //O(1)

        const desc_iterator& operator=(const base_iterator& rhv); //O(1)
        const desc_iterator& operator=(base_iterator&& rhv); //O(1)

    protected:
        explicit desc_iterator(Node* ptr); //O(1)
    };
public:
    class const_multi_iterator : public base_iterator
    {
        friend FrankList<value_type>;
    public:
        const_multi_iterator(const base_iterator& rhv); //O(1)
        const_multi_iterator(base_iterator&& rhv); //O(1)

        const const_multi_iterator& operator=(const base_iterator& rhv); //O(1)
        const const_multi_iterator& operator=(base_iterator&& rhv); //O(1)
        const_reference operator*() const; //O(1)
        const_pointer operator->() const; //O(1)

        const const_multi_iterator& operator++(); //O(1)
        const const_multi_iterator operator++(value_type); //O(1)
        const const_multi_iterator& operator--(); //O(1)
        const const_multi_iterator operator--(value_type); //O(1)

        void chmod(); //O(1)
    protected:
        explicit const_multi_iterator(Node* ptr); //O(1)
        bool mode = true;
    };
public:
    class multi_iterator : public const_multi_iterator
    {
        friend FrankList<value_type>;
    public:
        multi_iterator(const base_iterator& rhv); //O(1)
        multi_iterator(base_iterator&& rhv); //O(1)

        reference operator*(); //O(1)
        pointer operator->(); //O(1)

        const multi_iterator& operator=(const base_iterator& rhv); //O(1)
        const multi_iterator& operator=(base_iterator&& rhv); //O(1)

    protected:
        explicit multi_iterator(Node* ptr); //O(1)
    };
public:
    class const_multi_reverse_iterator : public base_iterator
    {
        friend FrankList<value_type>;
    public:
        const_multi_reverse_iterator(const base_iterator& rhv); //O(1)
        const_multi_reverse_iterator(base_iterator&& rhv); //O(1)

        const const_multi_reverse_iterator& operator=(const base_iterator& rhv); //O(1)
        const const_multi_reverse_iterator& operator=(base_iterator&& rhv); //O(1)
        const_reference operator*() const; //O(1)
        const_pointer operator->() const; //O(1)

        const const_multi_reverse_iterator& operator++(); //O(1)
        const const_multi_reverse_iterator operator++(value_type); //O(1)
        const const_multi_reverse_iterator& operator--(); //O(1)
        const const_multi_reverse_iterator operator--(value_type); //O(1)


        void chmod(); //O(1)
    protected:
        explicit const_multi_reverse_iterator(Node* ptr); //O(1)
        bool mode = true;
    };
*/   
template <typename T>
void FrankList<T>::pprint()
{
		Node* tmp = head;
		while(tmp)
		{
				std::cout << tmp -> val  << " ";
				tmp = tmp -> next;
		}
}
template <typename T>
void FrankList<T>::print(bool sorted, bool reversed)
{

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
	/*		int counter = 0;
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
		Node* tmp = atail;
		while(tmp)
		{
			std::cout << tmp -> val << " ";
			tmp = tmp ->desc;
		}
	}
/*
 Node* tmp = nullptr;

    if (sorted && reversed) {
        tmp = atail;
        while (tmp)
        {
			std::cout << 4 << " ";
            std::cout << tmp->val << " ";
            tmp = tmp->desc;
        }
    } else if (sorted && !reversed) {
        tmp = ahead;
        while (tmp)
        {
			std::cout << 3 << " ";
            std::cout << tmp->val << " ";
            tmp = tmp->asc;
        }
    } else if (!sorted && reversed) {
        tmp = tail;
        while (tmp)
        {
			std::cout << 2 << " ";
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
*/
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
		ptr -> asc = curr;
		ptr -> desc = curr -> desc;
		curr -> desc -> asc = ptr;
		curr -> desc = ptr;
	}
}

/*
//ctor
    template <typename input_iterator>
    FrankList(input_iterator f, input_iterator l); //O(n)
*/


#endif //FRANKLIST_HPP


