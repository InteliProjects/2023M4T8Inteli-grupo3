from driver.conn import connect
from fastapi import APIRouter

router = APIRouter()

@router.get("/{SN_barCode}")
async def confirmarAtivo(SN_barCode):

    database = await connect()

    print(SN_barCode)

    query = """
        SELECT "neName"
        FROM ativos WHERE "SN_barCode" = :SN_barCode
    """

    result = await database.fetch_all(query, {"SN_barCode": SN_barCode})

    await database.disconnect()

    return result

@router.get("/gps/{gps_id}")
async def confirmarGps(gps_id):

    database = await connect()

    query = """
        SELECT ""
        FROM gps WHERE "rfid" = :gps_id
    """

    result = await database.fetch_all(query, {"gps_id": gps_id})

    await database.disconnect()

    if result == None:
        return {"message": "GPS não encontrado"}
    else:
        return {"message": "GPS encontrado "}
    
