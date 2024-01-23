from driver.conn import connect
from fastapi import FastAPI, HTTPException, APIRouter
from pydantic import BaseModel
from typing import List

router = APIRouter()

class Registro(BaseModel):
    ativos: List[str]
    gps: str

@router.put("/")
async def leitura_ativo(registro_data: Registro):
    gps = int(registro_data.gps)

    errors = []
    correct = 0

    database = await connect()
    loc = await get_loc(database, gps)

    state = await get_state(database, registro_data.ativos[0])

    for ativo in registro_data.ativos:
        query = 'UPDATE ativos SET "lat" = :lat, "lon" = :lon, "state" = :state WHERE "SN_barCode" = :SN_barCode'
        values = {"lat": loc["lat"], "lon": loc["lng"], "state": state, "SN_barCode": ativo}

        try:
            await database.execute(query, values)
            correct += 1
        except Exception as e:
            print(f"Error: {e}")
            errors.append(ativo)
    
    await database.disconnect()

    return {"correct": correct, "errors": errors}


async def get_loc(database, gps):
    result = await database.fetch_one('SELECT "lat", "lng" FROM gps WHERE "rfid" = :gps', {"gps": gps})
    return result

async def get_state(database, ativo):
    query = 'SELECT state FROM ativos WHERE "SN_barCode" = :SN_barCode'
    values = {"SN_barCode": ativo}
    result = await database.fetch_one(query, values)

    return "movimento" if result["state"] == "movimento" else "parado"