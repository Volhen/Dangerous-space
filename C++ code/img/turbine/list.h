template <class var>
struct elem
{
	var data;
	elem<var>*prev,*next;
};

template <class var>
class list
{
	elem<var>*head,*tail;
	int count;
public:
	list();
	list(const list<var>&obj);
	~list();
	void add_tail(var data);
	void dell_head();
	void clear();
	void add_head(var data);
	void dell_tail();
	void insert(var data,int ind);
	void deleting(int ind);
	int get_count() const;
	elem<var>* get_head() const;
	elem<var>* get_tail() const;
	elem<var>* get_element(int ind);
	var* operator[] (int ind);
	list<var>& operator= (const list<var>&obj);
};

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
	elem<var>*temp=get_element(ind);
    if (!temp)
        return;
    if (head==tail)
    {
        delete head;
        tail=head=NULL;
        return;
    }
	temp->prev->next=temp->next;
	temp->next->prev=temp->prev;
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