from driver.conn import connect
from fastapi import APIRouter
from fastapi.responses import JSONResponse, StreamingResponse
import qrcode
from io import BytesIO

router = APIRouter()

@router.get("/{gps_id}")
async def gps_qrCode(gps_id: int):
    database = await connect()

    query = """
        SELECT * FROM gps WHERE rfid = :gps_id
    """

    result = await database.fetch_one(query, {"gps_id": gps_id})

    if result is None:
        return {"message": "GPS não encontrado"}
    else:
        qrcode_data = await generate_qr_code(gps_id)
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
