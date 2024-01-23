from dotenv import load_dotenv
load_dotenv()  # Carrega as variáveis de ambiente do arquivo .env

from driver.conn import connect
from fastapi import APIRouter, Response, HTTPException
from pydantic import BaseModel
import jwt
import os
from datetime import datetime, timedelta

router = APIRouter()

secret_jwt = os.environ.get('SECRET_JWT')

class Login(BaseModel):
    username: str
    password: str

@router.post("")
async def login(login: Login, response: Response):

    database = await connect()

    query = """
        SELECT "user_name", "password" FROM users WHERE "user_name" = :username
    """

    result = await database.fetch_one(query, {"username": login.username})

    print(result["password"])

    await database.disconnect()

    try:
        if result is None:
            print("entrei no primeiro if")
            #retornar status code 401
            return {"message": "Usuário não encontrado"}
        else:
            print("entrei no primeiro else")
            if not result["password"] == login.password:
                print("entrei no segundo if")
                return {"message": "Senha incorreta"}
            else:
                print("entrei no segundo else")
                expiration = datetime.utcnow() + timedelta(minutes=600)
                token = jwt.encode({"username": login.username, "exp": expiration}, secret_jwt, algorithm="HS256")
                response.set_cookie(key="token", value=token, httponly=True, samesite="none", secure=True)
                print(token)
                return {"message": "Login realizado com sucesso"}
    except Exception as e:
        print(e)
        return {"message": "Ocorreu um erro ao realizar o login"}
