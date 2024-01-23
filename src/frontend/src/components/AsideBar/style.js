import styled from "styled-components";

export const ContainerAside = styled.aside`
  box-shadow: 1px 0px 5px 0px rgba(0, 0, 0, 0.75);
  box-sizing: border-box;
  background-color: #ffffff;
  display: flex;
  flex-wrap: wrap;
  flex-direction: column;
  align-items: flex-start;
  width: 15%;
  position: fixed;
  min-height: 100vh;
  padding: 20px 0;
`;

export const ContainerLogo = styled.div`
  width: 100%;
  display: flex;
  justify-content: center;
  align-items: flex-start;

  img {
    width: 80%;
  }
`;

export const ContainerIconOptions = styled.div`
  width: 100%;
  display: flex;
  cursor: pointer;
  box-sizing: border-box;
  justify-content: space-between;
  padding: 10px 15%;
  border-bottom: 1.5px solid #bababa;
  margin: 10px 0;

  svg {
    border-radius: 50%;
    padding: 5px;
    &:hover {
      background-color: #f2f4f8;
    }
  }
`;

export const NavBar = styled.nav`
  padding: 0 7%;
  box-sizing: border-box;
  width: 100%;
  font-size: 1.3rem;

  a {
    text-decoration: none;
  }

  ul {
    cursor: pointer;
    list-style: none;
    padding: 0;
    margin: 0;

    li {
      display: flex;
      align-items: center;
      padding: 10px 2px;
      border-bottom: 0.1px solid #bababa;

      &:hover {
        background-color: #f2f4f8;
      }

      span {
        margin-left: 20px;
      }
    }
  }
`;
