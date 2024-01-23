import os
from databases import Database
from databases.core import DatabaseURL
from dotenv import load_dotenv
from yarl import URL

load_dotenv()

DB_HOST = os.environ.get('DB_HOST')
DB_PORT = os.environ.get('DB_PORT')
DB_NAME = os.environ.get('DB_NAME')
DB_USER = os.environ.get('DB_USER')
DB_PASSWORD = os.environ.get('DB_PASSWORD')

if not DB_HOST or not DB_PORT or not DB_NAME or not DB_USER or not DB_PASSWORD:
    raise Exception("Missing database environment variables")

# Use yarl para construir a URL do banco de dados
database_url = URL.build(
    scheme="postgresql",
    host=DB_HOST,
    port=int(DB_PORT),  # Certifique-se de que a porta seja convertida para um número inteiro
    path=f"/{DB_NAME}",
    user=DB_USER,
    password=DB_PASSWORD,
)

# Converta o objeto yarl.URL para DatabaseURL
database_url = DatabaseURL(str(database_url))

async def connect():
    try:
        database = Database(database_url)
        await database.connect()
        return database
    except Exception as error:
        print("Error while connecting to PostgreSQL", error)
        raise error