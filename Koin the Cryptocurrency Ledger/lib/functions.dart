import 'firebase.dart';
import 'package:flutter/material.dart';

class CoinFunctions extends StatefulWidget{
  CoinFunctions({Key key}) : super(key: key);
  @override
  CoinFunctionsState createState() => CoinFunctionsState();
}

class CoinFunctionsState extends State <CoinFunctions>{
  List <String> coins =[
    "bitcoin",
    "tether",
    "ethereum",
    "binancecoin",
    "dogecoin",
  ];

  String ddv = "bitcoin";
  TextEditingController ac = TextEditingController();
  @override
  Widget build(BuildContext context) {
    return Material(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: [
          DropdownButton(
            value: ddv,
            onChanged: (String value) {
              setState((){
                ddv = value;
              });
            },
            items: coins.map<DropdownMenuItem<String>>((String value){
              return DropdownMenuItem<String>(
                value: value,
                child: Text(value),
              );
            }).toList(),
          ),
          Container(
            width: MediaQuery.of(context).size.width/1.4,
            child: TextFormField(
              controller: ac,
              decoration: InputDecoration(
                labelText: "Amount",
              ),
            ),
          ),
          Container(
            width: MediaQuery.of(context).size.width/1.8,
            height: 40,
            decoration: BoxDecoration(
              borderRadius: BorderRadius.circular(11.0),
              color: Colors.blueGrey,
            ),
            child: MaterialButton(
              onPressed: () async{
                await connect_to_api(ddv, ac.text);
                Navigator.of(context).pop();
              },
              child: Text("Submit/Cancel"),
            ),
          ),
        ],
      ),
    );
  }
}