import axios from "axios";
import { API_URL } from "../../constants/api_url";
import Axios from "axios";

axios.defaults.withCredentials = true;

export async function GetAtivoBySerialNumber(id) {
  const result = await Axios.get(`${API_URL}/ativo/${id}`);

  return result.data;
}
