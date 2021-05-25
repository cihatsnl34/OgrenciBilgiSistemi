#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "conio.h"

#define EngDosyaAdi "eng101.txt"
#define FizDosyaAdi "fiz101.txt"
#define MatDosyaAdi "mat101.txt"

using namespace std;

struct ders {
	char derskodu[10];
	char dersadi[50];
	ders* sonraki;
};
struct ogrenci_Node {
	char ogrno[15];
	char ad[30];
	char soyad[30];
	ders* dersNode;
	ogrenci_Node* sonraki;
};

ogrenci_Node* ogrHead = NULL;
int ogrSayi = 0;

void listeKur();	
void dersSil();		
void ogrenciSil();	
void listele();		
int ara();			
void kesisimBul();	
void dosyayaYaz();	




void menu_yazdir();
bool islemYap(char secim);
ogrenci_Node *creatNode(char* Ad, char* Soyad, char* No, char* Dersadi, char* DersKodu);
void ekleNode(char* yeniAd, char* yeniSoyad, char* yeniNo, char* newDersadi, char* newDersKodu);
void listeBos();


int main()
{
    listeKur();
	bool bitir = false;
	char menuSec;
	while (!bitir)
	{
		menu_yazdir();
		cin >> menuSec;
		bitir = islemYap(menuSec);
	}


    listeBos();
	return EXIT_SUCCESS;
}

void menu_yazdir() {
	cout <<  endl;
	cout << "-------ISLEM MENUSU-------" << endl;
	cout << "Bir islem seciniz" << endl;
	cout << "A: Arama" << endl;
	cout << "D: Ders Silme" << endl;
	cout << "K: Kesisim Bulma" << endl;
	cout << "L: Listeyi Ekrana Yazdirma" << endl;
	cout << "O: Ogrenci Silme" << endl;
	cout << "Y: Dosyaya Yazma" << endl;
	cout << "C: Cikis" << endl;
	cout << endl;
	cout << "Bir secenek giriniz {A, D, K, L, O, Y, C} : ";
}
bool islemYap(char secim) {
	bool sonlan = false;
	switch (secim)
	{
	case 'A':
	case 'a':
        system ("cls");
        ara();
        system("pause");
		break;
	case 'D':
	case 'd':
	    system ("cls");
		dersSil();
		system("pause");
		break;
	case 'K':
	case 'k':
		kesisimBul();
		system("pause");
		break;
	case 'L':
	case 'l':
        listele();
        system("pause");
		break;
	case 'O':
	case 'o':
	    system ("cls");
        ogrenciSil();
        system("pause");
		break;
	case 'Y':
	case 'y':
		dosyayaYaz();
		cout << "Dosya: 'Liste_Cikti.txt'  Basariyla yaratilmistir.";
		system("pause");
		break;
	case 'C':
	case 'c':
		cout << "Programi sonlandirmak istediginize emin misiniz? {E/H} : ";
		cin >> secim;
		if (secim == 'E' || secim == 'e') {
			sonlan = true;
		}
		break;
	default:
		cout << "Yanlis Secim Yaptiniz. Tekrar deneyiniz {A, D, K, L, O, Y, C}";
		cin >> secim;
		sonlan = islemYap(secim);
		break;
	}
	return sonlan;
}
void listeKur() {	
	ifstream newFile;
	string line, dersAdi, dersKodu;
	
	string space = " ";
	size_t bulundu;
	string OgrNo;
	string Ad;
	string Soyad;
	int c;

    
	newFile.open(FizDosyaAdi, ios::in);
	if (!newFile)
	{
		cerr << "Dosya Acılmadı" << endl;
		exit(1);
	}
	
	getline(newFile,line);
	bulundu = line.find(space);
	dersKodu = line.substr(0, bulundu);
	dersAdi = line.substr(bulundu+1 , line.length()- dersKodu.length());


	while (getline(newFile, line))
	{
		c = line.length();
		bulundu = line.find(space);
		OgrNo = line.substr(0, 7);
		Ad = line.substr(8, bulundu - 8);
		Soyad = line.substr(Ad.length() + 9);
		ekleNode( (char*)OgrNo.c_str(),(char*)Ad.c_str(), (char*)Soyad.c_str(), (char*)dersAdi.c_str(), (char*)dersKodu.c_str());
	}
	newFile.close();

	
	newFile.open(MatDosyaAdi, ios::in);
	if (!newFile) 
	{
		cerr << "Dosya Acılmadı" << endl;
		exit(1);
	}
	
	getline(newFile,line);
	bulundu = line.find(space);
	dersKodu = line.substr(0, bulundu);
	dersAdi = line.substr(bulundu+1 , line.length()- dersKodu.length());


	while (!newFile.eof() && getline(newFile, line))
	{
		c = line.length();
		bulundu = line.find(space);
		OgrNo = line.substr(0, 7);
		Ad = line.substr(8, bulundu - 8);
		Soyad = line.substr(Ad.length() + 9);
    ekleNode( (char*)OgrNo.c_str(),(char*)Ad.c_str(), (char*)Soyad.c_str(), (char*)dersAdi.c_str(), (char*)dersKodu.c_str());	}
	newFile.close();


    
	newFile.open(EngDosyaAdi, ios::in);
	if (!newFile) 
	{
		cerr << "Dosya Acılmadı" << endl;
		exit(1);
	}
	
	getline(newFile,line);
	bulundu = line.find(space);
	dersKodu = line.substr(0, bulundu);
	dersAdi = line.substr(bulundu+1 , line.length()- dersKodu.length());


	while (!newFile.eof() && getline(newFile, line))
	{
		c = line.length();
		bulundu = line.find(space);
		OgrNo = line.substr(0, 7);
		Ad = line.substr(8, bulundu - 8);
		Soyad = line.substr(Ad.length() + 9);
		ekleNode( (char*)OgrNo.c_str(),(char*)Ad.c_str(), (char*)Soyad.c_str(), (char*)dersAdi.c_str(), (char*)dersKodu.c_str());
	}
	newFile.close();
}
ogrenci_Node *creatNode(char* No, char* Ad, char* Soyad,  char* Dersadi, char* DersKodu) {
	ogrenci_Node* yeniOgr;
	ders* newDers;

	yeniOgr = new ogrenci_Node;
	strcpy(yeniOgr->ogrno , No);
	strcpy(yeniOgr->ad , Ad);
	strcpy(yeniOgr->soyad , Soyad);


	newDers = new ders;
	yeniOgr->dersNode = newDers;
	strcpy(newDers->dersadi, Dersadi);
	strcpy(newDers->derskodu, DersKodu);
	newDers->sonraki = NULL;
	yeniOgr->sonraki = NULL;

	return yeniOgr;
}
void ekleNode(char* yeniNo, char* yeniAd, char* yeniSoyad,  char* newDersadi, char* newDersKodu) {
	ogrenci_Node *yeniOgr, *scan;
	ogrenci_Node* arka;
	ders* newDers;

	scan = ogrHead;
	if (ogrHead == NULL) 
	{
		ogrHead = creatNode( yeniNo, yeniAd, yeniSoyad, newDersadi, newDersKodu);
		ogrSayi++;
		return;
	}
	if (strcmp(yeniNo, scan->ogrno)<0)
	{
		yeniOgr = creatNode( yeniNo, yeniAd, yeniSoyad, newDersadi, newDersKodu);
		yeniOgr->sonraki = ogrHead;
		ogrHead = yeniOgr;
		ogrSayi++;
		return;
	}
	while (scan && (strcmp(yeniNo, scan->ogrno)>0))
	{
		arka = scan;
		scan = scan->sonraki;
	}
	if (scan &&  (strcmp(yeniNo, scan->ogrno) == 0)) 
	{
		newDers = new ders; 
		newDers->sonraki = scan->dersNode;
		scan->dersNode = newDers;
		strcpy(newDers->dersadi, newDersadi);
		strcpy(newDers->derskodu, newDersKodu);
	}
	else
	{
		yeniOgr = creatNode( yeniNo, yeniAd, yeniSoyad, newDersadi, newDersKodu);
		if (scan) 
		{
			yeniOgr->sonraki = scan;
            arka->sonraki = yeniOgr;
		}
		else 
		{
			arka->sonraki = yeniOgr;
			ogrSayi++;
		}
	}
}
void listele() {
	ogrenci_Node* current_node;
	if (ogrHead == NULL)
	{
		cout << "ogrenci yok" << endl;
	}
	else
	{
		current_node = ogrHead;
		while (current_node != NULL)
		{
		    if(current_node->dersNode->sonraki != NULL){ 
                string ikinciDersAd, ikinciDersKod;
                ikinciDersAd = current_node->dersNode->sonraki->dersadi ;
                ikinciDersKod = current_node->dersNode->sonraki->derskodu ;
                if(current_node->dersNode->sonraki->sonraki == NULL){
                    cout << "Ogr no: " << current_node->ogrno << "  |  " << "Ad:" << current_node->ad << "    " << "Soyad:" << current_node->soyad << "  |  " <<  "1.Ders Adi:" << current_node->dersNode->dersadi << "  " << "1.Ders Kodu:" << current_node->dersNode->derskodu << "  |  " << "2.Ders Adi: " << ikinciDersAd <<"  "<<"2.Ders Kod: " << ikinciDersKod << endl;
                    current_node = current_node->sonraki;
                }
                else{
                    string ucuncuDersAd, ucuncuDersKod;
                    ucuncuDersAd = current_node->dersNode->sonraki->sonraki->dersadi ;
                    ucuncuDersKod = current_node->dersNode->sonraki->sonraki->derskodu ;
                    cout << "Ogr no: " << current_node->ogrno << "  |  " << "Ad:" << current_node->ad << "  " << "Soyad:" << current_node->soyad << "  |  " <<  "1.Ders Adi:" << current_node->dersNode->dersadi << "  " << "1.Ders Kodu:" << current_node->dersNode->derskodu << "  |  " << "2.Ders Adi: " << ikinciDersAd <<"  "<<"2.Ders Kod: " << ikinciDersKod << "  |  " << "3.Ders Adi: " << ucuncuDersAd <<"\t"<<"3.Ders Kod: " << ucuncuDersKod << endl;
                    current_node = current_node->sonraki;
                }
		    }
		    else{
			cout << "Ogr no: " << current_node->ogrno << "  |  " << "Ad:" << current_node->ad << "  " << "Soyad:" << current_node->soyad << "  |  " <<  "Ders Adi:" << current_node->dersNode->dersadi << "  " << "Ders Kodu:" << current_node->dersNode->derskodu << endl;
			current_node = current_node->sonraki;
            }
		}
	}
}
void listeBos() {
	ogrenci_Node* p;
	ders* q;
	while (ogrHead)
	{
		p = ogrHead;
		ogrHead = ogrHead->sonraki;
		q = p->dersNode;
		while (q)
		{
			p->dersNode = p->dersNode->sonraki;
			delete q;
			q = p->dersNode;
		}
		delete p;
	}
	ogrSayi = 0;
}
void dersSil() {	
	string ogrNo;
	int dersNo;

	ogrenci_Node *scan, *current;
	ders *pDers;
	int say = 1 , i=1;
    scan = ogrHead;
	current = ogrHead;


	cout << "Ders Silme Ekrani\n=========================" << endl;
	cout << "Ogrenci no giriniz: ";
	cin >> ogrNo;


    if(ogrNo == scan->ogrno){ 
            cout << "\nOgrenci Bilgileri:\n==========================\n" <<"Ogrenci Adi ve Soyadi: " << scan->ad << " " << scan->soyad << "\n" << say << ".Ogrenci, Ogrenci No:" << scan->ogrno << "\n" <<endl;
            pDers = scan->dersNode;
            cout <<  "Aldigi Dersler:" << "\n==========================" <<endl;
            while(pDers){
                cout << i << ". Ders: " << pDers->derskodu  << ": " << pDers->dersadi<< "\n";
                pDers = pDers->sonraki;
                i++;
            }
            cout << "\n\nSilmek istediginiz ders no yaziniz(1,2,3...): ";
            cin >> dersNo;
            switch(dersNo){
            case 1:
                ogrHead->dersNode = scan->dersNode->sonraki;
                free(scan->dersNode);
                cout << "1.Ders Basariyla Silimistir\n";
                break;
            case 2:
                if(i != 3){
                    cout << "Yanlis Rakam Girdiniz\n";
                    break;
                }
                else{
                    ogrHead->dersNode->sonraki = scan->dersNode->sonraki->sonraki;
                    free(scan->dersNode->sonraki);
                    cout << "2.Ders Basariyla Silimistir\n";
                }
                break;
            case 3:
                if(i != 4){
                    cout << "Yanlis Rakam Girdiniz\n";
                    break;
                }
                else{
                    ogrHead->dersNode->sonraki->sonraki = scan->dersNode->sonraki->sonraki->sonraki;
                    free(scan->dersNode->sonraki->sonraki);
                    cout << "3.Ders Basariyla Silimistir\n";
                }
                break;
            default:
                cout << "Yanlis Rakam Girdiniz\n";
                break;

            }
            return;
    }
    while (ogrNo != scan->ogrno){
        scan = scan->sonraki;
        current = scan;
    }
            cout << "\nOgrenci Bilgileri:\n==========================\n" <<"Ogrenci Adi ve Soyadi: " << scan->ad << " " << scan->soyad << "\n" << say << ".Ogrenci, Ogrenci No:" << scan->ogrno << "\n" <<endl;
            pDers = scan->dersNode;
            cout <<  "Aldigi Dersler:" << "\n==========================" <<endl;
            while(pDers){
                cout << i << ". Ders: " << pDers->derskodu  << ": " << pDers->dersadi<< "\n";
                pDers = pDers->sonraki;
                i++;
            }
            cout << "\n\nSilmek istediginiz ders no yaziniz(1,2,3...): ";
            cin >> dersNo;
            switch(dersNo){
            case 1:
                current->dersNode = scan->dersNode->sonraki;
                free(scan->dersNode);
                cout << "1.Ders Basariyla Silimistir\n";
                break;
            case 2:
                if(i != 3){
                    cout << "Yanlis Rakam Girdiniz\n";
                    break;
                }
                else{
                    current->dersNode->sonraki = scan->dersNode->sonraki->sonraki;
                    free(scan->dersNode->sonraki);
                    cout << "2.Ders Basariyla Silimistir\n";
                }
                break;
            case 3:
                if(i != 4){
                    cout << "Yanlis Rakam Girdiniz\n";
                    break;
                }
                else{
                    current->dersNode->sonraki->sonraki = scan->dersNode->sonraki->sonraki->sonraki;
                    free(scan->dersNode->sonraki->sonraki);
                    cout << "3.Ders Basariyla Silimistir\n";
                }
                break;
            default:
                cout << "Yanlis Rakam Girdiniz\n";
                break;

            }
}
void ogrenciSil() {	
    string ogrNo;
    char secim;
	ogrenci_Node *scan, *arka;
	ders *pDers;
	int say = 1 , i=1 ;
    scan = ogrHead;
	arka = ogrHead;


	cout << "Ogreni Silme Ekrani\n=========================" << endl;
	cout << "Ogrenci no giriniz: ";
	cin >> ogrNo;


    if(ogrNo == scan->ogrno){
            cout << "\nOgrenci Bilgileri:\n==========================\n" <<"Ogrenci Adi ve Soyadi: " << scan->ad << " " << scan->soyad << "\n" << say << ".Ogrenci, Ogrenci No:" << scan->ogrno << "\n" <<endl;
            pDers = scan->dersNode;
            cout <<  "Aldigi Dersler:" << "\n==========================" <<endl;
            while(pDers){
                cout << i << ". Ders: " << pDers->derskodu  << ": " << pDers->dersadi<< "\n";
                pDers = pDers->sonraki;
                i++;
            }
            cout << "\n\nBu ogrenci silmek istediginiz emin misiniz?(E/H) : ";
            cin >> secim;
            switch(secim){
            case 'e':
            case 'E':
                ogrHead = scan->sonraki;
                free(scan);
                cout << "Ogrenci Basariyla Silimistir\n";
                break;
            case 'H':
            case 'h':
                break;
            default:
                cout << "Yanlis Secim Yaptiniz\n";
                break;
            }
            return;
    }
    while (ogrNo != scan->ogrno){
        arka = scan;
        scan = scan->sonraki;
    }
            cout << "\nOgrenci Bilgileri:\n==========================\n" <<"Ogrenci Adi ve Soyadi: " << scan->ad << " " << scan->soyad << "\n" << say << ".Ogrenci, Ogrenci No:" << scan->ogrno << "\n" <<endl;
            pDers = scan->dersNode;
            cout <<  "Aldigi Dersler:" << "\n==========================" <<endl;
            while(pDers){
                cout << i << ". Ders: " << pDers->derskodu  << ": " << pDers->dersadi<< "\n";
                pDers = pDers->sonraki;
                i++;
            }
            cout << "\n\nBu ogrenci silmek istediginiz emin misiniz?(E/H) : ";
            cin >> secim;
            switch(secim){
            case 'e':
            case 'E':
                arka->sonraki = scan->sonraki;
                free(scan);
                cout << "Ogrenci Basariyla Silimistir\n";
                break;
            case 'H':
            case 'h':
                break;
            default:
                cout << "Yanlis Secim Girdiniz\n";
                break;
            }
}
int ara() {
    int sec;
    cout << "Arama Ekaranina Hos Geldiniz \n================================="<<endl;
    cout << "Arama islemi nasil yapmak isterseniz?\nOgrenci no ile aramak icin 1'e\nSoyad ile aramak icin 2'e basiniz: "<< endl;
    cin >> sec;
    switch(sec){
case 1:
    {
    string ogrNo;
    char *ara_ogrNo;

    cout<< "lutfen ogrenci numarasi giriniz(Tumu icin '*'):"<<endl;
    cin >> ogrNo;

    ara_ogrNo = (char*)ogrNo.c_str();
	ogrenci_Node *scan;
	ders *pders;
	int say=0, i=1;
	int bulunan = 0;
	scan = ogrHead;
	bool tumu = false;
	if (ara_ogrNo[0] == '*'){
        tumu = true;
	}
	while(scan){
        say++;
        if(tumu){
            cout << say << ".Ogrenci: | " << scan->ad << " " << scan->soyad << " | " << "Ogrenci No: "<< scan->ogrno<< " | " << "Aldigi dersler: ";
            pders= scan->dersNode;
            int i = 1;
            while(pders){
                cout << i << ". Ders: " << pders->derskodu  << ": " << pders->dersadi<< "  ";
                pders = pders->sonraki;
                i++;
            }
            cout << "| \n-----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            bulunan++;
        }
        else if(strncmp(ara_ogrNo, scan->ogrno, strlen(ara_ogrNo))== 0){
            bulunan++;
            cout << "\nOgrenci Bilgileri:\n==========================\n" <<"Ogrenci Adi ve Soyadi: " << scan->ad << " " << scan->soyad << "\n" << "Ogrenci No:" << scan->ogrno << "\n" <<endl;
            pders = scan->dersNode;
            cout <<  "Aldigi Dersler:" << "\n==========================" <<endl;
            while(pders){
                cout << i << ". Ders: " << pders->derskodu  << ": " << pders->dersadi<< "  ";
                pders = pders->sonraki;
                i++;
            }
            cout << endl;
        }
        scan = scan->sonraki;
	}
        return bulunan;
  }
case 2:
{
    string araSoyad;
    cout<< "lutfen ogrenci soyadi giriniz(Tumu icin '*'):"<<endl;
    cin >> araSoyad;

    char *ara_soyad;
    ara_soyad = (char*)araSoyad.c_str();

	ogrenci_Node *scan;
	ders *pders;
	int say=0, i=1;
	int bulunan = 0;
	scan = ogrHead;
	bool tumu = false;
	if (ara_soyad[0] == '*'){
        tumu = true;
	}
	while(scan){
        say++;
        if(tumu){
            cout << say << ".Ogrenci: | " << scan->ad << " " << scan->soyad << " | " << "Ogrenci No: "<< scan->ogrno<< " | " << "Aldigi dersler: ";
            pders= scan->dersNode;
            int i = 1;
            while(pders){
                cout << i << ". Ders: " << pders->derskodu  << ": " << pders->dersadi<< "  ";
                pders = pders->sonraki;
                i++;
            }
            cout << "| \n-----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            bulunan++;
        }
        else if(strncmp(ara_soyad, scan->soyad, strlen(ara_soyad))== 0){
            bulunan++;
            cout << "\nOgrenci Bilgileri:\n==========================\n" <<"Ogrenci Adi ve Soyadi: " << scan->ad << " " << scan->soyad << "\n" << "Ogrenci No:" << scan->ogrno << "\n" <<endl;
            pders = scan->dersNode;
            cout <<  "Aldigi Dersler:" << "\n==========================" <<endl;
            while(pders){
                cout << i << ". Ders: " << pders->derskodu  << ": " << pders->dersadi<< "  ";
                pders = pders->sonraki;
                i++;
            }
            cout << endl;
        }
        scan = scan->sonraki;
	}
	return bulunan;
  }
default:
            cout << "Yanlis secim Yaptiniz tekrar secin" << endl;
            break;
    }

}
void kesisimBul() {
    string DersKod_1, DersKod_2;
    ogrenci_Node* scan;
    ders *pDers;
    int say = 0, kesisimSayisi, secim1, secim2;
    scan = ogrHead;
    cout << "Kesisim Bulma Ekrani\n========================" << endl;
    cout << "Mevct Ders Kodlari: \n1. ENG101\n2. FIZ101\n3. MAT101\n-----------------------\n"<<endl;
    cout << "Birinci ders kodu giriniz(1,2,3): ";
    cin >> secim1;
    switch(secim1){
    case 1: DersKod_1 = "ENG101";
        break;
    case 2: DersKod_1 = "FIZ101";
        break;
    case 3: DersKod_1 = "MAT101";
        break;
    default:
        cout << "yanlis secim" << endl;
        return;
    }
    cout << "\nIkinci ders kod numarasi giriniz(1,2,3): ";
    cin >> secim2;
    switch(secim2){
    case 1: DersKod_2 = "ENG101";
        break;
    case 2: DersKod_2 = "FIZ101";
        break;
    case 3: DersKod_2 = "MAT101";
        break;
    default:
        cout << "yanlis secim" << endl;
        return;
    }
    cout << "\nBu iki dersi birlikte alan ogrenciler:\n";

    while (scan != NULL){ 
        say ++;
        kesisimSayisi = 0;
        pDers = scan->dersNode;
        while(pDers){ 
            if(DersKod_1 == pDers->derskodu || DersKod_2 == pDers->derskodu){
                kesisimSayisi++;
            }
            pDers =  pDers->sonraki;
        }
        if(kesisimSayisi == 2){
             cout << say << ".Ogrenci: | " << scan->ad << " " << scan->soyad << " | " << "Ogrenci No: "<< scan->ogrno << endl;
        }
        scan = scan->sonraki;
    }
}
void dosyayaYaz() {
	


    string ogrno;
    string ad;
    string soyad;
    string derskodu;
    string dersadi;
    string line;
    string tab = " | ";
    string bosluk = " ";
    string altsatir = "\n-------------------------------------------------------------------------------------------------\n";



	ogrenci_Node *ogrenciler;
	ders *dersler;
    ofstream  newFile;

    newFile.open("Liste_Cikti.txt", ios::out);

	if (!newFile.is_open())
	{
		cerr << "Dosya Acilamadi" << endl;
		return;
	}
	ogrenciler = ogrHead;
	while(ogrenciler){
        dersler = ogrenciler->dersNode;
        ogrno = ogrenciler->ogrno;
        ad = ogrenciler->ad;
        soyad = ogrenciler->soyad;
        derskodu = dersler->derskodu;
        dersadi = dersler->dersadi;

            if(dersler->sonraki == NULL){
                line = ogrno + tab + ad + bosluk + soyad + tab + derskodu + bosluk + dersadi + altsatir;
                newFile << line;
            }
            else if (dersler->sonraki != NULL && dersler->sonraki->sonraki == NULL ){
                string ikincidersAdi, ikincidersKodu;
                ikincidersAdi = dersler->sonraki->dersadi;
                ikincidersKodu = dersler->sonraki->derskodu;
                line = ogrno + tab + ad + bosluk + soyad + tab + derskodu + bosluk + dersadi + tab + ikincidersKodu + bosluk + ikincidersAdi + altsatir;
                newFile << line;
            }
            else{
                string ikincidersAdi, ikincidersKodu, ucuncuDersAdi, ucuncuDersKodu;
                ikincidersAdi = dersler->sonraki->dersadi;
                ikincidersKodu = dersler->sonraki->derskodu;
                ucuncuDersAdi = dersler->sonraki->sonraki->dersadi;
                ucuncuDersKodu = dersler->sonraki->sonraki->derskodu;
                line = ogrno + tab + ad + bosluk + soyad + tab + derskodu + bosluk + dersadi + tab + ikincidersKodu + bosluk + ikincidersAdi+ tab + ucuncuDersKodu + bosluk + ucuncuDersAdi  + altsatir;
                newFile << line;
            }

        ogrenciler = ogrenciler->sonraki;
	}
	newFile.close();
}
