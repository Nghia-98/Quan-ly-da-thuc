#pragma
#include<iostream>
#include <fstream>
using namespace std;

class CBien{
protected:
	char tenBien; // Tên biến là 1 kí tự
	unsigned short int soMu; //số mũ của biến là một số nguyên dương.
public:
	CBien(){
		tenBien = ' ';
		soMu = 1;
	}
	CBien(char tbien, unsigned short int sMu){
		tenBien = tbien;
		soMu = sMu;
	}
	CBien(const CBien& obj){
		tenBien = obj.tenBien;
		soMu = obj.soMu;
	}
	~CBien(){
		return;
	}
	void set_Bien(char t, unsigned short int s)
	{
		tenBien = t;
		soMu = s;
	}

	char Get_tenbien() { return tenBien; }
	unsigned short int Get_soMu() { return soMu; };
	void Set_tenbien(char tb) { tenBien = tb; }
	void Set_soMU(unsigned short int sm) { soMu = sm; }

	CBien& operator = (const CBien &obj)
	{
		tenBien = obj.tenBien;
		soMu = obj.soMu;
		return *this;
	}

	bool operator == (const CBien &obj)
	{
		return (soMu == obj.soMu && tenBien == obj.tenBien);
	}

	bool operator != (const CBien &obj)
	{
		return (!(*this == obj));
	}

	bool operator > (const CBien &obj)
	{
		if (this->tenBien < obj.tenBien) return true;
		else if(this->tenBien > obj.tenBien) return false;
		else if (this->soMu < obj.soMu) return true;
		else return false;
	}

	bool operator < (const CBien &obj)
	{
		return ((*this > obj) == false && (*this == obj) == false);
	}

	bool operator <= (const CBien &obj)
	{
		return (!(*this > obj));
	}

	friend istream& operator >> (istream &f, CBien &obj){
		char tenbien, tmp;
		unsigned short int somu;
		f >> tenbien; // đọc tên biến vào
		if (f.eof() == true) somu = 1;
		else // nếu chưa hết file thì đọc tiếp số mũ ( để bắt trường hợp đơn thức cuối có dạng -n*......*k )
		{
			f >> tmp;     // kiểm tra có dấu ^ ko ( tmp có thể là '*' , '-', '+' )
			if (tmp == '^') // nếu có dấu mũ thì mới có số mũ
				f >> somu;
			else  // Nếu ko có dấu ^ thì ta xem số mũ là 1
			{
				f.seekg(-1, ios::cur); // dịch chuyển con trỏ đọc từ vị trí hiện hành sang trái 1 bước
				somu = 1;
			}
		}
		
		obj.set_Bien(tenbien, somu);
		return f;
	}

	friend ostream& operator << (ostream &f, const CBien& obj)
	{
		f << obj.tenBien; // xuất ra tên biến
		if (obj.soMu != 1){ // xuất ra số mũ nếu số mũ khác 1
			f << '^';
			f << obj.soMu;
		}
		return f;
	}
};