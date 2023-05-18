#include <stdio.h>
#include <string.h>
#define max 100
#define path_Menu "D:\\C\\PBBL1\\Menu.txt"
#define path_Loai_Mon "D:\\C\\PBBL1\\LoaiMon.txt"

struct MonAn{
	char tenMon[max][max];
	int stt[max];
	int soLuong[max];
	int giaTien[max];
	int loai[max];
} ; 

struct LoaiMon{
	int loai[max];
	char tenLoai[max][max];
};

struct MonAn monAn;
struct LoaiMon loaiMon;
int SoMonAn;
int SoLoaiMon;
long Doanh_thu_cua_ngay = 0;
char mdd[max], ngay[max];
int So_Hoa_Don = 0;

void Doc_MENU(){
	
	FILE *f;
	f = fopen(path_Menu, "r");
	if(f == NULL){
		printf("khong doc duoc tep");
	}
	
	fscanf(f, "%d", &SoMonAn);
	int i;
	for(i = 0; i < SoMonAn; i++){
		fscanf(f, "%d", &monAn.stt[i] );
		fscanf(f, "%s", &monAn.tenMon[i]);
		fscanf(f, "%d", &monAn.giaTien[i]);
		fscanf(f, "%d", &monAn.loai[i]);
	}

	fclose(f);
}

void Doc_Loai_Mon(){
	FILE *f;
	f = fopen(path_Loai_Mon, "r");
	if(f == NULL){
		printf("khong doc duoc tep");
	}
	
	fscanf(f, "%d", &SoLoaiMon);
	int i;
	for(i = 0; i < SoLoaiMon; i++){
		fscanf(f, "%d", &loaiMon.loai[i] );
		fscanf(f, "%s", &loaiMon.tenLoai[i]);
	}

	fclose(f);
}

void In_MENU();
long Dat_Mon(FILE *f);
long Ghi_Hoa_Don(char Dia_Chi_File_Hoa_Don[max]);
void Xuat_Hoa_Don(char Dia_Chi_File_Hoa_Don[max], int vitri);

void Tat_Ca_Hoa_Don_Cua_Ngay(char Dia_Chi_File_Hoa_Don[max]){
	FILE *f;
	f = fopen(Dia_Chi_File_Hoa_Don, "r");
	
	char read[max];
	int dem = 0;
	fgets(read, max, f);
	do{ // chuyen con tro den vi tri hoa don can xuat
		
		// Xuat Thong Tin
	char *hoten, *sdt, *diachi;
	hoten = strtok(read, ":");
	sdt = strtok(NULL, ":");
	diachi = strtok(NULL, ":");
	printf("Thong tin khach hang: \%s\t%s\t%s\n", hoten+1, sdt, diachi);
	fgets(read, max, f);
	
	do{
		char *stt, *tenMon, *soLuong, *gia;
		stt = strtok(read, ":");
		tenMon = strtok(NULL, ":");
		soLuong = strtok(NULL, ":");
		gia = strtok(NULL, ":");
		printf("%s\t%s\t%s\t%s", stt+1, tenMon, soLuong, gia);
		fgets(read, max, f);
	}while(read[0] != '+');
	
	printf("\nTong so tien: %s\n", read+1);
	printf("=====================================\n");
	}while(fgets(read, max, f) != NULL);
	
	printf("TONG DOANH THU HIEN TAI: %d", Doanh_thu_cua_ngay);
	
	fclose(f);
}

int main(){ //////////////////////////////////////////////////////////////////////////main
	Doc_MENU();
	Doc_Loai_Mon();
	In_MENU();
	
	printf("Bat dau ngay lam viec!!!\n");
	printf("Nhap ngay lam viec (vd: 01-01-2023): "); gets(ngay);
	printf("Nhap ma dao dich cua ngay lam viec de bat dau: "); gets(mdd);
	system("cls");
	
	char DiaChiGhiFile[max] = "D:\\C\\PBBL1\\HoaDon\\";
	
	strcat(DiaChiGhiFile, ngay);
	strcat(DiaChiGhiFile, "_Ma_giao_dich_");
	strcat(DiaChiGhiFile, mdd);
	strcat(DiaChiGhiFile, ".txt");
	
	Tat_Ca_Hoa_Don_Cua_Ngay(DiaChiGhiFile);
	//Doanh_thu_cua_ngay += Ghi_Hoa_Don(DiaChiGhiFile);
	//Xuat_Hoa_Don(DiaChiGhiFile, 3);
	//printf("%ld", Doanh_thu_cua_ngay);
}

void In_MENU(){
	int i, j;

	printf("=================== MENU ====================\n");
	for(i = 0; i < SoLoaiMon; i++){
		printf("\n\t%s\n", loaiMon.tenLoai[i]);
		for(j = 0; j < SoMonAn; j++){
			if(monAn.loai[j] == loaiMon.loai[i]){
				printf("%-2d.%-20s%-7dVND\n", monAn.stt[j], monAn.tenMon[j], monAn.giaTien[j]);
			}
		}
	}
	printf("===================*****======================\n");
}

long Dat_Mon(FILE *f){
	char HoTen[max];
	int soDT;
	char DiaChi[max];
	int tenMon;
	int soLuong;
	
	fflush(stdin);
	printf("Nhap ho va ten: "); gets(HoTen);
	printf("Nhap so dien thoai: "); scanf("%d", &soDT);
	fflush(stdin);
	printf("Nhap dia chi: "); gets(DiaChi);
	fprintf(f, "=%s:%d:%s\n", HoTen, soDT, DiaChi);
	++So_Hoa_Don;
	
	int count =  0; 
	int set;
	int tongtien=0;
	
	do{
		count++;
		printf("\nChon mon tren Menu: "); scanf("%d", &tenMon);
		printf("Ban da chon mon %s, hay chon so luong: ", monAn.tenMon[tenMon - 1]); scanf("%d", &soLuong);
		fprintf(f, "-%d:%s:%d:%d\n", count, monAn.tenMon[tenMon - 1], soLuong, soLuong * monAn.giaTien[tenMon - 1]);
		tongtien+=soLuong * monAn.giaTien[tenMon - 1];
		printf("\nBan co mon chon mon tiep hay khong (1.co 0.khong): "); scanf("%d", &set);
		
	}while(set != 0);
	fprintf(f, "+%d\n",tongtien);
	return tongtien;
}

long Ghi_Hoa_Don(char Dia_Chi_File_Hoa_Don[max]){
	long TongTien;
	
	FILE *f;
	f = fopen(Dia_Chi_File_Hoa_Don, "a");
	In_MENU(monAn);
	TongTien = Dat_Mon(f);
	fclose(f);
	
	system("cls");
	Xuat_Hoa_Don(Dia_Chi_File_Hoa_Don, So_Hoa_Don);
	
	system("pause");
	return TongTien;
}

void Xuat_Hoa_Don(char Dia_Chi_File_Hoa_Don[max], int vitri){
	FILE *f;
	f = fopen(Dia_Chi_File_Hoa_Don, "r");
	
	char read[max];
	int dem = 0;
	
	do{ // chuyen con tro den vi tri hoa don can xuat
		fgets(read, max, f);
		if(read[0] == '=') ++dem;
	}while(dem != vitri);
	
	// Xuat Thong Tin
	char *hoten, *sdt, *diachi;
	hoten = strtok(read, ":");
	sdt = strtok(NULL, ":");
	diachi = strtok(NULL, ":");
	
	printf("\n=====================================\n");
	printf("             HOA DON\n");
	printf("=====================================\n");
	printf("Ho ten khach hang: %s\n", hoten+1);
	printf("So dien thoai: %s\n", sdt);
	printf("Dia chi: %s\n", diachi);
	fgets(read, max, f);
	
	printf("=====================================\n");
	printf("STT    ten mon        so luong    gia\n");
	do{
		char *stt, *tenMon, *soLuong, *gia;
		stt = strtok(read, ":");
		tenMon = strtok(NULL, ":");
		soLuong = strtok(NULL, ":");
		gia = strtok(NULL, ":");
		printf("%s\t%s\t%s\t%s", stt+1, tenMon, soLuong, gia);
		fgets(read, max, f);
	}while(read[0] != '+');
	printf("=====================================\n");
	printf("\nTong so tien: %s\n", read+1);
	
	fclose(f);
}

