#include <stdio.h>
#include <string.h>
#define max 100
#define path_Menu "D:\\C\\PBBL1\\Menu.txt"  // Duong dan den file menu
#define path_Loai_Mon "D:\\C\\PBBL1\\LoaiMon.txt"  // Duong dan den file phan loai mon an
#define path_Hoa_Don "D:\\C\\PBBL1\\HoaDon\\"  // Duong dan den file luu hoa don
#define path_Hoa_Don_Dung_De_Ghi "D:\\\\C\\\\PBBL1\\\\HoaDon\\\\" // Su dung chuoi nay de ghi vao file Doanh thu, luu y "\\\\"
#define path_Dia_Chi_Doanh_Thu "D:\\C\\PBBL1\\Doanh_Thu\\Doanh_Thu.txt"  // Duong dan den file luu doanh thu

struct MonAn{
	char tenMon[max][max];
	int stt[max];
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

// HAM DOC DU LIEU MENU, LOAI MON
void Doc_MENU();
void Doc_Loai_Mon();

// HAM THAO TAC VOI DAT HANG VA IN HOA DON
void In_MENU();
long Dat_Mon(FILE *f);
long Ghi_Hoa_Don(char Dia_Chi_File_Hoa_Don[max]);
void Xuat_Hoa_Don(char Dia_Chi_File_Hoa_Don[max], int vitri);
void Tat_Ca_Hoa_Don_Cua_Ngay(char Dia_Chi_File_Hoa_Don[max]);

// HAM THAO TAC DOANH THU TIM KIEM QUAN LY QUANH THU
void In_Doanh_Thu(char Ngay[][15],  char MDD[][10], char Doanh_Thu[][15], int n);
void Tim_Kiem_Ngay(char Ngay[][15], char Dia_Chi_File[][max], char Doanh_Thu[][15], int n);
void Doanh_Thu(char DiaChiGhiFile[max]);

// HAM THAO TAC VOI MON AN, THEM MON, XOA MON
void Them_Mon();
void Sap_Xep_MENU();
void Xoa_Mon();
void ThemXoa_Loai();


int main(){ //////////////////////////////////////////////////////////////////////////main
	Doc_MENU();
	Doc_Loai_Mon();
	
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
	
	int t1; 
	char Mdd2[max];
	
	do{
		
		printf("Ma dao dich cua ngay: %s\n", mdd);
		printf("1. Dat do an\n");
		printf("2. Xem tat ca cac hoa don trong ngay\n");
		printf("3. Xem tong doanh thu trong ngay\n");
		printf("4. Thao tac voi doanh thu\n");
		printf("5. Them mon\n");
		printf("6. Xoa mon\n");
		printf("7. Them or xoa loai\n");
		printf("0. Thoat\n");
		printf("Nhap thoa tac:"); scanf("%d", &t1);
		system("cls"); 
		switch(t1){
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
				Them_Mon();
				break;
			case 6:
				Xoa_Mon();
				break;
			case 7:
				ThemXoa_Loai();
				break;
			case 0: 
				printf("Nhap ma giao dich: ");
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
	
}

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


void In_MENU(){
	int i, j;

	printf("=================== MENU ====================\n");
	for(i = 0; i < SoLoaiMon; i++){
		printf("\n\t%s\n", loaiMon.tenLoai[i]);
		for(j = 0; j < SoMonAn; j++){
			if(monAn.loai[j] == loaiMon.loai[i]){
				printf("%d.%-20s%-7dVND\n", monAn.stt[j], monAn.tenMon[j], monAn.giaTien[j]);
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
	
	char k;
	printf("Nhan phim ENTER de tiep tuc!!");
	fflush(stdin);
	scanf("%c", &k);
	system("cls");
}

void Tim_Kiem_Ngay(char Ngay[][15], char Dia_Chi_File[][max], char Doanh_Thu[][15], int n){
	system("cls");
	char ngay[15];
	printf("Nhap ngay: "); 
	fflush(stdin);
	scanf("%s", &ngay);
	system("cls");
	
	int i,j=0;
	
	for(i = 0; i < n; i++){
		if(strcmp(Ngay[i], ngay) == 0){
			char a[max];
			while(1 == 1){
				
				if(Dia_Chi_File[i][j] == '\n'){
					a[j] = '\0';
					break;
				}
				a[j] = Dia_Chi_File[i][j];
				j++;
			}
			printf("\nTONG DOANH THU: %s\n\n", Doanh_Thu[i]);
			Tat_Ca_Hoa_Don_Cua_Ngay(a);
			
			break;
			
	
		}
	}
	system("cls");
}

void Doanh_Thu(char DiaChiGhiFile[max]){
	int count = 0;
	char Doc[max];
	char Ngay[1000][15];
	char MDD[1000][10];
	char Doanh_Thu[1000][15];
	char Dia_Chi_File[1000][max];
	
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
	
	int t; 
	
	do{
		printf("1. In tat ca doanh thu\n");
		printf("2. In tat ca hoa don cua ngay\n"); 
		printf("0. Thoat\n");
		printf("Nhap thoa tac:"); scanf("%d", &t);
		 
		switch(t){
			case 1:
				In_Doanh_Thu(Ngay, MDD, Doanh_Thu, count);
				break;
			case 2:
				Tim_Kiem_Ngay(Ngay, Dia_Chi_File, Doanh_Thu, count);
				break;
			
			case 0: 
				system("cls");
				break;
		}
	}while(t != 0);
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
	
	int i;
	printf("Cac loai mon:\n");
	for(i = 0; i < SoLoaiMon; i++){
		printf("\t%d.\t%s\n", loaiMon.loai[i], loaiMon.tenLoai[i]);
	}
	
	printf("Nhap loai mon:");
	scanf("%d",&monAn.loai[SoMonAn]);
	monAn.stt[SoMonAn]=1+SoMonAn;
	printf("Nhap ten mon: ");
	fflush(stdin);
	gets(monAn.tenMon[SoMonAn]);
	fflush(stdin);
	printf("Nhap gia: ");
	scanf("%d", &monAn.giaTien[SoMonAn]);
	
	SoMonAn++;
	
	Sap_Xep_MENU();
	
	FILE *f;
	f = fopen(path_Menu, "w");
	fprintf(f, "%d\n", SoMonAn);
	for(i = 0; i < SoMonAn; i++){
		fprintf(f, "%d %s %d %d\n", monAn.stt[i], monAn.tenMon[i], monAn.giaTien[i], monAn.loai[i]);
	}
	fclose(f);
	
	In_MENU();
	system("pause");
}

void Xoa_Mon(){
	In_MENU();
	
	int i, vitri, set = 0;
	printf("Nhap vi tri mon muon xoa: ");
	scanf("%d", &vitri);
	
	FILE *f;
	f = fopen(path_Menu, "w");
	fprintf(f, "%d\n", SoMonAn-1);
	for(i = 0; i < SoMonAn-1; i++){
		if(i >= vitri-1){
			strcpy(monAn.tenMon[i], monAn.tenMon[i+1]);
			monAn.stt[i] = i+1;
			monAn.giaTien[i] = monAn.giaTien[i+1];
			monAn.loai[i] = monAn.loai[i+1];
			fprintf(f, "%d %s %d %d\n", monAn.stt[i], monAn.tenMon[i], monAn.giaTien[i], monAn.loai[i]);
		}
		else{
			fprintf(f, "%d %s %d %d\n", monAn.stt[i], monAn.tenMon[i], monAn.giaTien[i], monAn.loai[i]);
		}
	}
	SoMonAn--;
	In_MENU();
	system("pause");
	fclose(f);
}

void ThemXoa_Loai(){
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
	int key, vitri;
	printf("1.Them loai.\n");
	printf("2.Xoa loai.\n");
	printf("Nhap thao tac: ");
	scanf("%d",&key);
	switch(key){
		case 1:
			printf("So loai mon hien tai: %d\n",SoLoaiMon);
			printf("Cac loai mon:\n");
			for(i = 0; i < SoLoaiMon; i++){
			printf("\t%d.\t%s\n", loaiMon.loai[i], loaiMon.tenLoai[i]);
			}
			loaiMon.loai[SoLoaiMon]=1+SoLoaiMon;
			printf("Nhap ten loai mon can them: ");
			fflush(stdin);
			gets(loaiMon.tenLoai[SoLoaiMon]);
			SoLoaiMon++;
			
			f = fopen(path_Loai_Mon, "w");
			fprintf(f,"%d\n",SoLoaiMon);
			for(i = 0; i < SoLoaiMon; i++){
				fprintf(f, "%d %s\n",loaiMon.loai[i],loaiMon.tenLoai[i] );
			}	
		break;
		case 2:
			printf("So loai mon hien tai: %d\n",SoLoaiMon);
			printf("Cac loai mon:\n");
			for(i = 0; i < SoLoaiMon; i++){
				printf("\t%d.\t%s\n", loaiMon.loai[i], loaiMon.tenLoai[i]);
				}
			printf("Nhap vi tri muon xoa:");
			scanf("%d",&vitri);
			if(vitri<=0 || vitri>SoLoaiMon){
				printf("Thao tac khong hop le!");
				system("pause");
				break;
				}
			
			f = fopen(path_Loai_Mon, "w");
			fprintf(f,"%d\n", SoLoaiMon-1);
			for(i=0; i < SoLoaiMon-1;i++ ){
				if(i>= vitri-1){
				loaiMon.loai[i] = i+1;
				strcpy(loaiMon.tenLoai[i], loaiMon.tenLoai[i+1]);
				fprintf(f, "%d %s\n", loaiMon.loai[i], loaiMon.tenLoai[i]);
			}
			else{
				fprintf(f, "%d %s\n", loaiMon.loai[i], loaiMon.tenLoai[i]);
			}
		}
	}
	fclose(f);
}
