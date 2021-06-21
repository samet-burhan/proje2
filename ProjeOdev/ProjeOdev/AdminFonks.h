#pragma once
#include<string>
#include <iostream>
#include "Kullanici.h"
using namespace std;



string Admin::kullanciAdDondur() {

	return kullanciAdi;
}

string Admin::parolaDondur() {

	return password;
}

int Admin::onaylanacakSaticiSayiDondur() {



	return OnaylanacakSaticiSayisi;

}

int Admin::onaylanacakAliciSayiDondur() {


	return OnaylanacakAliciSayisi;
}

int Admin::onSiparisSayiDondur() {

	return OnSiparisSayisi;
}


int Admin::onaylanacakSaticiID(int secimSatici) {

	return OnaylanacakSaticiID[secimSatici];
}

int Admin::onaylanacakAliciID(int secimAlici) {

	return OnaylancakAliciID[secimAlici];
}



string Admin::getkUrunAd(int secimSatici) {

	return OnaylanacakUrunAd[secimSatici];
}

double  Admin::getUrunMiktar(int secimSatici) {

	return OnaylanacakUrunMiktar[secimSatici];
}

double Admin::getUrunFiyat(int secimSatici) {

	return OnaylanacakUrunFiyat[secimSatici];
}

double Admin::getPara(int secimAlici) {

	return OnaylanacakPara[secimAlici];
}


//onaylanmasý beklenen saticilar adminde dizilerle tutuldu
void Admin::OnaylacakSaticiFonk(string ad, string soyad, string tc, string urunad, double urunmiktar, double urunFiyat, int saticiId) {

	this->OnaylanacakSaticiAd[OnaylanacakSaticiSayisi] = ad;
	this->OnaylanacakSaticiSoyad[OnaylanacakSaticiSayisi] = soyad;
	this->OnaylacakSaticiTc[OnaylanacakSaticiSayisi] = tc;
	this->OnaylanacakUrunAd[OnaylanacakSaticiSayisi] = urunad;
	this->OnaylanacakUrunMiktar[OnaylanacakSaticiSayisi] = urunmiktar;
	this->OnaylanacakUrunFiyat[OnaylanacakSaticiSayisi] = urunFiyat;
	this->OnaylanacakSaticiID[OnaylanacakSaticiSayisi] = saticiId;

	OnaylanacakSaticiSayisi++;

}

//onaylanmasý beklenen alicilar adminde dizilerle tutuldu
void Admin::OnaylanacakAliciFonk(string ad, string soyad, string tc, double para, int AliciId) {

	this->OnaylanacakAliciAd[OnaylanacakAliciSayisi] = ad;
	this->OnaylanacakAliciSoyad[OnaylanacakAliciSayisi] = soyad;
	this->OnaylanacaAliciTc[OnaylanacakAliciSayisi] = tc;
	this->OnaylanacakPara[OnaylanacakAliciSayisi] = para;
	this->OnaylancakAliciID[OnaylanacakAliciSayisi] = AliciId;

	OnaylanacakAliciSayisi++;


}

void Admin::OnaylanacakSaticiGoster() {

	if (OnaylanacakSaticiSayisi > 0) {

		for (int i = 0; i < OnaylanacakSaticiSayisi; i++) {
			cout << "\t" << (i + 1) << ". satici ad: " << OnaylanacakSaticiAd[i] << " satici soyad: " << OnaylanacakSaticiSoyad[i] << " satici tc: " << OnaylacakSaticiTc[i] << " urunAd: " << OnaylanacakUrunAd[i] << " urun miktar: " << OnaylanacakUrunMiktar[i] << " kg " << " urun birim fiyat: " << OnaylanacakUrunFiyat[i] << " tl" << endl;
		}
	}

	else {
		cout << "\t" << "Suan onaylanacak satici bulunmamaktadir." << endl;
	}
}

void Admin::onaylanacakAliciGoster() {

	if (OnaylanacakAliciSayisi > 0) {

		for (int i = 0; i < OnaylanacakAliciSayisi; i++) {
			cout << "\t" << (i + 1) << ". alici ad: " << OnaylanacakAliciAd[i] << " alici soyad: " << OnaylanacakAliciSoyad[i] << " alici tc: " << OnaylanacaAliciTc[i] << " para: " << OnaylanacakPara[i] << " tl" << endl;
		}

	}
	else {
		cout << "\t" << "Suan onaylanacak alici bulunmamaktadir." << endl;


	}

}


//onaylanmýs saticilarin admin onaylanmasý beklenen dizilerden cýkarilma islemi gerceklestirildi
void Admin::SetOnaySaticiFonk(int secimSatici) {

	for (int i = secimSatici; i < OnaylanacakSaticiSayisi - 1; i++) {
		OnaylanacakSaticiAd[i] = OnaylanacakSaticiAd[i + 1];
		OnaylanacakSaticiSoyad[i] = OnaylanacakSaticiSoyad[i + 1];
		OnaylacakSaticiTc[i] = OnaylacakSaticiTc[i + 1];
		OnaylanacakUrunAd[i] = OnaylanacakUrunAd[i + 1];
		OnaylanacakUrunMiktar[i] = OnaylanacakUrunMiktar[i + 1];
		OnaylanacakUrunFiyat[i] = OnaylanacakUrunFiyat[i + 1];
		OnaylanacakSaticiID[i] = OnaylanacakSaticiID[i + 1];

	}

	OnaylanacakSaticiSayisi--;
}


//onaylanmýs alicilarin admin onaylanmasý beklenen dizilerden cýkarýlma islemi gerceklestirildi
void Admin::SetOnayAliciFonk(int secimAlici) {

	for (int i = secimAlici; i < OnaylanacakAliciSayisi - 1; i++) {
		OnaylanacakAliciAd[i] = OnaylanacakAliciAd[i + 1];
		OnaylanacakAliciSoyad[i] = OnaylanacakAliciSoyad[i + 1];
		OnaylanacaAliciTc[i] = OnaylanacaAliciTc[i + 1];
		OnaylanacakPara[i] = OnaylanacakPara[i + 1];
		OnaylancakAliciID[i] = OnaylancakAliciID[i + 1];

	}
	OnaylanacakAliciSayisi--;
}


void Admin::OnSiparisAliciFonk(string ad, int SaticiId, string urunAd, double urunmiktar, double urunFiyat) {

	OnSiparisAliciAd[OnSiparisSayisi] = ad;
	OnSiparisAliciID[OnSiparisSayisi] = SaticiId;
	OnSiparisUrunAD[OnSiparisSayisi] = urunAd;
	OnSiparisUrunMiktar[OnSiparisSayisi] = urunmiktar;
	OnSiparisUrunFiyat[OnSiparisSayisi] = urunFiyat;

	OnSiparisSayisi++;
}

void Admin::OnSiparisGoster() {

	if (OnSiparisSayisi == 0) {
		cout << "on sipariste bulunan alici bulunmamaktadir.." << endl;
	}
	else {
		for (int i = 0; i < OnSiparisSayisi; i++) {
			cout << "Id: " << OnSiparisAliciID[i] << " ad: " << OnSiparisAliciAd[i] << " urun ad: " << OnSiparisUrunAD[i] << " urun miktar: " << OnSiparisUrunMiktar[i] << " urun fiyat: " << OnSiparisUrunFiyat[i] << endl;
				
		}
	}

	
}

string Admin::getOnSiparisUrunAd(int onSecim) {

	return OnSiparisUrunAD[onSecim];
}

double Admin::getOnSiparisUrunFiyat(int onSecim) {

	return OnSiparisUrunFiyat[onSecim];
}

double Admin::getOnSiparisUrunMiktar(int onSecim) {

	return OnSiparisUrunMiktar[onSecim];
}

int Admin::getOnsiparisAliciIDDondur(int onSecim) {

	return OnSiparisAliciID[onSecim];
}

void Admin::setOnSiparisFonk(int onSecim) {


	for (int i = onSecim; i < OnSiparisSayisi-1; i++) {
		OnSiparisAliciAd[i] = OnSiparisAliciAd[i + 1];
		OnSiparisAliciID[i] = OnSiparisAliciID[i + 1];
		OnSiparisUrunAD[i] = OnSiparisUrunAD[i + 1];
		OnSiparisUrunFiyat[i] = OnSiparisUrunFiyat[i + 1];
		OnSiparisUrunMiktar[i] = OnSiparisUrunMiktar[i + 1];


	}
	OnSiparisSayisi--;
}