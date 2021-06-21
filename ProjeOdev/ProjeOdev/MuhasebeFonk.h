#pragma once

#include<string>
#include <iostream>
#include "Kullanici.h"
using namespace std;


string Muhasebeci::KullaniciAdDondur() {


	return kullanciAdi;

}

string Muhasebeci::passWordDondur() {

	return password;
}

double Muhasebeci::paraDondur() {

	return para;
}


void Muhasebeci::bilgiGoster() {

	cout << "ad: " << ad << endl;
	cout << "soyad: " << soyad << endl;
	cout << "Tc No: " << TC_KimlikNo << endl;
	cout << "Telefon: " << telefon << endl;
	cout << "EMail: " << Email << endl;
	cout << "Adres: " << adres << endl;
}

void Muhasebeci::setPara(double para) {

	this->para = this->para + para;
}