function obterCidadeEstado(latitude, longitude) {
  const url = `https://nominatim.openstreetmap.org/reverse?format=json&lat=${latitude}&lon=${longitude}&zoom=18&addressdetails=1`;

  fetch(url)
    .then((response) => response.json())
    .then((data) => {
      const cidade =
        data.address.city || data.address.town || data.address.village || "";
      const estado = data.address.state || "";

      if (cidade && estado) {
        console.log(`Cidade: ${cidade}, Estado: ${estado}`);
      } else {
        console.log("Não foi possível obter informações de localização.");
      }
    })
    .catch((error) => {
      console.error("Erro ao obter informações de localização:", error);
    });
}

// Exemplo de uso
const latitude = -23.5505; // Exemplo de latitude (para São Paulo)
const longitude = -46.6333; // Exemplo de longitude (para São Paulo)

obterCidadeEstado(latitude, longitude);
