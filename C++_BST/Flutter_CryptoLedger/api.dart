import 'package:http/http.dart' as http;
import 'dart:convert';

Future <double> coin_data(String id) async{
    var api_link = "https://api.coingecko.com/api/v3/coins/" + id;
    var body = await http.get(api_link);
    var data = jsonDecode(body.body);
    var coin = data['market_data']['current_price']['usd'].toString();
    return double.parse(coin);
}