
#include <iostream>
#include <regex>
#include <string>
#include <ctime>
#include "Estudiante.h"

using namespace std;

// Funcion fecha estado
bool esFechaValida(int anio, int mes, int dia) {
	if (mes < 1 || mes > 12) return false;
	if (dia < 1 || dia > 31) return false;

	int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	//Años bisiestos
	if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {

		diasPorMes[1] = 29;
	}

	if (dia > diasPorMes[mes - 1]) {
		return false;
	}

	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);

	int anioAct = now.tm_year + 1900;
	int mesAct = now.tm_mon + 1;
	int diaAct = now.tm_mday;

	if (anio > anioAct) return false;
	if (anio == anioAct && mes > mesAct) return false;
	if (anio == anioAct && mes == mesAct && dia > diaAct) return false;

	return true;
}

bool validarNombreApellido(string texto) {
	const regex pattern("^[a-zA-ZÁ-ÿ\\s]{1,60}$");
	return regex_match(texto, pattern);
}

bool validarDireccion(string texto) {
	const regex pattern("^[a-zA-Z0-9Á-ÿ\\s#\\-\\.,]{1,100}$");
	return regex_match(texto, pattern);
}

int main() {
	string codigo, nombres, apellidos, direccion, fecha_nacimiento;
	int telefono = 0, id_tipo_sangre = 0, id_estudiante = 0;
	
	bool codigoValido = false;
	const regex exp_codigo("E[0-9]{3}"); //Indica el formato del codigo

	do {
		cout << "Ingrese Codigo (Formato E001): ";
		cin >> codigo;

		if (regex_match(codigo, exp_codigo)) {
			codigoValido = true;
		}
		else {
			cout << " xxx Formato incorrecto. Debe ser E seguido de 3 numeros (ej: E001) xxx" << endl;
		}
	} while (!codigoValido);

	cin.ignore();

	do {
		cout << "Ingrese Nombres: ";
		getline(cin, nombres);
		if (!validarNombreApellido(nombres)) {
			cout << " xxx Error: Solo se permiten letras y espacios (Max 60 caracteres) xxx" << endl;
		}
	} while (!validarNombreApellido(nombres));

	do {
		cout << "Ingrese Apellidos: ";
		getline(cin, apellidos);
		if (!validarNombreApellido(apellidos)) {
			cout << " xxx Error: Solo se permiten letras y espacios (Max 60 caracteres) xxx" << endl;
		}
	} while (!validarNombreApellido(apellidos));

	do {
		cout << "Ingrese Direccion: ";
		getline(cin, direccion);
		if (!validarDireccion(direccion)) {
			cout << " xxx Error: Direccion invalida o demasiado larga (Max 100 caracteres). xxx" << endl;
			cout << " xxx No use caracteres especiales como ' o ; xxx" << endl;
		}
	} while (!validarDireccion(direccion));

	
	string tel_aux;
	bool telValido = false;
	do {
		cout << "Ingrese Telefono (8 digitos): ";
		cin >> tel_aux;
		const regex exp_tel("^[0-9]{8}$");
		if (regex_match(tel_aux, exp_tel)) {
			telefono = stoi(tel_aux); // Convertir string a entero
			telValido = true;
		}
		else {
			cout << " xxx Error: El telefono debe tener exactamente 8 digitos numericos, sin espacios ni letras. xxx" << endl;
		}
	} while (!telValido);

	cin.ignore();
	string fecha_aux;
	bool fechaValida = false;
	do {
		cout << "Ingrese Fecha Nacimiento (AAAA-MM-DD): ";
		getline(cin, fecha_aux);

		//Formato fecha AAAA-MM-DD
		const regex exp_fecha("^(\\d{4})-(\\d{2})-(\\d{2})$");
		smatch matches;

		if (regex_match(fecha_aux, matches, exp_fecha)) {

			int anio = stoi(matches[1].str());
			int mes = stoi(matches[2].str());
			int dia = stoi(matches[3].str());

			if (esFechaValida(anio, mes, dia)) {
				fecha_nacimiento = fecha_aux;
				fechaValida = true;
			}
			else {
				cout << " xxx Error: La fecha no es real o es una fecha futura. xxx" << endl;
			}
		}
		else {
			cout << " xxx Error: Formato invalido. Use AAAA-MM-DD (ej: 2000-05-15). xxx" << endl;
		}
	} while (!fechaValida);

	cout << "Ingrese Tipo Sangre:";
	cin >> id_tipo_sangre;

	Estudiante e = Estudiante(nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre, codigo, id_estudiante);
	e.crear();
	e.leer();

	// Actualizacion
	cout << "Ingrese el ID a modificar:";
	cin >> id_estudiante;
	cout << "Ingrese Codigo:";
	cin >> codigo;
	cin.ignore();
	cout << "Ingres Nombres:";
	getline(cin, nombres);
	cout << "Ingres Apellidos:";
	getline(cin, apellidos);
	cout << "Ingres Direccion:";
	getline(cin, direccion);
	cout << "Ingrese Telefono:";
	cin >> telefono;
	cin.ignore();
	cout << "Ingres Fecha Nacimiento:";
	getline(cin, fecha_nacimiento);
	cout << "Ingrese Tipo Sangre:";
	cin >> id_tipo_sangre;

	e.setId_estudiante(id_estudiante);
	e.setCodigo(codigo);
	e.setNombres(nombres);
	e.setApellidos(apellidos);
	e.setDireccion(direccion);
	e.setTelefono(telefono);
	e.setFecha_Nacimiento(fecha_nacimiento);
	e.setId_Tipo_Sangre(id_tipo_sangre);
	e.actualizar();
	e.leer();
	cout << "Ingrese el ID a Eliminar:";
	cin >> id_estudiante;
	e.setId_estudiante(id_estudiante);
	e.borrar();
	e.leer();


}
