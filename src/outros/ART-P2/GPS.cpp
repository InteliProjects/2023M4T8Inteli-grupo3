// Inclui os cabeçalhos das classes GPS e LCD
#include "GPS.h"
#include "LCD.h"

// Construtor da classe GPS: inicializa a disponibilidade como falsa
GPS::GPS()
{
    isAvailable = false;
}

// Gera um valor aleatório de latitude entre -90 e 90 graus
float GPS::generate_random_latitude()
{
    uint32_t randNumber = esp_random();                                        // Gera um número aleatório
    float latitude = -90.0 + (90.0 + 90.0) * (randNumber / (float)UINT32_MAX); // Converte para latitude
    return latitude;
}

// Gera um valor aleatório de longitude entre -180 e 180 graus
float GPS::generate_random_longitude()
{
    uint32_t randNumber = esp_random();                                            // Gera um número aleatório
    float longitude = -180.0 + (180.0 + 180.0) * (randNumber / (float)UINT32_MAX); // Converte para longitude
    return longitude;
}

// Atualiza as coordenadas GPS com valores aleatórios
bool GPS::update()
{
    delay(250); // Delay para simular a atualização de dados

    latitude = generate_random_latitude();   // Atualiza a latitude
    longitude = generate_random_longitude(); // Atualiza a longitude

    isAvailable = true; // Marca as coordenadas como disponíveis
    return true;        // Retorna verdadeiro indicando atualização bem-sucedida
}

// Retorna a latitude atual se disponível; caso contrário, retorna 0
float GPS::getLatitude()
{
    if (isAvailable)
    {
        return latitude;
    }
    else
    {
        return 0; // Retorna 0 se os dados não estiverem disponíveis
    }
}

// Retorna a longitude atual se disponível; caso contrário, retorna 0
float GPS::getLongitude()
{
    if (isAvailable)
    {
        return longitude;
    }
    else
    {
        return 0; // Retorna 0 se os dados não estiverem disponíveis
    }
}
