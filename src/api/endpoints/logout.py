from fastapi import APIRouter, Response

router = APIRouter()

@router.post("/")
def logout(response : Response):
    response.delete_cookie(key="token")
    return {"message": "Logout realizado com sucesso"}