from driver.conn import connect
from fastapi import APIRouter, Path

router = APIRouter()

@router.get("/{page}/{items_per_page}")
async def listAtivos(page: int, items_per_page: int):
    database = await connect()

    # Calculate the offset based on the page number
    offset = (page - 1) * items_per_page

    query = """
        SELECT "SN_barCode", "cidade", "Description", "fim_garantia" FROM ativos
        LIMIT :items_per_page OFFSET :offset
    """

    result = await database.fetch_all(query, {"items_per_page": items_per_page, "offset": offset})

    await database.disconnect()

    return result
