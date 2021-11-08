#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int totalId = 0;
int kembali();
void menu_harga();
int main();

struct Pelanggan {
	string nama, area, idPs;
	int id, jenis, jam;
	string var1;
	int var2;
};

struct Node {
	int data;
	struct Node *next;
    Pelanggan perental[100];
}; struct Node* head = NULL;

void menu_rental(Node **head);
void daftar_pengguna(struct Node* nodeUser);

int shell_sort(string arr1[], int arr2[], int &n, string order, char menuSort);
void quick_sort(string arr1[], int arr2[], int low, int high, string order, char menuSort);
void merge_sort(string arr1[], int arr2[], int l, int r, string order, char menuSort);

int jumpSearch(string arr1[], int arr2[], int x, string y, int n, char menuSearch);
int fibMonaccianSearch(string arr1[], int arr2[], int x, string y, int n, char menuSearch);

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
	char masuk;
	system("cls");
	cout << "===== PIXEL RENTAL PS =====" << endl;
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
			menu_rental(&head);
			break;
		case '2':
			menu_harga();
			break;
		case '3':
			daftar_pengguna(head);
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

void menu_rental(Node **head) {
	system("cls");
    int jenisPs[10];
    Node *nodeBaru = new Node();

    nodeBaru->data = totalId;
	nodeBaru->perental->id = totalId;
	totalId++;
	
	cout << "+------------------------------------+\n";
	cout << "| Masukkan nama anda   : ";
	cin.ignore(); getline(cin, nodeBaru->perental->nama);
	if (nodeBaru->perental->nama.size() > 13) {
		cout << "+------------------------------------+" << endl;
		cout << "\nTidak dapat menerima nama lebih dari 13 huruf" << endl;
		totalId--;
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
		cin >> nodeBaru->perental->jenis;

		int get, iPs;
		for (int j = 0; j < 10; j++) {
			if (jenisPs[j] == nodeBaru->perental->jenis) {
				get = jenisPs[j];
				iPs = j;
				break;
			} else {
				get = -1;
			}
		}
		
		if (get == -1 || ps[iPs][4] != "Tersedia") {
			cout << "+------------------------------------+\n"; 
			cout << "\nJenis Ps-" << nodeBaru->perental->jenis << " tidak tersedia, atau\n";
			cout << "sedang full digunakan\n";
			totalId--;
			kembali();
		} else {
			cout << "| Masukkan jam sewa    : ";
			cin >> nodeBaru->perental->jam;
			
			if (nodeBaru->perental->jam == 0) {
				cout << "+------------------------------------+" << endl;
				cout << "\nJam tidak dapat berisi kosong" << endl;
				totalId--;
				kembali();
			} else {

				int harga;
				string price = ps[iPs][3];
				for (int j = 0; j < 3; j++) {
					price[j] = '0';
				} harga = stoi(price); // jika stoi error pastikan untuk mengupdate compiler ke C++11

				nodeBaru->perental->area = ps[iPs][2];
				nodeBaru->perental->idPs = ps[iPs][0];
				nodeBaru->perental->id = totalId;
				ps[iPs][4] = "Disewa Id-"+to_string(totalId);
				
				cout << "|-Ps " << nodeBaru->perental->jenis << " = Rp."<< harga << "/jam \n";
				cout << "+------------------------------------+"<<endl;
				cout << "Struk:" << endl;

				// Membuat file .txt sebagai struk pengguna
				string file = "Struk Rental Ps Id-"+to_string(totalId)+".txt";
				string baris;
				ofstream output(file, fstream::app);
				ofstream outfile;
				outfile.open(file.c_str());

				while(true){
				    outfile << " +-----------------------------+" << endl;
					outfile << " |        PIXEL Rental PS      |" << endl;
					outfile << " |           SAMARINDA         |" << endl;
					outfile << " +-----------------------------+" << endl;
					outfile << " |           id : " << nodeBaru->perental->id << endl;
					outfile << " |         nama : " << nodeBaru->perental->nama << endl;
					outfile << " |        jenis : Ps " << nodeBaru->perental->jenis << endl;
					outfile << " |       durasi : " << nodeBaru->perental->jam << " jam" << endl;
					outfile << " |      ruangan : " << nodeBaru->perental->area << endl;
					outfile << " +----------------------------+" << endl;
					outfile << " | Tagihan anda : Rp." << nodeBaru->perental->jam * harga << endl;
					outfile << " +----------------------------+" << endl;
					outfile << " ==============================" << endl;
					outfile << "          TERIMA KASIH         " << endl;
					outfile << " ==============================" << endl;
					outfile << baris << endl;
					break;
				} outfile.close();
				ifstream infile;
				
				// File eksternal berupa txt
				// Menampilkan isi struk / isi dari file .txt
				infile.open(file.c_str());
				while (getline (infile,baris)) {
					cout << baris << '\n';
				} infile.close();

				cout << "Struk anda disimpan dalam bentuk file .txt" << endl;
    
				nodeBaru->next = NULL;
				if (*head == NULL) {
					*head = nodeBaru;
					kembali();
				}
				Node *temp = *head;
				while (temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = nodeBaru;
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

string menu_sorting(string arr1[], int arr2[], Node *head, char menuSort, char metodeSort, string order) {
	Node *tempCount = head;
	int n = 0;
	while(tempCount != NULL) {
		n++;
		tempCount = tempCount->next;
	}

	Node *temp = head;
	string arrTemp[n][6] = {};

	order = (order=="1") ? "Ascending" : "Descending";
	for (int i = 0; i < n; i++) {
		switch(menuSort) {
			case '1':
				arr2[i] = temp->perental->id;
				break;
			case '2':
				arr1[i] = temp->perental->nama;
				break;
			case '3':
				arr2[i] = temp->perental->jenis;
				break;
			case '4':
				arr1[i] = temp->perental->area;
				break;
			case '5':
				arr2[i] = temp->perental->jam;
				break;
		}
		temp = temp->next;
	}

	if (metodeSort == '1') {
		shell_sort(arr1, arr2, n, order, menuSort);
	} else if (metodeSort == '2') {
		 quick_sort(arr1, arr2, 0, n - 1, order, menuSort);
	} else if (metodeSort == '3') {
		 merge_sort(arr1, arr2, 0, n - 1, order, menuSort);
	}
	
	Node *temp2 = head;
	int x = 0;
	while(x < n) {
		arrTemp[x][0] = to_string(temp2->perental->id);
		arrTemp[x][1] = temp2->perental->nama;
		arrTemp[x][2] = to_string(temp2->perental->jenis);
		arrTemp[x][3] = temp2->perental->area;
		arrTemp[x][4] = to_string(temp2->perental->jam);
		arrTemp[x][5] = temp2->perental->idPs;
		temp2 = temp2->next;
		x++;
	}
	
	int y = 0;
	while(y < n) {
		int z = 0;
		while(z < n) {
			switch(menuSort) {
				case '1':
					if(arr2[y] == stoi(arrTemp[z][0])) {
						head->perental->id = stoi(arrTemp[z][0]);
						head->perental->nama = arrTemp[z][1];
						head->perental->jenis = stoi(arrTemp[z][2]);
						head->perental->area = arrTemp[z][3];
						head->perental->jam = stoi(arrTemp[z][4]);
						head->perental->idPs = arrTemp[z][5];
						head = head->next;
						y++;
						if (head == NULL) {
							return order;
							break;
						}
					}
					break;
				case '2':
					if(arr1[y] == arrTemp[z][1]) {
						head->perental->id = stoi(arrTemp[z][0]);
						head->perental->nama = arrTemp[z][1];
						head->perental->jenis = stoi(arrTemp[z][2]);
						head->perental->area = arrTemp[z][3];
						head->perental->jam = stoi(arrTemp[z][4]);
						head->perental->idPs = arrTemp[z][5];
						head = head->next;
						y++;
						if (head == NULL) {
							return order;
							break;
						}
					}
					break;
				case '3':
					if(arr2[y] == stoi(arrTemp[z][2])) {
						head->perental->id = stoi(arrTemp[z][0]);
						head->perental->nama = arrTemp[z][1];
						head->perental->jenis = stoi(arrTemp[z][2]);
						head->perental->area = arrTemp[z][3];
						head->perental->jam = stoi(arrTemp[z][4]);
						head->perental->idPs = arrTemp[z][5];
						head = head->next;
						y++;
						if (head == NULL) {
							return order;
							break;
						}
					}
					break;
				case '4':
					if(arr1[y] == arrTemp[z][3]) {
						head->perental->id = stoi(arrTemp[z][0]);
						head->perental->nama = arrTemp[z][1];
						head->perental->jenis = stoi(arrTemp[z][2]);
						head->perental->area = arrTemp[z][3];
						head->perental->jam = stoi(arrTemp[z][4]);
						head->perental->idPs = arrTemp[z][5];
						head = head->next;
						y++;
						if (head == NULL) {
							return order;
							break;
						}
					}
					break;
				case '5':
					if(arr2[y] == stoi(arrTemp[z][4])) {
						head->perental->id = stoi(arrTemp[z][0]);
						head->perental->nama = arrTemp[z][1];
						head->perental->jenis = stoi(arrTemp[z][2]);
						head->perental->area = arrTemp[z][3];
						head->perental->jam = stoi(arrTemp[z][4]);
						head->perental->idPs = arrTemp[z][5];
						head = head->next;
						y++;
						if (head == NULL) {
							return order;
							break;
						}
					}
					break;
			}
			z++;
		}
	}
	return order;
}

void menu_searching(string arr1[], int arr2[], Node *head, char menuSearch, char metodeSearch) {
	Node *tempCount = head;
	int n = 0;
	while(tempCount != NULL) {
		n++;
		tempCount = tempCount->next;
	}

	Node *temp = head;
	string y, nomor;
	int x;
	string tempArr[n][6] = {};

	switch (menuSearch) {
		// Pilihan kategori yang ingin di Search
		case '1':
			cout << "-- Masukkan id yang ingin \n - anda cari : ";
			cin >> x;
			break;
		case '2':
			cout << "-- Masukkan nama yang \n - ingin anda cari : ";
			cin.ignore(); getline(cin, y);
			break;
		case '3':
			cout << "-- Masukkan jenis Ps yang \n - ingin anda cari : Ps ";
			cin >> x;
			break;
		case '4':
			cout << "-- Masukkan ruang yang ingin \n - anda cari : Area ";
			cin >> nomor; y = "Area "+nomor;
			break;
		case '5':
			cout << "-- Masukkan jam yang \n - ingin anda cari : ";
			cin >> x;
			break;
	}
	
	int k = 0;
	while(k < n) {
		tempArr[k][0] = to_string(temp->perental->id);
		tempArr[k][1] = temp->perental->nama;
		tempArr[k][2] = to_string(temp->perental->jenis);
		tempArr[k][3] = temp->perental->area;
		tempArr[k][4] = to_string(temp->perental->jam);
		tempArr[k][5] = temp->perental->idPs;
		temp = temp->next;
		k++;
	}

	int j = -1;
	int index;
	system("cls");
	cout << " =======================DAFTAR PENGGUNA==================\n";
	cout << "|========================================================|\n";
	cout << "| ID  | NAMA \t\t| JENIS | RUANG  | SELESAI DALAM |\n";
	cout << "+-----|-----------------|-------|--------|---------------+\n";
	if (menuSearch == '2' || menuSearch == '4') {
		if (metodeSearch == '1') {
			index = fibMonaccianSearch(arr1, arr2, x, y, n - 1, menuSearch);
		} else if (metodeSearch == '2') {
			index = jumpSearch(arr1, arr2, x, y, n, menuSearch);
		}
		if (index != -1) {
			arr1[index] = "";
			if (tempArr[index][1].size() < 7 && stoi(tempArr[index][0]) > 0) {
				cout << "|  " << tempArr[index][0] << "  | " << tempArr[index][1] << " \t\t| Ps "<< tempArr[index][2] << "  | " << tempArr[index][3] << " | " << tempArr[index][4] <<" jam \t |\n";
			} else if (tempArr[index][1].size() < 13 && stoi(tempArr[index][0]) > 0) {
				cout << "|  " << tempArr[index][0] << "  | " << tempArr[index][1] << " \t| Ps "<< tempArr[index][2] << "  | " << tempArr[index][3] << " | " << tempArr[index][4] <<" jam \t |\n";
			}
			j++;
		}
	} else if (menuSearch == '1' || menuSearch == '3' || menuSearch == '5') {
		for (int i = 0; i < n; i++) {
			if (metodeSearch == '1') {
				index = fibMonaccianSearch(arr1, arr2, x, y, n - 1, menuSearch);
			} else if (metodeSearch == '2') {
				index = jumpSearch(arr1, arr2, x, y, n, menuSearch);
			}
			if (index != -1) {
				arr2[index] = -1;
				if (tempArr[index][1].size() < 7 && stoi(tempArr[index][0]) > 0) {
					cout << "|  " << tempArr[index][0] <<"  | " << tempArr[index][1] << " \t\t| Ps " << tempArr[index][2] << "  | " << tempArr[index][3] << " | " << tempArr[index][4] <<" jam \t |\n";
				} else if (tempArr[index][1].size() < 13 && stoi(tempArr[index][0]) > 0) {
					cout << "|  " << tempArr[index][0] <<"  | " << tempArr[index][1] << " \t| Ps " << tempArr[index][2] << "  | " << tempArr[index][3] << " | " << tempArr[index][4] <<" jam \t |\n";
				}
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

void ganti_struct(Node *head, int &usr) {
	string nomor;

	while (head != NULL) {
		if (head->perental->id == usr) {
			cout << " -- Masukkan nama user: ";
			cin.ignore(); getline(cin, head->perental->nama);
			cout << " -- Masukkan jenis ps : ";
			cin >> head->perental->jenis;
			cout << " -- Masukkan ruang ke : ";
			cin >> nomor; head->perental->area = "Area "+nomor;
			cout << " -- Lama user selesai : ";
			cin >> head->perental->jam;
			cout << "\nData pengguna berhasil di perbarui!" << endl;
			kembali();
			break;
		}
		head = head->next;
	}
	cout << "\nGagal mengedit, id tidak ditemukan\n";
	kembali();
}

void hapus_data(Node **headUsr, int pos) {
	
	if (pos == 1) {
		if(*headUsr == NULL) {
			cout << "\nGagal menghapus, data perental kosong\n";
			kembali();
		}
		Node *temp = *headUsr;
		*headUsr = (*headUsr)->next;
		delete temp;
		cout << "\nData berhasil dihapus!" << endl;
		kembali();
	} else if (pos == 2) {
		if(*headUsr == NULL) {
			cout << "\nGagal menghapus, data perental kosong\n";
			kembali();
		} if((*headUsr)->next == NULL) {
			*headUsr = NULL;
			cout << "\nData berhasil dihapus!" << endl;
			kembali();
		}
		Node *temp = *headUsr;
		while(temp->next->next != NULL) {
			temp = temp->next;
		}
		temp->next = NULL;
		cout << "\nData berhasil dihapus!" << endl;
		kembali();
	}
}

void daftar_pengguna(struct Node* nodeUser) {
	system("cls");
	char opsi2;
	int usr, idPs;
	int k = 0;
	int n = 0;

	Node *tempCount = nodeUser;
	while(tempCount != NULL) {
		n++;
		tempCount = tempCount->next;
	}

	string arr1[n] = {};
	int arr2[n] = {};
	
	cout << " =======================DAFTAR PENGGUNA==================\n";
	cout << "|========================================================|\n";
	cout << "| ID  | NAMA \t\t| JENIS | RUANG  | SELESAI DALAM |\n";
	if (nodeUser == NULL) {
		cout << "| --- | ---  \t\t| ---   | ---    | ---           |\n";
		cout << "|========================================================|\n";
		cout << "*daftar pengguna akan tampil jika ada perental\n\n";
		kembali();

	} cout << "+-----|-----------------|-------|--------|---------------+\n";
	while (nodeUser != NULL) {
		if (nodeUser->perental->nama == "" && nodeUser->perental->id == -1) {
			continue;
		} else if (nodeUser->perental->nama.size() < 7 && nodeUser->perental->id > 0) {
			cout << "|  " << nodeUser->perental->id << "  | "<< nodeUser->perental->nama << " \t\t| Ps " << nodeUser->perental->jenis << "  | " << nodeUser->perental->area << " | " << nodeUser->perental->jam <<" jam \t |\n";
			k++;
		} else if (nodeUser->perental->nama.size() < 13 && nodeUser->perental->id > 0) {
			cout << "|  " << nodeUser->perental->id << "  | " << nodeUser->perental->nama << " \t| Ps " << nodeUser->perental->jenis << "  | " << nodeUser->perental->area << " | " << nodeUser->perental->jam <<" jam \t |\n";
			k++;
		}
		nodeUser = nodeUser->next;
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
				cout << "--- Masukkan user id  : "; cin >> usr;
				ganti_struct(head, usr);

			} else if (opsi2 == '2') {
				int pos;
				cout << "[1] Hapus Depan" << endl;
				cout << "[2] Hapus Belakang" << endl;
				cout << "--- Hapus data dari  : "; cin >> pos;
				// Mengubah status pada menu harga menjadi tersedia
				Node *temp = head;
				while (temp != NULL) {
					if (pos == 1) {
						stringstream statusPs(temp->perental->idPs);
						statusPs >> idPs;
						ps[idPs-1][4] = "Tersedia";
						temp = temp->next;
						break;
					} else if (pos == 2) {
						if (temp->perental->id == n) {
							stringstream statusPs(temp->perental->idPs);
							statusPs >> idPs;
							ps[idPs-1][4] = "Tersedia";
							break;
						}
						temp = temp->next;
					}
				}
				hapus_data(&head, pos);
			} else if (opsi2 == '3') {
				char menuSort, metodeSort;
				string order;
	
				cout << "\n-- MENU SORTING --" << endl;
				cout << "[1] Id" << endl;
				cout << "[2] Nama" << endl;
				cout << "[3] Jenis Ps" << endl;
				cout << "[4] Ruang" << endl;
				cout << "[5] Sisa Waktu" << endl;
				cout << "-- Pilih menu sorting   : ";
				cin >> menuSort;
				cout << "[1] Shell Sort" << endl;
				cout << "[2] Quick Sort" << endl;
				cout << "[3] Merge Sort" << endl;
				cout << "-- Pilih metode sorting : ";
				cin >> metodeSort;
				cout << "[1] Ascending" << endl;
				cout << "[2] Descending" << endl;
				cout << "[0] Kembali" << endl;
				cout << "-- Sorting Secara(1/2)  : ";
				cin >> order;
				if (order == "0") {
					cout << endl;
					kembali();
				} else {
					order = menu_sorting(arr1, arr2, head, menuSort, metodeSort, order);
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
					cout << endl;
					kembali();
				} else {
					menu_sorting(arr1, arr2, head, menuSearch, '1', "1");
					menu_searching(arr1, arr2, head, menuSearch, metodeSearch);
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
}}

int shell_sort(string arr1[], int arr2[], int &n, string order, char menuSort) {
	if (menuSort == '1' || menuSort == '3' || menuSort == '5') {
		for (int gap = n/2; gap > 0; gap /= 2) {
			if (order == "Ascending") {
				for (int i = gap; i < n; i += 1) {
					int temp = arr2[i];
					int j;
					for (j = i; j >= gap && arr2[j - gap] > temp; j -= gap) {
						arr2[j] = arr2[j - gap];
					}
				arr2[j] = temp;
				}
			}
			else if (order == "Descending") {
				for (int i = gap; i < n; i += 1) {
					int temp = arr2[i];
					int j;
					for (j = i; j >= gap && arr2[j - gap] < temp; j -= gap) {
						arr2[j] = arr2[j - gap];
					}
				arr2[j] = temp;
				}
			}	
		}
	} else if (menuSort == '2' || menuSort == '4') {
		for (int gap = n/2; gap > 0; gap /= 2) {
			if (order == "Ascending") {
				for (int i = gap; i < n; i += 1) {
					string temp = arr1[i];
					int j;
					for (j = i; j >= gap && arr1[j - gap] > temp; j -= gap) {
						arr1[j] = arr1[j - gap];
					}
				arr1[j] = temp;
				}
			}
			else if (order == "Descending") {
				for (int i = gap; i < n; i += 1) {
					string temp = arr1[i];
					int j;
					for (j = i; j >= gap && arr1[j - gap] < temp; j -= gap) {
						arr1[j] = arr1[j - gap];
					}
					arr1[j] = temp;
				}
			}	
		}
	}
	return 0;
}

void quick_sort(string arr1[], int arr2[], int low, int high, string order, char menuSort) {
	if (menuSort == '1' || menuSort == '3' || menuSort == '5') {
		if (low < high) {
			int pivot = arr2[high];
			int i = (low - 1);
			for (int j = low; j <= high - 1; j++) {
				if (order == "Ascending") {
					if (arr2[j] < pivot) {
						i++;
						int t = arr2[i];
						arr2[i] = arr2[j];
						arr2[j] = t;
					}
				} else if (order == "Descending") {
					if (arr2[j] > pivot) {
						i++;
						int t = arr2[i];
						arr2[i] = arr2[j];
						arr2[j] = t;
					}
				} 
			}
			int t = arr2[i + 1];
			arr2[i + 1] = arr2[high];
			arr2[high] = t;
			int pi = i + 1;
			
			quick_sort(arr1, arr2, low, pi - 1, order, menuSort);
			quick_sort(arr1, arr2, pi + 1, high, order, menuSort);
		}
	} else if (menuSort == '2' || menuSort == '4') {
		if (low < high) {
			string pivot = arr1[high];
			int i = (low - 1);
			for (int j = low; j <= high - 1; j++) {
				if (order == "Ascending") {
					if (arr1[j] < pivot) {
						i++;
						string t = arr1[i];
						arr1[i] = arr1[j];
						arr1[j] = t;
					}
				} else if (order == "Descending") {
					if (arr1[j] > pivot) {
						i++;
						string t = arr1[i];
						arr1[i] = arr1[j];
						arr1[j] = t;
					}
				} 
			}
			string t = arr1[i + 1];
			arr1[i + 1] = arr1[high];
			arr1[high] = t;
			int pi = i + 1;
			
			quick_sort(arr1, arr2, low, pi - 1, order, menuSort);
			quick_sort(arr1, arr2, pi + 1, high, order, menuSort);
		}
	}
}

void merge_sort(string arr1[], int arr2[], int l, int r, string order, char menuSort) {
	if (menuSort == '1' || menuSort == '3' || menuSort == '5') {
		if (l < r) {
			int m = l+(r-l)/2;
			merge_sort(arr1, arr2, l, m, order, menuSort);
			merge_sort(arr1, arr2, m+1, r, order, menuSort);
			
			int i, j, k;
			int n1 = m - l + 1;
			int n2 = r - m;
			int L[n1], R[n2];

			for (i = 0; i < n1; i++) {
				L[i] = arr2[l + i];
			} 	for (j = 0; j < n2; j++) {
					R[j] = arr2[m + 1+ j];
				}

			i = 0; 
			j = 0; 
			k = l; 
			while (i < n1 && j < n2) {
				if (order == "Ascending") {
					if (L[i] <= R[j]) {
						arr2[k] = L[i];
						i++;
					} else {
						arr2[k] = R[j];
						j++;
					}
				} else if (order == "Descending") {
					if (L[i] > R[j]) {
						arr2[k] = L[i];
						i++;
					} else {
						arr2[k] = R[j];
						j++;
					}
				} k++;
			}

			while (i < n1) {
				arr2[k] = L[i];
				i++;
				k++;
			}

			while (j < n2) {
				arr2[k] = R[j];
				j++;
				k++;
			}
		}
	} else if (menuSort == '2' || menuSort == '4') {
		if (l < r) {
			int m = l+(r-l)/2;
			merge_sort(arr1, arr2, l, m, order, menuSort);
			merge_sort(arr1, arr2, m+1, r, order, menuSort);
			
			int i, j, k;
			int n1 = m - l + 1;
			int n2 = r - m;
			string L[n1], R[n2];

			for (i = 0; i < n1; i++) {
				L[i] = arr1[l + i];
			} 	for (j = 0; j < n2; j++) {
					R[j] = arr1[m + 1+ j];
				}

			i = 0; 
			j = 0; 
			k = l; 
			while (i < n1 && j < n2) {
				if (order == "Ascending") {
					if (L[i] <= R[j]) {
						arr1[k] = L[i];
						i++;
					} else {
						arr1[k] = R[j];
						j++;
					}
				} else if (order == "Descending") {
					if (L[i] > R[j]) {
						arr1[k] = L[i];
						i++;
					} else {
						arr1[k] = R[j];
						j++;
					}
				} k++;
			}

			while (i < n1) {
				arr1[k] = L[i];
				i++;
				k++;
			}

			while (j < n2) {
				arr1[k] = R[j];
				j++;
				k++;
			}
		}
	}
}

int fibMonaccianSearch(string arr1[], int arr2[], int x, string y, int n, char menuSearch) {
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
			if (arr1[i] < y) {
				fibM = fibMMm1;
				fibMMm1 = fibMMm2;
				fibMMm2 = fibM - fibMMm1;
				offset = i;
			} else if (arr1[i] > y) {
				fibM = fibMMm2;
				fibMMm1 = fibMMm1 - fibMMm2;
				fibMMm2 = fibM - fibMMm1;
			} else {
				return i;
			}
		}
		if(fibMMm1 && arr1[offset+1] == y) {
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
			if (arr2[i] < x) {
				fibM = fibMMm1;
				fibMMm1 = fibMMm2;
				fibMMm2 = fibM - fibMMm1;
				offset = i;
			} else if (arr2[i] > x) {
				fibM = fibMMm2;
				fibMMm1 = fibMMm1 - fibMMm2;
				fibMMm2 = fibM - fibMMm1;
			} else {
				return i;
			}
		}
		if(fibMMm1 && arr2[offset+1] == x) {
			return offset+1;
		}
	}
    return -1;
}

int jumpSearch(string arr1[], int arr2[], int x, string y, int n, char menuSearch) {
	int step = sqrt(n);
	int prev = 0;
	if (menuSearch == '2' || menuSearch == '4') {
		while (arr1[min(step, n)-1] < y) {
			prev = step;
			step += sqrt(n);
			if (prev >= n) {
				return -1;
			}
		}
		while (arr1[prev] < y) {
			prev++;
			if (prev == min(step, n)) {
				return -1;
			}
		}
		if (arr1[prev] == y) {
			return prev;
		}
	} else if (menuSearch == '1' || menuSearch == '3' || menuSearch == '5') {
		while (arr2[min(step, n)-1] < x) {
			prev = step;
			step += sqrt(n);
			if (prev >= n) {
				return -1;
			}
		}
		while (arr2[prev] < x) {
			prev++;
			if (prev == min(step, n)) {
				return -1;
			}
		}
		if (arr2[prev] == x) {
			return prev;
		}
	}
	return -1;
}

int main() {
	while (true) {
		menu();
	}
	return 0;
}
