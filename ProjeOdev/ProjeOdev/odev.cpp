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
		cout << "tekrardan muhasebe paneline gönderilmek icin enter'a basiniz." << endl;
		system("pause");
		muhasebePaneli(Genelsatici, Genelalici);
		break;

	case 2:
		system("cls");
		cout << "para miktarini: " << muhasebe.paraDondur() << endl;
		cout << "tekrardan muhasebe paneline gönderilmek icin enter'a basiniz." << endl;
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
	double muhasabekalanyatýrým;
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

		//onaylanmasý beklenen satýcýlar admine gosterilir.
		admin.OnaylanacakSaticiGoster();

		//onaylamasý beklenen saticilarin sayýsý dondurulerek 0 ise panele atilir degilse isleme devam eder
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
		//secilen degerin olup olmadýgý test edilir.
		if (saticisecim <= 0 || (saticisecim - 1) >= admin.onaylanacakSaticiSayiDondur()) {
			cout << endl << "sectiginiz degere uygun onaylama bulunanamadi." << endl;
			cout << "tekrardan admin paneline gönderilmek icin enter'a basiniz." << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);
		}


		

		else {

			//onaylama gerceklesmis ise saticiID ýle hangi satýcýya ait oldugu bilgisi alýnýr.
			saticiID = admin.onaylanacakSaticiID(saticisecim - 1);


			double eksilecekMiktar = 0;
			if (admin.onSiparisSayiDondur()>0) {
				
				for (int i = 0; i < admin.onSiparisSayiDondur(); i++) {
					
					if (admin.getOnSiparisUrunAd(i) == admin.getkUrunAd(saticisecim - 1) && admin.getOnSiparisUrunMiktar(i) <= admin.getUrunMiktar(saticisecim - 1) && admin.getOnSiparisUrunFiyat(i) >= admin.getUrunFiyat(saticisecim - 1)) {
						
						time_t tarih = time(NULL);
						struct tm *tarih_bilgisi = localtime(&tarih);

						int onSiparisAlýcýID = admin.getOnsiparisAliciIDDondur(i);
						eksilecekMiktar = admin.getOnSiparisUrunMiktar(i);


						muhasabekalanyatýrým = admin.getOnSiparisUrunMiktar(i)*admin.getOnSiparisUrunFiyat(i)/100.0  -  (admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(saticisecim - 1)) / 100.0;


						Genelsatici[saticiID].satilanEkleme(admin.getOnSiparisUrunAd(i), admin.getOnSiparisUrunMiktar(i), admin.getUrunFiyat(i), tarih_bilgisi->tm_year + 1900, tarih_bilgisi->tm_mon + 1, tarih_bilgisi->tm_mday); //satilan urunleri saticilara ekleme
						Genelsatici[saticiID].setPara(admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(i)); //onsiparis urun miktari ile saticinin sattigi fiyattan islemi yaptým
						Genelalici[onSiparisAlýcýID].siparisEdilenlerEkleme(admin.getOnSiparisUrunAd(i), admin.getOnSiparisUrunMiktar(i), (admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(i)+ (admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(saticisecim - 1)) / 100.0), tarih_bilgisi->tm_year + 1900, tarih_bilgisi->tm_mon + 1, tarih_bilgisi->tm_mday, admin.getUrunFiyat(saticisecim - 1)); //aliciya siparisini ekleme
						Genelalici[saticiID].paraEkleme((admin.getOnSiparisUrunMiktar(i)*admin.getOnSiparisUrunFiyat(i))+ muhasabekalanyatýrým - (admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(saticisecim - 1))); //alicidan alinan fazla para iade edildi muhasebeye odenen tutar iade edilmez
						muhasebe.setPara((admin.getOnSiparisUrunMiktar(i)*admin.getUrunFiyat(saticisecim - 1)) / 100.0);  //ticarete gore muhasebeye para verilir 
						admin.setOnSiparisFonk(i);
						break;
					}

				}
			}




			
			//saticinin bulunup urunlerin ekleme islemi gerceklestirilmistir
			Genelsatici[saticiID].urunEkleme(admin.getkUrunAd(saticisecim - 1), admin.getUrunMiktar(saticisecim - 1)-eksilecekMiktar, admin.getUrunFiyat(saticisecim - 1));
			//setOnaySaticiFonk ile onaylanmasý beklenen saticilardan cýkarýlma islemi gerceklestirildi
			admin.SetOnaySaticiFonk(saticisecim - 1);
			cout << endl << "islemler gerceklestirilmistir.." << endl;
			cout << "tekrardan admin paneline gönderilmek icin enter'a basiniz." << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);

		}


		break;

	case 2:
		system("cls");
		cout << endl << "\t\t --- Onaylanacak alicilar ---" << endl << endl;

		//onaylanmasý beklenen alýcýlar admine gosterilir.
		admin.onaylanacakAliciGoster();

		//onaylamasý beklenen alýcýlarýn sayýsý dondurulerek 0 ise panele atilir degilse isleme devam eder
		if (admin.onaylanacakAliciSayiDondur() == 0) {
			cout << endl << "admin paneline gitmek icin enter'a basiniz" << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);
		}


		cout << endl << "onaylamak istediginiz alicinin numarasini giriniz: ";
		cin >> alicisecim;

		//secilen degerin olup olmadýgý test edilir.
		if (alicisecim <= 0 || (alicisecim - 1) >= admin.onaylanacakAliciSayiDondur()) {
			cout << endl << "sectiginiz degere uygun onaylama bulunanamadi." << endl;
			cout << "tekrardan admin paneline gönderilmek icin enter'a basiniz." << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);

		}
		else {
			//onaylama gerceklesmis ise aliciID ýle hangi alýcýya ait oldugu bilgisi alýnýr.
			aliciID = admin.onaylanacakAliciID(alicisecim - 1);
			//alýcýnýn bulunup para  ekleme islemi gerceklestirilmistir
			Genelalici[aliciID].paraEkleme(admin.getPara(alicisecim - 1));
			//setOnayAliciFonk ile onaylanmasý beklenen alicilarýn cýkarýlma islemi gerceklestirildi
			admin.SetOnayAliciFonk(alicisecim - 1);
			cout << endl << "islemler gerceklestirilmistir.." << endl;
			cout << "tekrardan admin paneline gönderilmek icin enter'a basiniz." << endl;
			system("pause");
			AdminPaneli(Genelsatici, Genelalici);
		}


		break;



	case 3:
		system("cls");
		cout << endl << "\t\t --- On siparis bulunanlar bilgi paneli ---" << endl << endl;

		//on sipariste bulunanlarý gösterme
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







//saticinin urunlerinin eklemesi ve fiyatladýrýlmasý icin olusturudu
void urunVeFiyatBelirlemeMenu(Satici & satici, Satici  *Genelsatici, Alici *Genelalici) {
	system("cls");
	string urunad;
	double  ürünFiyat, ürünMiktar;
	int saticiId = 0;
	cout << "\t\t --- Urun ve Fiyat belirleme Ekran ---" << endl << endl;
	cout << "urunun adinin giriniz: ";
	getline(cin, urunad);
	getline(cin, urunad);
	cout << "urunun miktarini giriniz: ";
	cin >> ürünMiktar;
	cout << "urunun birim fiyatini giriniz: ";
	cin >> ürünFiyat;

	//satýcýId ile islemi hangi satýcýnýn yaptýgý bilgisi tutturuldu
	for (int i = 0; i < saticiSayisi; i++) {

		if (Genelsatici[i].KullaniciAdDondur() == satici.KullaniciAdDondur()) {
			saticiId = i;
		}
	}

	//adminin onaylanmasý icin onaylanacakSaticiFonk cagrýldý 
	//onaylanmasý beklenen satýcýlara ekleme islemi gerceklestirilmis oldu
	admin.OnaylacakSaticiFonk(satici.adDondur(), satici.soyadDondur(), satici.TcDondur(), urunad, ürünMiktar, ürünFiyat, saticiId);
	cout << endl << "Girilen degerler admin onayindan sonra sizin ekraninizada düþecektir.." << endl << endl;
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

	//alýcýID ile islemi hangi alýcýnýn yaptýgý tespit edilip bu bilgi admin'e gonderildi
	for (int i = 0; i < aliciSayisi; i++) {
		if (Genelalici[i].KullaniciAdDondur() == alici.KullaniciAdDondur()) {
			aliciId = i;
		}
	}

	//admin onaylamasi icin onaylanacakAliciFonk bilgiler gonderildi.alýcýId ile alýcýnýn sistemde bilgierinin kaybolmamasý saglandý
	//onaylamasý beklenen alicilara ekleme islemi gerceklestirildi
	admin.OnaylanacakAliciFonk(alici.adDondur(), alici.soyadDondur(), alici.TcDondur(), para, aliciId);
	cout << endl << "Girilen degerler admin onayindan sonra sizin ekraninizada düþecektir.." << endl << endl;
	cout << "Alici bilgi munusune yonlendirilmek icin enter'a basiniz.." << endl;
	system("pause");
	AliciBilgiMenu(alici, Genelsatici, Genelalici);



}



//alýcýnýn ticaretini gerceklestirilmesi ýcýn olusturulmustur ve AliciBilgiMenuden cagrýlmaktadýr
void TicaretYapma(Alici &alici, Satici *Genelsatici, Alici *GenelAlici) {

	system("cls");
	int saticisecme = 0, urunsecme = 0;
	double urunAlinacakMiktar = 0;
	string ticaretGerceklestirme;
	int ticaretKontrol = 1;
	double odenecekTutar = 0;
	double muhasebeyeOdenecekTutar = 0;
	string ticaretDevamlýlýk;
	cout << "\t\t --- Ticaret Yapma Ekran ---" << endl << endl;

	//piyasadaki satýcýlar ve urunleri gostermek icin olusturdum.
	if (saticiSayisi > 0) {

		for (int i = 0; i < saticiSayisi; i++) {

			cout << i + 1 << ".Satici ad: " << Genelsatici[i].adDondur() << " " << i + 1 << ".Satici soyad: " << Genelsatici[i].soyadDondur() << endl << endl;
			Genelsatici[i].sahipOlunanMallar();
			cout << endl << "-----------------------------" << endl;
		}
	}


	//alicin saticilara bakýp uygun olan satýcýyý ve satýcýyý ait olan urunun secilmesi icin islemleri gerceklestirdim.
	cout << "kacinci saticidan ticaret yapmak istedigini giriniz: ";
	cin >> saticisecme;
	cout << "Sectiginiz saticinin kacinci urununu almak istedigini giriniz: ";
	cin >> urunsecme;


	//secilen degere uygun satýcýnýn test edilme islemi. saticisecme-1 ile -1'lenmesinin sebebi ekranda secimler 1 den baslarken
	//dizide -1 yaparak secilenin dizideki karsýlýgýna erisildi.Yani 1. satici dizide 0 indekse karsýlýk gelir.

	if ((saticisecme - 1) >= saticiSayisi || saticisecme <= 0) {
		cout << endl << "sectiginiz degerlere uygun satici bulunmamaktadir" << endl;
		cout << "bilgi menusune gitmek icin enter'a basiniz" << endl;
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
	}
	else {

		//secilen satýcýnýn sacilen urunu bulundugu testi yapýlýr.
		//urunsecme -1 yapýlmasýnýn sebebi secilen degerin dizide secilen degerin bir eksigine karsýlýk gelmesidir.

		if ((urunsecme - 1) >= Genelsatici[saticisecme - 1].urunSayisiDondur() || urunsecme <= 0) {

			cout << endl << "sectigininiz degere göre saticinin ürünü bulunmamaktadir." << endl;
			cout << "bilgi menusune gitmek icin enter'a basiniz" << endl;
			system("pause");
			AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		}
		else {
			cout << endl << "secilen ürün bulunmaktadir ticaret islemlerin yapilmasi icin enter'a basiniz.." << endl;
			system("pause");


			//ticaretin gerceklestirilmesi eger ticaret uygun olmadýgýnda ticaret panelinden cýkmayýp
			//ticarete uygun sekilde devam etmesi icin dongu olusturdum.
			while (ticaretKontrol == 1) {
				system("cls");
				cout << "ticaret yapmak istediginiz ürünün bilgileri; " << endl;

				//satinin secilen urununu gosterme
				Genelsatici[saticisecme - 1].satilacakUrunGösterme(urunsecme - 1);

				cout << Genelsatici[saticisecme - 1].getUrunAd(urunsecme - 1) << " ürününden kac kg almak istersiniz:  ";
				cin >> urunAlinacakMiktar;

				//alýnmak istenen miktarýn alýcýda olup olmadýgý test edilir.
				if (urunAlinacakMiktar > 0 && urunAlinacakMiktar <= Genelsatici[saticisecme - 1].getUrunMiktar(urunsecme - 1)) {


					//muhasebeye odenecek tutar aliciya yansýtýldý
					odenecekTutar = urunAlinacakMiktar * Genelsatici[saticisecme - 1].getUrunFiyat(urunsecme - 1);
					muhasebeyeOdenecekTutar = odenecekTutar / 100.0;

					odenecekTutar = odenecekTutar + muhasebeyeOdenecekTutar;

					//alýnacan tutar uymakta ise alýnýcýn bunu odecek parasý olup olmadýgý kontrol edilir.
					if (odenecekTutar <= alici.paraDondur()) {

						//alýcýya islemin onaylanmasý icin kabul kontrolu yapýlýr
						cout << "ticaret gerceklestirilebilir durumda ticaretin gerceklesmesi icin E tusuna basiniz: ";
						cin >> ticaretGerceklestirme;

						//butun kosullar saglanýp alcýcý ticareti kabul etmis ise ticaret islemleri gerceklestirilir.
						if (ticaretGerceklestirme == "E" || ticaretGerceklestirme == "e") {

							//saticinin mallarýnda azalma ve parasýnda artttýrýlma islmeleri yapýldý
							Genelsatici[saticisecme - 1].setUrunMiktar(urunAlinacakMiktar, urunsecme - 1);
							Genelsatici[saticisecme - 1].setPara(odenecekTutar-muhasebeyeOdenecekTutar);

							time_t tarih = time(NULL);
							struct tm *tarih_bilgisi = localtime(&tarih);


							//saticinin sattýgý urunleri gormesi icin gerceklestiridi
							Genelsatici[saticisecme - 1].satilanEkleme(Genelsatici[saticisecme - 1].getUrunAd(urunsecme - 1), urunAlinacakMiktar, Genelsatici[saticisecme - 1].getUrunFiyat(urunsecme - 1), tarih_bilgisi->tm_year + 1900, tarih_bilgisi->tm_mon + 1, tarih_bilgisi->tm_mday);

							//alýcýnýn aldýgý urunleri gormesi icin gerceklestirildi
							alici.siparisEdilenlerEkleme(Genelsatici[saticisecme - 1].getUrunAd(urunsecme - 1), urunAlinacakMiktar, odenecekTutar, tarih_bilgisi->tm_year + 1900, tarih_bilgisi->tm_mon + 1, tarih_bilgisi->tm_mday, Genelsatici[saticisecme - 1].getUrunFiyat(urunsecme - 1));

							//alýcýnýn parasýnda azalma saglandý ve donguden cýkma islemi gerceklestirildi
							alici.setPara(odenecekTutar);
							ticaretKontrol = 0;

							muhasebe.setPara(muhasebeyeOdenecekTutar);

							//istenilen detaylar gosterildi
						
	
							cout << endl << endl;
							cout << "isleme zamaný: " <<tarih_bilgisi->tm_year+1900<<"."<<tarih_bilgisi->tm_mon+1<<"."<<tarih_bilgisi->tm_mday<<" "<<tarih_bilgisi->tm_hour<<"."<<tarih_bilgisi->tm_min<<"."<<tarih_bilgisi->tm_sec<< endl;
							cout << "Yapýlan Ýþlem Detayi: " << alici.adDondur() << " adli alici " << Genelsatici[saticisecme - 1].adDondur() << " adli saticidan " << Genelsatici[saticisecme - 1].getUrunAd(urunsecme - 1) << " ürününden birim fiyati " << Genelsatici[saticisecme - 1].getUrunFiyat(urunsecme - 1) << " tl olmak üzere " << urunAlinacakMiktar << " kg almistir" << endl << endl;
							cout << "Harcanan Tutar: " << alici.adDondur() << " adli alici " << Genelsatici[saticisecme - 1].adDondur() << " adli saticinin hesabýna " << odenecekTutar-muhasebeyeOdenecekTutar << " tl tuatunda para gönderdi." << endl << endl;
							cout << "Alicinin Kalan Parasý: " << alici.adDondur() << " adli alicinin " << alici.paraDondur() << " tl parasi kaldi." << endl << endl;
							cout << "satilan malin birim fiyati: " << Genelsatici[saticisecme - 1].getUrunFiyat(urunsecme - 1) << " tl" << endl;
							cout << "muhasebeye odenen tutar: " << muhasebeyeOdenecekTutar<<" tl" << endl << endl;

							cout << "Ticaret gerçekleþmistir bilgi menusu icin enter'a basiniz.." << endl;
							system("pause");
							AliciBilgiMenu(alici, Genelsatici, GenelAlici);




						}
						else {
							cout << endl << "ticaretten vaz geçilmiþtirdir bilgi menüsüne dönmek için enter basiniz." << endl;
							ticaretKontrol = 0;
							system("pause");
							AliciBilgiMenu(alici, Genelsatici, GenelAlici);
						}


						break;
					}
					else {
						cout << endl << "almak istediginiz mikatiri ödeyecek bakiyeniz bulunmamaktadir.." << endl;


					}

				}
				else {
					cout << endl << "saticida bu kadar ürün bulunmamaktadir.." << endl;
				}

				//ticarete devam edilip edilmemek istediginin kontroulu gerceklestirildi
				cout << endl << "yeniden aliþ iþlemine devam etmek istiyorsaniz E tuþuna basiniz.Ticaret yapmadan bilgi menüsüne dönmek istiyorsaniz H basiniz: ";
				cin >> ticaretDevamlýlýk;

				if (ticaretDevamlýlýk == "E" || ticaretDevamlýlýk == "e") {
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






//menunden gelen aliciyi , saticilarin ait oldugu ve alicilarin oldugunu degerler alicibilgi menuye yollanmýstýr
//Genelsaticida ve Genelalicida butun satici ve alicilar tutulur. alici sadece o alicinin bilgileri bulunmaktadýr



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
	cout << "\t|4.Para gösterme                     |" << endl;
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
		//alicilarýn bilgileri gosterir
		system("cls");
		cout << endl << "\t\t --- Profil Bilgileri ---" << endl;
		alici.bilgiGoster();
		cout << endl << "Tekrardan bilgi menuye donmek için enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		break;

	case 2:
		//alicinin piyasadaki satýcýlarýn sattýgý mallarýný gosterilme islemini gerceklestirdim
		system("cls");
		cout << endl << "\t\t --- Piyasadaki Satici Mallar ---" << endl << endl;

		if (saticiSayisi > 0) {
			//Genel satici ile butun satýcýlara ve onlarýn ait oldugu urunlere ulastýk
			for (int i = 0; i < saticiSayisi; i++) {

				cout << i + 1 << ".Satici ad: " << Genelsatici[i].adDondur() << " " << i + 1 << ".Satici soyad: " << Genelsatici[i].soyadDondur() << endl << endl;
				Genelsatici[i].sahipOlunanMallar();
				cout << endl << "-----------------------------" << endl;
			}
		}
		else {
			cout <<endl<< "piyasada satici bulunmamaktadir." << endl;
		}


		cout << endl << "Tekrardan bilgi menuye donmek için enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		break;

	case 3:
		//alýcýnýn para hesabýna para ekleme istegini gerceklestirdik
		ParaEkleme(alici, Genelsatici, GenelAlici);

		cout << endl << "Tekrardan bilgi menuye donmek için enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		break;

	case 4:
		//alýcýnýn hesabýndaký para miktarýný gostermek icin olusturdum
		system("cls");
		cout << endl << "\t\t --- Para Gösterme ---" << endl << endl;
		cout << "Bakiyeniz: " << alici.paraDondur();
		cout << endl << "Tekrardan bilgi menuye donmek için enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);
		break;

	case 5:
		//alýcýnýn ticaret islemini gerceklestirmek icin alicinýn bilgilerini ve sistemdeki butun alýcý ve satýcýnýn bilgilerini yolladým.
		TicaretYapma(alici, Genelsatici, GenelAlici);

		break;

	case 6:
		//alýcýnýn aldýgý urunleri gostermek ýcýn olusturdum.
		alici.siparislerGosterme();
		cout << endl << "Tekrardan bilgi menuye donmek için enter'a basiniz.";
		system("pause");
		AliciBilgiMenu(alici, Genelsatici, GenelAlici);

		break;



	case 7:
		system("cls");
		
		cout << "\t\t --- On Siparis Paneli ---" << endl << endl;
		cout << "siparis etmek istediginiz urunun adý: ";
		cin >> OnSiparisurunAd;
		cout << "siparis etmek istediginiz urunun miktari: ";
		cin >> urunMiktar;
		cout << "siparis etmek istediginiz urunun birim fiyati: ";
		cin >> urunFiyat;

		//muhasebeye odenecek para aliya yansýtýlýr
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
			//Genel satici ile butun satýcýlara ve onlarýn ait oldugu urunlere ulastýk
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


//menunden gelen saticiyi , saticilarin ait oldugu ve alicilarin oldugunu degerler saticibilgi menuye yollanmýstýr
//Genelsaticida ve Genelalicida butun satici ve alicilar tutulur. saticida sadece o saticinin bilgileri bulunmaktadýr

void SaticiBilgiMenu(Satici &satici, Satici  *Genelsatici, Alici *Genelalici) {

	system("cls");
	int secim = 0;

	cout << "\t\t --- Satici Bilgi Ekran ---" << endl << endl;
	cout << "\t----------------------------------" << endl;
	cout << "\t|1.Profil bilgileri              |" << endl;
	cout << "\t|2.Sahip olunan mallari göster   |" << endl;
	cout << "\t|3.Urun ekleme ve fiyatlandirma  |" << endl;
	cout << "\t|4.Bakiye gösterme               |" << endl;
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
		cout << endl << "Tekrardan bilgi menuye donmek için enter'a basiniz.";
		system("pause");
		SaticiBilgiMenu(satici, Genelsatici, Genelalici);
		break;

	case 2:
		//saticinin kaydedilmis olan urunlerinin gosterilmesi
		system("cls");
		cout << endl << "\t\t --- Sahip Olunan Urun Bilgileri ---" << endl;
		satici.sahipOlunanMallar();
		cout << endl << "Tekrardan bilgi menuye donmek için enter'a basiniz.";
		system("pause");
		SaticiBilgiMenu(satici, Genelsatici, Genelalici);

	case 3:
		//saticinin urunlerini sisteme kaydetme isteginde bulunmasý islemi icin fonksiyana yolladýk
		urunVeFiyatBelirlemeMenu(satici, Genelsatici, Genelalici);
		break;

	case 4:
		//saticinin sahip oldugu parayý gostermek ýcýn yaptým
		system("cls");
		cout << "bakiyeniz: " << satici.paraDondur() << " tl" << endl;;
		cout << endl << "bilgi menusune dönmek için enter'a basiniz.";
		system("pause");
		SaticiBilgiMenu(satici, Genelsatici, Genelalici);

		break;

	case 5:
		//satilan urunlerin gosterimi
		satici.satilanUrunlerGoster();
		cout << endl << "bilgi menusune dönmek için enter'a basiniz.";
		system("pause");
		SaticiBilgiMenu(satici, Genelsatici, Genelalici);

		break;


	case 6:

		//satilan urunu raporlandýrma

		satici.raporOlusturma();
		cout << endl << "bilgi menusune dönmek için enter'a basiniz.";
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



void KayitMenu(Satici  *satici, Alici *alici) {  //menuden gelen kayýt istegi icin olusturdum.
	system("cls");


	double  Fiyat = 0, miktar = 0;
	string ad, soyad, kullancýAdi, password, E_mail, Adres, ürünAdi, Telefon, TcKimlikNo;

	int kontrol = 1;
	int kullaniciAdKontrol = 0;

	system("cls");
	int hangiKullanici = 0;
	cout << "\t\t --- Kayit Ekrani ---" << endl << endl;
	cout << "\t------------------------------------------------------------------------" << endl;
	cout << "\t|Hangi kullanici olarak kayit yaptýrmak istersiniz...                  |" << endl;
	cout << "\t|Satici olarak kayit icin 1'e Alici olarak kayit icin 2'e basiniz: ";
	cin >> hangiKullanici;



	//kullanýcýnýn satici mý yoksa alici mý oldugunu ogrenip ona yonelelik kaydetme islemini gerceklestirdim
	if (hangiKullanici == 1 || hangiKullanici == 2) {
		cout << endl;
		cout << "Adinizi giriniz: ";
		getline(cin, ad);
		getline(cin, ad);


		cout << "Soyadinizi giriniz: ";
		getline(cin, soyad);

		//kullanýcý adininn daha once kullanýlýp kullanýlmadýgýný test etmek ve ona gore kullanýcý secmek icin olusturdum
		while (kontrol == 1) {
			kullaniciAdKontrol = 0;
			cout << "Kullanici adini giriniz: ";
			getline(cin, kullancýAdi);

			//kullanýcýAdKontrol benim kullanýcý adýmýn daha once kullanýlýlmýsmý onu test eder
			for (int i = 0; i < saticiSayisi; i++) {
				if (satici[i].KullaniciAdDondur() == kullancýAdi) {
					kullaniciAdKontrol = 1;
				}
			}
			for (int i = 0; i < aliciSayisi; i++) {
				if (alici[i].KullaniciAdDondur() == kullancýAdi) {
					kullaniciAdKontrol = 1;
				}
			}

			//daha once bu kullanýcý adýyla islem yapmadýgýný gösteren ve donguden cýkmak icin if yapýsýný olusturdum
			if (kullaniciAdKontrol == 0 && kullancýAdi != admin.kullanciAdDondur()) {
				kontrol = 0;
			}
			else {
				cout << "Bu kullanici adi alinmiþtir baþka bir kullanici adi seçiniz.." << endl;
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


		//secilen kullanýcýyýya gore kayýdý gerceklestiriliyor
		if (hangiKullanici == 1) {

			//kullanýcýfonk bulunan kayit fonksiyonuyla satici kaydedildi
			satici[saticiSayisi].kayit(ad, soyad, kullancýAdi, password, E_mail, Adres, TcKimlikNo, Telefon);
			saticiSayisi++;

		}
		else if (hangiKullanici == 2) {
			//kullanýcýfonk bulunan kayit fonksiyonuyla alici kaydedildi
			alici[aliciSayisi].kayit(ad, soyad, kullancýAdi, password, E_mail, Adres, TcKimlikNo, Telefon);
			aliciSayisi++;
		}

		cout << endl << "Kayit iþleminiz gerçekleþmiþtir Giriþ için enter basiniz..";
		system("pause");
		menu(satici, alici);

	}

	else {
		cout << "\tGirdiginiz deger uygun secim degildir.Kayit ekranýna tekrardan yollaniyorsunuz." << endl;
		KayitMenu(satici, alici);
	}


	system("pause");

}



void menu(Satici  *satici, Alici *alici) { //olusturdugum  satici ve alýcý kullanýcýlarý menu ekranýna yolladýk
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

	//saticinin daha önce kaydýnýn yapýlýp yapýlmadýgýný anlamak icin olusturdum.Eger varsa bunun hangi saticiya ait oldugunu
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

	//alýcýnýn daha once kaydýnýn yapýlýp yapýlmadýgýný anlamak icin olusturdum.Eger varsa bunun hangi aliciya ait oldugunu
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


	//Girilen kullanýcýlar bulunmus ise ona ait bilgi paneline gonderme islemini gerceklestirdim
	if (saticiBulmaKullanici == 1 && saticiBulmaPassword == 1) {

		SaticiBilgiMenu(satici[saticiKonum], satici, alici);



	}
	else if (aliciBulmaKullanici == 1 && aliciBulmaPassword == 1) {

		AliciBilgiMenu(alici[alicikonum], satici, alici);

	}

	//kullanýcýyý bulmus fakat sifresi yanlýs ise bunu kullanýcýya bilgilerdime islemi yaptým
	else if (saticiBulmaKullanici == 1 || aliciBulmaKullanici == 1) {
		cout << endl << "þifreyi yanlis girdiniz..Tekrar denemek icin enter'a basiniz." << endl;
		system("pause");
		menu(satici, alici);
	}



	//admin giris yapmýs ise admþn paneline yolladým
	else if (kullaniciAd == admin.kullanciAdDondur() && parola == admin.parolaDondur()) {
		AdminPaneli(satici, alici);
	}

	//muhasebeci giris yapmýs ise muhasebe paneline gonder

	else if (kullaniciAd == muhasebe.KullaniciAdDondur() && parola == muhasebe.passWordDondur()) {
		muhasebePaneli(satici, alici);
	}



	else {
		cout << endl << "kimliginiz bulunamadi yeni kayit olmak icin E tusuna basiniz.Tekrardan menuye ulasmak icin herhangi bir tusa basiniz: ";
		cin >> kullaniciSecim;


		//kayýt daha once yoksa kayýt yapmak istediginin teyitini etmek eger istiyorsa kayýt icin yonlendirilmesini gerceklestirdim
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

	
	
	
	//alýcý ve satici olusturdum ve menuye yolladým
	Satici *satici = new Satici[30];
	Alici *alici = new Alici[30];

	menu(satici, alici);



	system("pause");
	return 0;
}