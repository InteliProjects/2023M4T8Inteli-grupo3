import React from "react";
import { Container } from "./style";
import Mapa from "../../components/Mapa";
import AsideBar from "../../components/AsideBar";
import MainContent from "../../components/MainContent";
import ContadorAtivos from "../../components/ContadorAtivos";

function Homepage() {
  return (
    <>
      <Container>
        <AsideBar />
        <MainContent
          title="Distribuição de ativos"
          components={[
            <ContadorAtivos />,
            <Mapa width={"100%"} caption={true} />,
          ]}
        />
      </Container>
    </>
  );
}

export default Homepage;
