#include "DaThuc.h"


void main()
{
	ifstream fin1, fin2;
	ofstream fout;
	fin1.open("F1.txt", ios::in);
	fin2.open("F2.txt", ios::in);
	fout.open("F-result.txt", ios::out);
	if (fin1.good() &&fin2.good() && fout.good())
	{
		CDaThuc F1, F2;
		fin1 >> F1;
		cout << " Da thuc ban dau F1 :\n ";
		cout << F1;
		cout << "\n Da thuc sau khi sort F1 : \n";
		F1.sapXepDaThuc();
		cout << F1;
		cout << "\n Da Thuc sau khi rut gon F1 : \n ";
		F1.rutGonDaThuc();
		cout << F1 ;
		fout << "\n F1 \n" << F1;
		cout << "\n Da thuc khac co dang F2 : \n";
		fin2 >> F2;
	    F2.sapXepDaThuc();
		F2.rutGonDaThuc();
		cout << F2;
		fout << "\n\n F2 \n " << F2;
		cout << "\n Ket qua sau khi cong 2 da thuc F1+F2 : \n";
		CDaThuc tong = (F1 + F2);
		cout << tong;
		fout << "\n\n F3 \n" << tong;
		cout << "\n Ket qua sau khi tru 2 da thuc la F1-F2 :\n";
		CDaThuc hieu = (F1 - F2);
		cout << hieu ;
		fout << "\n\n F4 \n" << hieu;
		cout << "\n Ket qua sau khi nhan da thuc F1*F2 : \n";
		CDaThuc tich = (F1*F2);
		tich.sapXepDaThuc();
		tich.rutGonDaThuc();
		cout << tich<<endl;
		fout << "\n\n F5 \n" << tich;	
		cout << "\n =========== Nhan 1 nut bat ki va chon Yes to All de xuat ket qua ra file F-result  ===========\n" << endl;
		
	}
	else cout << "Khong mo dc file!\n";
	system("pause");
	fin1.close();
	fin2.close();
	fout.close();
}

//void main()
//{
//	CLinked_List<int> a;
//	
//	a.insert(a.getLength(),1);
//	a.insert(a.getLength(), -53);
//	a.insert(a.getLength(), 7);
//	a.insert(a.getLength(), 0);
//	a.insert(a.getLength(), -1);
//	a.insert(a.getLength(), 5);
//	a.insert(a.getLength(), 5);
//	a.insert(a.getLength(), 5);
//
//	a.remove(0);
//	a.remove(0);
//	cout << "\n Danh sach vua nhap la : ";
//	int n = a.getLength();
//	int *arr = new int[n];
//	for (int i = 0; i < n; i++)
//	{
//		a.retrieve(i, arr[i]);
//		cout << arr[i] << "  ";
//	}
//
//	cout << endl;
//	a.remove(2);
//	int m = a.getLength();
//	int *t = new int[n];
//	for (int i = 0; i < m; i++)
//	{
//		a.retrieve(i, t[i]);
//		cout << t[i] << "  ";
//	}
//
//	CLinked_List<int> b=a; // test test copy constructor
//	int *Arr2 = new int[b.getLength()];
//	b.remove(b.getLength()-1);    // Test hàm remove của đối tượng CLinked_List
//	b.insert(b.getLength(), 9);
//	b.insert(b.getLength(), 9);
//	b.insert(b.getLength(), 8);
//	b.insert(b.getLength(), -7);
//	b.insert(b.getLength(), 4);
//	cout << "\n Danh sach b la : ";
//	int i = 0;
//	while (i < b.getLength())
//	{
//		b.retrieve(i, Arr2[i]);
//		cout << Arr2[i] << "  ";
//		i++;
//	}
//	cout << "\n Sau khi sort : \n";
//	b.sapXep();
//	b.Xuat();
//	cout << endl;
//
//
//
//	system("pause");
//}
//
//


