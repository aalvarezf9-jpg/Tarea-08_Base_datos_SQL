#pragma once
#include <mysql.h>
#include <iostream>
class ConexionBD
{
private:
	MYSQL* conector;
public:
	void abrir_conexion() {
		conector = mysql_init(0);
		conector = mysql_real_connect(conector, "localhost", "root", "Admin123.", "db_escuela", 3306, NULL, 0);
	}
	MYSQL* getConector() {
		return conector;
	}
	void cerrar_conexion() {
		if (conector) {
			mysql_close(conector);
			conector = nullptr;
		}
	}
};

