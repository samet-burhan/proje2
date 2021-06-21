#include <iostream>
#include <string>
#include <stdio.h>
#include "Kullanici.h"
#include <fstream>
#include<cstring>
#include "kullaniciFonk.h"
#include "SaticiFonks.h"
#include "AliciFonks.h"
#include "AdminFonks.h"
#include <clocale>
#include <ctime>
#include "MuhasebeFonk.h"
#include <tchar.h>









using namespace std;





void menu(Satici  *satici, Alici *alici);
void KayitMenu(Satici  *satici, Alici *alici);
void SaticiBilgiMenu(Satici &satici, Satici  *Genelsatici, Alici *Genelalici);
void AliciBilgiMenu(Alici &alici, Satici *Genelsatici, Alici *Genelalici);
void ParaEkleme(Alici &alici, Satici  *Genelsatici, Alici *Genelalici);
void urunVeFiyatBelirlemeMenu(Satici & satici, Satici  *Genelsatici, Alici *Genelalici);
Admin admin;
Muhasebeci muhasebe;





//muhasebe paneli olusturuldu
void muhasebePaneli(Satici  *Genelsatici, Alici *Genelalici) {

	system("cls");
	int secim = 0;
	cout << "\t\tMuhasebe Paneli" << endl << endl;
	cout << "\t1.Profil bilgileri" << endl;
	cout << "\t2.Para goster" << endl;
	cout << "\t3.Geri" << endl << endl;

	cout << "yapmak istediginiz secimin numarasini giriniz: ";
	cin >> secim;

	switch (secim)
{

	

	case 1:
		system("cls");
		muhasebe.bilgiGoster();
		cout << "tekrardan muhasebe paneline g�nderilmek icin enter'a basiniz." << endl;
		system("pause");
		muhasebePaneli(Genelsatici, Genelalici);
		break;

	case 2:
		system("cls");
		cout << "para miktarini: " << muhasebe.paraDondur() << endl;
		cout << "tekrardan muhasebe paneline g�nderilmek icin enter'a basiniz." << endl;
		system("pause");
		muhasebePaneli(Genelsatici, Genelalici);
		break;

	case 3:
		menu(Genelsatici, Genelalici);

		break;

	default:

		cout << endl << "yanlis deger girdiniz...Tekrardan muhasebe paneline gitmek icin enter'a basiniz.";
		system("pause");
		muhasebePaneli(Genelsatici, Genelalici);
		break;
	}


}







//admin ait olan panel olusturuldu
void AdminPaneli(Satici  *Genelsatici, Alici *Genelalici) {
	system("cls");
	int secim = 0;
	double muhasabekalanyat�r�m;
	int onsiparisSayisi = 0;
	int saticisecim = 0, alicisecim = 0, saticiID = 0, aliciID = 0;
	string onaylama;

	cout << "\t\t --- Admin Paneli ---" << endl << endl;
	cout << "\t--------------------------------------" << endl;
	cout << "\t|1.Satici bilgileri onaylama         |" << endl;
	cout << "\t|2.Alici bilgileri onaylama          |" << endl;
	cout << "\t|3.On siparis isteginde bulunanlar   |" << endl;
	cout << "\t|4.Geri                              |" << endl << endl;


	cout << "yapmak istediginiz secimin numarasini giriniz: ";
	cin >> secim;

	switch (secim)
	{

	case 1:
		system("cls");
		cout << endl << "\t\t --- Onaylanacak saticilar ---" << endl << endl;

		//onaylanmas� beklenen sat�c�lar admine gosterilir.
		admin.OnaylanacakSaticiGoster();

		//onaylamas� beklenen saticilarin say�s� dondurulerek 0 ise panele atilir degilse isleme devam eder
		if (admin.onaylanacakSaticiSayiDondur() == 0) {
			cout << endl << "admin paneline gitmek icin enter'a basiniz" << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);
		}

		cout << endl << "onaylamak istediginiz saticinin numarasini giriniz: ";
		cin >> saticisecim;

		cout << "onaylamak istiyorsaniz E tusuna basiniz: ";
		cin >> onaylama;

		if (onaylama != "e" && onaylama != "E") {
			cout << endl << "onaylamamaniz gerceklesmistir." << endl;
			cout << "admin paneline gitmek icin enter'a basiniz" << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);

		}
		//secilen degerin olup olmad�g� test edilir.
		if (saticisecim <= 0 || (saticisecim - 1) >= admin.onaylanacakSaticiSayiDondur()) {
			cout << endl << "sectiginiz degere uygun onaylama bulunanamadi." << endl;
			cout << "tekrardan admin paneline g�nderilmek icin enter'a basiniz." << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);
		}


		

		else {

			//onaylama gerceklesmis ise saticiID �le hangi sat�c�ya ait oldugu bilgisi al�n�r.
			saticiID = admin.onaylanacakSaticiID(saticisecim - 1);


			double eksilecekMiktar = 0;
			if (admin.onSiparisSayiDondur()>0) {
				
				for (int i = 0; i < admin.onSiparisSayiDondur(); i++) {
					
					if (admin.getOnSiparisUrunAd(i) == admin.getkUrunAd(saticisecim - 1) && admin.getOnSiparisUrunMiktar(i) <= admin.getUrunMiktar(saticisecim - 1) && admin.getOnSiparisUrunFiyat(i) >= admin.getUrunFiyat(saticisecim - 1)) {
						
						time_t tarih = time(NULL);
						struct tm *tarih_bilgisi = localtime(&tarih);

						int onSiparisAl�c�ID = admin.getOnsiparisAliciIDDondur(i);
						eksilecekMiktar = admin.getOnSiparisUrunMiktar(i);


						muhasabekalanyat�r�m = admin.getOnSiparisUrunMiktar(i)*admin.getOnSiparisUrunFiyat(i)/100.0  -  (admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(saticisecim - 1)) / 100.0;


						Genelsatici[saticiID].satilanEkleme(admin.getOnSiparisUrunAd(i), admin.getOnSiparisUrunMiktar(i), admin.getUrunFiyat(i), tarih_bilgisi->tm_year + 1900, tarih_bilgisi->tm_mon + 1, tarih_bilgisi->tm_mday); //satilan urunleri saticilara ekleme
						Genelsatici[saticiID].setPara(admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(i)); //onsiparis urun miktari ile saticinin sattigi fiyattan islemi yapt�m
						Genelalici[onSiparisAl�c�ID].siparisEdilenlerEkleme(admin.getOnSiparisUrunAd(i), admin.getOnSiparisUrunMiktar(i), (admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(i)+ (admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(saticisecim - 1)) / 100.0), tarih_bilgisi->tm_year + 1900, tarih_bilgisi->tm_mon + 1, tarih_bilgisi->tm_mday, admin.getUrunFiyat(saticisecim - 1)); //aliciya siparisini ekleme
						Genelalici[saticiID].paraEkleme((admin.getOnSiparisUrunMiktar(i)*admin.getOnSiparisUrunFiyat(i))+ muhasabekalanyat�r�m - (admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(saticisecim - 1))); //alicidan alinan fazla para iade edildi muhasebeye odenen tutar iade edilmez
						muhasebe.setPara((admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(saticisecim - 1)) / 100.0);  //ticarete gore muhasebeye para verilir 
						admin.setOnSiparisFonk(i);
						break;
					}

				}
			}




			
			//saticinin bulunup urunlerin ekleme islemi gerceklestirilmistir
			Genelsatici[saticiID].urunEkleme(admin.getkUrunAd(saticisecim - 1), admin.getUrunMiktar(saticisecim - 1)-eksilecekMiktar, admin.getUrunFiyat(saticisecim - 1));
			//setOnaySaticiFonk ile onaylanmas� beklenen saticilardan c�kar�lma islemi gerceklestirildi
			admin.SetOnaySaticiFonk(saticisecim - 1);
			cout << endl << "islemler gerceklestirilmistir.." << endl;
			cout << "tekrardan admin paneline g�nderilmek icin enter'a basiniz." << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);

		}


		break;

	case 2:
		system("cls");
		cout << endl << "\t\t --- Onaylanacak alicilar ---" << endl << endl;

		//onaylanmas� beklenen al�c�lar admine gosterilir.
		admin.onaylanacakAliciGoster();

		//onaylamas� beklenen al�c�lar�n say�s� dondurulerek 0 ise panele atilir degilse isleme devam eder
		if (admin.onaylanacakAliciSayiDondur() == 0) {
			cout << endl << "admin paneline gitmek icin enter'a basiniz" << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);
		}


		cout << endl << "onaylamak istediginiz alicinin numarasini giriniz: ";
		cin >> alicisecim;

		//secilen degerin olup olmad�g� test edilir.
		if (alicisecim <= 0 || (alicisecim - 1) >= admin.onaylanacakAliciSayiDondur()) {
			cout << endl << "sectiginiz degere uygun onaylama bulunanamadi." << endl;
			cout << "tekrardan admin paneline g�nderilmek icin enter'a basiniz." << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);

		}
		else {
			//onaylama gerceklesmis ise aliciID �le hangi al�c�ya ait oldugu bilgisi al�n�r.
			aliciID = admin.onaylanacakAliciID(alicisecim - 1);
			//al�c�n�n bulunup para  ekleme islemi gerceklestirilmistir
			Genelalici[aliciID].paraEkleme(admin.getPara(alicisecim - 1));
			//setOnayAliciFonk ile onaylanmas� beklenen alicilar�n c�kar�lma islemi gerceklestirildi
			admin.SetOnayAliciFonk(alicisecim - 1);
			cout << endl << "islemler gerceklestirilmistir.." << endl;
			cout << "tekrardan admin paneline g�nderilmek icin enter'a basiniz." << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);
		}


		break;



	case 3:
		system("cls");
		cout << endl << "\t\t --- On siparis bulunanlar bilgi paneli ---" << endl << endl;

		//on sipariste bulunanlar� g�sterme
		admin.OnSiparisGoster();

		cout << "Tekrardan admin paneline donmek icin enter'a basiniz.." << endl;
		system("pause");
		AdminPaneli(Genelsatici, Genelalici);

		break;



	case 4:
		menu(Genelsatici, Genelalici);

		break;

	default:
		cout << endl << "yanlis deger girdiniz...Tekrardan admin paneline gitmek icin enter'a basiniz.";
		system("pause");
		AdminPaneli(Genelsatici, Genelalici);

		break;
	}





}







//saticinin urunlerinin eklemesi ve fiyatlad�r�lmas� icin olusturudu
void urunVeFiyatBelirlemeMenu(Satici & satici, Satici  *Genelsatici, Alici *Genelalici) {
	system("cls");
	string urunad;
	double  �r�nFiyat, �r�nMiktar;
	int saticiId = 0;
	cout << "\t\t --- Urun ve Fiyat belirleme Ekran ---" << endl << endl;
	cout << "urunun adinin giriniz: ";
	getline(cin, urunad);
	getline(cin, urunad);
	cout << "urunun miktarini giriniz: ";
	cin >> �r�nMiktar;
	cout << "urunun birim fiyatini giriniz: ";
	cin >> �r�nFiyat;

	//sat�c�Id ile islemi hangi sat�c�n�n yapt�g� bilgisi tutturuldu
	for (int i = 0; i < saticiSayisi; i++) {

		if (Genelsatici[i].KullaniciAdDondur() == satici.KullaniciAdDondur()) {
			saticiId = i;
		}
	}

	//adminin onaylanmas� icin onaylanacakSaticiFonk cagr�ld� 
	//onaylanmas� beklenen sat�c�lara ekleme islemi gerceklestirilmis oldu
	admin.OnaylacakSaticiFonk(satici.adDondur(), satici.soyadDondur(), satici.TcDondur(), urunad, �r�nMiktar, �r�nFiyat, saticiId);
	cout << endl << "Girilen degerler admin onayindan sonra sizin ekraninizada d��ecektir.." << endl << endl;
	cout << "satici bilgi munusune yonlendirilmek icin enter'a basiniz.." << endl;
	system("pause");
	SaticiBilgiMenu(satici, Genelsatici, Genelalici);




}

//aliciya para eklemek icin olusturuldu
void ParaEkleme(Alici &alici, Satici  *Genelsatici, Alici *Genelalici) {
	system("cls");
	cout << "\t\t --- Para Ekleme Ekran ---" << endl << endl;
	double para;
	int aliciId = 0;
	cout << "Eklemek istediginiz parayi tl cinsinden giriniz: ";
	cin >> para;

	//al�c�ID ile islemi hangi al�c�n�n yapt�g� tespit edilip bu bilgi admin'e gonderildi
	for (int i = 0; i < aliciSayisi; i++) {
		if (Genelalici[i].KullaniciAdDondur() == alici.KullaniciAdDondur()) {
			aliciId = i;
		}
	}

	//admin onaylamasi icin onaylanacakAliciFonk bilgiler gonderildi.al�c�Id ile al�c�n�n sistemde bilgierinin kaybolmamas� sagland�
	//onaylamas� beklenen alicilara ekleme islemi gerceklestirildi
	admin.OnaylanacakAliciFonk(alici.adDondur(), alici.soyadDondur(), alici.TcDondur(), para, aliciId);
	cout << endl << "Girilen degerler admin onayindan sonra sizin ekraninizada d��ecektir.." << endl << endl;
	cout << "Alici bilgi munusune yonlendirilmek icin enter'a basiniz.." << endl;
	system("pause");
	AliciBilgiMenu(alici, Genelsatici, Genelalici);



}



//al�c�n�n ticaretini gerceklestirilmesi �c�n olusturulmustur ve AliciBilgiMenuden cagr�lmaktad�r
void TicaretYapma(Alici &alici, Satici *Genelsatici, Alici *GenelAlici) {

	system("cls");
	int saticisecme = 0, urunsecme = 0;
	double urunAlinacakMiktar = 0;
	string ticaretGerceklestirme;
	int ticaretKontrol = 1;
	double odenecekTutar = 0;
	double muhasebeyeOdenecekTutar = 0;
	string ticaretDevaml�l�k;
	cout << "\t\t --- Ticaret Yapma Ekran ---" << endl << endl;

	//piyasadaki sat�c�lar ve urunleri gostermek icin olusturdum.
	if (saticiSayisi > 0) {

		for (int i = 0; i < saticiSayisi; i++) {

			cout << i + 1 << ".Satici ad: " << Genelsatici[i].adDondur() << " " << i + 1 << ".Satici soyad: " << Genelsatici[i].soyadDondur() << endl << endl;
			Genelsatici[i].sahipOlunanMallar();
			cout << endl << "-----------------------------" << endl;
		}
	}


	//alicin saticilara bak�p uygun olan sat�c�y� ve sat�c�y� ait olan urunun secilmesi icin islemleri gerceklestirdim.
	cout << "kacinci saticidan ticaret yapmak istedigini giriniz: ";
	cin >> saticisecme;
	cout << "Sectiginiz saticinin kacinci urununu almak istedigini giriniz: ";
	cin >> urunsecme;


	//secilen degere uygun sat�c�n�n test edilme islemi. saticisecme-1 ile -1'lenmesinin sebebi ekranda secimler 1 den baslarken
	//dizide -1 yaparak secilenin dizideki kars�l�g�na erisildi.Yani 1. satici dizide 0 indekse kars�l�k gelir.

	if ((saticisecme - 1) >= saticiSayisi || saticisecme <= 0) {
		cout << endl << "sectiginiz degerlere uygun satici bulunmamaktadir" << endl;
		cout << "bilgi menusune gitmek icin enter'a basiniz" << endl;
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
	}
	else {

		//secilen sat�c�n�n sacilen urunu bulundugu testi yap�l�r.
		//urunsecme -1 yap�lmas�n�n sebebi secilen degerin dizide secilen degerin bir eksigine kars�l�k gelmesidir.

		if ((urunsecme - 1) >= Genelsatici[saticisecme - 1].urunSayisiDondur() || urunsecme <= 0) {

			cout << endl << "sectigininiz degere g�re saticinin �r�n� bulunmamaktadir." << endl;
			cout << "bilgi menusune gitmek icin enter'a basiniz" << endl;
			system("pause");
			AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		}
		else {
			cout << endl << "secilen �r�n bulunmaktadir ticaret islemlerin yapilmasi icin enter'a basiniz.." << endl;
			system("pause");


			//ticaretin gerceklestirilmesi eger ticaret uygun olmad�g�nda ticaret panelinden c�kmay�p
			//ticarete uygun sekilde devam etmesi icin dongu olusturdum.
			while (ticaretKontrol == 1) {
				system("cls");
				cout << "ticaret yapmak istediginiz �r�n�n bilgileri; " << endl;

				//satinin secilen urununu gosterme
				Genelsatici[saticisecme - 1].satilacakUrunG�sterme(urunsecme - 1);

				cout << Genelsatici[saticisecme - 1].getUrunAd(urunsecme - 1) << " �r�n�nden kac kg almak istersiniz:  ";
				cin >> urunAlinacakMiktar;

				//al�nmak istenen miktar�n al�c�da olup olmad�g� test edilir.
				if (urunAlinacakMiktar > 0 && urunAlinacakMiktar <= Genelsatici[saticisecme - 1].getUrunMiktar(urunsecme - 1)) {


					//muhasebeye odenecek tutar aliciya yans�t�ld�
					odenecekTutar = urunAlinacakMiktar * Genelsatici[saticisecme - 1].getUrunFiyat(urunsecme - 1);
					muhasebeyeOdenecekTutar = odenecekTutar / 100.0;

					odenecekTutar = odenecekTutar + muhasebeyeOdenecekTutar;

					//al�nacan tutar uymakta ise al�n�c�n bunu odecek paras� olup olmad�g� kontrol edilir.
					if (odenecekTutar <= alici.paraDondur()) {

						//al�c�ya islemin onaylanmas� icin kabul kontrolu yap�l�r
						cout << "ticaret gerceklestirilebilir durumda ticaretin gerceklesmesi icin E tusuna basiniz: ";
						cin >> ticaretGerceklestirme;

						//butun kosullar saglan�p alc�c� ticareti kabul etmis ise ticaret islemleri gerceklestirilir.
						if (ticaretGerceklestirme == "E" || ticaretGerceklestirme == "e") {

							//saticinin mallar�nda azalma ve paras�nda arttt�r�lma islmeleri yap�ld�
							Genelsatici[saticisecme - 1].setUrunMiktar(urunAlinacakMiktar, urunsecme - 1);
							Genelsatici[saticisecme - 1].setPara(odenecekTutar-muhasebeyeOdenecekTutar);

							time_t tarih = time(NULL);
							struct tm *tarih_bilgisi = localtime(&tarih);


							//saticinin satt�g� urunleri gormesi icin gerceklestiridi
							Genelsatici[saticisecme - 1].satilanEkleme(Genelsatici[saticisecme - 1].getUrunAd(urunsecme - 1), urunAlinacakMiktar, Genelsatici[saticisecme - 1].getUrunFiyat(urunsecme - 1), tarih_bilgisi->tm_year + 1900, tarih_bilgisi->tm_mon + 1, tarih_bilgisi->tm_mday);

							//al�c�n�n ald�g� urunleri gormesi icin gerceklestirildi
							alici.siparisEdilenlerEkleme(Genelsatici[saticisecme - 1].getUrunAd(urunsecme - 1), urunAlinacakMiktar, odenecekTutar, tarih_bilgisi->tm_year + 1900, tarih_bilgisi->tm_mon + 1, tarih_bilgisi->tm_mday, Genelsatici[saticisecme - 1].getUrunFiyat(urunsecme - 1));

							//al�c�n�n paras�nda azalma sagland� ve donguden c�kma islemi gerceklestirildi
							alici.setPara(odenecekTutar);
							ticaretKontrol = 0;

							muhasebe.setPara(muhasebeyeOdenecekTutar);

							//istenilen detaylar gosterildi
						
	
							cout << endl << endl;
							cout << "isleme zaman�: " <<tarih_bilgisi->tm_year+1900<<"."<<tarih_bilgisi->tm_mon+1<<"."<<tarih_bilgisi->tm_mday<<" "<<tarih_bilgisi->tm_hour<<"."<<tarih_bilgisi->tm_min<<"."<<tarih_bilgisi->tm_sec<< endl;
							cout << "Yap�lan ��lem Detayi: " << alici.adDondur() << " adli alici " << Genelsatici[saticisecme - 1].adDondur() << " adli saticidan " << Genelsatici[saticisecme - 1].getUrunAd(urunsecme - 1) << " �r�n�nden birim fiyati " << Genelsatici[saticisecme - 1].getUrunFiyat(urunsecme - 1) << " tl olmak �zere " << urunAlinacakMiktar << " kg almistir" << endl << endl;
							cout << "Harcanan Tutar: " << alici.adDondur() << " adli alici " << Genelsatici[saticisecme - 1].adDondur() << " adli saticinin hesab�na " << odenecekTutar-muhasebeyeOdenecekTutar << " tl tuatunda para g�nderdi." << endl << endl;
							cout << "Alicinin Kalan Paras�: " << alici.adDondur() << " adli alicinin " << alici.paraDondur() << " tl parasi kaldi." << endl << endl;
							cout << "satilan malin birim fiyati: " << Genelsatici[saticisecme - 1].getUrunFiyat(urunsecme - 1) << " tl" << endl;
							cout << "muhasebeye odenen tutar: " << muhasebeyeOdenecekTutar<<" tl" << endl << endl;

							cout << "Ticaret ger�ekle�mistir bilgi menusu icin enter'a basiniz.." << endl;
							system("pause");
							AliciBilgiMenu(alici, Genelsatici, GenelAlici);




						}
						else {
							cout << endl << "ticaretten vaz ge�ilmi�tirdir bilgi men�s�ne d�nmek i�in enter basiniz." << endl;
							ticaretKontrol = 0;
							system("pause");
							AliciBilgiMenu(alici, Genelsatici, GenelAlici);
						}


						break;
					}
					else {
						cout << endl << "almak istediginiz mikatiri �deyecek bakiyeniz bulunmamaktadir.." << endl;


					}

				}
				else {
					cout << endl << "saticida bu kadar �r�n bulunmamaktadir.." << endl;
				}

				//ticarete devam edilip edilmemek istediginin kontroulu gerceklestirildi
				cout << endl << "yeniden ali� i�lemine devam etmek istiyorsaniz E tu�una basiniz.Ticaret yapmadan bilgi men�s�ne d�nmek istiyorsaniz H basiniz: ";
				cin >> ticaretDevaml�l�k;

				if (ticaretDevaml�l�k == "E" || ticaretDevaml�l�k == "e") {
					continue;
				}
				else {
					ticaretKontrol = 0;
					cout << endl << "bilgi menusune donmek icin enter'a basiniz" << endl;
					system("pause");
					AliciBilgiMenu(alici, Genelsatici, GenelAlici);

				}



			}






		}

	}

}






//menunden gelen aliciyi , saticilarin ait oldugu ve alicilarin oldugunu degerler alicibilgi menuye yollanm�st�r
//Genelsaticida ve Genelalicida butun satici ve alicilar tutulur. alici sadece o alicinin bilgileri bulunmaktad�r



void AliciBilgiMenu(Alici &alici, Satici *Genelsatici, Alici *GenelAlici) {

	system("cls");
	int secim = 0;
	int OnSiparsiAliciId = 0;
	double urunMiktar, urunFiyat;
	string OnSiparisurunAd;
	int onSipariskontrol = 0;
	double odenecekTutar = 0;
	double muhasebeyeOdenecekTutar = 0;

	cout << "\t\t --- Alici Bilgi Ekran ---" << endl << endl;
	cout << "\t--------------------------------------" << endl;
	cout << "\t|1.Profil Bilgileri                  |" << endl;
	cout << "\t|2.Piyasadaki satici mallari         |" << endl;
	cout << "\t|3.Para ekleme                       |" << endl;
	cout << "\t|4.Para g�sterme                     |" << endl;
	cout << "\t|5.Ticaret yapma                     |" << endl;
	cout << "\t|6.Siparislerim                      |" << endl;
	cout << "\t|7.On siparis olusturma              |" << endl;
	cout << "\t|8.Rapor olusturma                   |" << endl;
	cout << "\t|9.Geri                              |" << endl << endl;
	cout << "yukaridaki ekrana secim icin uygun olan sayiyi giriniz: ";
	cin >> secim;

	switch (secim)
	{

	case 1:
		//alicilar�n bilgileri gosterir
		system("cls");
		cout << endl << "\t\t --- Profil Bilgileri ---" << endl;
		alici.bilgiGoster();
		cout << endl << "Tekrardan bilgi menuye donmek i�in enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		break;

	case 2:
		//alicinin piyasadaki sat�c�lar�n satt�g� mallar�n� gosterilme islemini gerceklestirdim
		system("cls");
		cout << endl << "\t\t --- Piyasadaki Satici Mallar ---" << endl << endl;

		if (saticiSayisi > 0) {
			//Genel satici ile butun sat�c�lara ve onlar�n ait oldugu urunlere ulast�k
			for (int i = 0; i < saticiSayisi; i++) {

				cout << i + 1 << ".Satici ad: " << Genelsatici[i].adDondur() << " " << i + 1 << ".Satici soyad: " << Genelsatici[i].soyadDondur() << endl << endl;
				Genelsatici[i].sahipOlunanMallar();
				cout << endl << "-----------------------------" << endl;
			}
		}
		else {
			cout <<endl<< "piyasada satici bulunmamaktadir." << endl;
		}


		cout << endl << "Tekrardan bilgi menuye donmek i�in enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		break;

	case 3:
		//al�c�n�n para hesab�na para ekleme istegini gerceklestirdik
		ParaEkleme(alici, Genelsatici, GenelAlici);

		cout << endl << "Tekrardan bilgi menuye donmek i�in enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		break;

	case 4:
		//al�c�n�n hesab�ndak� para miktar�n� gostermek icin olusturdum
		system("cls");
		cout << endl << "\t\t --- Para G�sterme ---" << endl << endl;
		cout << "Bakiyeniz: " << alici.paraDondur();
		cout << endl << "Tekrardan bilgi menuye donmek i�in enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		break;

	case 5:
		//al�c�n�n ticaret islemini gerceklestirmek icin alicin�n bilgilerini ve sistemdeki butun al�c� ve sat�c�n�n bilgilerini yollad�m.
		TicaretYapma(alici, Genelsatici, GenelAlici);

		break;

	case 6:
		//al�c�n�n ald�g� urunleri gostermek �c�n olusturdum.
		alici.siparislerGosterme();
		cout << endl << "Tekrardan bilgi menuye donmek i�in enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);

		break;



	case 7:
		system("cls");
		
		cout << "\t\t --- On Siparis Paneli ---" << endl << endl;
		cout << "siparis etmek istediginiz urunun ad�: ";
		cin >> OnSiparisurunAd;
		cout << "siparis etmek istediginiz urunun miktari: ";
		cin >> urunMiktar;
		cout << "siparis etmek istediginiz urunun birim fiyati: ";
		cin >> urunFiyat;

		//muhasebeye odenecek para aliya yans�t�l�r
		odenecekTutar = urunMiktar * urunFiyat;
		muhasebeyeOdenecekTutar = odenecekTutar / 100;
		odenecekTutar = odenecekTutar + muhasebeyeOdenecekTutar;

		if ((urunMiktar*urunFiyat) > alici.paraDondur()) {
			cout << "istediginiz on siparisi gerceklestirebilecek paraniz bulunmamaktadir." << endl;
			cout << "tekrardan gerceklestirmek icin bilgi menusune gitmek icin enter'a basiniz.." << endl;
			system("pause");
			AliciBilgiMenu(alici, Genelsatici, GenelAlici);

		}

		if (saticiSayisi > 0) {
			//Genel satici ile butun sat�c�lara ve onlar�n ait oldugu urunlere ulast�k
			for (int i = 0; i < saticiSayisi; i++) {

				for(int j=0;j<Genelsatici[i].urunSayisiDondur();j++){

					if (Genelsatici[i].getUrunAd(j) == OnSiparisurunAd && Genelsatici[i].getUrunMiktar(j) >= urunMiktar && Genelsatici[i].getUrunFiyat(j) <= urunFiyat) {
						time_t tarih = time(NULL);
						struct tm *tarih_bilgisi = localtime(&tarih);

						Genelsatici[i].satilanEkleme(OnSiparisurunAd, urunMiktar, Genelsatici[i].getUrunFiyat(j), tarih_bilgisi->tm_year + 1900, tarih_bilgisi->tm_mon + 1, tarih_bilgisi->tm_mday);

						Genelsatici[i].setUrunMiktar(urunMiktar, j);
						Genelsatici[i].setPara(urunMiktar*Genelsatici[i].getUrunFiyat(j));
						alici.siparisEdilenlerEkleme(OnSiparisurunAd, urunMiktar, urunMiktar*Genelsatici[i].getUrunFiyat(j)+ urunMiktar * Genelsatici[i].getUrunFiyat(j) / 100.0, tarih_bilgisi->tm_year + 1900 , tarih_bilgisi->tm_mon + 1 , tarih_bilgisi->tm_mday, Genelsatici[i].getUrunFiyat(j));
						alici.setPara(urunMiktar*Genelsatici[i].getUrunFiyat(j) + urunMiktar * Genelsatici[i].getUrunFiyat(j) / 100.0);
						muhasebe.setPara(urunMiktar*Genelsatici[i].getUrunFiyat(j)/100);
						onSipariskontrol = 1;
						break;

					}
				}

			}
		}
		
		if (onSipariskontrol == 0) {

			for (int i = 0; i < aliciSayisi; i++) {

				if (alici.TcDondur() == GenelAlici[i].TcDondur()) {
					OnSiparsiAliciId = i;
				}

			}

			admin.OnSiparisAliciFonk(alici.adDondur(), OnSiparsiAliciId, OnSiparisurunAd, urunMiktar, urunFiyat);
			alici.setPara(odenecekTutar);
			

		}
		
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);


		break;


	case 8:
		alici.raporOlusturma();
		cout << "Tekrardan bilgi menusune donmek icin enter'a basiniz.. "<<endl;
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);



		break;


	case 9:
		menu(Genelsatici, GenelAlici);
		break;


	default:
		cout << endl << "Girdiginiz deger secime uygun degildir.Tekrardan bilgi menuye aktarmak icin enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		break;
	}

}


//menunden gelen saticiyi , saticilarin ait oldugu ve alicilarin oldugunu degerler saticibilgi menuye yollanm�st�r
//Genelsaticida ve Genelalicida butun satici ve alicilar tutulur. saticida sadece o saticinin bilgileri bulunmaktad�r

void SaticiBilgiMenu(Satici &satici, Satici  *Genelsatici, Alici *Genelalici) {

	system("cls");
	int secim = 0;

	cout << "\t\t --- Satici Bilgi Ekran ---" << endl << endl;
	cout << "\t----------------------------------" << endl;
	cout << "\t|1.Profil bilgileri              |" << endl;
	cout << "\t|2.Sahip olunan mallari g�ster   |" << endl;
	cout << "\t|3.Urun ekleme ve fiyatlandirma  |" << endl;
	cout << "\t|4.Bakiye g�sterme               |" << endl;
	cout << "\t|5.Satilan urun gosterme         |" << endl;
	cout << "\t|6.Rapor olusturma               |" << endl;
	cout << "\t|7.Geri                          |" << endl << endl;
	cout << "yukaridaki ekrana secim icin uygun olan sayiyi giriniz: ";
	cin >> secim;

	switch (secim)
	{
	case 1:
		//saticinin bilgilerini gosterir
		system("cls");
		cout << endl << "\t\t --- Profil Bilgileri ---" << endl;
		satici.bilgiGoster();
		cout << endl << "Tekrardan bilgi menuye donmek i�in enter'a basiniz.";
		system("pause");
		SaticiBilgiMenu(satici, Genelsatici, Genelalici);
		break;

	case 2:
		//saticinin kaydedilmis olan urunlerinin gosterilmesi
		system("cls");
		cout << endl << "\t\t --- Sahip Olunan Urun Bilgileri ---" << endl;
		satici.sahipOlunanMallar();
		cout << endl << "Tekrardan bilgi menuye donmek i�in enter'a basiniz.";
		system("pause");
		SaticiBilgiMenu(satici, Genelsatici, Genelalici);

	case 3:
		//saticinin urunlerini sisteme kaydetme isteginde bulunmas� islemi icin fonksiyana yollad�k
		urunVeFiyatBelirlemeMenu(satici, Genelsatici, Genelalici);
		break;

	case 4:
		//saticinin sahip oldugu paray� gostermek �c�n yapt�m
		system("cls");
		cout << "bakiyeniz: " << satici.paraDondur() << " tl" << endl;;
		cout << endl << "bilgi menusune d�nmek i�in enter'a basiniz.";
		system("pause");
		SaticiBilgiMenu(satici, Genelsatici, Genelalici);

		break;

	case 5:
		//satilan urunlerin gosterimi
		satici.satilanUrunlerGoster();
		cout << endl << "bilgi menusune d�nmek i�in enter'a basiniz.";
		system("pause");
		SaticiBilgiMenu(satici, Genelsatici, Genelalici);

		break;


	case 6:

		//satilan urunu raporland�rma

		satici.raporOlusturma();
		cout << endl << "bilgi menusune d�nmek i�in enter'a basiniz.";
		system("pause");
		SaticiBilgiMenu(satici, Genelsatici, Genelalici);

		break;


	case 7:
		menu(Genelsatici, Genelalici);
		break;

	default:
		cout << endl << "Girdiginiz deger secime uygun degildir.Tekrardan bilgi menuye aktarmak icin enter'a basiniz.";
		system("pause");
		SaticiBilgiMenu(satici, Genelsatici, Genelalici);
		break;
	}




}



void KayitMenu(Satici  *satici, Alici *alici) {  //menuden gelen kay�t istegi icin olusturdum.
	system("cls");


	double  Fiyat = 0, miktar = 0;
	string ad, soyad, kullanc�Adi, password, E_mail, Adres, �r�nAdi, Telefon, TcKimlikNo;

	int kontrol = 1;
	int kullaniciAdKontrol = 0;

	system("cls");
	int hangiKullanici = 0;
	cout << "\t\t --- Kayit Ekrani ---" << endl << endl;
	cout << "\t------------------------------------------------------------------------" << endl;
	cout << "\t|Hangi kullanici olarak kayit yapt�rmak istersiniz...                  |" << endl;
	cout << "\t|Satici olarak kayit icin 1'e Alici olarak kayit icin 2'e basiniz: ";
	cin >> hangiKullanici;



	//kullan�c�n�n satici m� yoksa alici m� oldugunu ogrenip ona yonelelik kaydetme islemini gerceklestirdim
	if (hangiKullanici == 1 || hangiKullanici == 2) {
		cout << endl;
		cout << "Adinizi giriniz: ";
		getline(cin, ad);
		getline(cin, ad);


		cout << "Soyadinizi giriniz: ";
		getline(cin, soyad);

		//kullan�c� adininn daha once kullan�l�p kullan�lmad�g�n� test etmek ve ona gore kullan�c� secmek icin olusturdum
		while (kontrol == 1) {
			kullaniciAdKontrol = 0;
			cout << "Kullanici adini giriniz: ";
			getline(cin, kullanc�Adi);

			//kullan�c�AdKontrol benim kullan�c� ad�m�n daha once kullan�l�lm�sm� onu test eder
			for (int i = 0; i < saticiSayisi; i++) {
				if (satici[i].KullaniciAdDondur() == kullanc�Adi) {
					kullaniciAdKontrol = 1;
				}
			}
			for (int i = 0; i < aliciSayisi; i++) {
				if (alici[i].KullaniciAdDondur() == kullanc�Adi) {
					kullaniciAdKontrol = 1;
				}
			}

			//daha once bu kullan�c� ad�yla islem yapmad�g�n� g�steren ve donguden c�kmak icin if yap�s�n� olusturdum
			if (kullaniciAdKontrol == 0 && kullanc�Adi != admin.kullanciAdDondur()) {
				kontrol = 0;
			}
			else {
				cout << "Bu kullanici adi alinmi�tir ba�ka bir kullanici adi se�iniz.." << endl;
			}
		}
		cout << "Password giriniz: ";
		getline(cin, password);

		cout << "E mail giriniz: ";
		getline(cin, E_mail);

		cout << "Adres giriniz: ";
		getline(cin, Adres);

		cout << "Telefon giriniz: ";
		cin >> Telefon;


		cout << "Tc kimlik no giriniz: ";
		cin >> TcKimlikNo;


		//secilen kullan�c�y�ya gore kay�d� gerceklestiriliyor
		if (hangiKullanici == 1) {

			//kullan�c�fonk bulunan kayit fonksiyonuyla satici kaydedildi
			satici[saticiSayisi].kayit(ad, soyad, kullanc�Adi, password, E_mail, Adres, TcKimlikNo, Telefon);
			saticiSayisi++;

		}
		else if (hangiKullanici == 2) {
			//kullan�c�fonk bulunan kayit fonksiyonuyla alici kaydedildi
			alici[aliciSayisi].kayit(ad, soyad, kullanc�Adi, password, E_mail, Adres, TcKimlikNo, Telefon);
			aliciSayisi++;
		}

		cout << endl << "Kayit i�leminiz ger�ekle�mi�tir Giri� i�in enter basiniz..";
		system("pause");
		menu(satici, alici);

	}

	else {
		cout << "\tGirdiginiz deger uygun secim degildir.Kayit ekran�na tekrardan yollaniyorsunuz." << endl;
		KayitMenu(satici, alici);
	}


	system("pause");

}



void menu(Satici  *satici, Alici *alici) { //olusturdugum  satici ve al�c� kullan�c�lar� menu ekran�na yollad�k
	system("cls");
	int saticiBulmaKullanici = 0, saticiBulmaPassword = 0, saticiKonum = 0;
	int aliciBulmaKullanici = 0, aliciBulmaPassword = 0, alicikonum = 0;
	string kullaniciSecim = "";
	string kullaniciAd, parola;
	cout << endl;
	cout << "\t\t--- Giris Paneli ---" << endl << endl;
	cout << "Kullanici adi: ";
	cin >> kullaniciAd;
	cout << "Parola: ";
	cin >> parola;

	//saticinin daha �nce kayd�n�n yap�l�p yap�lmad�g�n� anlamak icin olusturdum.Eger varsa bunun hangi saticiya ait oldugunu
	//saticikonum ile tuttum
	for (int i = 0; i < saticiSayisi; i++) {

		if (kullaniciAd == satici[i].KullaniciAdDondur()) {

			if (parola == satici[i].passWordDondur()) {
				saticiBulmaPassword = 1;
				saticiKonum = i;
			}


			saticiBulmaKullanici = 1;
		}



	}

	//al�c�n�n daha once kayd�n�n yap�l�p yap�lmad�g�n� anlamak icin olusturdum.Eger varsa bunun hangi aliciya ait oldugunu
	//alicikonum ile tuttum
	for (int i = 0; i < aliciSayisi; i++) {


		if (kullaniciAd == alici[i].KullaniciAdDondur()) {

			if (parola == alici[i].passWordDondur()) {
				aliciBulmaPassword = 1;
				alicikonum = i;
			}


			aliciBulmaKullanici = 1;
		}

	}


	//Girilen kullan�c�lar bulunmus ise ona ait bilgi paneline gonderme islemini gerceklestirdim
	if (saticiBulmaKullanici == 1 && saticiBulmaPassword == 1) {

		SaticiBilgiMenu(satici[saticiKonum], satici, alici);



	}
	else if (aliciBulmaKullanici == 1 && aliciBulmaPassword == 1) {

		AliciBilgiMenu(alici[alicikonum], satici, alici);

	}

	//kullan�c�y� bulmus fakat sifresi yanl�s ise bunu kullan�c�ya bilgilerdime islemi yapt�m
	else if (saticiBulmaKullanici == 1 || aliciBulmaKullanici == 1) {
		cout << endl << "�ifreyi yanlis girdiniz..Tekrar denemek icin enter'a basiniz." << endl;
		system("pause");
		menu(satici, alici);
	}



	//admin giris yapm�s ise adm�n paneline yollad�m
	else if (kullaniciAd == admin.kullanciAdDondur() && parola == admin.parolaDondur()) {
		AdminPaneli(satici, alici);
	}

	//muhasebeci giris yapm�s ise muhasebe paneline gonder

	else if (kullaniciAd == muhasebe.KullaniciAdDondur() && parola == muhasebe.passWordDondur()) {
		muhasebePaneli(satici, alici);
	}



	else {
		cout << endl << "kimliginiz bulunamadi yeni kayit olmak icin E tusuna basiniz.Tekrardan menuye ulasmak icin herhangi bir tusa basiniz: ";
		cin >> kullaniciSecim;


		//kay�t daha once yoksa kay�t yapmak istediginin teyitini etmek eger istiyorsa kay�t icin yonlendirilmesini gerceklestirdim
		if (kullaniciSecim == "e" || kullaniciSecim == "E") {
			KayitMenu(satici, alici);
		}

		else {
			menu(satici, alici);

		}
	}
	system("pause");
}


int main() {



	setlocale(LC_ALL, "Turkish");

	
	
	
	//al�c� ve satici olusturdum ve menuye yollad�m
	Satici *satici = new Satici[30];
	Alici *alici = new Alici[30];

	menu(satici, alici);



	system("pause");
	return 0;
}