#include "TSE.h"
#include <iostream>
#include<Windows.h>
#include<sstream>
using namespace std;
class Partido { // Interfaz de los elementos observers
protected:
	int valorPLN;
	int valorPUSC;
	int valorPSD;
public:
	Partido();
	virtual ~Partido();
	virtual void upDate(int, int, int) = 0;
	virtual string toString() = 0;
	virtual void graficando() = 0;
	virtual int getValPLN();
	virtual int getValPUSC();
	virtual int getValPSD();

};

Partido::Partido()
{
	cout << "---Construyendo partido politico---" << endl;
	valorPLN = 0;
	valorPSD = 0;
	valorPUSC = 0;
}

Partido::~Partido()
{
}

int Partido::getValPLN()
{
	return valorPLN;
}

int Partido::getValPUSC()
{
	return valorPUSC;
}

int Partido::getValPSD()
{
	return valorPSD;
}

//-------------------------------------------------------------------------------------------------
//------------------------- Sub clases observers concretos ----------------------------------------

class PartidoLiberacion : public Partido {
private:
	string nombre;
	//otras cosas....
public:
	PartidoLiberacion(): Partido() {
		nombre = "Partido Liberacion Nacional";
	}
	virtual ~PartidoLiberacion(){}
	void upDate(int a, int b, int c) { // a = PLN  b = PUSC  c = PSD
		valorPLN += a;
		valorPUSC += b;
		valorPSD += c;
	}
	string toString() {
		stringstream s;
		s << "-----" << nombre << "-----\n"
			<< "Votos PLN No.1: " << valorPLN << endl
			<< "Votos PUSC No.2: " << valorPUSC << endl
			<< "Votos PSD No.3: " << valorPSD << endl;
		return s.str();
	}
	void graficando() {
		// Esta vision no le interesa al PLN....
	}
};

class PartidoUnidad : public Partido {
private:
	string nombre;
	//otras cosas....
public:
	PartidoUnidad() : Partido() {
		nombre = "Partido Unidad Social Cristiana";
	}
	virtual ~PartidoUnidad() {}
	void upDate(int a, int b, int c) { // a = PLN  b = PUSC  c = PSD
		valorPLN += a;
		valorPUSC += b;
		valorPSD += c;
	}
	string toString() {
		// Esto no le interesa al PUSC
		return "";
	}
	void graficando() {
		cout << "---------- GRAFICA ----------\n";
		cout << "------------ PUSC -----------\n" << endl;
		cout << "1- PLN = " << endl;
		for (int i = 0; i < valorPLN / 100; i++) { cout << "*"; } cout << endl;
		cout << "2- PUSC = " << endl;
		for (int i = 0; i < valorPUSC / 100; i++) { cout << "*"; } cout << endl;
		cout << "3- PSD = " << endl;
		for (int i = 0; i < valorPSD / 100; i++) { cout << "*"; } cout << endl;
	}
};

class PartidoSocial : public Partido {
private:
	string nombre;
	//otras cosas....
public:
	PartidoSocial() : Partido() {
		nombre = "Partido Social Democrata";
	}
	virtual ~PartidoSocial() {}
	void upDate(int a, int b, int c) { // a = PLN  b = PUSC  c = PSD
		valorPLN += a;
		valorPUSC += b;
		valorPSD += c;
	}
	string toString() {
		stringstream s;
		int sumaVotos = valorPLN + valorPSD + valorPUSC;
		s << "-----" << nombre << "-----\n"
			<< "Porcentajes PLN No.1: " << (double)valorPLN * 100 / sumaVotos << "%" << endl
			<< "Porcentajes PUSC No.2: " << (double)valorPUSC * 100 / sumaVotos << "%" << endl
			<< "Porcentajes PSD No.3: " << (double)valorPSD * 100 / sumaVotos << "%" << endl;
		return s.str();
	}
	void graficando() {
		// Esta vision no le interesa al PSD....
	}
};

//-----------------------------------------------------------------------------------------------------
//-------------------------------------- Lo observado -------------------------------------------------
//----------------------------------------- TSE--------------------------------------------------------

class TSE {
private:
	int numMesa;
	int valor1; // votos de la mesa numMesa del PLN
	int valor2;// votos de la mesa numMesa del PUSC
	int valor3;// votos de la mesa numMesa del PSD
	Partido** vec;
	int can;
	int tam;
public:
	TSE();
	virtual ~TSE();
	void attach(Partido*); // agregar observer
	void setValores(int a, int b, int c); //setea sus valores por cada mesa nueva
	void notify(); // notificar de los cambios (nueva mesa) a todos los observers.
	void conteoDeVotosXMesa(); 
	void infoMesa();
	void solicitudDeNuevaMesa();
};

TSE::TSE()
{
	numMesa = 0;
	valor1 = 0;
	valor2 = 0;
	valor3 = 0;
	//contenedor...
	vec = new Partido * [5];
	tam = 5;
	can = 0;
	for (int i = 0; i < tam; i++)
	{
		vec[i] = NULL;
	}
}

TSE::~TSE()
{
	for (int i = 0; i < can; i++)
	{
		delete vec[i];
	}
	delete[] vec;
}

void TSE::attach(Partido* obs)
{
	if (can < tam) {
		vec[can++] = obs;
	}
}

void TSE::setValores(int a, int b, int c)
{
	valor1 = a;
	valor2 = b;
	valor3 = c;
	notify();
}

void TSE::notify()
{
	for (int i = 0; i < can; i++) {
		vec[i]->upDate(valor1, valor2, valor3);
	}
}

void TSE::conteoDeVotosXMesa()
{
	int v1, v2, v3;// valores aleatorios... ficticios para conteo de simulacion
	v1 = 1 + rand() / (101 - 1); 
	v2 = 1 + rand() / (101 - 1);
	v3 = 1 + rand() / (101 - 1);
	numMesa = 1 + rand() % (10001 - 1);
	//Sacamos simbolicamente el conteo de votos usando numeros aleatorios...
	this->setValores(v1, v2, v3);
}

void TSE::infoMesa()
{
	cout << "---- Informacion de la mesa numero: " << numMesa << endl;
	cout << "PLN = " << valor1 << " votos." << endl;
	cout << "PUSC = " << valor2 << " votos." << endl;
	cout << "PSD = " << valor3 << " votos." << endl;
	cout << "--------------------------------------------" << endl;
}

void TSE::solicitudDeNuevaMesa()
{
	this->conteoDeVotosXMesa();
}

// ---------------------------------- fin de las clases ----------------------------------------------


int main() {
	int x = 0;
	cout << "-----Participacion popular-----\n" << endl;
	cout << "Creacion de observadores de los partidos politicos...\n";
	Partido* obs1 = new PartidoLiberacion();
	Partido* obs2 = new PartidoUnidad();
	Partido* obs3 = new PartidoSocial;

	cout << "Creacion del TSE (subject)... \n";
	TSE* objTse = new TSE();
	
	cout << "Ingresar suscriptores (observers) al TSE..." << endl;
	objTse->attach(obs1);
	objTse->attach(obs2);
	objTse->attach(obs3);
	cout << endl;
	
	system("pause");
	system("cls");
	
	cout << "--------------------------Simulacion TSE--------------------------" << endl << endl;
	system("pause");
	while (x < 100) {
		system("cls");
		cout << "-------------------- TSE ------------------- \n";
		objTse->solicitudDeNuevaMesa();
		cout << endl;
		cout << "---------Informacion de la mesa-------\n";
		objTse->infoMesa();
		cout << endl;
		cout << "----- Informacion de la vista de los partidos politicos-----" << endl;
		cout << endl;
		cout << obs1->toString() << endl;
		cout << endl;
		obs2->graficando(); 
		cout << obs3->toString() << endl;
		x++;
		Sleep(3000);
	}

	system("pause");
	return 0;
}