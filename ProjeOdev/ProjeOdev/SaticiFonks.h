#pragma once
#include<string>
#include <iostream>
#include "Kullanici.h"
using namespace std;



void Satici::sahipOlunanMallar() {

	if (urunSayisi == 0) {
		cout << "urunler bulunmamaktadir.." << endl;

	}
	else {
		for (int i = 0; i < urunSayisi; i++) {

			cout << i + 1 << ".urunun adi: " << urun[i] << " " << i + 1 << ".urunun miktari: " << urunMiktar[i] << " kg " << i + 1 << ".urunun birim fiyati: " << urunFiyat[i] << " tl" << endl;

		}
	}

}


string Satici::adDondur() {

	return ad;
}





int Satici::urunSayisiDondur() {
	return urunSayisi;
}




void Satici::urunEkleme(string urunad, double urunMiktar, double urunFiyat) {

	this->urun[urunSayisi] = urunad;
	this->urunMiktar[urunSayisi] = urunMiktar;
	this->urunFiyat[urunSayisi] = urunFiyat;
	urunSayisi++;

}

void Satici::satilacakUrunGösterme(int urunK) {

	cout << "urun ad: " <<  urun[urunK] << " urun miktar: " <<  urunMiktar[urunK] << " kg " << " urun birim fiyat: " <<  urunFiyat[urunK] << " tl" << endl;
}

double Satici::getUrunFiyat(int urunK) {

	return  urunFiyat[urunK];
}

double Satici::getUrunMiktar(int urunK) {
	return urunMiktar[urunK];
}

//urun miktarindan ticaret yapýlmýs ise ona uygun azalma gerceklestirildi
void Satici::setUrunMiktar(double miktar, int urunK) {

	this-> urunMiktar[urunK] = this->urunMiktar[urunK] - miktar;
}

string Satici::getUrunAd(int urunK) {

	return urun[urunK];
}

//urun satilmissa ona gore para arttýrýlmasý icin set islemi gerceklestirildi
void Satici::setPara(double para) {

	this->para = this->para + para;
}


void Satici::satilanEkleme(string urunAd, double urunmiktar, double birimFiyat, int urunYil, int urunAy, int urunGun) {

	this->satilanUrun[satilanSayisi] = urunAd;
	this->satilanUrunMiktar[satilanSayisi] = urunmiktar;
	this->satilanBirimFiyat[satilanSayisi] = birimFiyat;
	this->satilanUrunYil[satilanSayisi] = urunYil;
	this->satilanUrunAy[satilanSayisi] = urunAy;
	this->satilanUrunGun[satilanSayisi] = urunGun;

	satilanSayisi++;


}






void Satici::satilanUrunlerGoster() {
	system("cls");
	cout << "\t\t --- Satilan urunler --- " << endl << endl;

	if (satilanSayisi > 0) {

		for (int i = 0; i < satilanSayisi; i++) {

			cout << "Tarih: " << satilanUrunGun[i] << "." << satilanUrunAy[i] << "." << satilanUrunYil[i] << " satilan urun: " << satilanUrun[i] << " satilan urun miktar: " << satilanUrunMiktar[i] << " satilan urun birim fiyat: " << satilanBirimFiyat[i] << endl;
		}

	}
	else {
		cout << "Satilan urun bulunmamaktadir.." << endl;
	}

}


void Satici::raporOlusturma() {

	system("cls");

	int tarih1Yil, tarih1Ay, tarih1Gun, tarih2Yil, tarih2Ay, tarih2Gun;
	int temp;
	string tarih;
	int kontrol = 0;
	string urunAD;
	cout << "hangi tarihlerde rapor olusturmak istediginizi giriniz.." << endl;
	cout << "Birinci tarih'in Yili: ";
	cin >> tarih1Yil;
	cout << "Birinci tarih'in Ayi: ";
	cin >> tarih1Ay;
	cout << "Birinci tarih'in Gun: ";
	cin >> tarih1Gun;
	cout << endl;

	cout << "Ikinci tarih Yili: ";
	cin >> tarih2Yil;
	cout << "Ikinci tarih Ay'i: ";
	cin >> tarih2Ay;
	cout << "Ikinci tarih Gun: ";
	cin >> tarih2Gun;

	//kucuk olan tarihi tarih1'e atanmasýný kontrol ediyorum
	if (tarih1Yil > tarih2Yil) {
		temp = tarih1Yil;
		tarih1Yil = tarih2Yil;
		tarih2Yil = temp;

		temp = tarih1Ay;
		tarih1Ay = tarih2Ay;
		tarih2Ay = temp;

		temp = tarih1Gun;
		tarih1Gun = tarih2Gun;
		tarih2Gun = temp;

	}
	else if (tarih1Yil == tarih2Yil && tarih1Ay > tarih2Ay) {

		temp = tarih1Ay;
		tarih1Ay = tarih2Ay;
		tarih2Ay = temp;

		temp = tarih1Gun;
		tarih1Gun = tarih2Gun;
		tarih2Gun = temp;

	}
	else if (tarih1Yil == tarih2Yil && tarih1Ay == tarih2Ay && tarih1Gun > tarih2Gun) {

		temp = tarih1Gun;
		tarih1Gun = tarih2Gun;
		tarih2Gun = temp;

	}
	cout << endl << "Hangi ürünün listelenmek istediginizi giriniz: ";
	cin >> urunAD;

	cout << endl << tarih1Gun << "." << tarih1Ay << "." << tarih1Yil << "  --  " << tarih2Gun << "." << tarih2Ay << "." << tarih2Yil << " tarihleri arasindaki " << urunAD << " adli urunlerin raporlari olusturuluyor.." << endl;

	ofstream dosya;
	dosya.open("SaticiRapor.csv");

	dosya << "Tarih" << ";" << "Urun tipi" << ";" << "Alim tutari" << ";" << "Miktar" << endl;


	for (int i = 0; i < satilanSayisi; i++) {

		if (satilanUrun[i] == urunAD) {

			if (satilanUrunYil[i] > tarih1Yil && satilanUrunYil[i] < tarih2Yil) {

				tarih = to_string(satilanUrunGun[i]) + "." + to_string(satilanUrunAy[i]) + "." + to_string(satilanUrunYil[i]);
				dosya << tarih << ";" << urunAD << ";" << satilanBirimFiyat[i] << ";" << satilanUrunMiktar[i] << endl;

				kontrol = 1;
			}
			else if (satilanUrunYil[i] == tarih1Yil) {

				if (satilanUrunAy[i] > tarih1Ay) {
					tarih = to_string(satilanUrunGun[i]) + "." + to_string(satilanUrunAy[i]) + "." + to_string(satilanUrunYil[i]);

					dosya << tarih << ";" << urunAD << ";" << satilanBirimFiyat[i] << ";" << satilanUrunMiktar[i] << endl;
					kontrol = 1;
				}
				else if (satilanUrunAy[i] == tarih1Ay) {
					if (satilanUrunGun[i] >= tarih1Gun) {

						tarih = to_string(satilanUrunGun[i]) + "." + to_string(satilanUrunAy[i]) + "." + to_string(satilanUrunYil[i]);

						dosya << tarih << ";" << urunAD << ";" << satilanBirimFiyat[i] << ";" << satilanUrunMiktar[i] << endl;
						kontrol = 1;
					}
				}
			}
			else if (satilanUrunYil[i] == tarih2Yil) {

				if (satilanUrunAy[i] < tarih2Ay) {

					tarih = to_string(satilanUrunGun[i]) + "." + to_string(satilanUrunAy[i]) + "." + to_string(satilanUrunYil[i]);
					dosya << tarih << ";" << urunAD << ";" << satilanBirimFiyat[i] << ";" << satilanUrunMiktar[i] << endl;
					kontrol = 1;
				}
				else if (satilanUrunAy[i] == tarih2Ay) {
					if (satilanUrunGun[i] <= tarih2Gun) {

						tarih = to_string(satilanUrunGun[i]) + "." + to_string(satilanUrunAy[i]) + "." + to_string(satilanUrunYil[i]);

						dosya << tarih << ";" << urunAD << ";" << satilanBirimFiyat[i] << ";" << satilanUrunMiktar[i] << endl;
						kontrol = 1;
					}
				}

			}


		}

	}

	if (kontrol == 0) {
		cout << endl << "Girilen degerlere uygun urunler bulunamamistir" << endl;
	}

	dosya.close();



}

