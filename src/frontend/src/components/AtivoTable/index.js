import React from "react";
import { TabelaAtivo } from "./style";

function AtivoTable(props) {
  const ativo = props.ativo?.result?.[0];

  return ativo ? (
    <TabelaAtivo>
      <tr>
        <td>Descrição</td>
        <td>{ativo.Description}</td>
      </tr>
      <tr>
        <td>Localização</td>
        <td>{ativo.cidade}</td>
      </tr>
      <tr>
        <td>NE Name</td>
        <td>{ativo.neName}</td>
      </tr>
      <tr>
        <td>NE Address 2</td>
        <td>{ativo.neAddress2}</td>
      </tr>
      <tr>
        <td>Board Full Name</td>
        <td>{ativo.boardFullName}</td>
      </tr>
      <tr>
        <td>Board Name</td>
        <td>{ativo.boardName}</td>
      </tr>
      <tr>
        <td>Board Type</td>
        <td>{ativo.boardType}</td>
      </tr>
      <tr>
        <td>NE Type (MPU TYPE)</td>
        <td>{ativo.neType}</td>
      </tr>
      <tr>
        <td>SN (Bar Code)</td>
        <td>{ativo.SN_barCode}</td>
      </tr>
      <tr>
        <td>PN (BOM Code)</td>
        <td>{ativo.PN_BOMcode}</td>
      </tr>
      <tr>
        <td>List Price (USD)</td>
        <td>{ativo.ListPrice}</td>
      </tr>
      <tr>
        <td>Preço</td>
        <td>{ativo.price}</td>
      </tr>
    </TabelaAtivo>
  ) : (
    <p>Carregando</p>
  );
}

export default AtivoTable;
