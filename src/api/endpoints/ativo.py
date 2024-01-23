from driver.conn import connect
from fastapi import APIRouter
from fastapi.responses import JSONResponse, StreamingResponse
import qrcode
from io import BytesIO

router = APIRouter()

@router.get("/{SN_barCode}")
async def get_ativo(SN_barCode):

    database = await connect()

    print(SN_barCode)

    query = """
        SELECT lat, lon, state, "neName", "neAddress2", "UF", "cidade", "boardFullName",
               "Description", "PN_BOMcode", "SN_barCode", "neType", "boardType", "boardName",
               "fim_contrato", "inicio_contrato", "num_contrato", "fim_garantia", "projeto",
               "processo_compra", "ListPrice", "price", "tag_ativo"
        FROM ativos WHERE "SN_barCode" = :SN_barCode
    """

    result = await database.fetch_all(query, {"SN_barCode": SN_barCode})

    result = [dict(record) for record in result]

    await database.disconnect()

    # retorna os dados do ativo
    return JSONResponse(content={"result": result, "qrcode_url": "ativo/qrcode/" + SN_barCode})

@router.get("/qrcode/{SN_barCode}")
async def get_qrcode(SN_barCode: str):
    qrcode_data = await generate_qr_code(SN_barCode)
    return StreamingResponse(BytesIO(qrcode_data), media_type="image/png")

async def generate_qr_code(message):
    # Cria um objeto QRCode
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=10,
        border=4,
    )

    # Adiciona os dados ao objeto QRCode
    qr.add_data(message)
    qr.make(fit=True)

    # Cria uma imagem PIL a partir do objeto QRCode
    img = qr.make_image(fill_color="black", back_color="white")

    # Salva a imagem em um buffer de bytes
    img_byte_array = BytesIO()
    
    # Salva a imagem no buffer
    img.save(img_byte_array)

    # Retorna o buffer de bytes
    return img_byte_array.getvalue()
