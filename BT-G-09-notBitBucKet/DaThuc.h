#pragma once

#include"DonThuc.h"
class CDaThuc /*:public CLinked_List<CDonThuc>,public CBien,public CDonThuc*/{
	// Đa thức có dạng danh sách liên kết, mỗi node chứa thông tin 1 đơn thức
private:

	CLinked_List<CDonThuc> daThuc; // danh sách các đơn thức

public:
	CDaThuc();
	CDaThuc(const CDaThuc&);				// đọc đa thức từ file .txt
	~CDaThuc();
	CDaThuc operator+(const CDaThuc &d2);	// + đa thức ban đầu với đa thức d2
	CDaThuc operator-(const CDaThuc &d2);	// - đa thức ban đầu với đa thức d2
	CDaThuc operator*(const CDaThuc &d2);	// * đa thức ban đầu với đa thức d2
	CDaThuc& operator~();					// rút gọn đa thức
	CDaThuc& operator!();					// chuẩn hóa đa thức

	CDaThuc& operator = (const CDaThuc& d2)
	{
		this->daThuc = d2.daThuc; // toán tử gán = của đối tượng CLinked_List
	}

	void sapXepTungDonThuc()
	{
		int n = daThuc.getLength();
		CDonThuc* arr = new CDonThuc[n]; // arr dùng để lưu data của 1 mỗi node trong CDaThuc
		for (int i = 0; i < n; i++)	{ // lấy từng đơn thức trong đa thức ra rồi sắp xếp danh sách các biến của đơn thức đó
			daThuc.retrieve(i, arr[i]); // đưa 1 đơn thức vào mảng arr
			arr[i].sapXepDonThuc();     // sắp xếp đơn thức vừa lấy dc
		}
		while (!daThuc.isEmpty()) daThuc.remove(0); // xóa tất cả các đơn thức chưa đc sắp xếp trong đa thức
		for (int j = 0; j < n; j++) {
			daThuc.insert(daThuc.getLength(), arr[j]); // đưa các đơn thức đã đc sắp xếp vào lại đa thức
		}
		delete[] arr; 
	}

	void sapXepDaThuc()
	{
		sapXepTungDonThuc(); // sắp xếp trong từng đơn thức
		daThuc.sapXep();     // sắp xếp thứ tự các đơn thức trong đa thức ( phương thức sắp xếp data của các node trong đối tượng CLinked_List)
	}

	void rutGonTungDonThuc()
	{
		int n = daThuc.getLength();
		CDonThuc* arr = new CDonThuc[n]; // arr dùng để lưu data của 1 mỗi node trong CDaThuc
		for (int i = 0; i < n; i++)	{ // lấy từng đơn thức trong đa thức ra rồi rút gọn ds các biến trong đơn thức đó
			daThuc.retrieve(i, arr[i]); // đưa 1 đơn thức vào mảng arr
			arr[i].sapXepDonThuc();     // rút gọn đơn thức vừa lấy dc
		}
		while (!daThuc.isEmpty()) daThuc.remove(0); // xóa tất cả các đơn thức chưa đc rút gọn trong đa thức
		for (int j = 0; j < n; j++) {
			daThuc.insert(daThuc.getLength(), arr[j]); // đưa các đơn thức đã đc rút gọn vào lại đa thức
		}
		delete[] arr;
	}

	void rutGonDaThuc()
	{
		rutGonTungDonThuc();
		CDonThuc tmp1, tmp2;
		for (int i = 0; i < daThuc.getLength() ; i++)
		{
			daThuc.retrieve(i, tmp1); // lấy ra 1 đơn thức đưa vào tmp1
			if (tmp1.Get_heSo() == 0){ // nếu tmp1 có hệ số bằng 0 thì xóa tmp1 tại vị trí i, sau đó cập nhật lại vị trí duyệt tmp1
				daThuc.remove(i);
				i--;
			}
			else{ // nếu tmp1 có hệ số != 0 thì đem so sánh với các đơn thức ở sau nó
				for (int j = i + 1; j < daThuc.getLength(); j++)
				{
					daThuc.retrieve(j, tmp2); // lấy ra 1 đơn thức đưa vào tmp2
					if (tmp1.isEqual_dsBien(tmp2) == true) // nếu danh sách các biến của đơn thức tmp1 và tmp2 bằng nhau
					{
						float heso = tmp1.Get_heSo() + tmp2.Get_heSo(); // thì cộng hệ số của 2 đơn thức và gán cho đơn thức đứng trc
						tmp1.Set_heSO(heso); 
						daThuc.remove(j);
						daThuc.insert(i, tmp1); // chèn vào sau vị trí i; 
						daThuc.remove(i + 1);
						j--;
					}
				}
			}
		}
	}

	

	friend istream& operator >> (istream &f, CDaThuc &obj)
	{
		
		while (f.eof() == false){ // đọc cho đến cuối file
			CDonThuc donthuc;
			f >> donthuc; // đọc vào từng đơn thức
		    obj.daThuc.insert(obj.daThuc.getLength(), donthuc);
		}
		return f;
	}


	friend ostream& operator << (ostream& f, const CDaThuc &obj)
	{
		CDonThuc tmp;
		for (int i = 0; i < obj.daThuc.getLength(); i++)
		{
			obj.daThuc.retrieve(i, tmp); 
			if (i == 0) tmp.xuatDonThucDauTien(f);
			else f << tmp;
		}
		return f;
	}

};