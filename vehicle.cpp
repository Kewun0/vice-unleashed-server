#include "netgame.h"
#include <math.h>

extern CNetGame *pNetGame;

#define PI 3.14159265

//----------------------------------------------------------

CVehicle::CVehicle( BYTE byteModel, VECTOR *vecPos,
				    float fRotation, int iColor1,
				    int iColor2)
{

	// Store the spawn info.
	m_SpawnInfo.byteVehicleType = byteModel;
	m_SpawnInfo.fRotation = fRotation;
	m_SpawnInfo.vecPos.X = vecPos->X;
	m_SpawnInfo.vecPos.Y = vecPos->Y;
	m_SpawnInfo.vecPos.Z = vecPos->Z;
	m_SpawnInfo.iColor1 = iColor1;
	m_SpawnInfo.iColor2 = iColor2;

	// Set the initial pos to spawn pos.
	memset(&m_matWorld,0,sizeof(MATRIX4X4));
	m_matWorld.vPos.X = m_SpawnInfo.vecPos.X;
	m_matWorld.vPos.Y = m_SpawnInfo.vecPos.Y;
	m_matWorld.vPos.Z = m_SpawnInfo.vecPos.Z;

	memset(&m_vecMoveSpeed,0,sizeof(VECTOR));
	memset(&m_vecTurnSpeed,0,sizeof(VECTOR));
	
	m_bIsActive = TRUE;
	m_bIsWasted = FALSE;
	m_bHasHadUpdate = FALSE;
	m_byteDriverID = INVALID_ID;
	m_fHealth = 1000.0f;
}

//----------------------------------------------------
// Updates our stored data structures for this
// network vehicle.

void CVehicle::Update(BYTE bytePlayerID, MATRIX4X4 * matWorld,
		VECTOR * vecMoveSpeed, float fHealth)
{
	m_byteDriverID = bytePlayerID;
	memcpy(&m_matWorld,matWorld,sizeof(MATRIX4X4));
	memcpy(&m_vecMoveSpeed,vecMoveSpeed,sizeof(VECTOR));
	m_fHealth = fHealth;
	m_bHasHadUpdate = TRUE;
}

//----------------------------------------------------

void CVehicle::SpawnForPlayer(BYTE byteForPlayerID)
{
	RakNet::BitStream bsVehicleSpawn;

	// This system originally spawned at the last
	// reported location. Now it simply spawns
	// directly to the config entry point.
	// p.s. remove this comment if/when fixed.

	bsVehicleSpawn.Write(m_byteVehicleID);
	bsVehicleSpawn.Write(m_SpawnInfo.byteVehicleType);
	bsVehicleSpawn.Write(m_SpawnInfo.vecPos.X); // use spawn pos (having problems)
	bsVehicleSpawn.Write(m_SpawnInfo.vecPos.Y);
	bsVehicleSpawn.Write(m_SpawnInfo.vecPos.Z);
	bsVehicleSpawn.Write(m_SpawnInfo.fRotation);
	bsVehicleSpawn.Write(m_SpawnInfo.iColor1);
	bsVehicleSpawn.Write(m_SpawnInfo.iColor2);
	bsVehicleSpawn.Write(m_fHealth);

	// now add spawn co-ords and rotation
	bsVehicleSpawn.Write(m_SpawnInfo.vecPos.X);
	bsVehicleSpawn.Write(m_SpawnInfo.vecPos.Y);
	bsVehicleSpawn.Write(m_SpawnInfo.vecPos.Z);
	bsVehicleSpawn.Write(m_SpawnInfo.fRotation);
	
	pNetGame->GetRakServer()->RPC("VehicleSpawn",&bsVehicleSpawn,HIGH_PRIORITY,RELIABLE_ORDERED,
		0,pNetGame->GetRakServer()->GetPlayerIDFromIndex(byteForPlayerID),FALSE,FALSE);
}

//----------------------------------------------------------
