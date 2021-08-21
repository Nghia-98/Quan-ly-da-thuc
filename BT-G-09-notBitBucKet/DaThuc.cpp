#include "DaThuc.h"


CDaThuc::CDaThuc()
{
	::CDonThuc();
	::CLinked_List<CDonThuc>();
	::CBien();
}

CDaThuc::CDaThuc(const CDaThuc&obj)
{
	daThuc = obj.daThuc;
}


CDaThuc::~CDaThuc()
{
}

CDaThuc CDaThuc::operator*(const CDaThuc& d2)
{
	CDaThuc temp;
	int size1 = this->daThuc.getLength();
	int size2 = d2.daThuc.getLength();
	CDonThuc obj;
	CDonThuc *temp1 = new CDonThuc[size1];
	CDonThuc *temp2 = new CDonThuc[size2];
	CDonThuc a;
	for (int i = 0; i < size1; i++)
	{
		this->daThuc.retrieve(i, a);				//lưu this->daThuc vào mảng temp1
		temp1[i] = a;
	}
	for (int i = 0; i < size2; i++)
	{
		d2.daThuc.retrieve(i, a);					//lưu d2.daThuc vào mảng temp2
		temp2[i] = a;
	}
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j<size2; j++)
		{
			obj = temp1[i] * temp2[j];
			temp.daThuc.insert(temp.daThuc.getLength(), obj);
		}
	}
	return temp;
}

CDaThuc CDaThuc:: operator+(const CDaThuc &d2)
{
	CDaThuc tmp;
	tmp.daThuc = this->daThuc + d2.daThuc;
	tmp.sapXepDaThuc();
	tmp.rutGonDaThuc();
	return tmp;
}

CDaThuc CDaThuc:: operator-(const CDaThuc &d2)	// - đa thức ban đầu với đa thức d2
{

	CDaThuc a;
	CDonThuc tmp;
	for (int i = 0; i < this->daThuc.getLength(); i++) // đưa từng node của danh sách this vào cuối danh sách a;
	{
		this->daThuc.retrieve(i, tmp);
		a.daThuc.insert(a.daThuc.getLength(), tmp); 
	}
	for (int i = 0; i < d2.daThuc.getLength(); i++) // đưa từng node của danh sách obj vào cuối danh sách temp
	{
		d2.daThuc.retrieve(i, tmp);
		tmp.Set_heSO(-tmp.Get_heSo()); // đổi dấu của từng đơn thức sau đó đưa vào ds a
		a.daThuc.insert(a.daThuc.getLength(), tmp); // thêm vào cuối
	}

	a.sapXepDaThuc();
	a.rutGonDaThuc();
	return a;
}
