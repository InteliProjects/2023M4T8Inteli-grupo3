import axios from "axios";
import { API_URL } from "../../constants/api_url";
import Axios from "axios";

axios.defaults.withCredentials = true;

export async function AtualizarLocs(body) {
    const result = await Axios.post(`${API_URL}/atualizar-locs`, body);
    return result.data;
}