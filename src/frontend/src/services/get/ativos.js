import axios from "axios";
import { API_URL } from "../../constants/api_url";
import Axios from "axios";

axios.defaults.withCredentials = true;

export async function GetAtivos(body) {
  const pesquisa = { [`${body.type}`]: body.value };

  const result = await Axios.post(`${API_URL}/search/1/10`, pesquisa);

  return result.data;
}
