from driver.conn import connect
from fastapi import APIRouter

router = APIRouter()

@router.get("/{sn_barcode}")
async def logs(sn_barcode: str):
    database = await connect()

    query = """
        SELECT * FROM logs INNER JOIN ativos ON logs."id_ativo" = ativos."id_ativo" WHERE ativos."SN_barCode" = :sn_barcode
    """

    result = await database.fetch_all(query, {"sn_barcode": sn_barcode})

    await database.disconnect()

    return result