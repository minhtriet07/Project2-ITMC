#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>
using namespace std;

#define file_LopHoc "lophoc.txt"
#define file_HocPhi "hocphi.txt"
#define file_SinhVien "sinhvien.txt"

struct HocPhi {
    char MSSV[50];
    double TongHocPhi;
};

struct SinhVien {
    char MSSV[50];
    char HoTen[50];
    char MaLop[50];
    char Nganh[100];
    int NamVaoTruong;
};

struct LopHoc {
    char MaLop[50];
    char TenLop[50];
    vector<SinhVien> danhSachSinhVien;
};

vector<LopHoc> danhSachLop;

void DocFileLopHoc() {
    ifstream f(file_LopHoc);
    if (!f) return;
    
    LopHoc lop;
    while (f.getline(lop.MaLop, 50) && f.getline(lop.TenLop, 50)) {
        danhSachLop.push_back(lop);
    }
    f.close();
}

void GhiFileLopHoc() {
    ofstream f(file_LopHoc);
    if (!f) return;
    
    for (const auto &lop : danhSachLop) {
        f << lop.MaLop << '\n' << lop.TenLop << '\n';
    }
    f.close();
}

void DocFileSinhVien() {
    ifstream f(file_SinhVien);
    if (!f) return;
    
    SinhVien sv;
    char buffer[100];
    
    while (f.getline(sv.MSSV, 50) && 
           f.getline(sv.HoTen, 50) &&
           f.getline(sv.MaLop, 50) &&
           f.getline(sv.Nganh, 100) &&
           f.getline(buffer, 100)) {
        sv.NamVaoTruong = atoi(buffer);
        
        for (auto &lop : danhSachLop) {
            if (strcmp(lop.MaLop, sv.MaLop) == 0) {
                lop.danhSachSinhVien.push_back(sv);
                break;
            }
        }
    }
    f.close();
}

void GhiFileSinhVien() {
    ofstream f(file_SinhVien);
    if (!f) return;
    
    for (const auto &lop : danhSachLop) {
        for (const auto &sv : lop.danhSachSinhVien) {
            f << sv.MSSV << '\n' 
              << sv.HoTen << '\n'
              << sv.MaLop << '\n'
              << sv.Nganh << '\n'
              << sv.NamVaoTruong << '\n';
        }
    }
    f.close();
}

vector<HocPhi> DocFileHocPhi() {
    vector<HocPhi> danhSachHocPhi;
    ifstream f(file_HocPhi);
    if (!f) return danhSachHocPhi;
    
    HocPhi hp;
    char buffer[100];
    
    while (f.getline(hp.MSSV, 50) && f.getline(buffer, 100)) {
        hp.TongHocPhi = atof(buffer);
        danhSachHocPhi.push_back(hp);
    }
    f.close();
    return danhSachHocPhi;
}

void MenuChinh() {
    cout << "\n****** HE THONG QUAN LY ******" << endl;
    cout << "1. Quan ly lop hoc" << endl;
    cout << "2. Quan ly sinh vien" << endl;
    cout << "3. Xem hoc phi sinh vien" << endl;
    cout << "0. Thoat" << endl;
    cout << "Chon chuc nang: ";
}

void MenuLopHoc() {
    cout << "\n****** QUAN LY LOP HOC ******" << endl;
    cout << "1. Them lop hoc" << endl;
    cout << "2. Xoa lop hoc" << endl;
    cout << "3. Danh sach lop hoc" << endl;
    cout << "4. Xem sinh vien trong lop" << endl;
    cout << "0. Quay lai" << endl;
    cout << "Chon chuc nang: ";
}

void MenuSinhVien() {
    cout << "\n****** QUAN LY SINH VIEN ******" << endl;
    cout << "1. Them sinh vien" << endl;
    cout << "2. Xoa sinh vien" << endl;
    cout << "3. Danh sach sinh vien" << endl;
    cout << "0. Quay lai" << endl;
    cout << "Chon chuc nang: ";
}

void ThemLopHoc() {
    LopHoc lop;
    cout << "\n--- THEM LOP HOC ---" << endl;
    cout << "Ma lop: ";
    gets(lop.MaLop);
    cout << "Ten lop: ";
    gets(lop.TenLop);
    
    for (const auto &l : danhSachLop) {
        if (strcmp(l.MaLop, lop.MaLop) == 0) {
            cout << "Ma lop da ton tai!" << endl;
            return;
        }
    }
    
    danhSachLop.push_back(lop);
    GhiFileLopHoc();
    cout << "Them lop hoc thanh cong!" << endl;
}

void XoaLopHoc() {
    char maLop[50];
    cout << "\n--- XOA LOP HOC ---" << endl;
    cout << "Nhap ma lop can xoa: ";
    gets(maLop);
    
    for (auto it = danhSachLop.begin(); it != danhSachLop.end(); ++it) {
        if (strcmp(it->MaLop, maLop) == 0) {
            if (!it->danhSachSinhVien.empty()) {
                cout << "Khong the xoa lop vi van con sinh vien!" << endl;
                return;
            }
            danhSachLop.erase(it);
            GhiFileLopHoc();
            cout << "Xoa lop hoc thanh cong!" << endl;
            return;
        }
    }
    cout << "Khong tim thay lop hoc!" << endl;
}

void HienThiDanhSachLop() {
    cout << "\n--- DANH SACH LOP HOC ---" << endl;
    if (danhSachLop.empty()) {
        cout << "Chua co lop hoc nao!" << endl;
        return;
    }
    
    cout << left << setw(10) << "Ma lop" << setw(23) << "Ten lop" 
         << setw(10) << "So SV" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    
    for (const auto& lop : danhSachLop) {
        cout << left << setw(10) << lop.MaLop << setw(23) << lop.TenLop 
             << setw(10) << lop.danhSachSinhVien.size() << endl;
    }
}

void HienThiSinhVienTheoLop() {
    char maLop[50];
    cout << "\n--- SINH VIEN TRONG LOP ---" << endl;
    cout << "Nhap ma lop: ";
    gets(maLop);
    
    for (const auto& lop : danhSachLop) {
        if (strcmp(lop.MaLop, maLop) == 0) {
            cout << "\nLOP: " << lop.TenLop << " (" << lop.MaLop << ")" << endl;
            cout << left << setw(15) << "MSSV" << setw(25) << "Ho ten" 
                 << setw(25) << "Nganh" << setw(10) << "Nam" << endl;
            cout << "-------------------------------------------------------------------" << endl;
            
            if (lop.danhSachSinhVien.empty()) {
                cout << "Khong co sinh vien nao trong lop!" << endl;
            } else {
                for (const auto& sv : lop.danhSachSinhVien) {
                    cout << left << setw(15) << sv.MSSV 
                         << setw(25) << sv.HoTen 
                         << setw(25) << sv.Nganh 
                         << setw(10) << sv.NamVaoTruong << endl;
                }
            }
            return;
        }
    }
    cout << "Khong tim thay lop hoc!" << endl;
}

void ThemSinhVien() {
    if (danhSachLop.empty()) {
        cout << "Vui long them lop hoc truoc!" << endl;
        return;
    }
    
    SinhVien sv;
    cout << "\n--- THEM SINH VIEN ---" << endl;
    cout << "MSSV: ";
    gets(sv.MSSV);
    
    for (const auto& lop : danhSachLop) {
        for (const auto& s : lop.danhSachSinhVien) {
            if (strcmp(s.MSSV, sv.MSSV) == 0) {
                cout << "MSSV da ton tai!" << endl;
                return;
            }
        }
    }
    
    cout << "Ho ten: ";
    gets(sv.HoTen);
    cout << "Nganh: ";
    gets(sv.Nganh);
    cout << "Nam vao truong: ";
    cin >> sv.NamVaoTruong;
    getchar();
    
    HienThiDanhSachLop();
    cout << "Chon ma lop: ";
    gets(sv.MaLop);
    
    for (auto& lop : danhSachLop) {
        if (strcmp(lop.MaLop, sv.MaLop) == 0) {
            lop.danhSachSinhVien.push_back(sv);
            GhiFileSinhVien();
            cout << "Them sinh vien thanh cong vao lop " << lop.TenLop << "!" << endl;
            return;
        }
    }
    
    cout << "Khong tim thay lop!" << endl;
}

void XoaSinhVien() {
    char mssv[50];
    cout << "\n--- XOA SINH VIEN ---" << endl;
    cout << "Nhap MSSV can xoa: ";
    gets(mssv);
    
    for (auto& lop : danhSachLop) {
        for (auto it = lop.danhSachSinhVien.begin(); it != lop.danhSachSinhVien.end(); ++it) {
            if (strcmp(it->MSSV, mssv) == 0) {
                lop.danhSachSinhVien.erase(it);
                GhiFileSinhVien();
                cout << "Xoa sinh vien thanh cong!" << endl;
                return;
            }
        }
    }
    cout << "Khong tim thay sinh vien!" << endl;
}

void HienThiTatCaSinhVien() {
    cout << "\n--- DANH SACH TAT CA SINH VIEN ---" << endl;
    bool coSinhVien = false;
    
    for (const auto& lop : danhSachLop) {
        if (!lop.danhSachSinhVien.empty()) {
            coSinhVien = true;
            cout << "\nLOP: " << lop.TenLop << " (" << lop.MaLop << ")" << endl;
            cout << left << setw(28) << "MSSV" << setw(27) << "Ho ten" 
                 << setw(30) << "Nganh" << setw(6) << "Nam" << endl;
            cout << "------------------------------------------------" << endl;
            
            for (const auto& sv : lop.danhSachSinhVien) {
                cout << left << setw(10) << sv.MSSV << setw(23) << sv.HoTen 
                     << setw(23) << sv.Nganh << setw(6) << sv.NamVaoTruong << endl;
            }
        }
    }
    
    if (!coSinhVien) {
        cout << "Khong co sinh vien nao!" << endl;
    }
}

void XemHocPhiSinhVien() {
    char mssv[50];
    cout << "\n--- XEM HOC PHI SINH VIEN ---" << endl;
    cout << "Nhap MSSV: ";
    gets(mssv);
    
    vector<HocPhi> danhSachHocPhi = DocFileHocPhi();
    
    for (const auto& hp : danhSachHocPhi) {
        if (strcmp(hp.MSSV, mssv) == 0) {
            char hoTen[50] = "Khong tim thay";
            char lop[100] = "Khong tim thay";
            
            for (const auto& lopHoc : danhSachLop) {
                for (const auto& sv : lopHoc.danhSachSinhVien) {
                    if (strcmp(sv.MSSV, mssv) == 0) {
                        strcpy(hoTen, sv.HoTen);
                        strcpy(lop, sv.MaLop);
                        break;
                    }
                }
            }
            
            cout << "\nTHONG TIN HOC PHI" << endl;
            cout << "MSSV: " << mssv << endl;
            cout << "Ho ten: " << hoTen << endl;
            cout << "Lop: " << lop << endl;
            cout << "Hoc phi: " << fixed << setprecision(0) << hp.TongHocPhi << " TR" << endl;
            return;
        }
    }
    
    cout << "Khong tim thay hoc phi cho sinh vien nay!" << endl;
}

int main() {
    int choice;
    
    DocFileLopHoc();
    DocFileSinhVien();
    
    cout << "=== HE THONG QUAN LY TRUONG HOC ===" << endl;
    
    while (true) {
        MenuChinh();
        cin >> choice;
        getchar();
        
        if (choice == 0) {
            cout << "Thoat chuong trinh. Tam biet!" << endl;
            break;
        }
        
        switch (choice) {
            case 1: { 
                int choiceLop;
                while (true) {
                    MenuLopHoc();
                    cin >> choiceLop;
                    getchar();
                    
                    if (choiceLop == 0) break;
                    
                    switch (choiceLop) {
                        case 1: ThemLopHoc(); break;
                        case 2: XoaLopHoc(); break;
                        case 3: HienThiDanhSachLop(); break;
                        case 4: HienThiSinhVienTheoLop(); break;
                        default: cout << "Chuc nang khong hop le!\n";
                    }
                }
                break;
            }
            case 2: { 
                int choiceSV;
                while (true) {
                    MenuSinhVien();
                    cin >> choiceSV;
                    getchar();
                    
                    if (choiceSV == 0) break;
                    
                    switch (choiceSV) {
                        case 1: ThemSinhVien(); break;
                        case 2: XoaSinhVien(); break;
                        case 3: HienThiTatCaSinhVien(); break;
                        default: cout << "Chuc nang khong hop le!\n";
                    }
                }
                break;
            }
            case 3: { 
                XemHocPhiSinhVien();
                break;
            }
            default:
                cout << "Chuc nang khong hop le!\n";
        }
    }
    
    return 0;
}