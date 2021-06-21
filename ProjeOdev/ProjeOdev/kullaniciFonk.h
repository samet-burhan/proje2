#pragma once

#include<string>
#include <iostream>
using namespace std;
#include "Kullanici.h"




//kullanýcýlarýn kayýt islemi gerceklestirildi
void Kullanicilar::kayit(string ad, string soyad, string kullanciAdi, string password, string Email, string adres, string   Tc_KimlikNo, string   telefon) {

	this->ad = ad;
	this->soyad = soyad;
	this->kullanciAdi = kullanciAdi;
	this->password = password;
	this->Email = Email;
	this->adres = adres;
	this->TC_KimlikNo = Tc_KimlikNo;
	this->telefon = telefon;


}

string Kullanicilar::KullaniciAdDondur() {

	return kullanciAdi;
}


string Kullanicilar::passWordDondur() {
	return password;
}

void Kullanicilar::bilgiGoster() {

	cout << "ad: " << ad << endl;
	cout << "soyad: " << soyad << endl;
	cout << "Tc No: " << TC_KimlikNo << endl;
	cout << "Telefon: " << telefon << endl;
	cout << "EMail: " << Email << endl;
	cout << "Adres: " << adres << endl;

}

string Kullanicilar::adDondur() {
	return ad;
}



double Kullanicilar::paraDondur() {

	return para;
}

string Kullanicilar::soyadDondur() {

	return soyad;
}

string Kullanicilar::TcDondur() {

	return TC_KimlikNo;
}