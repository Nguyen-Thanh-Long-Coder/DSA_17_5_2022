#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define MonHoc 3

struct SinhVien
{
	string mssv, hoTen, queQuan;
	float dsDiem[MonHoc];

	void nhapThongTinSinhVien()
	{
		cout << "Nhap mssv: ";
		getline(cin, mssv);
		cout << "Nhap ho ten: ";
		getline(cin, hoTen);
		cout << "Nhap que quan: ";
		getline(cin, queQuan);
		for(int i=0; i<MonHoc; i++)
		{
			cout << "Nhap diem mon thu " << i + 1 << ": ";
			cin >> dsDiem[i]; 
		}
		cin.ignore();
	}

	void xuatThongTinSinhVien()
	{
		cout << "MSSV: " << mssv << endl;
		cout << "Ho ten: " << hoTen << endl;
		cout << "Que quan: " << queQuan << endl;
		cout << "DS diem: ";
		for(int i=0; i<MonHoc; i++)
			cout << dsDiem[i] << " ";
	}

	void docFileThongTinSinhVien(ifstream &filein)
	{
		getline(filein, mssv, ',');
		filein.ignore();
		// filein.seekg(1, ios::cur);
		getline(filein, hoTen, ',');
		// filein.seekg(1, ios::cur);
		filein.ignore();
		getline(filein, queQuan, ',');
		// filein.seekg(1, ios::cur);
		filein.ignore();

		for(int i=0; i<MonHoc; i++)
			filein >> dsDiem[i];
	}
};

SinhVien* nhapThongTinDSSV(int &sl);
void hienThiDSSV(SinhVien *ptr, int sl);
void docFileDSSV(SinhVien *&ptr, int &sl, ifstream &filein);
void timKiemSinhVienTheoTen(SinhVien *ptr, int sl, string hoTen);
void timKiemSinhVienTheoQueQuan(SinhVien *ptr, int sl, string queQuan);
void sapXepSVTangDanHoTen(SinhVien *ptr, int sl);
void ghiFileDSSVHocBong(SinhVien *ptr, int sl, ofstream &fileout);
bool ktHocBong(SinhVien a);

int main()
{
	SinhVien *ptrSV = nullptr;
	int sl;
	ifstream filein;
	ofstream fileout;
	filein.open("SinhVienText.txt", ios::in);
	fileout.open("hocbong.txt", ios::out);

	if(!filein.is_open())
		return 1;

	docFileDSSV(ptrSV, sl, filein);
	hienThiDSSV(ptrSV, sl);

	sapXepSVTangDanHoTen(ptrSV, sl);
	cout << endl << "DS SINH VIEN SAU KHI SAP XEP" << endl;
	hienThiDSSV(ptrSV, sl);

	ghiFileDSSVHocBong(ptrSV, sl, fileout);
	filein.close();
	fileout.close();

	return 0;
}

SinhVien* nhapThongTinDSSV(int &sl)
{
	SinhVien *ptr = nullptr;
	cout << "Nhap so luong sinh vien: ";
	cin >> sl;
	cin.ignore();

	ptr = new SinhVien[sl];

	for(int i=0; i<sl; i++)
	{
		ptr[i].nhapThongTinSinhVien();
	}

	return ptr;
}

void hienThiDSSV(SinhVien *ptr, int sl)
{
	cout << "Danh Sach Sinh Vien" << endl;
	for(int i=0; i<sl; i++)
	{
		ptr[i].xuatThongTinSinhVien();
		cout << endl;
	}
}

void docFileDSSV(SinhVien *&ptr, int &sl, ifstream &filein)
{
	filein >> sl;
	filein.ignore();
	ptr = new SinhVien[sl];
	// filein.seekg(1, ios::cur);

	for(int i=0; i<sl; i++)
	{
		ptr[i].docFileThongTinSinhVien(filein);
		filein.ignore();
	}
}

void timKiemSinhVienTheoTen(SinhVien *ptr, int sl, string hoTen)
{
	for(int i=0; i<sl; i++)
	{
		if(ptr[i].hoTen == hoTen)
		{
			cout << "Tim thay" << endl;
			ptr[i].xuatThongTinSinhVien();
			return; 
		}
	}

	cout << "Khong tim thay" << endl;
}

void timKiemSinhVienTheoQueQuan(SinhVien *ptr, int sl, string queQuan)
{
	for(int i=0; i<sl; i++)
	{
		if(ptr[i].queQuan == queQuan)
		{
			cout << "Tim thay" << endl;
			ptr[i].xuatThongTinSinhVien();
			return;
		}
	}

	cout << "Khong tim thay" << endl;
}

void sapXepSVTangDanHoTen(SinhVien *ptr, int sl)
{
	for(int i=0; i<sl-1; i++)
	{
		SinhVien *ss = &ptr[i];
		for(int j=i+1; j<sl; j++)
		{
			if(ptr[j].hoTen < ss->hoTen)
				ss = &ptr[j];
		}

		SinhVien tmp = *ss;
		*ss = ptr[i];
		ptr[i] = tmp;
	}
}

void ghiFileDSSVHocBong(SinhVien *ptr, int sl, ofstream &fileout)
{
	for(int i=0; i<sl; i++)
	{
		if(ktHocBong(ptr[i]))
		{
			float dtb = 0;
			fileout << ptr[i].mssv << " - " << ptr[i].hoTen << endl;
			for(int j=0; j<MonHoc; j++)
			{
				fileout << ptr[i].dsDiem[j] << " ";
				dtb += ptr[i].dsDiem[j];
			}

			dtb /= MonHoc;
			fileout << "- " << dtb << endl;
		}
	}
}

bool ktHocBong(SinhVien a)
{
	float dtb = 0;
	for(int i=0; i<MonHoc; i++)
	{
		if(a.dsDiem[i] < 5)
			return false;
		dtb += a.dsDiem[i];
	}

	dtb /= MonHoc;
	if(dtb < 7.5)
		return false;
	return true;
}