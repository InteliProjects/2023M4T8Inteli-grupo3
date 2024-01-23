from fastapi import HTTPException, Cookie
import jwt
from dotenv import load_dotenv
import os
from datetime import datetime, timedelta

secret = os.environ.get('SECRET_JWT')

def check_token(token: str = Cookie(None)):
    credentials_exception = HTTPException(
    status_code=401,
    detail="Não autorizado",
)
    print(token)
    
    if token is None:
        raise credentials_exception

    try:
        payload = jwt.decode(token, secret, algorithms=["HS256"])
        username: str = payload.get("username")
        expiration: datetime = datetime.fromtimestamp(payload.get("exp"))

        if expiration is None:
            raise credentials_exception
        if datetime.utcnow() > expiration:
            raise credentials_exception
        
        if username is None:
            raise credentials_exception
        
    except jwt.PyJWTError:
        raise credentials_exception

    return True
