
#pragma once

template <class T>
class CLinked_List
{
protected:
	struct ListNode{
		T data; // dữ liệu chứa trong 1 node
		ListNode *next; // con trỏ next dùng để lưu địa chỉ của node tiếp theo
	};
	int size; // số lượng node hiện có trong list
	ListNode *head; // con trỏ head lưu lại node đầu tiên trong danh sách ( Node thứ nhất có số thứ tự là 0)

	ListNode* GetNode(T newItem) { // phuong thuc tao 1 node moi
		ListNode* p = new ListNode();
		if (p == nullptr) {
			return nullptr;
		}
		else {
			p->data = newItem;
			p->next = nullptr;
			return p;
		}
	}
public:
	CLinked_List(); // defaut constructor
	CLinked_List(const CLinked_List &); // copy constructor
	~CLinked_List(); // destructor

	/* Các phương  thức hoạt động của Linked List */
	bool isEmpty();
	int getLength()const;
	bool insert(int index, T newItem); // index = 0 là thêm vào đầu, index = size là thêm vào cuối, 0 < index < size chèn vào giữa danh sách
	bool remove(int index);
	int findNode(T key);               // Trả về số thự tự của Node hoặc trả về -1 nếu ko tìm thấy
	bool retrieve(int index, T &itemData)const; // lấy data của node có số thứ tự index đưa vào biến itemData
	CLinked_List& operator = (const CLinked_List&);
	CLinked_List operator + (const CLinked_List &);
	bool operator == (const CLinked_List&);
	bool operator < (const CLinked_List &);
	bool operator > (const CLinked_List &);
	void Xuat();
	void sapXep();
};

/* ===============Cài đặt các phương thức===============*/

template <class T> CLinked_List<T>::CLinked_List()  // constructor default
{
	size = 0;
	head = NULL;
}

template <class T> CLinked_List<T>::CLinked_List(const CLinked_List &obj) // copy constructor
{
	size = 0;
	ListNode *p = new ListNode();
	p = obj.head;
	while (p != NULL)
	{
		insert(size, p->data); // thêm vào cuối danh sách
		p = p->next;
	}
}

template <class T> CLinked_List<T>::~CLinked_List()
{
	while (isEmpty() == false) remove(0); // xóa node ở vị trí đầu tiên cho đến khi danh sách trống
}

template <class T> bool CLinked_List<T>::isEmpty()
{
	return (size == 0);
}

template <class T> int  CLinked_List<T>::getLength()const
{
	return size;
}

template <class T> bool CLinked_List<T>::insert(int index, T newItem) // sau khi chèn thì a[index] có data = newItem
{
	if (index < 0 || index > size) return false;

	ListNode* tmp = GetNode(newItem); // Tạo node có data = newItem
	if (index == 0){        // thêm vào đầu
		tmp->next = head;
		head = tmp;
	}
	else{
		ListNode* p = new ListNode();    //  con trỏ p dùng để duyệt tìm node tại ví trí có số thứ tự "index"
		ListNode *pPre = new ListNode(); //  con trỏ pPre dùng để lưu lại node đứng liền trước node p 

		p = head->next; // duyệt từ node thứ 2 ( node tại vị trí có số thứ tự là 1)
		pPre = head;    // pPre đứng liền trước p 

		int i = 1;      // duyệt từ vị trí có số thứ tự bằng 1
		while (i != index) // tìm ra node tại vị trí có số thứ tự "index" cần chèn và node đứng trước nó
		{
			p = p->next;
			pPre = pPre->next;
			i++;
		}

		if (index == size){   // thêm vào cuối
			pPre->next = tmp;
		}
		else{                 // chèn vào giữa danh sách
			pPre->next = tmp;
			tmp->next = p;
		}
	}
	size++;
	return true;
}

template <class T> bool CLinked_List<T>::remove(int index)
{
	if (index < 0 || index > size - 1) return false;

	ListNode* p = new ListNode();    //  con trỏ dùng để duyệt tìm node cần xóa
	ListNode* pPre = new ListNode(); //  con trỏ dùng để lưu lại node đứng liền trước node p ( node cần xóa )

	if (index == 0){             // nếu node cần xóa nằm ở vị trí đầu tiên (node thứ nhất được đánh số thứ tự là 0)
		//if (size == 1){ // nếu danh sách chỉ có 1 node
		//	delete head;
		//	head = NULL;
		//}
		//else{
			p = head;
			head = head->next;      // cập nhật lại node đầu danh sách
			p->next = NULL;
			delete p;
			p = NULL;
		//}
	}
	else{ // nếu node cần xóa ko nằm ở đầu danh sách
		p = head->next;
		pPre = head;
		int i = 1;      // duyệt từ node thứ 2 ( node có số thứ tự là 1 )
		while (i != index){ // vòng lặp giúp tìm ra node cần xóa và node đứng liền trước node cần xóa
			pPre = p;
			p = p->next;
			i++;
		}
			pPre->next = p->next;
			p->next=NULL;
			delete p;
			p = NULL;
	}
	size--;
	return true;
}

template <class T> int CLinked_List<T>::findNode(T key)
{
	ListNode* p = new ListNode();
	p = head;
	int i = 0;
	for (i ; i < size; i++)
	{
		if (p->data = key) return i;
		p = p->next;
	}
	return -1;
}

template <class T> bool CLinked_List<T>::retrieve(int index, T &itemData)const
{
	if (index < 0 || index > size - 1) return false;

	ListNode *p = new ListNode();
	p = head; int i = 0;
	while (i != index)
	{
		p = p->next;
		i++;
	}
	itemData = p->data;
	return true;
}

template<class T> CLinked_List<T>& CLinked_List<T>::operator = (const CLinked_List& obj)
{
	while (isEmpty() == false) this->remove(0); // Xóa hết các node có trong danh sách ban đầu

	ListNode *p = new ListNode();
	p = obj.head;
	while (p)
	{
		insert(size, p->data); // thêm vào cuối danh sách 
		p = p->next;
	}
	return *this;
}

template<class T> bool CLinked_List<T>::operator == (const CLinked_List& obj) // 2 danh sách đã được sắp xếp
{
	if (this->size != obj.size) return false;
	else{
			ListNode *p = this->head;
			ListNode *q = obj.head;
			for (int i = 0; i < this->size; i++)
			{
				if (p->data != q->data) return false;
				else{
					p = p->next;
					q = q->next;
				}
			}
			return true;
	}
}

template<class T> bool CLinked_List<T>::operator < (const CLinked_List &obj) 
{
	ListNode*p = head;
	ListNode*q = obj.head;
	if (*this == obj) return false; 
	while (p && q) // duyệt đến khi p = null hoặc q = null (duyệt hết ds this hoặc hết ds obj)
	{
		if ((p->data > q->data)) return false;
		else
		{
			p = p->next;
			q = q->next;
		}
	}
	return true;
	
}

template<class T> bool CLinked_List<T>:: operator > (const CLinked_List &obj)
{
	return(!(*this == obj) && !(*this < obj));
}

template <class T> void CLinked_List<T>::Xuat()
{
	ListNode *p = head;
	while (p != NULL)
	{
		cout << p->data<<" ";
		p = p->next;
	}
}

template<class T> void CLinked_List<T>::sapXep() // sắp sếp danh sách chứa kiểu dữ liệu T
{
	int n = size;
	ListNode *p = head; // duyệt p từ đầu danh sach
	for (int i = 0; i < n-1; i++)
	{
		ListNode *q = p->next; // duyệt q từ node liền sau node p
		for (int j = i + 1; j < n;j++)
		{
			if (p->data <= q->data)
			{
				T tmp = p->data;
				p->data = q->data;
				q->data = tmp;
			}
			q = q->next;
		}
		p = p->next;
	}
}

template <class T> CLinked_List<T> CLinked_List<T>::operator + (const CLinked_List &obj)
{
	CLinked_List<T> a; 
	T tmp;
	for (int i = 0; i < this->size; i++) // đưa từng node của danh sách this vào cuối danh sách a;
	{
		this->retrieve(i, tmp);
		a.insert(a.size, tmp); // đưa vào cuối ds a, ban đầu constructor sẽ khởi tạo size của a = 0, mỗi lần insert size sẽ tự tăng thêm 1
	}
	for (int i = 0; i < obj.size; i++) // đưa từng node của danh sách obj vào cuối danh sách temp
	{
		obj.retrieve(i, tmp);
		a.insert(a.size, tmp); // thêm vào cuối
	}
	return a;
}

