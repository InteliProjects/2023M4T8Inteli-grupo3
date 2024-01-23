import React, { useEffect } from "react";
import { LoadingContainer, RotatingIcon, TabelaStyle } from "./style";
import { Link } from "react-router-dom";
import { IoEye } from "react-icons/io5";

function Tabela({ ativos, setAtivos }) {
  if(!Array.isArray(ativos)) {
    return(
      <h1>Ativos não encontrados</h1>
    )
  }
  return (
    <>
      <TabelaStyle>
        <thead>
          <tr>
            <td>Nome do ativo</td>
            <td>Serial Number</td>
            <td>Localização</td>
            <td>Validade</td>
            <td>Status</td>
            <td>Detalhes</td>
          </tr>
        </thead>
        <tbody>
          {ativos ? (
            ativos.map((item) => {
              return (
                <tr>
                  <td>{item.Description}</td>
                  <td>{item.SN_barCode}</td>
                  <td>{item.cidade}</td>
                  <td>Dezembro de 2026</td>
                  <td>
                    {item.state[0].toUpperCase() + item.state.substring(1)}
                  </td>
                  <td>
                    <Link to={`/ativo/${item.SN_barCode}`}>
                      <IoEye size={20} />
                    </Link>
                  </td>
                </tr>
              );
            })
          ) : (
            <tr>
              <LoadingContainer colSpan="6">
                <RotatingIcon />
              </LoadingContainer>
            </tr>
          )}
        </tbody>
      </TabelaStyle>
    </>
  );
}

export default Tabela;
