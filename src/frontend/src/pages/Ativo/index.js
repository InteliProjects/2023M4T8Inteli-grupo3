import React, { useState, useEffect } from "react";
import { Container } from "./../Homepage/style";
import AsideBar from "../../components/AsideBar";
import MainContent from "../../components/MainContent";
import TrackerLog from "../../components/TrackerLog";
import { GetAtivoBySerialNumber } from "../../services/get/ativoBySerialNumber";
import TabelaAtivo from "../../components/AtivoTable";
import Mapa from "../../components/Mapa";
import { useLocation } from "react-router-dom";
import { useReactToPrint } from "react-to-print";
import {
  LeftContainerContent,
  QrCode,
  QrCodeContainer,
  QrCodeInfo,
} from "./style";

function LeftContainer({ coordenadas, urlqrcode }) {
  const componentRef = React.useRef();

  const handlePrint = useReactToPrint({
    content: () => componentRef.current,
  });

  return (
    <LeftContainerContent>
      <QrCodeContainer onClick={handlePrint}>
        <QrCode ref={componentRef} src={`https://dotnemo.tech/api/${urlqrcode}`} />
        <QrCodeInfo>
          Este é o QR associado ao seu ativo. Clique aqui para imprimí-lo.
        </QrCodeInfo>
      </QrCodeContainer>
      <Mapa
        key="map"
        width={"100%"}
        caption={false}
        coordenadas={coordenadas}
      />
    </LeftContainerContent>
  );
}

function AtivoPage() {
  const [ativo, setAtivo] = useState(null);
  const location = useLocation();
  const serialNumber = location.pathname.replace("/ativo/", "");

  useEffect(() => {
    (async () => {
      await GetAtivoBySerialNumber(serialNumber).then((response) => {
        setAtivo(response);
      });
    })();
  }, []);

  const coordenadas = ativo
    ? [
        {
          position: [ativo.result[0].lat, ativo.result[0].lon],
          name: "Ativo Location",
        },
      ]
    : [];

  const urlqrcode = ativo ? ativo.qrcode_url : null;

  console.log(ativo);
  return (
    <Container>
      <AsideBar />
      <MainContent
        title={"Detalhamento de ativo"}
        components={[
          <LeftContainer urlqrcode={urlqrcode} coordenadas={coordenadas} />,
          <TabelaAtivo key="table" ativo={ativo} />,
          <TrackerLog />,
        ]}
      />
    </Container>
  );
}
export default AtivoPage;
