#pragma once

template <class var>
struct elem
{
	var data;
	elem<var>*prev,*next;
};

template <class var>
class list
{
	protected:

	elem<var>*head,*tail;
	int count;

	public:

	list();
	list(const list<var>&obj);
	virtual ~list();
	virtual void add_tail(var data);
	virtual void dell_head();
	virtual void clear();
	virtual void add_head(var data);
	virtual void dell_tail();
	virtual void insert(var data,int ind);
	virtual void deleting(int ind);
	virtual int get_count() const;
	virtual elem<var>* get_head() const;
	virtual elem<var>* get_tail() const;
	virtual elem<var>* get_element(int ind);
	virtual var* operator[] (int ind);
	virtual list<var>& operator= (const list<var>&obj);
};
template <class var>
class listptr:public list<var>
{
	public:
		listptr(){}
		void dell_head();
		void dell_tail();
		void deleting(int ind);
};
template <class var>

void listptr<var>::dell_head()
{
	if (!head)
		return;
	elem<var>*temp=head;
	head=head->next;
	if (head)
		head->prev=NULL;
	else
		tail=NULL;

	delete temp->data;
	delete temp; 
	count--;
}
template <class var>
void listptr<var>::dell_tail()
{
	if (!tail)
		return;
	elem<var>*temp=tail;
	tail=tail->prev;
	if (tail)
		tail->next=NULL;
	else
		head=NULL;

	delete temp->data;
	delete temp; 
	count--;
}
template <class var>
void listptr<var>::deleting(int ind)
{
	if (!ind||head==tail)
	{
		dell_head();
		return;
	}
	if (ind==count-1)
	{
		dell_tail();
		return;
	}
	elem<var>*temp=get_element(ind);
    if (!temp)
        return;

	temp->prev->next=temp->next;
	temp->next->prev=temp->prev;
	
	delete temp->data;
	delete temp;
	count--;
}
//************************************************
template <class var>
list<var>::list(const list<var>&obj)
{
	head=tail=NULL;
	count=0;
	elem<var>*temp=obj.head;
	while(temp)
	{
		add_tail(temp->data);
		temp=temp->next;
	}
}

template <class var>
list<var>& list<var>::operator= (const list<var>&obj)
{
    if (this==&obj)
        return *this;
    (*this).clear();
	elem<var>*temp=obj.head;
	while(temp)
	{
		add_tail(temp->data);
		temp=temp->next;
	}
	return *this;
}

template <class var>
list<var>::list()
{
	head=tail=NULL;
	count=0;
}

template <class var>
list<var>::~list()
{
	clear();
}

template <class var>
void list<var>::add_tail(var data)
{
	elem<var>*temp=new elem<var>;
	temp->data=data;
	temp->next=NULL;
	temp->prev=tail;
	if (!head)
		head=temp;
	else
		tail->next=temp;
	tail=temp;
	count++;
}

template <class var>
void list<var>::add_head(var data)
{
	elem<var>*temp=new elem<var>;
	temp->data=data;
	temp->next=head;
	temp->prev=NULL;
	if (!head)
		tail=temp;
	else
		head->prev=temp;
	head=temp;
	count++;
}

template <class var>
void list<var>::deleting(int ind)
{
	if (!ind||head==tail)
	{
		dell_head();
		return;
	}
	if (ind==count-1)
	{
		dell_tail();
		return;
	}
	elem<var>*temp=get_element(ind);
    if (!temp)
        return;

	temp->prev->next=temp->next;
	temp->next->prev=temp->prev;


    //weapon2*temp=(*this)[ind]; // this->operator[](ind);
	/*elem<var>*ptr=temp->prev;
	ptr->next=temp->next;
	ptr=temp->next;
	ptr->prev=temp->prev;*/

	delete temp;
	count--;
}

template <class var>
void list<var>::insert(var data,int ind)
{
	if (ind<=0)
	{
		add_head(data);
		return;
	}
	if (ind>=count)
	{
		add_tail(data);
		return;
	}
	elem<var>*temp=new elem<var>;
	temp->data=data;

	elem<var>*ptr=head;
	for (int i=0; i<ind-1; i++)
		ptr=ptr->next;

	/*temp->prev=ptr;
	ptr=ptr->next;
	temp->next=ptr;
	ptr->prev=temp;*/

	temp->next=ptr->next;
	temp->prev=ptr;
	ptr->next=temp;
	temp->next->prev=temp;

	count++;
}

template <class var>
void list<var>::dell_head()
{
	if (!head)
		return;
	elem<var>*temp=head;
	head=head->next;
	if (head)
		head->prev=NULL;
	else
		tail=NULL;
	delete temp; // delete temp->data;
	count--;
}

template <class var>
void list<var>::dell_tail()
{
	if (!tail)
		return;
	elem<var>*temp=tail;
	tail=tail->prev;
	if (tail)
		tail->next=NULL;
	else
		head=NULL;
	delete temp; // delete temp->data;
	count--;
}

template <class var>
void list<var>::clear()
{
	while(head)
		dell_head();
}

template <class var>
int list<var>::get_count() const
{
	return count;
}

template <class var>
elem<var>*list<var>::get_element(int ind)
{
    if (ind < 0|| ind >= count)
		return NULL;

    elem<var>*temp=head;
    if (ind<count/2)
		for (int i(0);i<ind;i++)
			temp=temp->next;
	else
	{
		temp=tail;
		for (int i=count-1;i>ind;i--)
			temp=temp->prev;
	}
	return temp;
}

template <class var>
var* list<var>::operator[] (int ind)
{
	elem<var>*temp=get_element(ind);
    if (!temp)
        return NULL;

	return &temp->data;
}

template <class var>
elem<var>* list<var>::get_head() const
{
	return head;
}

template <class var>
elem<var>* list<var>::get_tail() const
{
	return tail;
}

