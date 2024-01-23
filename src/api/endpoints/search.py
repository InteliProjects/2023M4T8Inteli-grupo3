from driver.conn import connect
from fastapi import APIRouter, Path
from pydantic import BaseModel, ValidationError
from fastapi import HTTPException

router = APIRouter()


class Filtro(BaseModel):
    localizacao: str = "todas"
    fim_garantia: str = "todas"
    status: str = "todas"
    neType: str = "todas"
    search: str = ""
    Description: str = "todas"


@router.post("/{page}/{items_per_page}")
async def filtros(
    page: int,
    items_per_page: int,
    filtro: Filtro = Filtro()
):
    database = await connect()

    query = """
        SELECT * FROM ativos
        WHERE ("SN_barCode" ILIKE :search OR "boardFullName" ILIKE :search)
    """

    parameters = {
        "search": f"%{filtro.search}%",
        "limit": items_per_page,
        "offset": (page - 1) * items_per_page
    }

    if filtro.localizacao != "todas":
        query += ' AND "cidade" ILIKE :cidade'
        parameters["cidade"] = f"%{filtro.localizacao}%"

    if filtro.fim_garantia != "todas":
        query += ' AND "fim_garantia" ILIKE :fim_garantia'
        parameters["fim_garantia"] = f"%{filtro.fim_garantia}%"

    if filtro.status != "todas":
        query += ' AND "state" ILIKE :state'
        parameters["state"] = f"%{filtro.status}%"

    if filtro.neType != "todas":
        query += ' AND "neType" ILIKE :neType'
        parameters["neType"] = f"%{filtro.neType}%"

    if filtro.Description != "todas":
        query += ' AND "Description" ILIKE :Description'
        parameters["Description"] = f"%{filtro.Description}%"

    query += ' ORDER BY "boardFullName" LIMIT :limit OFFSET :offset'

    result = await database.fetch_all(query, parameters)

    print(query, "\n \n", parameters)

    await database.disconnect()

    if not result:
        return result
    else:
        return result
