import React, {useState, useEffect} from "react";
import Mapa from "./../Mapa";
import { LogContainer } from "./style";
import {getLogs} from "../../services/get/logs";

function TrackerLog(sn) {
  const [log, setLog] = useState(null);

  console.log(sn);

  useEffect(() => {
    (async () => {
      await getLogs(sn).then((response) => {
        console.log(response);
        setLog(response);
      });
    })();
  }, []);

  return (
    <LogContainer>
      <h2>Histórico de localização</h2>
      <Mapa width={"100%"} caption={true} />,
    </LogContainer>
  );
}

export default TrackerLog;
