#pragma once
#include<string>
#include <iostream>
#include <string>
#include "Kullanici.h"
using namespace std;


void Alici::paraEkleme(double para) {

	this->para = para + this->para;
}

void Alici::setPara(double para) {

	this->para = this->para - para;
}





//al�nan urunlerin dizilerde tutulma islemi icin olusturuldu
void Alici::siparisEdilenlerEkleme(string alinanUrunAd, double alinanmiktar, double odenenTutar, int siparisEdilenUrunY�l, int siparisEdilenUrunAy, int siparisEdilenUrunGun, double siparisEdilenBirimFiyat) {

	siparisEdilenUrun[siparisSayisi] = alinanUrunAd;
	siparisEdilenUrunMiktar[siparisSayisi] = alinanmiktar;
	siperisteOdenentutar[siparisSayisi] = odenenTutar;
	this->siparisEdilenBirimFiyat[siparisSayisi] = siparisEdilenBirimFiyat;
	this->siparisEdilenUrunY�l[siparisSayisi] = siparisEdilenUrunY�l;
	this->siparisEdilenUrunAy[siparisSayisi] = siparisEdilenUrunAy;
	this->siparisEdilenUrunGun[siparisSayisi] = siparisEdilenUrunGun;

	siparisSayisi++;
}

void Alici::siparislerGosterme() {
	system("cls");

	cout << "\t\t -- S�PAR�SLER�M ---" << endl;


	if (siparisSayisi > 0) {

		for (int i = 0; i < siparisSayisi; i++) {
			cout << "\tTarih:"<< siparisEdilenUrunGun[i]<<"."<< siparisEdilenUrunAy[i]<<"."<< siparisEdilenUrunY�l[i] <<"  alinan urun ad: " << siparisEdilenUrun[i] << " alinan urunun miktari: " << siparisEdilenUrunMiktar[i] <<" alinan urun birim fiyat: "<< siparisEdilenBirimFiyat[i] <<" alinan urun icin odenen tutar: " << siperisteOdenentutar[i] << endl;
		}

	}
	else {
		cout << "siparisiniz bulunmamaktadir." << endl;
	}

}

void Alici::raporOlusturma() {
	system("cls");
	
	int tarih1Y�l, tarih1Ay, tarih1Gun, tarih2Y�l, tarih2Ay, tarih2Gun;
	int temp;
	string tarih;
	int kontrol = 0;
	string urunAD;
	cout << "hangi tarihlerde rapor olusturmak istediginizi giriniz.." << endl;
	cout << "Birinci tarih'in Y�l�: ";
	cin >> tarih1Y�l;
	cout << "Birinci tarih'in Ay�: ";
	cin >> tarih1Ay;
	cout << "Birinci tarih'in Gun: ";
	cin >> tarih1Gun;
	cout << endl;

	cout << "Ikinci tarih Y�l�: ";
	cin >> tarih2Y�l;
	cout << "Ik�nc� tarih Ay'�: ";
	cin >> tarih2Ay;
	cout << "Ik�nc� tarih Gun: ";
	cin >> tarih2Gun;


	//kucuk olan tarihi tarih1'e atanmas�n� kontrol ediyorum
	if (tarih1Y�l > tarih2Y�l) {
		temp = tarih1Y�l;
		tarih1Y�l = tarih2Y�l;
		tarih2Y�l = temp;

		temp = tarih1Ay;
		tarih1Ay = tarih2Ay;
		tarih2Ay = temp;

		temp = tarih1Gun;
		tarih1Gun = tarih2Gun;
		tarih2Gun = temp;

	}
	else if (tarih1Y�l == tarih2Y�l && tarih1Ay > tarih2Ay) {

		temp = tarih1Ay;
		tarih1Ay = tarih2Ay;
		tarih2Ay = temp;

		temp = tarih1Gun;
		tarih1Gun = tarih2Gun;
		tarih2Gun = temp;

	}
	else if (tarih1Y�l == tarih2Y�l && tarih1Ay == tarih2Ay && tarih1Gun > tarih2Gun) {

		temp = tarih1Gun;
		tarih1Gun = tarih2Gun;
		tarih2Gun = temp;

	}
	cout << endl << "Hangi �r�n�n listelenmek istediginizi giriniz: ";
	cin >> urunAD;

	cout << endl << tarih1Gun << "." << tarih1Ay << "." << tarih1Y�l << "  --  " << tarih2Gun << "." << tarih2Ay << "." << tarih2Y�l << " tarihleri arasindaki "<<urunAD <<" adl� urunlerin raporlari olusturuluyor.." << endl;

	ofstream dosya;
	dosya.open("AliciRapor.csv");

	dosya << "Tarih" << ";" << "Urun tipi" << ";" << "Al�m tutari" << ";" << "Miktar" << endl;



	for (int i = 0; i < siparisSayisi; i++) {
		
		if (siparisEdilenUrun[i] == urunAD) {

			if (siparisEdilenUrunY�l[i] > tarih1Y�l && siparisEdilenUrunY�l[i] < tarih2Y�l) {

				tarih = to_string(siparisEdilenUrunGun[i]) + "." + to_string(siparisEdilenUrunAy[i]) + "." + to_string(siparisEdilenUrunY�l[i]);
				dosya << tarih<<";" << urunAD << ";" << siparisEdilenBirimFiyat[i] << ";" << siparisEdilenUrunMiktar[i] << endl;

				kontrol = 1;
			}
			else if (siparisEdilenUrunY�l[i] == tarih1Y�l) {

				if (siparisEdilenUrunAy[i] > tarih1Ay) {
					tarih = to_string(siparisEdilenUrunGun[i]) + "." + to_string(siparisEdilenUrunAy[i]) + "." + to_string(siparisEdilenUrunY�l[i]);

					dosya <<tarih << ";" << urunAD << ";" << siparisEdilenBirimFiyat[i] << ";" << siparisEdilenUrunMiktar[i] << endl;
					kontrol = 1;
				}
				else if (siparisEdilenUrunAy[i] == tarih1Ay) {
					if (siparisEdilenUrunGun[i] >= tarih1Gun) {

						tarih = to_string(siparisEdilenUrunGun[i]) + "." + to_string(siparisEdilenUrunAy[i]) + "." + to_string(siparisEdilenUrunY�l[i]);

						dosya <<tarih<< ";" << urunAD << ";" << siparisEdilenBirimFiyat[i] << ";" << siparisEdilenUrunMiktar[i] << endl;
						kontrol = 1;
					}
				}
			}
			else if (siparisEdilenUrunY�l[i] == tarih2Y�l) {

				if (siparisEdilenUrunAy[i] < tarih2Ay) {

					tarih = to_string(siparisEdilenUrunGun[i]) + "." + to_string(siparisEdilenUrunAy[i]) + "." + to_string(siparisEdilenUrunY�l[i]);
					dosya << tarih<< ";" << urunAD << ";" << siparisEdilenBirimFiyat[i] << ";" << siparisEdilenUrunMiktar[i] << endl;
					kontrol = 1;
				}
				else if (siparisEdilenUrunAy[i] == tarih2Ay) {
					if (siparisEdilenUrunGun[i] <= tarih2Gun) {

						tarih = to_string(siparisEdilenUrunGun[i]) + "." + to_string(siparisEdilenUrunAy[i]) + "." + to_string(siparisEdilenUrunY�l[i]);

						dosya <<tarih << ";" << urunAD << ";" << siparisEdilenBirimFiyat[i] << ";" << siparisEdilenUrunMiktar[i] << endl;
						kontrol = 1;
					}
				}

			}


}

	}

	if (kontrol == 0) {
		cout<<endl << "Girilen degerlere uygun urunler bulunamamistir" << endl;
	}

	dosya.close();

	





}




