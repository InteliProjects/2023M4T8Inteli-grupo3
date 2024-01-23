import React, { useState, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import {
  FormButton,
  FormContainer,
  FormTitle,
  InputForm,
  PageContainer,
} from "./style";
import { Logar } from "./../../services/post/logar";

function LoginPage() {
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [response, setResponse] = useState(null);
  const history = useNavigate();

  async function handleSubmit(event) {
    event.preventDefault();

    try{
      await Logar(username, password).then((response) => {
        setResponse(response);

        history("/home");
      });
    }catch(error){
      console.log(error);
    }
    
  }
  return (
    <PageContainer>
      <FormContainer onSubmit={handleSubmit}>
        <FormTitle>Login</FormTitle>
        <InputForm
          onChange={(event) => setUsername(event.target.value)}
          placeholder="Username"
        />
        <InputForm
          onChange={(event) => setPassword(event.target.value)}
          type="password"
          placeholder="Senha"
        />
        <FormButton type="submit">Enviar</FormButton>
      </FormContainer>
    </PageContainer>
  );
}

export default LoginPage;
