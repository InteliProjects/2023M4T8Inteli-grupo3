import styled from "styled-components"
import { FormQrCode } from "./style"
import { GetQrCode } from "../../services/get/qrCode";
import React,{ useEffect, useState } from "react";

export const GenQrCode = () => {
    const [qrCode, setQrCode] = useState(null);
    const [serialNumber, setSerialNumber] = useState(null);

  async function submit(){
    await GetQrCode(serialNumber).then((response) => {
        console.log(response);
        setQrCode(response);
      });
  }

    return (
        <FormQrCode>
            <label htmlFor="sn">Informe identificador do GPS:</label>
            <input type="text" name="sn" id="sn" placeholder="Serial Number" onChange={(event)=>setSerialNumber(event.target.value)}/>
            <button type="submit" onClick={(event) => { event.preventDefault(); submit(); }}>Gerar</button>
            {
                qrCode !== null ? <img src={`https://dotnemo.tech/api/gps/${serialNumber}`} alt="QR Code" /> : null
            }
        </FormQrCode>
    )
}