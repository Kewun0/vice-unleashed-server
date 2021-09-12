#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

#define MAX_PLAYER_NAME		24
#define MAX_PLAYERS			50
#define MAX_VEHICLES		200

#include "raknet/RakServer.h"
#include "raknet/RakNetworkFactory.h"
#include "raknet/BitStream.h"

#include "system.h"
#include "config.h"

#define DEFAULT_CONFIG_FILE "server.ini"
#define DEFAULT_MAX_PLAYERS 32
#define DEFAULT_LISTEN_PORT 8192
#define DEFAULT_RCON_PORT	8190
#define DEFAULT_RCON_MAXUSERS	8

//----------------------------------------------------

void logprintf(char * format, ...);

//----------------------------------------------------

