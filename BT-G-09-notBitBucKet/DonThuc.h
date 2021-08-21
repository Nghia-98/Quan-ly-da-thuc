#pragma once

#include "Bien.h"
#include "Linked_List.h"

using namespace std;
class CDonThuc /*:public CBien, public CLinked_List<CBien>*/ {
	//Một đơn thức có 1 hệ số và có thể có 1 hoặc nhiều biến, mỗi biến có 1 số mũ
protected:
	// Lưu đơn thức dưới dạng danh sách liên kết, mỗi Node chứa thông tin biến và mũ tương ứng
	float heSo;// hệ số
	CLinked_List<CBien> List; // danh sách các biến

public:
	CDonThuc();
	CDonThuc(const CDonThuc&);
	~CDonThuc();

	int getLen()const{ return List.getLength(); }
	int tongSoMu()const{
		unsigned short int tongMu = 0;
		CBien tmp;
		for (int i = 0; i < List.getLength(); i++)
		{
			List.retrieve(i, tmp);
			tongMu += tmp.Get_soMu();
		}
		return tongMu;
	}
	CDonThuc operator+(const CDonThuc &d2);
	CDonThuc operator-(const CDonThuc &d2);
	CDonThuc operator*(const CDonThuc &d2);
	CDonThuc& operator=(const CDonThuc &d2)
	{
		this->heSo = d2.heSo;
		this->List = d2.List;
		return *this;
	}

	float Get_heSo() const{ return heSo; }
	void Set_heSO(float hs) { heSo = hs; }

	bool isEqual_dsBien(const CDonThuc &obj)
	{
		return (this->List == obj.List); // toán tử so sánh == của 2 dslk (phương thức của đối tượng CLinked_List)
	}

	bool operator <= (CDonThuc &obj)
	{
		/*this->List.sapXep();
		obj.List.sapXep();*/
		if (this->tongSoMu() < obj.tongSoMu()) return false;
		else if (this->tongSoMu() > obj.tongSoMu()) return true;
		int n = this->getLen();
		int m = obj.getLen();
		int i = 0;
		while (i < n && i < m) // lặp đến khi nào this hết phần tử hoặc obj hết phần tử
		{
			CBien tmp1, tmp2;
			this->List.retrieve(i, tmp1);
			obj.List.retrieve(i, tmp2);
			if (tmp1.Get_tenbien() < tmp2.Get_tenbien()) return false;
			i++;
		}
		if (this->Get_heSo() < obj.Get_heSo()) return true;
		return false;
	}

	void sapXepDonThuc()
	{
		List.sapXep(); // sắp xếp các biến trong danh sách liên kết các biến
	}

	friend istream& operator >> (istream &f, CDonThuc &obj)
	{
		char kitu1, kitu2, kitu3; // Test các trường hợp đơn thức nhập vào có dạng  a^i, -a^i, +a^i, +n*a^i, -n*a^i (5 loại đơn thức)
		f >> kitu1;
		if (!f.eof())
		{
			f >> kitu2;
			if (kitu2 == '^') { // đơn thức loại a^i
				obj.heSo = 1;
				f.seekg(-2, ios::cur); // quay lại từ đầu để đọc tên biến
			}
			else{ // 4 loại đơn thức còn lại : -a^i, +a^i, +n*a^i, -n*a^i
				f >> kitu3; // là 1 tên biến hoặc là kí tự số mũ '^' hoặc là dấu '*' ( -a^1, -3*a^1)
				if (kitu3 == '^') // nếu kí tự thứ 3 của đơn thức là '^' (-a^i) => kitu2 là tên biến => kí tự 1 đại diện cho hệ số =-1 hoặc +1
				{
					if (kitu1 == '-') obj.heSo = -1;
					else obj.heSo = 1;
					f.seekg(-2, ios::cur); // quay lại đọc từ tên biến, trg hợp hệ số = 1 hoặc = -1 thì ko có dấu nhân '*' sau hệ số.( vd -a^3)
				}
				else // ngược lại kí tự thứ 3 của đơn thức là '*' (+n*a^i, -n*a^i) 
				{
					f.seekg(-3, ios::cur); // quay lại đọc hệ số từ đầu
					float heso;
					f >> heso;
					obj.heSo = heso;
					char tmp;
					f >> tmp; // sau khi đọc hệ số , ta phải đọc qua dấu nhân '*' để chuẩn bị đọc tên biến
				}
			}
		}
		else 
		{
			f.seekg(-1, ios::cur);
			obj.heSo = 1;
		}

		CBien bien;
		while (f.eof()==false){
			f >> bien; // nhập vào 1 biến (gồm có tên biến và số mũ)
			int Size = obj.List.getLength(); // ban đầu danh sách các biến của đơn thức có độ dài = 0
			obj.List.insert(Size, bien); // thêm vào cuối danh sách. hàm insert(int index, T newItem) của đối tượng CLinked_List
			//char tmp;
			//f >> tmp; // là dấu nhân '*' hoặc là dấu của hệ số của đơn thức tiếp theo
			//if (tmp == '-' || tmp == '+'|| tmp == '.'){ // khi gặp dấu trừ hoặc dấu cộng thì tức là đã đọc hết 1 đơn thức
			//	f.seekg(-1, ios::cur);
			//	//break;
			//}
			/* Sau khi doc het 1 biến trong đơn thức */
			char tmp; //  ta sẽ gặp dấu '*' tiếp đến là 1 biến khác trong cùng đơn thức 
			          // hoặc ta sẽ gặp dấu '-','+' của hệ số trong đơn thức tiếp theo
			if (!f.eof()){
				f >> tmp; // nếu đơn thức vẫn còn biến chưa đc đọc thì tmp sẽ bằng '*'
				if (tmp == '-' || tmp == '+'){ // đã đọc qua phần hệ số của đơn thức tiếp theo
					f.seekg(-1, ios::cur);
					break;
				}
			}
		}
		return f;
	}

	void xuatHeSoDonThuc(ostream &f)const
	{ 
		if (heSo == -1) f << '-';
		else {
			if (heSo == 1) f << '+';
			else{
				if (heSo >= 0){
					f << '+';
					f << heSo;
				}
				else{
					f << heSo;
				}
				f << "*";
			}
		}
	}
	void xuatDanhSachBien(ostream& f)const
	{
		int n = List.getLength();
		CBien tmp;
		int i = 0;
		for (i; i < n; i++)
		{
			List.retrieve(i, tmp); // hàm lấy data tại node i đưa vào tmp của đối tượng CLinked_List
			f << tmp;
			if (i != n - 1) f << "*";
		}
	}

	void xuatDonThucDauTien(ostream &f)const
	{ 
		if (heSo == -1)
		{
			f << '-';
			xuatDanhSachBien(f);
		}
		else 
		{
			if (heSo != 1)
			{
				if (heSo >= 0){
					f << heSo;
					f << '*';
					xuatDanhSachBien(f);
				}
				else{
					f << heSo;
					f << '*';
					xuatDanhSachBien(f);
				}
			}
			else
			{
				xuatDanhSachBien(f);
			}
		}
	
	}

	void rutGonDonThuc() // với điều kiện đã sắp xếp các biến của đơn thức đó
	{
		CBien tmp1, tmp2;
		for (int i = 0; i < List.getLength() - 1; i++) // duyệt từ đầu đến node kế cuối trong danh sách
		{
			List.retrieve(i, tmp1); // lấy ra 1 biến đưa vào tmp1
			for (int j = i + i; j < List.getLength(); j++) // duyệt từ biến liền sau biến tmp1 đến biến cuối cùng trong danh sách
			{
				List.retrieve(j, tmp2); // lấy ra 1 biến đưa vào tmp2
				if (tmp1.Get_tenbien() == tmp2.Get_tenbien()) // nếu tmp1 và tmp2 trừng tên biến
				{
					int somu = tmp1.Get_soMu() + tmp2.Get_soMu(); // cộng số mũ của tmp2 vào tmp1
					tmp1.Set_soMU(somu); // cập nhật số mũ tmp1
					List.remove(j); // xóa biến bị trùng ( tmp2 )
					List.insert(i, tmp1); // đưa biến mới tmp1 vào ds các biến của đơn thức
					List.remove(i + 1); // xóa biến đứng trc biến mới đưa vào
					j--; // để bắt trường hợp tên biến của node liền sau trùng với tên biến của node vừa dc xóa
				}
			}
		}
	}

	friend ostream& operator << (ostream &f, const CDonThuc &obj) // đã cài đặt phương thức gán = cho đối tượng CBien
	{
		///*if (obj.heSo == -1) f << '-';
		//else {
		//	if (obj.heSo == 1) f << '+';
		//	else{
		//		if (obj.heSo >= 0){
		//			f << '+';
		//			f << obj.heSo;
		//		}
		//		else{
		//			f << obj.heSo;
		//		}
		//		f << "*";
		//	}
		//}*/
		//
	

		///*CBien tmp;
		//obj.List.retrieve(0, tmp);
		//f << tmp;*/
		//
		//int n = obj.List.getLength();
		//CBien tmp;
		//int i = 0;
		//for (i ; i < n; i++)
		//{
		//	obj.List.retrieve(i, tmp); // hàm lấy data tại node i đưa vào tmp của đối tượng CLinked_List
		//	f << tmp;
		//    if(i != n-1) f << "*"; 
		//}
		//
		
		obj.xuatHeSoDonThuc(f);
		obj.xuatDanhSachBien(f);

		return f;
	}
};
