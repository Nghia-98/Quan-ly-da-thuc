#include "DonThuc.h"


CDonThuc::CDonThuc() // gồm hệ số và danh sách các biến (List)
{
	heSo = 1;
	// Khi gọi constructor của đơn thức thì constructor của linked_list tự đc gọi ( nên danh sách các biến ban đầu sẽ là List rỗng )
}

CDonThuc::CDonThuc(const CDonThuc &obj)
{
	this->heSo = obj.heSo;
	this->List = obj.List;
}

CDonThuc::~CDonThuc()
{
	
}

CDonThuc CDonThuc::operator*(const CDonThuc& d2)
{
	int size1 = this->List.getLength();
	int size2 = d2.List.getLength();
	CDonThuc temp;

	CBien *temp1 = new CBien[size1];
	CBien *temp2 = new CBien[size2];
	CBien cb;
	for (int i = 0; i < size1; i++)
	{
		this->List.retrieve(i, cb);				//lưu this->List vào mảng temp1
		temp1[i] = cb;
	}
	for (int i = 0; i < size2; i++)
	{
		d2.List.retrieve(i, cb);					//lưu d2.List vào mảng temp2
		temp2[i] = cb;
	}
	temp.Set_heSO(this->Get_heSo()*d2.Get_heSo());		//Lưu hệ số của biến temp = tích 2 hệ số của 2 đơn thức ban đầu

	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j<size2; j++)
		if (temp1[i].Get_tenbien() == temp2[j].Get_tenbien())
		{
			CBien a;
			a.set_Bien(temp1[i].Get_tenbien(), temp1[i].Get_soMu() + temp2[j].Get_soMu());
			temp.List.insert(temp.List.getLength(), a);
		}
		else
		{
			temp.List.insert(temp.List.getLength(), temp1[i]);
			temp.List.insert(temp.List.getLength(), temp2[i]);
		}
	}
	return temp;
}

