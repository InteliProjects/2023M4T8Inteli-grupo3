import styled from "styled-components";

export const TabelaAtivo = styled.table`
  width: 45%;
  border: 1px solid #fff;
  border-collapse: collapse;

  tr {
    td {
      &:first-child {
        font-weight: 600;
      }
    }
  }

  td {
    color: #f8f8ff;
    padding: 7px;
    border: 1px solid #fff;
  }
`;
