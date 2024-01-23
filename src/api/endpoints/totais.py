from driver.conn import connect
from fastapi import APIRouter

router = APIRouter()

@router.get("/")
async def get_totais():

    database = await connect()

    query_n_ativos = "SELECT COUNT(*) FROM ativos"
    n_ativos = await database.fetch_all(query_n_ativos)

    query_manutencao = "SELECT COUNT(*) FROM ativos WHERE state = 'manutencao'"
    manutencao = await database.fetch_all(query_manutencao)

    query_movimento = "SELECT COUNT(*) FROM ativos WHERE state = 'movimento'"
    movimento = await database.fetch_all(query_movimento)

    query_estoque = "SELECT COUNT(*) FROM ativos WHERE state = 'estoque'"
    estoque = await database.fetch_all(query_estoque)

    await database.disconnect()

    return {
        "n_ativos": n_ativos[0][0],
        "manutencao": manutencao[0][0],
        "movimento": movimento[0][0],
        "estoque": estoque[0][0]
    }