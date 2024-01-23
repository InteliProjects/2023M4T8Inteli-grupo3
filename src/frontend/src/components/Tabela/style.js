import styled, { keyframes } from "styled-components";
import { AiOutlineLoading } from "react-icons/ai";

const rotate = keyframes`
  from {
    transform: rotate(0deg);
  }
  to {
    transform: rotate(360deg);
  }
`;

export const RotatingIcon = styled(AiOutlineLoading)`
  animation: ${rotate} 1s linear infinite;
  font-size: 50px;
  color: red;
`;

export const LoadingContainer = styled.td`
  height: 30vh;
`;

export const TabelaStyle = styled.table`
  width: 100%;
  border: 2px solid #fff;
  border-collapse: collapse;
  margin: 20px 0;
  background-color: #e6e6fa;
  text-align: center;

  thead {
    font-weight: 600;
    border: 0;
    text-align: center;

    td {
      padding: 10px;
    }
  }

  tbody {
    background-color: #fff;

    tr {
      &:nth-child(2n) {
        background-color: #f2f4f8;
      }

      td {
        &:last-child {
          text-align: center;
        }
      }
    }
  }

  td {
    padding: 7px;
    border: 1px solid #fff;
  }
`;
