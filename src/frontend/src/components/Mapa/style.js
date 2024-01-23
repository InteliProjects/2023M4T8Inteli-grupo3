import styled from "styled-components";

export const ContainerMapa = styled.div`
  width: 100%;
  display: flex;
  align-items: center;
  flex-wrap: wrap;

  div {
    &:focus {
      outline: none;
    }
  }
`;

export const ContainerCaption = styled.div`
  padding: 10px;
  background-color: #d8dcdc;
  box-sizing: border-box;
  width: 100%;
  display: flex;

  span {
    display: flex;
    align-items: center;
    margin-right: 15px;

    p {
      margin: 0;
      margin-left: 5px;
    }
  }
`;
