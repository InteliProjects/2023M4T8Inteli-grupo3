import React, { useState, useEffect } from "react";
import { Html5QrcodeScanner } from "html5-qrcode";
import { AtualizarLocs } from "../../services/get/atualizarLocs";

function LeitorQrCode() {
  const [scanResult, setScanResult] = useState(null);
  const [gps_id, setGps_id] = useState(null);
  const [ativos, setAtivos] = useState([]);
  const [first, setFirst] = useState(true);

  let scanner;

  function enviarAtivos(gps_id, ativos) {
    const body = {
      gps_id: gps_id,
      ativos: ativos,
    };
    AtualizarLocs(body);
  }

  useEffect(() => {
    scanner = new Html5QrcodeScanner("reader", {
      qrbox: {
        width: 250,
        height: 250,
      },
      supportedScanTypes: Html5QrcodeScanner.SCAN_TYPE_CAMERA,
      fps: 10,
    });

    scanner.render(success, error);

    function success(result) {
      if (first) {
        setGps_id(result);
        setFirst(false);
        console.log("gps: ",result);
        
      } else {
        console.log("ativo: ",result);
        setAtivos([...ativos, result]);
      }
      scanner.clear();
      setScanResult(result);

      return;
    }

    function error(error) {
      console.warn(error);
    }
    return () => {
      scanner.clear(); // Cleanup the scanner when the component is unmounted
    };
  }, []);

  function resetar() {
    setGps_id(null);
    setAtivos([]);
  }

  return (
    <div id="reader">
      <div className="Reader">
      </div>
      <h1>Leitor QR Code</h1>
      <h1>Primeiro leia o QrCode do GPS</h1>
      
      <button onClick={() => enviarAtivos(gps_id, ativos)}>Enviar</button>
      <button onClick={() => resetar()}>Cancelar</button>
    </div>
  );
}

export default LeitorQrCode;
