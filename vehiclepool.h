#pragma once

//----------------------------------------------------

class CVehiclePool
{
private:
	
	BOOL m_bVehicleSlotState[MAX_VEHICLES];
	CVehicle *m_pVehicles[MAX_VEHICLES];

public:
	
	CVehiclePool();
	~CVehiclePool();

	BOOL New(BYTE byteVehicleID, BYTE byteVehicleType, VECTOR * vecPos, float fRotation, int iColor1, int iColor2);
	BOOL Delete(BYTE byteVehicleID);	
		
	// Retrieve a vehicle by id
	CVehicle* GetAt(BYTE byteVehicleID) {
		if(byteVehicleID > MAX_VEHICLES) { return NULL; }
		return m_pVehicles[byteVehicleID];
	};

	// Find out if the slot is inuse.
	BOOL GetSlotState(BYTE byteVehicleID) {
		if(byteVehicleID > MAX_VEHICLES) { return FALSE; }
		return m_bVehicleSlotState[byteVehicleID];
	};

	BOOL InitialiseFromConfig(CConfig *pConfig);
	void Process();
};

//----------------------------------------------------