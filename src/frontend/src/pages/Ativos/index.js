import React, { useState } from "react";
import AsideBar from "../../components/AsideBar";
import MainContent from "../../components/MainContent";
import Tabela from "../../components/Tabela";
import { Container } from "./../Homepage/style";
import FilterOptions from "../../components/FilterOptions";

function AtivosTablePage() {
  const [ativos, setAtivos] = useState(null);
  return (
    <Container>
      <AsideBar />
      <MainContent
        title={"Consulta de ativos"}
        components={[
          <FilterOptions ativos={ativos} setAtivos={setAtivos} />,
          <Tabela ativos={ativos} setAtivos={setAtivos} />,
        ]}
      />
    </Container>
  );
}

export default AtivosTablePage;
