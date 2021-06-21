#pragma once


#include<string>
using namespace std;


static int saticiSayisi = 0;
static int aliciSayisi = 0;

class Admin {
private:
	string kullanciAdi, password;
	string *OnaylanacakSaticiAd, *OnaylanacakAliciAd, *OnaylanacakSaticiSoyad, *OnaylanacakAliciSoyad, *OnaylacakSaticiTc, *OnaylanacaAliciTc;
	string *OnaylanacakUrunAd;
	double *OnaylanacakUrunMiktar, *OnaylanacakUrunFiyat, *OnaylanacakPara;
	int OnaylanacakSaticiSayisi, OnaylanacakAliciSayisi,OnSiparisSayisi;
	int *OnaylanacakSaticiID, *OnaylancakAliciID;
	int *OnSiparisAliciID;
	string *OnSiparisUrunAD,*OnSiparisAliciAd;
	double *OnSiparisUrunMiktar,*OnSiparisUrunFiyat;



public:
	Admin() {
		kullanciAdi = "admin";
		password = "admin";
		OnaylanacakSaticiID = new int[20];
		OnaylancakAliciID = new int[20];
		OnaylanacakSaticiAd = new string[20];
		OnaylanacakAliciAd = new string[20];
		OnaylanacakSaticiSoyad = new string[20];
		OnaylanacakAliciSoyad = new string[20];
		OnaylacakSaticiTc = new string[20];
		OnaylanacaAliciTc = new string[20];
		OnaylanacakUrunAd = new string[20];
		OnaylanacakUrunMiktar = new double[20];
		OnaylanacakUrunFiyat = new double[20];
		OnaylanacakPara = new double[20];
		OnaylanacakSaticiSayisi = 0;
		OnaylanacakAliciSayisi = 0;

		OnSiparisAliciID = new int[20];
		OnSiparisAliciAd = new string[20];
		OnSiparisUrunAD = new string[20];
		OnSiparisUrunMiktar = new double[20];
		OnSiparisUrunFiyat = new double[20];
		OnSiparisSayisi = 0;

	}


	string kullanciAdDondur();
	void OnaylacakSaticiFonk(string ad, string soyad, string tc, string urunad, double urunmiktar, double urunFiyat, int saticiId);
	void OnaylanacakAliciFonk(string ad, string soyad, string tc, double para, int AliciId);

	void OnaylanacakSaticiGoster();
	void onaylanacakAliciGoster();
	string parolaDondur();

	int onaylanacakSaticiSayiDondur();
	int onaylanacakAliciSayiDondur();

	int onaylanacakSaticiID(int secimSatici);
	int onaylanacakAliciID(int secimAlici);

	string getkUrunAd(int secimSatici);
	double  getUrunMiktar(int secimSatici);
	double getUrunFiyat(int secimSatici);


	double getPara(int secimAlici);

	void SetOnaySaticiFonk(int secimSatici);
	void SetOnayAliciFonk(int secimAlici);

	void OnSiparisAliciFonk(string ad, int SaticiId, string urunAd, double urunmiktar, double urunFiyat);
	void  OnSiparisGoster();

	int onSiparisSayiDondur();
	
	string getOnSiparisUrunAd(int onSecim);
	double getOnSiparisUrunMiktar(int onSecim);
	double getOnSiparisUrunFiyat(int onSecim);

	int getOnsiparisAliciIDDondur(int onSecim);
	void setOnSiparisFonk(int onSecim);


};





class Kullanicilar {

protected:
	string ad, soyad, kullanciAdi, password, Email, adres, TC_KimlikNo, telefon;
	double para;

public:
	void kayit(string ad, string soyad, string kullanciAdi, string password, string Email, string adres, string   Tc_KimlikNo, string   telefon);
	string KullaniciAdDondur();
	string passWordDondur();
	string adDondur();
	string soyadDondur();
	string TcDondur();
	void bilgiGoster();

	double paraDondur();
};

class Alici :public Kullanicilar {
private:
	string *siparisEdilenUrun;
	double *siparisEdilenUrunMiktar, *siperisteOdenentutar;
	double *siparisEdilenBirimFiyat;
	int *siparisEdilenUrunYýl, *siparisEdilenUrunAy, *siparisEdilenUrunGun;
	int siparisSayisi;


public:
	Alici() {
		para = 0;
		siparisEdilenUrun = new string[20];
		siparisEdilenUrunMiktar = new double[20];
		siperisteOdenentutar = new double[20];
		siparisEdilenUrunYýl = new int[20];
		siparisEdilenUrunAy= new int[20];
		siparisEdilenUrunGun = new int[20];
		siparisEdilenBirimFiyat = new double[20];

		siparisSayisi = 0;

	}
	void paraEkleme(double para);
	void setPara(double para);
	void siparisEdilenlerEkleme(string alinanUrunAd, double alinanmiktar, double odenenTutar, int siparisEdilenUrunYil,int siparisEdilenUrunAy,int siparisEdilenUrunGun,double siparisEdilenBirimFiyat);
	void siparislerGosterme();
	void raporOlusturma();
	
};


class Satici :public Kullanicilar {
private:
	string *urun;
	double  *urunFiyat, *urunMiktar;
	int urunSayisi;

	string *satilanUrun;
	double *satilanUrunMiktar;
	double *satilanBirimFiyat;
	int *satilanUrunYil, *satilanUrunAy, *satilanUrunGun;
	int satilanSayisi;


public:
	Satici() {
		urun = new string[20];
		urunFiyat = new double[20];
		urunMiktar = new double[20];
		urunSayisi = 0;

		satilanUrun = new string[20];
		satilanUrunMiktar = new double[20];
		satilanBirimFiyat = new double[20];
		satilanUrunYil = new int[20];
		satilanUrunAy= new int[20];
		satilanUrunGun= new int[20];
		satilanSayisi = 0;



		para = 0;
	};
	void sahipOlunanMallar();
	string adDondur();
	
	int urunSayisiDondur();

	void urunEkleme(string urunad, double urunMiktar, double urunFiyat);
	void satilacakUrunGösterme(int urunK);

	string getUrunAd(int urunK);
	double getUrunMiktar(int urunK);
	double getUrunFiyat(int urunK);

	void setUrunMiktar(double miktar, int urunK);
	void setPara(double para);

	void satilanEkleme(string urunAd, double urunmiktar, double birimFiyat, int urunYil, int urunAy, int urunGun);
	void satilanUrunlerGoster();

	void raporOlusturma();
	




};



class Muhasebeci :public Kullanicilar {

public:
	Muhasebeci() {

		ad = "muhasebe";
		soyad = "muhasebe";
		kullanciAdi = "muhasebe";
		password = "muhasebe";
		Email = "muhasebe@gmail.com";
		adres = "istanbul";
		TC_KimlikNo = "12122345621";
		telefon = "02124568595";
		para = 0;

	}

	string KullaniciAdDondur();
	string passWordDondur();
	double paraDondur();
	void bilgiGoster();
	void setPara(double para);
	


};
