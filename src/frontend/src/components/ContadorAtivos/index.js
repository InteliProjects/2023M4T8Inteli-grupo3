import React from "react";
import { CounterCard, CounterContainer } from "./style";

function ContadorAtivos() {
  const contadores = [
    { label: "Total de ativos", value: "11.840" },
    { label: "Ativos instalados", value: "11.340" },
    { label: "Ativos em estoque", value: "500" },
    { label: "Ativo em manutenção", value: "0" },
  ];

  return (
    <CounterContainer>
      {contadores.map((item, index) => {
        return (
          <CounterCard key={index}>
            <p>{item.label}</p>
            <span>{item.value}</span>
          </CounterCard>
        );
      })}
    </CounterContainer>
  );
}

export default ContadorAtivos;
