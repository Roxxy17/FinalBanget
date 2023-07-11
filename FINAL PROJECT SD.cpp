#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <queue>
using namespace std;

const int MAX_BOOKS = 3; // Jumlah maksimum buku dalam satu dataPerpus

string user_akun[10] = {"kalila", "ozii"};
string user_jurusan[10] = {"Informatika 09" , "Informatika 07"};
string user_nim[10] = {"22.11.5115", "22.11.5132"};

int jumlah_akun = 2;

int pilih_menu(), cariakun(string nama);
void tambah_akun(), lihat_akun(), sortakun(), masuk(), peminjaman(), input_buku(), lihat_peminjaman(), lihat_buku(), edit_buku();

struct tanggal {
	int day, month, year;
};

struct book {
    string title;
    string author;
    string publisher;
    string year;
    string id;
};

struct peminjam{
	string nama;
	string nim;
	string jurusan;
};

struct dataPerpus {
    book books[MAX_BOOKS];
    
};

struct peminjam pnjm;
struct tanggal pjm, bck, jt;
struct dataPerpus dt;

const string FILENAME = "data_buku.txt";

int main(){
	//Judul homepage
    cout<<endl;
    cout<<"|====================================================================================================================|"<<endl;
    cout<<"|  ----------------------------------- AMIKOM YOGYAKARTA LIBRARY DIGITAL SYSTEM -----------------------------------  |"<<endl;
    cout<<"|  ------------------------------------------                             -----------------------------------------  |"<<endl;
    cout<<"|  ------Simple programming application that use for store new book and lending books to customers in library------  |"<<endl;
    cout<<"|====================================================================================================================|"<<endl;
    cout<<endl;
    cout<<endl;

	int menu; 
	do {
		cout<<"|====================================================================================================================|"<<endl;
    	cout<<"|  ------------------------------------------- AMIKOM YOGYAKARTA LIBRARY ------------------------------------------  |"<<endl;
    	cout<<"|  --------------------------------------------       OPTION MENU      --------------------------------------------  |"<<endl;
    	cout<<"|====================================================================================================================|"<<endl;

		cout << "Buat akun baru atau masuk : " << endl;
		cout << "1. Buat Akun " << endl;
		cout << "2. Masuk" << endl;
		cout << "3. Input Buku" << endl;
		cout << "4. Edit Buku" << endl;
		cout << "5. Lihat tampilan buku" << endl;
		cout << "6. Lihat User" << endl;
		cout << "7. Lihat Peminjaman" << endl;
		cout << "8. Keluar " << endl; 
		cout << "Pilih [1/2/3/4/5/6/7/8] : ";
		cin >> menu;

		
		if (menu== 1){
			tambah_akun();
		}
		else if (menu==2)
		{
		  	system ("cls");
		 	masuk();
		}
		else if (menu==3)
		{
		 	system("cls");
            input_buku();
		}
		else if (menu==4)
		{
		  	system("cls");
            edit_buku();
		}
		else if (menu==5)
		{
		  system ("cls");
		  lihat_buku();
		}
		else if (menu==6)
		{
	       system ("cls");
		   lihat_akun();
		}
		else if (menu==7)
		{
	      system ("cls");
          lihat_peminjaman();
		}
		else if (menu==8)
		{
	      cout << "Program telah dihentikan" << endl;
		}
		else
		{
		  cout << "Pilihan Tidak Ditemukan" << endl;
		  system("cls");
		}
	} while (menu != 8); 

}

void masuk(){
	string nama;
    string nim;
    int urutan_akun = -1;
    
    lihat_akun();
    
    do{
        cout << "Masukan Nama Kamu : ";
    	cin >> pnjm.nama;
    	cout << "Masukan Jurusan kamu : ";
    	cin >> pnjm.jurusan;
    	cout << "Masukan NIM kamu : ";
    	cin >> pnjm.nim;
        
        urutan_akun = cariakun(pnjm.nama);
        
        if(urutan_akun == -1){
            cout << "Nama pengguna tidak ditemukan, coba lagi!" << endl;
        }else if(user_nim[urutan_akun] != pnjm.nim){
            cout << "NIM tidak sesuai, coba lagi!" << endl;
            urutan_akun = -1;
        }else{
            // Lanjut ke fitur berikutnya
            peminjaman();
        }
    }while(urutan_akun == -1);
	
}

void lihat_akun(){
	//tampilan Data Pengunjung
    cout<< "Data Pengunjung Amikom Library sampai hari ini: "<<endl;
    	for (int i = 0; i < jumlah_akun; i++) { 
            cout << (i+1) << " " << ".";
			cout << "DATA PENGUNJUNG KE "<<(i+1)<<":"<<endl;
            cout <<endl;
            cout << (1) << "." << "Nama Pengujung Perpustakaan         	: " << user_akun[i]<<endl;
            cout << (2) << "." << "Jurusan           					: " << user_jurusan[i]<<endl;
            cout << (3) << "." << "NIM Pengunjung					  	: " << user_nim[i]<<endl;

            cout << endl;
	}
}

void tambah_akun(){
    if (jumlah_akun < 100) {
        cout << "Masukan Nama Kamu : ";
        cin >> user_akun[jumlah_akun];
        cout << "Masukan Jurusan kamu : ";
        cin >> user_jurusan[jumlah_akun];
        cout << "Masukan NIM kamu : ";
        cin >> user_nim[jumlah_akun];

        cout << "Membuat akun sukses" << endl;

        jumlah_akun++;

        sortakun();
        system("cls");
    } else {
        cout << "Kapasitas akun penuh" << endl;
    }
}

void sortakun() {
    int i, j, lokasi_min;
    string temp_nama, temp_jurusan, temp_nim;

    for (i = 0; i < jumlah_akun - 1; i++) {
        lokasi_min = i;
        for (j = i + 1; j < jumlah_akun; j++) {
            if (user_akun[j] < user_akun[lokasi_min]) {
                lokasi_min = j;
            }
        }

        temp_nama = user_akun[i];
        temp_jurusan = user_jurusan[i];
        temp_nim = user_nim[i];

        user_akun[i] = user_akun[lokasi_min];
        user_jurusan[i] = user_jurusan[lokasi_min];
        user_nim[i] = user_nim[lokasi_min];

        user_akun[lokasi_min] = temp_nama;
        user_jurusan[lokasi_min] = temp_jurusan;
        user_nim[lokasi_min] = temp_nim;
    }
}

int cariakun(string nama) {
    int lo = 0, hi = jumlah_akun - 1;
    int mid;

    while (hi >= lo) {
        mid = (hi + lo) / 2;
        if (user_akun[mid] == nama) {
            return mid;
        } else if (user_akun[mid] < nama) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return -1;
}

void input_buku() {
    int jumlah_buku;

    cout << "Masukkan jumlah buku yang ingin diinput: ";
    cin >> jumlah_buku;

    cin.ignore(); // Ignore newline character

    ofstream file;
    file.open(FILENAME, ios::app); // Open the file in append mode

    cout << "\n== Masukkan Detail Buku ==\n";

    for (int i = 0; i < jumlah_buku; i++) {
        book buku;

        cout << "\nData Buku ke-" << (i + 1) << endl;

        cout << "Judul Buku: ";
        getline(cin, buku.title);

        cout << "Pengarang: ";
        getline(cin, buku.author);

        cout << "Penerbit: ";
        getline(cin, buku.publisher);

        cout << "Tahun Terbit: ";
        getline(cin, buku.year);
        
        cout << "\n ID Buku\t:";
        getline(cin, buku.id);

        // Generate ID buku secara otomatis berdasarkan urutan buku yang diinput
        buku.id = "B" + to_string(i + 1);

        file << buku.title << "|" << buku.author << "|" << buku.publisher << "|" << buku.year << "|" << buku.id << "|" << endl;
    }

    file.close();

    cout << "\nInput buku selesai.\n";
}


void edit_buku() {
    string searchID;
    bool found = false;

    cout << "Masukkan ID Buku yang ingin diedit: ";
    cin.ignore();
    getline(cin, searchID);

    ifstream file(FILENAME);
    ofstream temp("temp.txt");

    if (file.is_open() && temp.is_open()) {
        string line;

        while (getline(file, line)) {
            size_t pos = 0;
            string token;
            int tokenIndex = 0;
            book buku;

            while ((pos = line.find("|")) != string::npos) {
                token = line.substr(0, pos);

                switch (tokenIndex) {
                    case 0:
                        buku.title = token;
                        break;
                    case 1:
                        buku.author = token;
                        break;
                    case 2:
                        buku.publisher = token;
                        break;
                    case 3:
                        buku.year = token;
                        break;
                    case 4:
                        buku.id = token;
                        break;
                }

                line.erase(0, pos + 1);
                tokenIndex++;
            }

            // Jika ID buku ditemukan, buku ditemukan
            if (buku.id == searchID) {
                found = true;

                cout << "\nBuku dengan ID " << searchID << " ditemukan. Silakan masukkan detail baru:" << endl;

                cout << "Judul Buku: ";
                getline(cin, buku.title);

                cout << "Pengarang: ";
                getline(cin, buku.author);

                cout << "Penerbit: ";
                getline(cin, buku.publisher);

                cout << "Tahun Terbit: ";
                getline(cin, buku.year);
                
                cout << "\n ID Buku\t:";
       			getline(cin, buku.id);
            }

            temp << buku.title << "|" << buku.author << "|" << buku.publisher << "|" << buku.year << "|" << buku.id << "|" << endl;
        }

        file.close();
        temp.close();

        remove(FILENAME.c_str());
        rename("temp.txt", FILENAME.c_str());

        if (!found) {
            cout << "Buku dengan ID " << searchID << " tidak ditemukan." << endl;
        } else {
            cout << "Buku berhasil diubah." << endl;
        }
    } else {
        cout << "File tidak dapat dibuka." << endl;
    }
}

void peminjaman() {
    int byk;
    while (1) {
        cout << "\n Banyak peminjaman buku: ";
        cin >> byk;
        if (byk > 3) {
            cout << "\n --- MAXIMAL PEMINJAMAN 2 BUKU ---";
        } else {
            break;
        }
    }
	
	system("cls");
	lihat_buku();
	cout<<"============================="<<endl;
	cout<<"	INPUT DATA PEMINJAMAN BUKU	"<<endl;
	cout<<"============================="<<endl;
	
	
	
	cin.ignore(); // Menambahkan cin.ignore() untuk mengabaikan newline character
	
	for (int a = 1; a <= byk; a++) {	
		cout << "\n data buku ke " << a;
		cout << "\n judul buku\t:";
        cin.ignore();
        getline(cin, dt.books[a].title);

        cout << "\n pengarang\t:";
        getline(cin, dt.books[a].author);

        cout << "\n penerbit\t:";
        getline(cin, dt.books[a].publisher);

        cout << "\n Tahun Terbit\t:";
        getline(cin, dt.books[a].year);

        cout << "\n ID Buku\t:";
        getline(cin, dt.books[a].id);


		ifstream file(FILENAME);
        ofstream temp("temp.txt");
        bool bukuTersedia = false;

        if (file.is_open() && temp.is_open()) {
            string line;

            while (getline(file, line)) {
                size_t pos = 0;
                string token;
                int tokenIndex = 0;
                book books;

                while ((pos = line.find("|")) != string::npos) {
                    token = line.substr(0, pos);

                    switch (tokenIndex) {
                        case 0:
                            books.title = token;
                            break;
                        case 1:
                            books.author = token;
                            break;
                        case 2:
                            books.publisher = token;
                            break;
                        case 3:
                            books.year = token;
                            break;
                        case 4:
                            books.id = token;
                            break;
                    }

                    line.erase(0, pos + 1);
                    tokenIndex++;
                }

                if (bukuTersedia) {
                    cout << "\nBuku dengan ID " << dt.books[a].id << " berhasil dipinjam." << endl;
                } else {
                    cout << "\nBuku dengan ID " << dt.books[a].id << " tidak tersedia." << endl;
                    continue;  // Lanjutkan ke iterasi berikutnya jika buku tidak tersedia
                }

            }

            file.close();
            temp.close();

            remove(FILENAME.c_str());
            rename("temp.txt", FILENAME.c_str());
        } else {
            cout << "File tidak dapat dibuka." << endl;
        }
        
	}
		system("cls");
	
	cout<<"\n tanggal pinjam: \n";
	while(1){
		cout<<"tanggal [1 - 30]\t: "; cin>>pjm.day;
		if(pjm.day<=0||pjm.day>30){
			cout<<" ERROR ...!\n";
		}else{break;}
	}
	
	cout<<"\n bulan pinjam: \n";
	while(1){
		cout<<"bulan [1 - 12]\t: "; cin>>pjm.month;
		if(pjm.month<=0||pjm.month>12){
			cout<<" ERROR ...!\n";
		}else{break;}
	}
	
	cout<<"\n tahun pinjam: \n";
	while(1){
		cout<<"tahun [yyyy]\t: "; cin>>pjm.year;
		if(pjm.month<=0){
			cout<<" ERROR ...!\n";
		}else{break;}
	}
	system("cls");
	cout<<"\n tanggal kembali : \n";
	while(1){
		cout<<"tanggal [1 - 30]\t: "; cin>>bck.day;
		if(bck.day<=0||bck.day>30){
			cout<<" ERROR ..!\n";
		}else{break;}
	}
	
	cout<<"\n bulan kembali: \n";
	while(1){
		cout<<" bulan [1 - 12]\t\t: "; cin>>bck.month;
		if(bck.month<=0||bck.month>12){
			cout<<" ERROR ..!\n";
		}else{break;}
	}
	
	cout<<"\n tahun kembali: \n";
	while(1){
		cout<<" tahun [yyyy]\t\t: "; cin>>bck.year;
		if(bck.year<=0){
			cout<<" ERROR ..!\n";
		}else{break;}
	}
	
	int lamapinjam = (bck.day - pjm.day)+((bck.month-pjm.month)*30)+((bck.year-pjm.year)*360);
	int terlambat = lamapinjam - 7;
	int denda=0;
	if(lamapinjam>7){
		denda = terlambat *100*byk;
	}
	
	jt.day = pjm.day+7;
	jt.day = pjm.month+(jt.day/31);
	jt.day = pjm.year+(jt.day/13);
	if(jt.day>30){
		jt.day-=30;
	}
	if(jt.month>12){
		jt.month-=12;
	}
	
	system("cls");
	
	cout<<"\n ============================";
	cout<< "\n OUTPUT PEMINJAMAN";
	cout<<"\n ============================";
	cout<<"\n data buku yang dipinjam:";
	cout<<"\n\n\n ============================";
	for(int a=1; a<=byk; a++){
		cout<<"\n data buku ke "<<a;
		cout<<"\n judul buku\t: "<<dt.books[a].title;
		cout<<"\n pengarang\t: "<<dt.books[a].author;
		cout<<"\n penerbit\t: "<<dt.books[a].publisher;
		cout<<"\n Tahun Terbit\t: "<<dt.books[a].year;
		cout<<"\n ID buku\t: "<<dt.books[a].id;
	cout<<"\n ============================";
	}
	
	cout<<"\n\n\n ============================";
	cout<<"\n Tanggal Pinjam\t: "<<pjm.day<<"/"<<pjm.month<<"/"<<pjm.year;
	cout<<"\n Tanggal Kembali\t: "<<bck.day<<"/"<<bck.month<<"/"<<bck.year;
	cout<<"\n Tanggal Jatuh Tempo\t: "<<jt.day<<"/"<<jt.month<<"/"<<jt.year;
	cout<<"\n Lama Pinjam\t: "<<lamapinjam<<" hari";
	cout<<"\n Denda\t\t: "<<denda;
	cout<<"\n\n ==================================\n";
	
	
    ofstream file(FILENAME, ios::app); // Open the file in append mode

    for (int i = 1; i <= byk; i++) {
        file << dt.books[i].title << "|" << dt.books[i].author << "|" << dt.books[i].publisher << "|" << dt.books[i].year << "|" << dt.books[i].id << "|" << endl;
    }

    file.close();
}



void lihat_buku() {
    ifstream file(FILENAME);

    if (file.is_open()) {
        string line;
        int count = 0;

        cout << "\n== Daftar Buku ==\n";

        while (getline(file, line)) {
            size_t pos = 0;
            string token;
            int tokenIndex = 0;
            book buku;

            while ((pos = line.find("|")) != string::npos) {
                token = line.substr(0, pos);

                switch (tokenIndex) {
                    case 0:
                        buku.title = token;
                        break;
                    case 1:
                        buku.author = token;
                        break;
                    case 2:
                        buku.publisher = token;
                        break;
                    case 3:
                        buku.year = token;
                        break;
                    case 4:
                        buku.id = token;
                        break;
                }

                line.erase(0, pos + 1);
                tokenIndex++;
            }

            count++;
            cout << "\nBuku ke-" << count << endl;
            cout << "Judul: " << buku.title << endl;
            cout << "Pengarang: " << buku.author << endl;
            cout << "Penerbit: " << buku.publisher << endl;
            cout << "Tahun Terbit: " << buku.year << endl;
            cout << "ID Buku: " << buku.id << endl;
        }

        file.close();
    } else {
        cout << "File tidak dapat dibuka." << endl;
    }
}

void lihat_peminjaman() {
    ifstream file(FILENAME);
    if (file.is_open()) {
        string line;
        int count = 0;
        //string peminjam[MAX_BOOKS]; // Array untuk menyimpan data peminjam

        // Read borrowing information from      the file and display it
        while (getline(file, line)) {
            // Display book information
            cout << "\nPeminjaman ke-" << (++count) << ":" << endl;
            cout << "Informasi Buku: " << line << endl;

            // Simpan informasi peminjam ke array peminjam[]
            /*peminjam[count] = line;

            // Cari indeks peminjam di array user_nim[]
            int indeks_peminjam = -1;
            for (int i = 0; i < jumlah_akun; i++) {
                if (user_nim[i] == peminjam[count]) {
                    indeks_peminjam = i;
                    break;
                }
            }*/

            // Tampilkan informasi peminjam jika ditemukan
            if (true) {
                cout << "Data Peminjam:" << endl;
                cout << "Nama: " << pnjm.nama << endl;
                cout << "Jurusan: " << pnjm.jurusan << endl;
                cout << "NIM: " << pnjm.nim << endl;
            } else {
                cout << "Data Peminjam tidak ditemukan." << endl;
            }

            // Tampilkan tanggal peminjaman dan pengembalian
            cout << "Tanggal Peminjaman: " << pjm.day << "/" << pjm.month << "/" << pjm.year << endl;
            cout << "Tanggal Pengembalian: " << bck.day << "/" << bck.month << "/" << bck.year << endl;
        }

        file.close();
    } else {
        cout << "File tidak dapat dibuka." << endl;
    }
}


