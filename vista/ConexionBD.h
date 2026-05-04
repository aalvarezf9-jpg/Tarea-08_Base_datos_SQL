#pragma once
#include <mysql.h>
#include <iostream>
class ConexionBD
{
private:
	MYSQL* conector;
public:
	void abrir_conexion() {
		MYSQL* init = mysql_init(nullptr);
        if (!init) {
			conector = nullptr;
			return;
		}
		MYSQL* conn = mysql_real_connect(init, "localhost", "root", "Bokunohero123.", "db_escuela", 3306, NULL, 0);
		if (!conn) {
			// cleanup the init handle
			mysql_close(init);
			conector = nullptr;
			return;
		}
		conector = conn;
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

