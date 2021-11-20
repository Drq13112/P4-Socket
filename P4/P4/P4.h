// P4.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

// TODO: Reference additional headers your program requires here.
struct datos_robot {
	char modo; // ‘x’: ningún modo activo
	// ‘m’: manual sin HOME
	// ‘M’ manual con HOME
	// ‘D’: MDI
	// ‘A’: automático
	char motor_activo; // ‘0’: ningún motor activo
	// ‘1/2/3’: activo el motor 1/2/3
	// ‘4’: todos los motores activos
	char tipo_interpolacion_G; // ‘0’, ‘1’, ‘2’, ‘3’, ‘4’
	float vel_F; // velocidad lineal
	float radio_giro_R; // radio
	struct posicion pos_XY_final; // posición final de la trayectoria actual
	struct posicion pos_XY_cmd; // posición comandada (o interpolada)
	struct posicion pos_XY_real; // posición real
	struct timeval timestamp; // instante temporal de lectura de datos
};

struct posicion {
	float X;
	float Y;
};

struct sockaddr_in
{
	short sin_family;   //address family: AF_INET
	short sin_port;     //port in network byte order
	uint32_t sin_addr; //internet address
};