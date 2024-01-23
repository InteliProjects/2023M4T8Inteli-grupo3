import axios from "axios";
import { API_URL } from "../../constants/api_url";
import Axios from "axios";

axios.defaults.withCredentials = true;

export async function GetQrCode(GPS_ID){
    const result = await Axios.get(`${API_URL}/gps/${GPS_ID}`);
    return result.data;
}