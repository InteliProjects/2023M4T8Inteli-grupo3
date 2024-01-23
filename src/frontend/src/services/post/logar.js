import axios from "axios";
import { API_URL } from "../../constants/api_url";
import Axios from "axios";

axios.defaults.withCredentials = true;

export async function Logar(username, password) {
  const body = { username, password };

  await Axios.post(`${API_URL}/login`, body).then((response) => {
    console.log(response);
    console.log(response.headers);
    return response;
  });
}
