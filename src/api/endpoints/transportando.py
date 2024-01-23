from driver.conn import connect
from fastapi import APIRouter

router = APIRouter()

@router.get("/{tag_transporte}")
async def get_transportando(tag_transporte):

    database = await connect()

    transporte_id, lat, lon = await get_transporte(tag_transporte, database)

    query = "SELECT SN_barCode FROM ativos WHERE id_gps = %s"

    result = await database.fetch_all(query, (transporte_id,))

    await database.disconnect()

    return result, lat, lon

async def get_transporte(tag_transporte, database):

    query = "SELECT id_transporte, lat, lon FROM transportes WHERE id_tag_transporte = %s"

    result = await database.fetch_all(query, (tag_transporte,))

    return result[0][0], result[0][1], result[0][2]

