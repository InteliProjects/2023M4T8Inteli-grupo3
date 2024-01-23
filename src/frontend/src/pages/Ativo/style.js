import styled from "styled-components";

export const LeftContainerContent = styled.div`
  width: 50%;
`;

export const QrCodeContainer = styled.div`
  display: flex;
  width: 100%;
  height: 100px;
  border: 1px solid #f8f8ff;
  margin-bottom: 10px;
  cursor: pointer;

  &:hover {
    background-color: #4d007e;
  }
`;

export const QrCodeInfo = styled.p`
  color: #f8f8ff;
  margin: auto 5%;
  text-align: center;
`;

export const QrCode = styled.img`
  height: 100%;
`;
