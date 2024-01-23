from driver.conn import connect
from fastapi import APIRouter
from pydantic import BaseModel, ValidationError

router = APIRouter()

class Ativo(BaseModel):
    NE_Name: str
    NE_Address: str
    UF: str
    CIDADE: str
    Board_Full_Name: str
    Board_Name: str
    Board_Type: str
    NE_Type: str
    Bar_Code: str
    PN: str
    Description: str
    List_Price: str
    Preço: str
    ProcessoDeCompra: str
    Projeto: str
    FimDaGarantia: str
    NumeroDoContrato: str
    InicioDoContrato: str
    FimDoContrato: str
    state: str = "parado"
    tag_ativo: str = None
    

@router.post("/")
async def cadastro(ativo: Ativo):
    #pegar infos do corpo da requisição

    database = await connect()

    #inserir no banco de dados
    try:
        if await get_ativo(ativo.Bar_Code, database):
            return {"status": "ativo já cadastrado"}
        else:
            await database.execute(
            """
                INSERT INTO ativos ("neName", "neAddress2", "UF", "cidade", "boardFullName", "boardName", "boardType", "neType", "SN_barCode", "PN_BOMcode", "Description", "ListPrice", "price", "processo_compra", "projeto", "fim_garantia", "num_contrato", "inicio_contrato", "fim_contrato", "tag_ativo", "state", "lat", "lon", "cadastrado")
                VALUES (:NE_Name, :NE_Address, :UF, :CIDADE, :Board_Full_Name, :Board_Name, :Board_Type, :NE_Type, :Bar_Code, :PN, :Description, :List_Price, :Preço, :ProcessoDeCompra, :Projeto, :FimDaGarantia, :NumeroDoContrato, :InicioDoContrato, :FimDoContrato, :tag_ativo, :state, :lat, :lon, :cadastrado)
            """,
            {
                "NE_Name": ativo.NE_Name,
                "NE_Address": ativo.NE_Address,
                "UF": ativo.UF,
                "CIDADE": ativo.CIDADE,
                "Board_Full_Name": ativo.Board_Full_Name,
                "Board_Name": ativo.Board_Name,
                "Board_Type": ativo.Board_Type,
                "NE_Type": ativo.NE_Type,
                "Bar_Code": ativo.Bar_Code,
                "PN": ativo.PN,
                "Description": ativo.Description,
                "List_Price": ativo.List_Price,
                "Preço": ativo.Preço,
                "ProcessoDeCompra": ativo.ProcessoDeCompra,
                "Projeto": ativo.Projeto,
                "FimDaGarantia": ativo.FimDaGarantia,
                "NumeroDoContrato": ativo.NumeroDoContrato,
                "InicioDoContrato": ativo.InicioDoContrato,
                "FimDoContrato": ativo.FimDoContrato,
                "tag_ativo": ativo.tag_ativo,
                "state": ativo.state,
                "lat": 0,
                "lon": 0,
                "cadastrado": await cadastro(ativo.tag_ativo)
            }
        )
    except ValidationError as e:
        await database.disconnect()
        print(e.json())
        return {"status": "erro"}
    except Exception as e:
        await database.disconnect()
        print(e)
        return {"status": "erro"}

    await database.disconnect()

    return {"status": "cadastrado com sucesso", "Bar_Code": ativo.Bar_Code}


async def get_ativo(Bar_Code: str, database):
    query = """
        SELECT * FROM ativos WHERE "SN_barCode" = :SN_barCode
    """
    result = await database.execute(query, {"SN_barCode": Bar_Code})
    if result == None:
        return False
    return True


async def cadastro(tag_ativo: str):
    if tag_ativo == None:
        return "false"
    else:
        return "true"                    
