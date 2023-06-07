#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define max 100
#define path_Menu "Menu.txt"  // Duong dan den file menu
#define path_Loai_Mon "LoaiMon.txt"  // Duong dan den file phan loai mon an
#define path_Hoa_Don "HoaDon\\"  // Duong dan den file luu hoa don
#define path_Hoa_Don_Cho_Khach "HoaDonChoKhach\\"  // Duong dan den file luu hoa don in ra cho khach hang
#define path_Hoa_Don_Dung_De_Ghi "HoaDon\\\\" // Su dung chuoi nay de ghi vao file Doanh thu, luu y "\\\\"
#define path_Dia_Chi_Doanh_Thu "Doanh_Thu\\Doanh_Thu.txt"  // Duong dan den file luu doanh thu
#define path_Giam_Gia "Muc_Giam_Gia.txt" // Duong dan den file giam gia

struct MonAn{
	char tenMon[max][max];
	int stt[max];
	int giaTien[max];
	int loai[max];
}; 

struct LoaiMon{
	char tenLoai[max][max];	
	int loai[max];
	
};

struct MonAn monAn;
struct LoaiMon loaiMon;
int SoMonAn; // TONG SO MON AN CO TRONG MENU
int SoLoaiMon; // TONG SO LOAI MON AN 
long Doanh_thu_cua_ngay = 0; // DOANH THU CUA NGAY
int So_Hoa_Don = 0; // SO DON DA BAN DUOC TRONG NGAY
char mdd[max], ngay[max];

char HoTen[max];
char soDT[max]; // Thong tin khach hang
char DiaChi[max];

/* Cac thong so khuyen mai */
long MucGiamGia;
int PhanTram;


/* 
	HAM DOC DU LIEU MENU, LOAI MON TAT CA CAC DU LIEU DUOC LUU VAO STRUCT MonAn, LoaiMon DE SU DUNG 
 	CHO CAC THAO TAC CUA CHUONG TRINH, CHINH SUA, THAY DOI DU LIEU, CUOI CHUONG TRINH SE DUOC LUU 
 	LAI SU DUNG CHO LAN SAU 
*/
void Doc_MENU();
void Doc_Loai_Mon();

/*
	HAM THAO TAC VOI DAT HANG VA IN HOA DON
*/
void In_MENU();
long Dat_Mon(FILE *f); /* THAO TAC DAT DO AN, TINH TOAN TRA VE GIA TRI CUA TONG HOA DON, 
				LUU TAT CA CAC THONG TIN CUA KHACH HANG VAO FILE HOA DON CUA NGAY HIEN TAI*/
void Xuat_Hoa_Don(char Dia_Chi_File_Hoa_Don[max], int vitri); /* XUAT HOA DON CUA KHACH HANH SAU KHI DAT HANG*/
long Ghi_Hoa_Don(char Dia_Chi_File_Hoa_Don[max]); /* THUC HIEN THAO TAC DAT_MON(), XUAT_HOA_DON()
				 VA LAY GIA TRI TRA VE CUA DAT_MON() CONG VAO TONG DOANH THU CUA NGAY*/
void Tat_Ca_Hoa_Don_Cua_Ngay(char Dia_Chi_File_Hoa_Don[max]); /* IN TAT CA THONG TIN CAC HOA DON TRONG NGAY*/

/*
	HAM THAO TAC DOANH THU TIM KIEM QUAN LY QUANH THU
*/
void In_Doanh_Thu(char Ngay[][15],  char MDD[][10], char Doanh_Thu[][15], int n); /* IN TAT CA NGAY, MA GIAO DICH, VA DOANH THU CUA NAGY DO*/
void Tim_Kiem_Ngay(char Ngay[][15], char Dia_Chi_File[][max], char Doanh_Thu[][15], int n); /* TIM KIEM VA IN TAT CA THONG TIN CAC HOA DON CUA NGAY DO */
void Doanh_Thu(char DiaChiGhiFile[max]); /* DOC DU LIEU CUA FILE DOANH THU PHAN TICH CAC DU LIEU DE THUC HIEN CAC THAO TAC In_Doanh_Thu(), Tim_Kiem_Ngay() */

/* 
	HAM THAO TAC VOI MON AN, THEM MON, XOA MON
*/
void Them_Mon();  /* THEM MON MOI VAO CUOI MANG SONG SONG*/
void Sap_Xep_MENU();  /* SAP XEP MON VUA THEM VAO VI TRI THICH HOP*/
void Xoa_Mon(); /* XOA MOT MON TRONG MENU*/
void Them_Xoa_Loai(); /*THEM XOA LOAI MON*/
void Chinh_Sua_Mon(); //Ghep 2 ham them xoa mon

/* 
	GHI DU LIEU TRO LAI VAO FILE MENU, FILE LOAI MON
*/
void Ghi_MENU();
void Ghi_Loai_Mon();

// check xem co ki tu trong chuoi hay khong
bool Check(char a[]);
void Doc_Giam_Gia();
void Sua_Doi();
void Ghi_Giam_Gia();


int main(){ //////////////////////////////////////////////////////////////////////////main
	Doc_MENU();
	Doc_Loai_Mon();
	Doc_Giam_Gia();
	
	printf("Bat dau ngay lam viec!!!\n");
	printf("Nhap ngay lam viec (vd: 01-01-2023): "); gets(ngay);
	printf("Nhap ma dao dich cua ngay lam viec de bat dau: "); gets(mdd);
	system("cls");
	
	char DiaChiFileHoaDon[max] = path_Hoa_Don;  // Duong dan den file hoa don
	
	strcat(DiaChiFileHoaDon, ngay);
	strcat(DiaChiFileHoaDon, "_Ma_giao_dich_");
	strcat(DiaChiFileHoaDon, mdd);
	strcat(DiaChiFileHoaDon, ".txt");
	
	char GhiDiaChiFile[max] = path_Hoa_Don_Dung_De_Ghi;  // Chuoi de ghi duong dan den file hoa don vao file Doanh thu
	
	strcat(GhiDiaChiFile, ngay);
	strcat(GhiDiaChiFile, "_Ma_giao_dich_");
	strcat(GhiDiaChiFile, mdd);
	strcat(GhiDiaChiFile, ".txt");
	
	char t1[10]; 
	char Mdd2[max];
	int t2;
	do{
		
		printf("Ma dao dich cua ngay: %s\n\n", mdd);
		printf("\tTiem An ONLINE Da Nang\n\n");
		if(PhanTram>0 ){
			
		printf("Giam gia %d %c Cho don hang lon hon %ld VND\n",PhanTram,37, MucGiamGia);
		}
		printf("1. Dat do an\n");
		printf("2. Xem tat ca cac hoa don trong ngay\n");
		printf("3. Xem tong doanh thu trong ngay\n");
		printf("4. Thao tac voi doanh thu\n");
		printf("5. Chinh sua mon\n");
		printf("6. Them hoac xoa loai\n");
		printf("7. Sua giam gia\n");
		printf("0. Thoat\n\n");
		printf("Nhap thoa tac:"); scanf("%s", &t1); fflush(stdin);
		while(!Check(t1)){
			printf("Thao tac khong hop le!!\n");
			printf("Nhap lai thao tac: "); gets(t1); fflush(stdin);
		}
		t2=atoi(t1);
		system("cls"); 
		switch(t2){
			case 1:
				Doanh_thu_cua_ngay += Ghi_Hoa_Don(DiaChiFileHoaDon); 
				break;
			case 2:
				Tat_Ca_Hoa_Don_Cua_Ngay(DiaChiFileHoaDon); 
				break;
			case 3:
				printf("Tong doanh thu hien tai trong ngay: %ld\n\n", Doanh_thu_cua_ngay); 
				system("pause");
				break;	
			case 4:
				Doanh_Thu(path_Dia_Chi_Doanh_Thu); 
				break;
			case 5:
				Chinh_Sua_Mon();
				break;
			case 6:
				Them_Xoa_Loai();
				break;
			case 7:
				Sua_Doi();
				break;
			case 0: 
				printf("Ma giao dich cua ngay: %s\n", mdd);
				printf("Nhap ma giao dich de thoat chuong trinh: ");
				fflush(stdin);
				gets(Mdd2);
				if(strcmp(Mdd2,mdd)!=0){
					printf("Ma giao dich khong dung!!!\n");
					system("pause");
					system("cls");
				}
				break;
			default:
				printf("Thao tac khong hop le!\n");
				printf("Moi ban chon lai!\n");
				system("pause");
				system("cls");
		}
		system("cls");
	}while(strcmp(Mdd2, mdd) != 0);
	
	FILE *h;
	h = fopen(path_Dia_Chi_Doanh_Thu, "a");
	fprintf(h, "%s %s %ld %s\n",ngay, mdd, Doanh_thu_cua_ngay, GhiDiaChiFile);
	fclose(h);
	
	Ghi_MENU();
	Ghi_Loai_Mon();
	Ghi_Giam_Gia();
}

void Doc_MENU(){
	FILE *f;
	f = fopen(path_Menu, "r");
	if(f == NULL){
		printf("khong doc duoc tep");
	}	
	char read[max];
	fgets(read,max,f);
	SoMonAn=atoi(read);
	int i=0;

	while(fgets(read,max,f)!=NULL){
		char *stt, *ten, *gia, *loai;
		stt = strtok(read, ":");
		ten = strtok(NULL, ":");
		gia = strtok(NULL, ":");	
		loai = strtok(NULL, ":");
		monAn.stt[i]=atoi(stt);
		strcpy(monAn.tenMon[i],ten);
		monAn.giaTien[i]=atoi(gia);
		monAn.loai[i]=atoi(loai);
		i++;
	}
	
	fclose(f);
}

void Doc_Loai_Mon(){
	FILE *f;
	f = fopen(path_Loai_Mon, "r");
	if(f == NULL){
		printf("khong doc duoc tep");
	}
	char read[max];
	fgets(read,max,f);
	SoLoaiMon=atoi(read);
	int i=0;
	while(fgets(read,max,f)!=NULL){
		char *stt, *tenloai;
		stt= strtok(read,":");
		tenloai= strtok(NULL,":");
		char *k = strstr(tenloai, "\n");  // xoa ki tu '\n' va thay vao la ki tu '\0'
		*k = '\0';
		loaiMon.loai[i]=atoi(stt);
		strcpy(loaiMon.tenLoai[i],tenloai);
		i++;
	}
	fclose(f);
}

void In_MENU(){
	int i, j, h, k = 60;
	for(h = 0; h <(k/2)-2; h++) printf("="); printf(" MENU "); for(h = 0; h <(k/2)-2; h++) printf("="); printf("\n");
	printf("| %7s | 		%-12s	 | %13s     |\n", "STT", "Mon an", "Gia");
	
	for(i = 0; i < SoLoaiMon; i++){
		printf("|"); for(h = 0; h < k; h++) printf("_"); printf("|\n");
		printf("|"); for(h = 0; h < k; h++) printf(" "); printf("|\n");
		printf("|                    %-40s|\n", loaiMon.tenLoai[i]);
		printf("|"); for(h = 0; h < k; h++) printf("_"); printf("|\n");
		for(j = 0; j < SoMonAn; j++){
			if(monAn.loai[j] == loaiMon.loai[i]){
				printf("| %7d |    %-25s | %10d  %4s  |\n", monAn.stt[j], monAn.tenMon[j], monAn.giaTien[j], "VND");
			}
		}
	}
	printf("|"); for(h = 0; h < k; h++) printf(" "); printf("|\n");
	for(h = 0; h <(k/2)-2; h++) printf("="); printf("******"); for(h = 0; h <(k/2)-2; h++) printf("="); printf("\n");
}

long Dat_Mon(FILE *f){

	fflush(stdin);
	printf("Nhap ho va ten: "); gets(HoTen); fflush(stdin);
	printf("Nhap so dien thoai: "); gets(soDT); fflush(stdin);
	// xet nhap so dt 
	int set;
	while(!Check(soDT)){
		printf("Thao tac khong hop le!!\n");
		printf("Nhap lai so dien thoai: "); gets(soDT); fflush(stdin);
	}
	
	printf("Nhap dia chi: "); gets(DiaChi); fflush(stdin);
	fprintf(f, "=%s:%s:%s\n", HoTen, soDT, DiaChi);
	++So_Hoa_Don;
	
	int count =  0; 
	int tongtien = 0;
	
	do{
		int tenMon, soLuong;
		char tenmon[max];
		char soluong[max];
		count++;
		
		printf("Chon mon tren Menu: "); gets(tenmon); fflush(stdin);
		tenMon = atoi(tenmon);
		while(!Check(tenmon) || tenMon < 0 || tenMon > SoMonAn){
			printf("Thao tac khong hop le!!\n");
			printf("Nhap lai chon mon: "); gets(tenmon); fflush(stdin);
			tenMon = atoi(tenmon);
		}
		
		printf("Ban da chon mon %s, hay chon so luong: ", monAn.tenMon[tenMon - 1]); gets(soluong); fflush(stdin);
		soLuong = atoi(soluong);
		while(!Check(soluong) || soLuong < 0){
			printf("Thao tac khong hop le!!\n");
			printf("Nhap lai chon so luong mon: "); gets(soluong); fflush(stdin);
			soLuong = atoi(soluong);
		}
		
		fprintf(f, "-%d:%s:%d:%d\n", count, monAn.tenMon[tenMon - 1], soLuong, soLuong * monAn.giaTien[tenMon - 1]);
		tongtien+=soLuong * monAn.giaTien[tenMon - 1];
		
		
		printf("Ban co mon chon mon tiep hay khong (1.co 0.khong): "); scanf("%d", &set); fflush(stdin);
		
	}while(set != 0);	
	
	if(tongtien > MucGiamGia ) tongtien= tongtien - tongtien*(1.0)*PhanTram/100;
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
	
	char DiaChiHoaDonKhachHang[max] = path_Hoa_Don_Cho_Khach;  // Duong dan den file hoa don cho khach hang
	
	strcat(DiaChiHoaDonKhachHang, ngay);
	strcat(DiaChiHoaDonKhachHang, "_");
	strcat(DiaChiHoaDonKhachHang, HoTen);
	strcat(DiaChiHoaDonKhachHang, "_");
	strcat(DiaChiHoaDonKhachHang, soDT);
	strcat(DiaChiHoaDonKhachHang, ".txt");
	
	
	FILE *f;
	f = fopen(Dia_Chi_File_Hoa_Don, "r");
	FILE *g;
	g = fopen(DiaChiHoaDonKhachHang, "w");
	
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
	
	int i, n = 60;
	for(i = 0; i < n; i++) printf("="); printf("\n");
	for(i = 0; i < n; i++) fprintf(g, "="); fprintf(g, "\n");
	
	printf("|"); for(i = 0; i < n/2-4; i++) printf(" "); printf("HOA DON"); for(i = 0; i < n/2-5; i++) printf(" "); printf("|\n");
	fprintf(g, "|"); for(i = 0; i < n/2-4; i++) fprintf(g, " "); fprintf(g, "HOA DON"); for(i = 0; i < n/2-5; i++) fprintf(g, " "); fprintf(g, "|\n");
	
	printf("|"); for(i = 0; i < n-2; i++) printf("="); printf("|\n");
	fprintf(g, "|"); for(i = 0; i < n-2; i++) fprintf(g, "="); fprintf(g, "|\n");
	
	printf("|	Ho ten khach hang: %-32s|\n", hoten+1);
	fprintf(g, "|	Ho ten khach hang: %-32s|\n", hoten+1);
	
	printf("|	So dien thoai: %-36s|\n", sdt);
	fprintf(g, "|	So dien thoai: %-36s|\n", sdt);
	
	char *k = strstr(diachi, "\n");  // xoa ki tu '\n' va thay vao la ki tu '\0'
	*k = '\0';
	
	printf("|	Dia chi: %-42s|\n", diachi);
	fprintf(g, "|	Dia chi: %-42s|\n", diachi);
	fgets(read, max, f);
	
	printf("|"); for(i = 0; i < n-2; i++) printf("="); printf("|\n");
	fprintf(g, "|"); for(i = 0; i < n-2; i++) fprintf(g, "="); fprintf(g, "|\n");
	
	printf("|"); for(i = 0; i < n-2; i++) printf(" "); printf("|\n");
	fprintf(g, "|"); for(i = 0; i < n-2; i++) fprintf(g, " "); fprintf(g, "|\n");
	
	printf("|%-3s | %-21s | %-8s | %-16s |\n", "STT", "ten mon", "so luong", "gia");
	fprintf(g, "|%-3s | %-21s | %-8s | %-16s |\n", "STT", "ten mon", "so luong", "gia");
	
	printf("|"); for(i = 0; i < n-2; i++) printf("-"); printf("|\n");
	fprintf(g, "|"); for(i = 0; i < n-2; i++) fprintf(g, "-"); fprintf(g, "|\n");
		
	do{
		char *stt, *tenMon, *soLuong, *gia;
		stt = strtok(read, ":");
		tenMon = strtok(NULL, ":");
		soLuong = strtok(NULL, ":");
		gia = strtok(NULL, ":");
		char *k = strstr(gia, "\n");  // xoa ki tu '\n' va thay vao la ki tu '\0'
		*k = '\0';
		printf("|%-3s | %-21s | %-8s | %-12s VND |\n", stt+1, tenMon, soLuong, gia);
		fprintf(g, "|%-3s | %-21s | %-8s | %-12s VND |\n", stt+1, tenMon, soLuong, gia);
		fgets(read, max, f);
	}while(read[0] != '+');
	printf("|"); for(i = 0; i < n-2; i++) printf("="); printf("|\n");
	fprintf(g, "|"); for(i = 0; i < n-2; i++) fprintf(g, "="); fprintf(g, "|\n");
	
	printf("|"); for(i = 0; i < n-2; i++) printf(" "); printf("|\n");
	fprintf(g, "|"); for(i = 0; i < n-2; i++) fprintf(g, " "); fprintf(g, "|\n");
	char *h = strstr(read, "\n");  // xoa ki tu '\n' va thay vao la ki tu '\0'
	*h = '\0';
	printf("|	Da giam gia %-3d %c				   |\n",PhanTram,37);
	fprintf(g, "|	Da giam gia %-3d %c				   |\n",PhanTram,37);
	printf("|    Tong so tien: %-10s  %-27s |\n", read+1, "VND");
	
	fprintf(g, "|    Tong so tien: %-10s  %-27s |\n", read+1, "VND");
	
	for(i = 0; i < n; i++) printf("="); printf("\n");
	for(i = 0; i < n; i++) fprintf(g, "="); fprintf(g, "\n");
	
	
	fclose(f);
	fclose(g);
}

void Tat_Ca_Hoa_Don_Cua_Ngay(char Dia_Chi_File_Hoa_Don[max]){
	FILE *f;
	f = fopen(Dia_Chi_File_Hoa_Don, "r");
	
	char read[max];
	int dem = 0;
	if(fgets(read, max, f) == NULL){
		printf("Chua co hoa don!!\n");
		system("pause");
		return;
	}
	printf("                       THONG TIN TAT CA CAC HOA DON");
		
	do{ 
		
		// Xuat Thong Tin
		char *hoten, *sdt, *diachi;
		hoten = strtok(read, ":");
		sdt = strtok(NULL, ":");
		diachi = strtok(NULL, ":");
		printf("\n\nThong tin khach hang thu %d:\n", ++dem);
		
		int i, n = 60;
		printf("|"); for(i = 0; i < n-2; i++) printf("="); printf("|\n");
		printf("|	Ho ten khach hang: %-32s|\n", hoten+1);
		printf("|	So dien thoai: %-36s|\n", sdt);
		char *k = strstr(diachi, "\n");  // xoa ki tu '\n' va thay vao la ki tu '\0'
		*k = '\0';
		printf("|	Dia chi: %-42s|\n", diachi);
		fgets(read, max, f);
	
		printf("|"); for(i = 0; i < n-2; i++) printf("="); printf("|\n");
		printf("|"); for(i = 0; i < n-2; i++) printf(" "); printf("|\n");
		printf("|%-3s | %-21s | %-8s | %-16s |\n", "STT", "ten mon", "so luong", "gia");
		printf("|"); for(i = 0; i < n-2; i++) printf("-"); printf("|\n");
	
		do{
			char *stt, *tenMon, *soLuong, *gia;
			stt = strtok(read, ":");
			tenMon = strtok(NULL, ":");
			soLuong = strtok(NULL, ":");
			gia = strtok(NULL, ":");
			char *k = strstr(gia, "\n");  // xoa ki tu '\n' va thay vao la ki tu '\0'
			*k = '\0';
			printf("|%-3s | %-21s | %-8s | %-12s VND |\n", stt+1, tenMon, soLuong, gia);
			fgets(read, max, f);
		}while(read[0] != '+');
		printf("|"); for(i = 0; i < n-2; i++) printf("="); printf("|\n");
		printf("|"); for(i = 0; i < n-2; i++) printf(" "); printf("|\n");
		char *h = strstr(read, "\n");  // xoa ki tu '\n' va thay vao la ki tu '\0'
		*h = '\0';
		printf("|    Tong so tien: %-10s  %-27s |\n", read+1, "VND");
		printf("|"); for(i = 0; i < n-2; i++) printf("="); printf("|\n");
	
	}while(fgets(read, max, f) != NULL);
	
	system("pause");
	system("cls");
	
	fclose(f);
}


void In_Doanh_Thu(char Ngay[][15],  char MDD[][10], char Doanh_Thu[][15], int n){
	system("cls");
	int i;
	printf("======================= TONG DOANH THU ====================\n");
	printf("Ngay\t\t\t Ma giao dich\t\t Doanh thu\n");
	for(i = 0; i < n; i++){
		printf("%-25s%-24s%s\n", Ngay[i], MDD[i], Doanh_Thu[i]);
	}
	
	system("pause");
	system("cls");
}

void Tim_Kiem_Ngay(char Ngay[][15], char Dia_Chi_File[][max], char Doanh_Thu[][15], int n){
	system("cls");
	char ngay[15];
	printf("Nhap ngay: "); 
	fflush(stdin);
	scanf("%s", &ngay);
	system("cls");
	
	int i, set = 0;
	
	for(i = 0; i < n; i++){
		if(strcmp(Ngay[i], ngay) == 0){
			set = 1;
			char dia_chi[max];
			strcpy(dia_chi, Dia_Chi_File[i]);
			char *h = strstr(dia_chi, "\n");  // xoa ki tu '\n' va thay vao la ki tu '\0'
			*h = '\0';
			printf("\nTONG DOANH THU: %s\n\n", Doanh_Thu[i]);
			Tat_Ca_Hoa_Don_Cua_Ngay(dia_chi);
			break;
		}
	}
	if(set == 0){
		printf("Khong tim thay ngay da nhap !!\n");
		system("pause");
	}
	system("cls");
}

void Doanh_Thu(char DiaChiGhiFile[max]){
	int count = 0;
	char Doc[max];
	char Ngay[max*30][15];
	char MDD[max*30][10];
	char Doanh_Thu[max*30][15];
	char Dia_Chi_File[max*30][max];
	
	FILE *k;
	k = fopen(DiaChiGhiFile, "r");
	while(fgets(Doc, max, k) != NULL){ // TACH CAC SO LIEU NHU (NGAY LAM VIEC, MA GIAO DICH, DOANH THU CUA NGAY) DE THUC HIEN CAC THAO TAC KHAC
		char * p;
		p = strtok(Doc, " ");
		strcpy(Ngay[count], p);
    	p = strtok(NULL, " ");
		strcpy(MDD[count], p);
		p = strtok(NULL, " ");
		strcpy(Doanh_Thu[count], p);
		p = strtok(NULL, " ");
		strcpy(Dia_Chi_File[count], p);
		count++;
	} 
	fclose(k);
	
	char key[10];
	int key2;
	
	do{
		printf("1. In tat ca doanh thu\n");
		printf("2. In tat ca hoa don cua ngay\n"); 
		printf("0. Thoat\n");
		printf("Nhap thoa tac:"); scanf("%s", &key); fflush(stdin);
		while(!Check(key)){
		printf("Thao tac khong hop le!!\n");
		
		printf("Nhap lai thao tac: "); gets(key); fflush(stdin);
		}
		key2=atoi(key);
		switch(key2){
			case 1:
				In_Doanh_Thu(Ngay, MDD, Doanh_Thu, count);
				break;
			case 2:
				Tim_Kiem_Ngay(Ngay, Dia_Chi_File, Doanh_Thu, count);
				break;
			
			case 0: 
				system("cls");
				break;
			default:
				printf("Thao tac khong hop le!!\n");
				system("pause");
				system("cls");
		}
	}while(key2 != 0);
}

void Sap_Xep_MENU(){
	int i, set = 0;
	
	char ten[max]; strcpy(ten, monAn.tenMon[SoMonAn-1]);
	int stt = monAn.stt[SoMonAn-1];
	int gia = monAn.giaTien[SoMonAn-1];
	int loai = monAn.loai[SoMonAn-1];
	
	for(i = SoMonAn-1; i >= 0; i--){
		if(loai >= monAn.loai[i-1]){
			strcpy(monAn.tenMon[i], ten);
			monAn.stt[i] = i+1;
			monAn.giaTien[i] = gia;
			monAn.loai[i] = loai;
			break;
		}
		strcpy(monAn.tenMon[i], monAn.tenMon[i-1]);
		monAn.stt[i] = i+1;
		monAn.giaTien[i] = monAn.giaTien[i-1];
		monAn.loai[i] = monAn.loai[i-1];
	}
}

void Them_Mon(){
	
	int i,set;
	printf("Cac loai mon:\n");
	for(i = 0; i < SoLoaiMon; i++){
		printf("\t%d. %s\n", loaiMon.loai[i], loaiMon.tenLoai[i]);
	}
	printf("Nhap loai mon:");
	int loai;
	scanf("%d",&loai);
	if(loai <= 0 || loai > SoLoaiMon){
		printf("Thao tac khong hop le!\n");
		system("pause");
		return;
	}
	else{
		char GiaTien[max];
		monAn.loai[SoMonAn] = loai;
		monAn.stt[SoMonAn]=1+SoMonAn;
		printf("Nhap ten mon: ");
		fflush(stdin);
		gets(monAn.tenMon[SoMonAn]);
		fflush(stdin);
		printf("Nhap gia: "); gets(GiaTien); fflush(stdin);
		monAn.giaTien[SoMonAn] = atoi(GiaTien);
		while(!Check(GiaTien) || monAn.giaTien[SoMonAn] < 0){
			printf("Thao tac khong hop le!!\n");
			printf("Nhap lai gia tien cho mon: "); gets(GiaTien); fflush(stdin);
			monAn.giaTien[SoMonAn] = atoi(GiaTien);
		}
	}
	
	SoMonAn++;
	
	Sap_Xep_MENU();
	system("cls");
	In_MENU();
	system("pause");
}

void Xoa_Mon(){
	In_MENU();
	
	char ViTri[5];
	int i, vitri, set = 0;
	printf("Nhap vi tri mon muon xoa: "); gets(ViTri); fflush(stdin);
	vitri = atoi(ViTri);
	if(!Check(ViTri) || vitri <= 0 || vitri > SoMonAn){
		printf("Thoa tac khong hop le!\n");
		system("pause");
		return;
	}
	for(i = 0; i < SoMonAn-1; i++){
		if(i >= vitri-1){
			strcpy(monAn.tenMon[i], monAn.tenMon[i+1]);
			monAn.stt[i] = i+1;
			monAn.giaTien[i] = monAn.giaTien[i+1];
			monAn.loai[i] = monAn.loai[i+1];
		}
	
	}
	SoMonAn--;
	
	In_MENU();
	system("pause");
}
void Chinh_Sua_Mon(){
	char a[10];
	int a1;
	printf("1. Them mon\n");
	printf("2. Xoa mon\n");
	printf("0. Thoat\n");
	printf("Nhap thao tac: ");
	gets(a); fflush(stdin);
	while(!Check(a)){
		printf("Thao tac khong hop le \n");
		printf("Nhap lai thao tac: "); gets(a); fflush(stdin);
	}
	a1=atoi(a);
	switch(a1){
		case 1: 
			system("cls");
			Them_Mon();
			break;
		case 2:
			system("cls");
			Xoa_Mon();
			break;
		case 0:
			break;
		default:
			printf("Khong hop le\n");
			system("pause");
			break;
	}
}

void Them_Xoa_Loai(){
	int i,vitri,key2;
	char key[10], ViTri[4];
	printf("1.Them loai.\n");
	printf("2.Xoa loai.\n");
	printf("0.Thoat.\n");
	printf("Nhap thao tac: ");
	scanf("%s",&key); fflush(stdin);
	while(!Check(key)){
		printf("Thao tac khong hop le!!\n");
		printf("Nhap lai thao tac: "); gets(key); fflush(stdin);
	}
	key2=atoi(key);
	switch(key2){
		case 1:
			system("cls");
			printf("So loai mon hien tai: %d\n",SoLoaiMon);
			printf("Cac loai mon:\n");
			for(i = 0; i < SoLoaiMon; i++){
				printf("\t%d. %s\n", loaiMon.loai[i], loaiMon.tenLoai[i]);
			}
			loaiMon.loai[SoLoaiMon]=1+SoLoaiMon;
			printf("Nhap ten loai mon can them:(Nhap 0 de thoat) "); 
			fflush(stdin);
			gets(loaiMon.tenLoai[SoLoaiMon]);
			if(strcmp(loaiMon.tenLoai[SoLoaiMon], "0") == 0) break;
			SoLoaiMon++;
			break;
		case 2:
			system("cls");
			printf("So loai mon hien tai: %d\n",SoLoaiMon);
			printf("Cac loai mon:\n");
			for(i = 0; i < SoLoaiMon; i++){
				printf("\t%d. %s\n", loaiMon.loai[i], loaiMon.tenLoai[i]);
				}
			printf("Nhap vi tri muon xoa:"); gets(ViTri); fflush(stdin);
			vitri = atoi(ViTri);
			if(!Check(ViTri) || vitri<=0 || vitri>SoLoaiMon){
				printf("Thao tac khong hop le!\n");
				system("pause");
				break;
			}

			for(i=0; i < SoLoaiMon;i++ ){
				if(i >= vitri-1){
					loaiMon.loai[i] = i+1;
					strcpy(loaiMon.tenLoai[i], loaiMon.tenLoai[i+1]);
				}
			}
			SoLoaiMon--;
			// 	BO XUNG PHAN XOA MON
			int count = 0;
			// Tim so mon can xoa (count), va vi tri can xoa tai vi tri i
			for(i = SoMonAn - 1; i >= 0; i--){
				if(monAn.loai[i] > vitri) continue;
				else if(monAn.loai[i] == vitri){
					++count;
					continue;
				}
				else if (monAn.loai[i] < vitri){
					++i;
					break;
				}
			}
			// Bat dau xoa mon 
			for(; i < SoMonAn; i++){
				strcpy(monAn.tenMon[i], monAn.tenMon[i + count]);
				monAn.loai[i] = monAn.loai[i + count] - 1;
				monAn.giaTien[i] = monAn.giaTien[i + count];
			}
			SoMonAn -= count;
			
			In_MENU();
			system("pause");
			break;
		case 0:
			break;
		default:
			printf("Thao tac khong hop le!");
			system("pause");
			break;

	}
}
void Ghi_MENU(){
	FILE *f;
	f = fopen(path_Menu, "w");
	fprintf(f, "%d\n", SoMonAn);
	int i;
	for(i = 0; i < SoMonAn; i++){
		fprintf(f, "%d:%s:%d:%d\n", monAn.stt[i], monAn.tenMon[i], monAn.giaTien[i], monAn.loai[i]);
	}
	fclose(f);
}

void Ghi_Loai_Mon(){
	FILE *f;
	f = fopen(path_Loai_Mon, "w");
	fprintf(f,"%d\n",SoLoaiMon);
	int i;
	for(i = 0; i < SoLoaiMon; i++){
		fprintf(f, "%d:%s\n",loaiMon.loai[i],loaiMon.tenLoai[i] );
	}
}

bool Check(char a[]){
	int i;
	for(i = 0; i < strlen(a); i++){
		if(a[i] < '0' || a[i] > '9') return false;
	}
	if(strlen(a)==0) return false;
	return true;
}
void Doc_Giam_Gia(){
	FILE *f;
	f=fopen(path_Giam_Gia,"r");
	fscanf(f,"%ld",&MucGiamGia);
	fscanf(f,"%d",&PhanTram);
	fclose(f);
	}
void Sua_Doi(){
	char Mucgiamgia[10], Phantram[10];
	int Mucgiamgia1, Phantram1;
	printf("Muc giam gia cu la: ");
	printf("Muc giam: %ld\tPhan tram giam: %d%\n",MucGiamGia,PhanTram);
	printf("Muc giam gia muon sua: ");
	gets(Mucgiamgia); fflush(stdin);
	while(!Check(Mucgiamgia)){
			printf("NHap khong hop le!!\n");
			printf("Nhap lai thao tac: "); gets(Mucgiamgia); fflush(stdin);
		}
		Mucgiamgia1=atoi(Mucgiamgia);
	printf("Pham tram giam gia muon sua: ");
	gets(Phantram);
	while(!Check(Phantram)){
			printf("Nhap khong hop le!!\n");
			printf("Nhap lai thao tac: "); gets(Phantram); fflush(stdin);
		}
		Phantram1=atoi(Phantram);
	fflush(stdin);
	MucGiamGia = Mucgiamgia1;
	PhanTram = Phantram1;
	
}
void Ghi_Giam_Gia(){
	FILE *f;
	f=fopen(path_Giam_Gia,"w");
	fprintf(f, "%ld %d", MucGiamGia, PhanTram);
	fclose(f);
	}
	

