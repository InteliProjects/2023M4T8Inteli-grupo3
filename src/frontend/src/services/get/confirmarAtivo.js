import axios from "axios";
import { API_URL } from "../../constants/api_url";
import Axios from "axios";

axios.defaults.withCredentials = true;

export async function ConfirmarAtivo(SN) {
    const result = await Axios.get(`${API_URL}/confirmar-ativo/${SN}`);
    return result.data;
}