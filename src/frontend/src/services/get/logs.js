import axios from "axios";
import { API_URL } from "../../constants/api_url";
import Axios from "axios";

axios.defaults.withCredentials = true;

export async function getLogs(sn){
    const result = await Axios.get(`${API_URL}/logs/${sn}`);
    return result.data;
}