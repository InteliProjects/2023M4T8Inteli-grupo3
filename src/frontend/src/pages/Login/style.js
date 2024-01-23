import styled from "styled-components";

export const PageContainer = styled.div`
  width: 100%;
  height: 100vh;
  background-color: #3c0064;
  display: flex;
  justify-content: center;
  align-items: center;
`;

export const FormContainer = styled.form`
  width: 40%;
  height: 70%;
  border: 2px solid #fff;
  background-color: rgba(255, 255, 255, 0.1);
  border-radius: 10px;
  display: flex;
  justify-content: center;
  //align-content: start;
  align-items: center;
  flex-wrap: wrap;
  box-sizing: border-box;
`;

export const InputForm = styled.input`
  background-color: #fff;
  width: 100%;
  margin: 0 15%;
  border: 1px solid #fff;
  height: 30px;
  padding-left: 20px;
  border-radius: 5px;

  &:focus {
    outline: none;
  }
`;

export const FormTitle = styled.h1`
  color: #fff;
  width: 100%;
  text-align: center;
`;

export const FormButton = styled.button`
  color: #3c0064;
  background-color: #fff;
  border-radius: 5%;
  padding: 10px 40px;
  border: 0;
  font-weight: 600;
  cursor: pointer;

  &:hover {
    background-color: #3c0064;
    color: #fff;
  }
`;
