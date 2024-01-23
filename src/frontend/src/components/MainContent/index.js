import React from "react";
import { MainContentContainer } from "./style";

function MainContent(props) {
  return (
    <MainContentContainer>
      <h1>{props.title}</h1>
      {props.components?.map((item) => {
        return item;
      })}
    </MainContentContainer>
  );
}

export default MainContent;
