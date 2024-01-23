import React from "react";
import { Container } from "./../Homepage/style";
import MainContent from "../../components/MainContent";
import { GenQrCode } from "../../components/GenQrCode";
import AsideBar from "../../components/AsideBar";


export default function QrCode() {

  return (
    <Container>
      <AsideBar />
      <MainContent
      title = {"Gerar QR Code do GPS"}
      components = {
      [
        <GenQrCode />
      ]
      }>
      </MainContent>
    </Container>
  );
}
