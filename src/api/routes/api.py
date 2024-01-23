from fastapi import APIRouter, Depends
import midleware
# from endpoints import x
from endpoints import totais, transportando, ativo, listAtivos, search, cadastro, leitorQrCode, confirmarAtivo, login, logout, qrCodeGPS, logs

router = APIRouter()


#exemplo de rota com autenticação
router.include_router(totais.router, prefix="/totais", dependencies = [Depends(midleware.check_token)])
router.include_router(transportando.router, prefix="/transporte", dependencies = [Depends(midleware.check_token)])
router.include_router(ativo.router, prefix="/ativo", dependencies = [Depends(midleware.check_token)])
router.include_router(listAtivos.router, prefix="/ativos", dependencies = [Depends(midleware.check_token)])
router.include_router(logs.router, prefix="/logs", dependencies = [Depends(midleware.check_token)])
router.include_router(search.router, prefix="/search", dependencies = [Depends(midleware.check_token)])
router.include_router(cadastro.router, prefix="/cadastro", dependencies = [Depends(midleware.check_token)])
router.include_router(leitorQrCode.router, prefix="/qrcode-read", dependencies = [Depends(midleware.check_token)])
router.include_router(confirmarAtivo.router, prefix="/confirmar-ativo", dependencies = [Depends(midleware.check_token)])
router.include_router(qrCodeGPS.router, prefix="/gps", dependencies = [Depends(midleware.check_token)])
router.include_router(logout.router, prefix="/logout", dependencies = [Depends(midleware.check_token)])
router.include_router(login.router, prefix="/login")