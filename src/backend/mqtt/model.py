from database.postgres import conn_postgres as database

import nest_asyncio
nest_asyncio.apply()

# Classe que representa o modelo MQTT
class MQTT_Model:

    @staticmethod
    async def get_ativo(identificador, by):
        if by == "tag":
            
            query = """SELECT * FROM ativos WHERE "tag_ativo" = $1"""

            async with database.transaction():
                result = await database.fetch(query, identificador)
                data = [{key: rec[key] for key in rec.keys()} for rec in result]
                if len(data)>0:
                    return data
                else:
                    query2 = """SELECT * FROM gps WHERE "rfid" = $1"""
                    async with database.transaction():
                            gps = await database.fetch(query2, int(identificador))
                    if len(gps)>0:
                        return [{"boardFullName":"gps","SN_barCode":""}]
                                          
                    else:
                        
                        return [{"boardFullName":"Tag_invalida","SN_barCode":""}]
        if by =="gps":
            query = """SELECT * FROM ativos WHERE "id_gps" = $1"""
            async with database.transaction():
                result = await database.fetch(query, identificador)
                data = [{key: rec[key] for key in rec.keys()} for rec in result]
                return data


    @staticmethod
    async def get_esp(tag_esp):
        query = """SELECT * FROM gps WHERE "rfid" = $1"""

        async with database.transaction():
            result = await database.fetch(query, tag_esp)
            print(result)
            return [{key: rec[key] for key in rec.keys()} for rec in result]

    async def atribuir_transporte_db(transport_id, tag_ativo):
        query = """UPDATE ativos SET "id_gps" = $1 WHERE "tag_ativo" = $2;"""

        async with database.transaction():
            await database.fetch(query, transport_id, tag_ativo)
            return "alterado"

    async def desatribuir_transporte_db(tag_ativo):
        query = """UPDATE ativos SET "id_gps" = NULL WHERE "tag_ativo" = $1;"""

        async with database.transaction():
            await database.fetch(query,tag_ativo)
            return "alterado"

    @staticmethod
    async def change_state_db(current_state, table, id_transporte, tag_ativo):

        if table == "ativos":
            query = """UPDATE ativos SET "state" = $1 WHERE "tag_ativo" = $2;"""

            async with database.transaction():
                await database.fetch(query, current_state, tag_ativo)
                return "alterado"
        elif table == "gps":
            query = """UPDATE gps SET "status" = $1 WHERE "id" = $2;"""

            async with database.transaction():
                await database.fetch(query, current_state, id_transporte)
                return "alterado"
        else:
            query = """UPDATE ativos SET "state" = $1 WHERE "tag_ativo" = $2;"""

            async with database.transaction():
                await database.fetch(query, current_state, tag_ativo)
                return "alterado"
    # Método estático para criar um log no banco de dados
    @staticmethod
    async def create_log_db(id_ativo, last_update, lat, lon, id_gps):
        # Executa a inserção no banco de dados
        query = """
            INSERT INTO logs(id_ativo, last_update, lat, lng, id_gps)
            VALUES($1, $2, $3, $4, $5);
            """

        async with database.transaction():
            await database.fetch(query, id_ativo, last_update, lat, lon, id_gps)



    @staticmethod
    async def atualizar_ativos_loc(lat, lon, id_gps):
        # Executa a inserção no banco de dados

        query2 = """
            UPDATE ativos SET "lat" = $1 , "lon" = $2 WHERE "id_gps" = $3;
            """
        async with database.transaction():
            await database.fetch(query2,lat, lon, id_gps)



    @staticmethod
    async def atualizar_gps_loc(lat, lon, id_gps):
        # Executa a inserção no banco de dados

        query3 = """
            UPDATE gps SET "lat" = $1 , "lng" = $2 WHERE "id" = $3;
            """
        async with database.transaction():
            await database.fetch(query3,lat, lon, id_gps)

