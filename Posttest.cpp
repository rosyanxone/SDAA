#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

// variabel i sebagai variabel struct global
int i = 0;
int kembali();
void menu_harga();
void daftar_pengguna();

struct Pelanggan {
	string nama, area, idPs;
	int id, jenis, jam;
	string var1;
	int var2;
}; 
Pelanggan perental[100];
void menu_rental(Pelanggan *perental);

int shell_sort(Pelanggan *perental, int &n, string order, char menuSort);
void quick_sort(Pelanggan *perental, int low, int high, string order, char menuSort);
void merge_sort(Pelanggan *perental, int l, int r, string order, char menuSort);

// Menggunakan 2 metode search yang ada di modul
int jumpSearch(Pelanggan *arr, int x, string y, int n, char menuSearch);
int fibMonaccianSearch(Pelanggan *arr, int x, string y, int n, char menuSearch);

string ps[10][5] = {
	{"1", "Ps 2", "Area 1", "Rp.8000", "Tersedia"},
	{"2", "Ps 2", "Area 2", "Rp.8000", "Tersedia"},
	{"3", "Ps 2", "Area 3", "Rp.8000", "Tersedia"},
	
	{"4", "Ps 3", "Area 4", "Rp.12000", "Tersedia"},
	{"5", "Ps 3", "Area 5", "Rp.12000", "Tersedia"},
	{"6", "Ps 3", "Area 6", "Rp.12000", "Tersedia"},
	
	{"7", "Ps 4", "Area 7", "Rp.17000", "Tersedia"},
	{"8", "Ps 4", "Area 8", "Rp.17000", "Tersedia"},
	{"9", "Ps 1", "Area 9", "Rp.5000" , "Tersedia"}
};

void menu() {
	system("cls");
	char masuk;
	
	cout << "=====PROGRAM RENTAL PS=====" << endl;
	cout << "+-------------------------+" << endl;
	cout << "| [1] Rental Now          |" << endl;
	cout << "| [2] Daftar Harga        |" << endl;
	cout << "| [3] Daftar Pengguna	  |" << endl;
	cout << "| [0] Keluar Program      |" << endl;
	cout << "+-------------------------+" << endl;
	cout << "--- Masukkan menu: ";
	cin >> masuk;
	
	switch (masuk) {
		case '0':
			cout << " -- Program selesai..." << endl;
			exit(0);
			break;
		case '1':
			menu_rental(perental);
			break;
		case '2':
			menu_harga();
			break;
		case '3':
			daftar_pengguna();
			break;
		default:			
			cout << "\nPilihan anda tidak valid!\n";
			kembali();
	}
}

int kembali() {
	system("pause");
	menu();
	
	return 0;
}

void menu_rental(Pelanggan *perental) {
	system("cls");
	i++;
	for (int k = 0; k < i; k++) {
		perental++;
	} int jenisPs[10];
	
	cout << "+------------------------------------+\n";
	cout << "| Masukkan nama anda   : ";
	cin.ignore(); getline(cin, perental->nama);
	if (perental->nama.size() > 13) {
		cout << "+------------------------------------+" << endl;
		cout << "\nTidak dapat menerima nama lebih dari 13 huruf" << endl;
		i--;
		kembali();
	} else {
		for (int j = 0; j < 10; j++) {
			if (ps[j][1] == "" || ps[j][4] != "Tersedia") {
			    continue;
			} else {
			    string pees = ps[j][1];
			    jenisPs[j] = pees[3] - '0';
			}
		}
		
		cout << "| Masukkan jenis Ps    : ";
		cin >> perental->jenis;

		int get, iPs;
		for (int j = 0; j < 10; j++) {
			if (jenisPs[j] == perental->jenis) {
				get = jenisPs[j];
				iPs = j;
				break;
			} else {
				get = -1;
			}
		}
		
		if (get == -1 || ps[iPs][4] != "Tersedia") {
			cout << "+------------------------------------+\n"; 
			cout << "\nJenis Ps-" << perental->jenis << " tidak tersedia, atau\n";
			cout << "sedang full digunakan\n";
			i--;
			kembali();
		} else {
			cout << "| Masukkan jam sewa    : ";
			cin >> perental->jam;
			
			if (perental->jam == 0) {
				cout << "+------------------------------------+" << endl;
				cout << "\nJam tidak dapat berisi kosong" << endl;
				i--;
				kembali();
			} else {

				int harga;
				string price = ps[iPs][3];
				for (int j = 0; j < 3; j++) {
					price[j] = '0';
				} harga = stoi(price); // jika stoi error pastikan untuk mengupdate compiler ke C++11

				perental->area = ps[iPs][2];
				perental->idPs = ps[iPs][0];
				perental->id = i;
				ps[iPs][4] = "Disewa Id-"+to_string(i);
				
				cout << "|-Ps " << perental->jenis << " = Rp."<< harga << "/jam \n";
				cout << "+------------------------------------+"<<endl;
				cout << "Struk:" << endl;

				// Membuat file .txt sebagai struk pengguna
				string file = "D:\\Struk Rental Ps Id-"+to_string(i)+".txt";
				string baris;
				ofstream output(file);
				ofstream outfile;
				outfile.open(file.c_str());

				while(true){
					outfile << "  ============================ " << endl;
					outfile << "             RENTAL PS         " << endl;
					outfile << "          SEMPAJA SELATAN      " << endl;
					outfile << " ==============================" << endl;
					outfile << " | Id pengguna  : " << perental->id << endl;
					outfile << " | Atas nama    : " << perental->nama << endl;
					outfile << " | Jenis        : Ps " << perental->jenis << endl;
					outfile << " | Anda menyewa : " << perental->jam << " jam" << endl;
					outfile << " +=============================" << endl;
					outfile << " | Ruang anda   : " << perental->area << endl;
					outfile << " | Tagihan anda : Rp." << perental->jam * harga << endl;
					outfile << " ==============================" << endl;
					outfile << "           TERIMA KASIH        " << endl;
					outfile << " ==============================" << endl;
					outfile << baris << endl;
					break;
				} outfile.close();
				ifstream infile;

				// Menampilkan isi struk / isi file .txt
				infile.open(file.c_str());
				while (getline (infile,baris)) {
					cout << baris << '\n';
				} infile.close();

				cout << "Struk anda disimpan dalam bentuk file .txt" << endl;
				cout << "dengan lokasi '"+file << "'\n" << endl;
				kembali();
}}}}

void ganti_array(int &data) {
	string pees, ruang, harga;
	cout << " -- Masukkan jenis Ps  : ";
	cin >> pees;
	cout << " -- Masukkan area baru : ";
	cin >> ruang;
	cout << " -- Masukkan harga/jam : Rp.";
	cin >> harga;
	
	ps[data - 1][1] = "Ps "+pees;
	ps[data - 1][2] = "Area "+ruang;
	ps[data - 1][3] = "Rp."+harga;
	ps[data - 1][4] = "Tersedia";
}

void menu_harga(){
	system("cls");
	char opsi;
	int data;
	
	cout << " =======================DAFTAR HARGA====================\n";
	cout << "|=======================================================|\n";
	cout << "| Id  | JENIS | RUANG   | HARGA PER JAM | STATUS\t|\n";
	cout << "+-----|-------|---------|---------------|---------------+";
	int a = 0;
	while(a < 9) {
		if (ps[a][1] == "" && ps[a][2] == "" && ps[a][3] == "" && ps[a][4] == "") {
			cout << "\n|  " << ps[a][0] << "  |       |         |               |               |";
		} else {
			cout << "\n|  " << ps[a][0] << "  | " << ps[a][1] << "  | " << ps[a][2] << "\t| " << ps[a][3] << "\t| " << ps[a][4] << " \t|";
		} a++;
	}
	cout << "\n|=======================================================|\n";
	cout << "[1] Edit data" << endl;
	cout << "[2] Hapus data" << endl;
	cout << "[0] Kembali " << endl;
	cout << "--- Masukkan menu      : ";
	cin >> opsi;
	
	if (opsi == '1') {
		cout << "--- Masukkan id data   : ";
		cin >> data;
		ganti_array(data);
		
		cout << "\nData berhasil di perbarui!" << endl;
		kembali();

	} else if (opsi == '2') {
		cout << "--- Masukkan id data   : ";
		cin >> data;
		
		ps[data - 1][1] = "";
		ps[data - 1][2] = "";
		ps[data - 1][3] = "";
		ps[data - 1][4] = "";
		
		cout << "\nData berhasil dihapus!" << endl;
		kembali();

	}  else {
		menu();
	}
}

string menu_sorting(char menuSort) {
	char metodeSort;
	string order;

	cout << "[1] Shell Sort" << endl;
	cout << "[2] Quick Sort" << endl;
	cout << "[3] Merge Sort" << endl;
	cout << "[0] Kembali" << endl;
	cout << "-- Pilih metode sorting : ";
	cin >> metodeSort;
	cout << "[1] Ascending" << endl;
	cout << "[2] Descending" << endl;
	cout << "-- Sorting Secara(1/2)  : ";
	cin >> order;
	order = (order=="1") ? "Ascending" : "Descending"; 
	int n = i+1;
	
	for (int j = 0; j < n; j++) {
		switch (menuSort) {
			case '0':
				menu();
				break;
			case '1':
				perental[j].var2 = perental[j].id;
				break;
			case '2':
				perental[j].var1 = perental[j].nama;
				break;
			case '3':
				perental[j].var2 = perental[j].jenis;
				break;
			case '4':
				perental[j].var1 = perental[j].area;
				break;
			case '5':
				perental[j].var2 = perental[j].jam;
				break;
			default:
				cout << "\nAnda memasukkan pilihan yang salah!" << endl;
				system("pause");
				menu();
				break;
		}	
	}

	if (metodeSort == '0') {
		menu();
	} else if (metodeSort == '1') {
		shell_sort(perental, n, order, menuSort);
	} else if (metodeSort == '2') {
		quick_sort(perental, 0, n-1, order, menuSort);
	} else if (metodeSort == '3') {
		merge_sort(perental, 0, n-1, order, menuSort);
	}
	
	return order;
}

void menu_searching(char menuSearch, char metodeSearch) {
	int n = i+1;
	string y, nomor;
	int x;

	switch (menuSearch) {
		// Pilihan kategori yang ingin di Search
		case '1':
			cout << "-- Masukkan id yang ingin \n-- anda cari : ";
			cin >> x;
			for (int h = 0; h < n; h++) {
				perental[h].var2 = perental[h].id;
			}
			shell_sort(perental, n, "Ascending", menuSearch);
			break;
		case '2':
			cout << "-- Masukkan nama yang \n-- ingin anda cari : ";
			cin.ignore(); getline(cin, y);
			for (int h = 0; h < n; h++) {
				perental[h].var1 = perental[h].nama;
			}
			shell_sort(perental, n, "Ascending", menuSearch);
			break;
		case '3':
			cout << "-- Masukkan jenis Ps yang \n-- ingin anda cari : Ps ";
			cin >> x;
			for (int h = 0; h < n; h++) {
				perental[h].var2 = perental[h].jenis;
			}
			shell_sort(perental, n, "Ascending", menuSearch);
			break;
		case '4':
			cout << "-- Masukkan ruang yang ingin \n-- anda cari : Area ";
			cin >> nomor; y = "Area "+nomor;
			for (int h = 0; h < n; h++) {
				perental[h].var1 = perental[h].area;
			}
			shell_sort(perental, n, "Ascending", menuSearch);
			break;
		case '5':
			cout << "-- Masukkan jam yang \n-- ingin anda cari : ";
			cin >> x;
			for (int h = 0; h < n; h++) {
				perental[h].var2 = perental[h].jam;
			}
			shell_sort(perental, n, "Ascending", menuSearch);
			break;
	}

	int array[n] = {};
	int j = -1;
	int index;
		system("cls");
		cout << " =======================DAFTAR PENGGUNA==================\n";
		cout << "|========================================================|\n";
		cout << "| ID  | NAMA \t\t| JENIS | RUANG  | SELESAI DALAM |\n";
		cout << "+-----|-----------------|-------|--------|---------------+\n";
	if (menuSearch == '2' || menuSearch == '4') {
		for (int i = 0; i < n; i++) {
			if (metodeSearch == '1') {
				index = jumpSearch(perental, x, y, n, menuSearch);
			} else if (metodeSearch == '2') {
				index = fibMonaccianSearch(perental, x, y, n, menuSearch);
			}
			if (index != -1) {
				if (perental[index].nama.size() < 7 && perental[index].id > 0) {
					cout << "|  " << perental[index].id <<"  | "<<perental[index].nama<<" \t\t| Ps "<<perental[index].jenis<<"  | " << perental[index].area << " | " << perental[index].jam <<" jam \t |\n";
				} else if (perental[index].nama.size() < 13 && perental[index].id > 0) {
					cout << "|  " << perental[index].id <<"  | " << perental[index].nama<<" \t| Ps "<<perental[index].jenis<<"  | " << perental[index].area << " | " << perental[index].jam <<" jam \t |\n";
				}
				perental[index].var1 = "";
				array[i] = index;
				j++;
			}
		}
	} else if (menuSearch == '1' || menuSearch == '3' || menuSearch == '5') {
		for (int i = 0; i < n; i++) {
			if (metodeSearch == '1') {
				index = jumpSearch(perental, x, y, n, menuSearch);
			} else if (metodeSearch == '2') {
				index = fibMonaccianSearch(perental, x, y, n, menuSearch);
			}
			if (index != -1) {
				if (perental[index].nama.size() < 7 && perental[index].id > 0) {
					cout << "|  " << perental[index].id <<"  | "<<perental[index].nama<<" \t\t| Ps "<<perental[index].jenis<<"  | " << perental[index].area << " | " << perental[index].jam <<" jam \t |\n";
				} else if (perental[index].nama.size() < 13 && perental[index].id > 0) {
					cout << "|  " << perental[index].id <<"  | " << perental[index].nama<<" \t| Ps "<<perental[index].jenis<<"  | " << perental[index].area << " | " << perental[index].jam <<" jam \t |\n";
				}
				perental[index].var2 = -1;
				array[i] = index;
				j++;
			}
		}
	}
	if (j == -1) {
		cout << "|           Data Yang Anda Cari Tidak Tersedia           |\n";
		cout << "|========================================================|\n\n";
	} else {
		cout << "|========================================================|\n";
		cout << "\nData ditemukan." << endl;
	}
}

void ganti_struct(Pelanggan *perental, int &usr) {
	string nomor;
	for (int j = 0; j < i+1; j++) {
		perental++;
		if (perental->id == usr) {
			cout << " -- Masukkan nama user: ";
			cin.ignore(); getline(cin, perental->nama);
			cout << " -- Masukkan jenis ps : ";
			cin >> perental->jenis;
			cout << " -- Masukkan ruang ke : ";
			cin >> nomor; perental->area = "Area "+nomor;
			cout << " -- Lama user selesai : ";
			cin >> perental->jam;
			break;
		}
	}
}

void daftar_pengguna() {
	system("cls");
	
	char opsi2;
	int usr, idPs;
	int k = 0;
	
	cout << " =======================DAFTAR PENGGUNA==================\n";
	cout << "|========================================================|\n";
	cout << "| ID  | NAMA \t\t| JENIS | RUANG  | SELESAI DALAM |\n";
	if (i == 0) {
		cout << "| --- | ---  \t\t| ---   | ---    | ---           |\n";
		cout << "|========================================================|\n";
		cout << "*daftar data pengguna akan tampil jika ada perental\n\n";
		kembali();
	} else {
		cout << "+-----|-----------------|-------|--------|---------------+\n";
		for (int j = 0; j < i+1; j++) {
			if (perental[j].nama == "" && perental[j].id == 0) {
				continue;
			} else if (perental[j].nama.size() < 7 && perental[j].id > 0) {
				cout << "|  " << perental[j].id <<"  | "<<perental[j].nama<<" \t\t| Ps "<<perental[j].jenis<<"  | " << perental[j].area << " | " << perental[j].jam <<" jam \t |\n";
				k++;
			} else if (perental[j].nama.size() < 13 && perental[j].id > 0) {
				cout << "|  " << perental[j].id <<"  | " << perental[j].nama<<" \t| Ps "<<perental[j].jenis<<"  | " << perental[j].area << " | " << perental[j].jam <<" jam \t |\n";
				k++;
			} 
		} if (k > 0) {
			cout << "|========================================================|\n";
			cout << "[1] Edit Pengguna" << endl;
			cout << "[2] Hapus Pengguna" << endl;
			cout << "[3] Lakukan Sorting" << endl;
			cout << "[4] Lakukan Searching" << endl;
			cout << "[0] Kembali " << endl;
			cout << "--- Masukkan menu     : ";
			cin >> opsi2;
			
			if (opsi2 == '1') {
				cout << "--- Masukkan user id  : ";
				cin >> usr;
				ganti_struct(perental, usr);
				
				cout << "\nData pengguna berhasil di perbarui!" << endl;
				kembali();

			} else if (opsi2 == '2') {
				cout << "--- Masukkan user id  : ";
				cin >> usr;

				for (int h = 0; h < i+1; h++) {
					if (perental[h].id == usr) {
						// Mengubah status disewa menjadi tersedia
						// karena data user dihapus
						stringstream ubah(perental[h].idPs);
						ubah >> idPs;
						ps[idPs-1][4] = "Tersedia";

						perental[h].nama = "";
						perental[h].area = "";
						perental[h].idPs = "";
						perental[h].id = 0;
						perental[h].jam = 0;
						perental[h].jenis = 0;
						break;
					}
				}
				cout << "\nData berhasil dihapus!" << endl;
				kembali();
			
			} else if (opsi2 == '3') {
				char menuSort;
	
				cout << "\n-- MENU SORTING --" << endl;
				cout << "[1] Id" << endl;
				cout << "[2] Nama" << endl;
				cout << "[3] Jenis Ps" << endl;
				cout << "[4] Ruang" << endl;
				cout << "[5] Sisa Waktu" << endl;
				cout << "[0] Kembali" << endl;
				cout << "-- Pilih menu sorting   : ";
				cin >> menuSort;
				if (menuSort == '0') {
					menu();
				} else {
					string order = menu_sorting(menuSort);
					
					cout << "\nBerhasil mensorting secara "+order << endl;
					kembali();
				}
				
			} else if (opsi2 == '4') {
				char menuSearch, metodeSearch;
	
				cout << "\n-- MENU SEARCHING --" << endl;
				cout << "[1] Id" << endl;
				cout << "[2] Nama" << endl;
				cout << "[3] Jenis Ps" << endl;
				cout << "[4] Ruang" << endl;
				cout << "[5] Sisa Waktu" << endl;
				cout << "-- Pilih menu searching   : ";
				cin >> menuSearch;
				cout << "[1] Fibonacci Search" << endl;
				cout << "[2] Jump Search" << endl;
				cout << "[0] Kembali" << endl;
				cout << "-- Pilih metode searching : ";
				cin >> metodeSearch;
				if (metodeSearch == '0') {
					menu();
				} else {
					menu_searching(menuSearch, metodeSearch);
					kembali();
				}
			} else {
				menu();
			}
		} else {
			cout << "| --- | ---  \t\t| ---   | ---    | ---           |\n";
			cout << "|========================================================|\n";
			cout << "*daftar data pengguna akan tampil jika ada perental\n\n";
			kembali();
}}}

int shell_sort(Pelanggan *perental, int &n, string order, char menuSort) {
	if (menuSort == '1' || menuSort == '3' || menuSort == '5') {
		for (int gap = n/2; gap > 0; gap /= 2) {
			if (order == "Ascending") {
				for (int i = gap; i < n; i += 1) {
					Pelanggan temp = perental[i];
					int j;
					for (j = i; j >= gap && perental[j - gap].var2 > temp.var2; j -= gap) {
						perental[j] = perental[j - gap];
					}
				perental[j] = temp;
				}
			}
			else if (order == "Descending") {
				for (int i = gap; i < n; i += 1) {
					Pelanggan temp = perental[i];
					int j;
					for (j = i; j >= gap && perental[j - gap].var2 < temp.var2; j -= gap) {
						perental[j] = perental[j - gap];
					}
				perental[j] = temp;
				}
			}	
		}
	} else if (menuSort == '2' || menuSort == '4') {
		for (int gap = n/2; gap > 0; gap /= 2) {
			if (order == "Ascending") {
				for (int i = gap; i < n; i += 1) {
					Pelanggan temp = perental[i];
					int j;
					for (j = i; j >= gap && perental[j - gap].var1 > temp.var1; j -= gap) {
						perental[j] = perental[j - gap];
					}
				perental[j] = temp;
				}
			}
			else if (order == "Descending") {
				for (int i = gap; i < n; i += 1) {
					Pelanggan temp = perental[i];
					int j;
					for (j = i; j >= gap && perental[j - gap].var1 < temp.var1; j -= gap) {
						perental[j] = perental[j - gap];
					}
				perental[j] = temp;
				}
			}	
		}
	}
	return 0;
}

void quick_sort(Pelanggan *perental, int low, int high, string order, char menuSort) {
	if (menuSort == '1' || menuSort == '3' || menuSort == '5') {
		if (low < high) {
			Pelanggan pivot = perental[high];
			int i = (low - 1);
			for (int j = low; j <= high - 1; j++) {
				if (order == "Ascending") {
					if (perental[j].var2 < pivot.var2) {
						i++;
						int t = perental[i].var2;
						perental[i].var2 = perental[j].var2;
						perental[j].var2 = t;
					}
				} else if (order == "Descending") {
					if (perental[j].var2 > pivot.var2) {
						i++;
						int t = perental[i].var2;
						perental[i].var2 = perental[j].var2;
						perental[j].var2 = t;
					}
				} 
			}
			Pelanggan t = perental[i + 1];
			perental[i + 1] = perental[high];
			perental[high] = t;
			int pi = i + 1;
			
			quick_sort(perental, low, pi - 1, order, menuSort);
			quick_sort(perental, pi + 1, high, order, menuSort);
		}
	} else if (menuSort == '2' || menuSort == '4') {
		if (low < high) {
			Pelanggan pivot = perental[high];
			int i = (low - 1);
			for (int j = low; j <= high - 1; j++) {
				if (order == "Ascending") {
					if (perental[j].var1 < pivot.var1) {
						i++;
						string t = perental[i].var1;
						perental[i].var1 = perental[j].var1;
						perental[j].var1 = t;
					}
				} else if (order == "Descending") {
					if (perental[j].var1 > pivot.var1) {
						i++;
						string t = perental[i].var1;
						perental[i].var1 = perental[j].var1;
						perental[j].var1 = t;
					}
				} 
			}
			Pelanggan t = perental[i + 1];
			perental[i + 1] = perental[high];
			perental[high] = t;
			int pi = i + 1;
			
			quick_sort(perental, low, pi - 1, order, menuSort);
			quick_sort(perental, pi + 1, high, order, menuSort);
		}
	}
}

void merge_sort(Pelanggan *perental, int l, int r, string order, char menuSort) {
	if (menuSort == '1' || menuSort == '3' || menuSort == '5') {
		if (l < r) {
			int m = l+(r-l)/2;
			merge_sort(perental, l, m, order, menuSort);
			merge_sort(perental, m+1, r, order, menuSort);
			
			int i, j, k;
			int n1 = m - l + 1;
			int n2 = r - m;
			Pelanggan L[n1], R[n2];

			for (i = 0; i < n1; i++) {
				L[i] = perental[l + i];
			} 	for (j = 0; j < n2; j++) {
					R[j] = perental[m + 1+ j];
				}

			i = 0; 
			j = 0; 
			k = l; 
			while (i < n1 && j < n2) {
				if (order == "Ascending") {
					if (L[i].var2 <= R[j].var2) {
						perental[k] = L[i];
						i++;
					} else {
						perental[k] = R[j];
						j++;
					}
				} else if (order == "Descending") {
					if (L[i].var2 > R[j].var2) {
						perental[k] = L[i];
						i++;
					} else {
						perental[k] = R[j];
						j++;
					}
				} k++;
			}

			while (i < n1) {
				perental[k] = L[i];
				i++;
				k++;
			}

			while (j < n2) {
				perental[k] = R[j];
				j++;
				k++;
			}
		}
	} else if (menuSort == '2' || menuSort == '4') {
		if (l < r) {
			int m = l+(r-l)/2;
			merge_sort(perental, l, m, order, menuSort);
			merge_sort(perental, m+1, r, order, menuSort);
			
			int i, j, k;
			int n1 = m - l + 1;
			int n2 = r - m;
			Pelanggan L[n1], R[n2];

			for (i = 0; i < n1; i++) {
				L[i] = perental[l + i];
			} 	for (j = 0; j < n2; j++) {
					R[j] = perental[m + 1+ j];
				}

			i = 0; 
			j = 0; 
			k = l; 
			while (i < n1 && j < n2) {
				if (order == "Ascending") {
					if (L[i].var1 <= R[j].var1) {
						perental[k] = L[i];
						i++;
					} else {
						perental[k] = R[j];
						j++;
					}
				} else if (order == "Descending") {
					if (L[i].var1 > R[j].var1) {
						perental[k] = L[i];
						i++;
					} else {
						perental[k] = R[j];
						j++;
					}
				} k++;
			}

			while (i < n1) {
				perental[k] = L[i];
				i++;
				k++;
			}

			while (j < n2) {
				perental[k] = R[j];
				j++;
				k++;
			}
		}
	}
}

int fibMonaccianSearch(Pelanggan *arr, int x, string y, int n, char menuSearch) {
	if (menuSearch == '2' || menuSearch == '4') {
		int fibMMm2 = 0;
		int fibMMm1 = 1;
		int fibM = fibMMm2 + fibMMm1;
		while (fibM < n) {
			fibMMm2 = fibMMm1;
			fibMMm1 = fibM;
			fibM = fibMMm2 + fibMMm1;
		}
		int offset = -1;

		while (fibM > 1) {
			int i = min(offset+fibMMm2, n-1);
			if (arr[i].var1 < y) {
				fibM = fibMMm1;
				fibMMm1 = fibMMm2;
				fibMMm2 = fibM - fibMMm1;
				offset = i;
			} else if (arr[i].var1 > y) {
				fibM = fibMMm2;
				fibMMm1 = fibMMm1 - fibMMm2;
				fibMMm2 = fibM - fibMMm1;
			} else {
				return i;
			}
		}
		if(fibMMm1 && arr[offset+1].var1==y) {
			return offset+1;
		}
	} else if (menuSearch == '1' || menuSearch == '3' || menuSearch == '5') {
		int fibMMm2 = 0;
		int fibMMm1 = 1;
		int fibM = fibMMm2 + fibMMm1;
		while (fibM < n) {
			fibMMm2 = fibMMm1;
			fibMMm1 = fibM;
			fibM = fibMMm2 + fibMMm1;
		}
		int offset = -1;

		while (fibM > 1) {
			int i = min(offset+fibMMm2, n-1);
			if (arr[i].var2 < x) {
				fibM = fibMMm1;
				fibMMm1 = fibMMm2;
				fibMMm2 = fibM - fibMMm1;
				offset = i;
			} else if (arr[i].var2 > x) {
				fibM = fibMMm2;
				fibMMm1 = fibMMm1 - fibMMm2;
				fibMMm2 = fibM - fibMMm1;
			} else {
				return i;
			}
		}
		if(fibMMm1 && arr[offset+1].var2==x) {
			return offset+1;
		}
	}
    return -1;
}

int jumpSearch(Pelanggan *arr, int x, string y, int n, char menuSearch) {
	int step = sqrt(n);
	int prev = 0;
	if (menuSearch == '2' || menuSearch == '4') {
		while (arr[min(step, n)-1].var1 < y) {
			prev = step;
			step += sqrt(n);
			if (prev >= n) {
				return -1;
			}
		}
		while (arr[prev].var1 < y) {
			prev++;
			if (prev == min(step, n)) {
				return -1;
			}
		}
		if (arr[prev].var1 == y) {
			return prev;
		}
	} else if (menuSearch == '1' || menuSearch == '3' || menuSearch == '5') {
		while (arr[min(step, n)-1].var2 < x) {
			prev = step;
			step += sqrt(n);
			if (prev >= n) {
				return -1;
			}
		}
		while (arr[prev].var2 < x) {
			prev++;
			if (prev == min(step, n)) {
				return -1;
			}
		}
		if (arr[prev].var2 == x) {
			return prev;
		}
	}
	return -1;
}

int main() {
	perental[0].nama = "";
	perental[0].area = "";
	perental[0].idPs = "";
	perental[0].id = 0;
	perental[0].jam = 0;
	perental[0].jenis = 0;
	menu();

	return 0;
}
