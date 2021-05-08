import 'api.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'fireauth.dart';
import 'functions.dart';
import 'package:cloud_firestore/cloud_firestore.dart';

class Landing extends StatefulWidget{
  Landing({Key key}) : super(key: key);
  @override
  LandingState createState() => LandingState();
}

class LandingState extends State <Landing>{
  double bitcoin = 0.0;
  double ethereum = 0.0;
  double tether = 0.0;
  double binancecoin = 0.0;
  double dogecoin = 0.0;
  @override
  initState(){
    LoadCoinData();
  }

  LoadCoinData() async{
    bitcoin = await coin_data("bitcoin");
    ethereum = await coin_data("ethereum");
    tether = await coin_data("tether");
    binancecoin = await coin_data("binancecoin");
    dogecoin = await coin_data("dogecoin");
    setState(() {});
  }

  @override
  Widget build(BuildContext context){
    GetCoinData(String id, double price){
      if(id == "bitcoin"){
        return(bitcoin * price).toStringAsFixed(2);
      }
      if(id == "ethereum"){
        return(ethereum * price).toStringAsFixed(2);
      }
      if(id == "tether"){
        return(tether * price).toStringAsFixed(2);
      }
      if(id == "binancecoin"){
        return(binancecoin * price).toStringAsFixed(2);
      }
      if(id == "dogecoin"){
        return(dogecoin * price).toStringAsFixed(2);
      }
    }

    return Scaffold(
      body: Container(
        decoration: BoxDecoration(
          color: Colors.blueGrey,
        ),
        height: MediaQuery.of(context).size.height,
        width: MediaQuery.of(context).size.width,
        child: Center(
          child: StreamBuilder(
              stream: FirebaseFirestore.instance
                  .collection('Users')
                  .doc(FirebaseAuth.instance.currentUser.uid)
                  .collection('Coins')
                  .snapshots(),
              builder: (BuildContext context, AsyncSnapshot<QuerySnapshot> snapshot){
                return ListView(
                  children: snapshot.data.docs.map((document){
                    return Padding(
                       padding: EdgeInsets.only(
                         top: 7,
                         left: 17,
                         right: 17,
                       ),
                        child: Container(
                          height: MediaQuery.of(context).size.height/16,
                        decoration: BoxDecoration(
                          borderRadius: BorderRadius.circular(7.0),
                          color: Colors.pink[50],
                        ),
                        child: Row(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: [
                            Text("  ${document.id}"),
                            Text("Value(USD): ${GetCoinData(document.id, document.data()['Amount'])}  "),
                            ],
                         )
                        )
                    );
                  }).toList(),
                );
              }),
        ),
      ),
      floatingActionButtonLocation: FloatingActionButtonLocation.centerFloat,
      floatingActionButton: Container(
        padding: EdgeInsets.symmetric(vertical: 0, horizontal: 10.0),
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: <Widget>[
            FloatingActionButton(
              heroTag: null,
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => fireauth(),),
                );
              },
              backgroundColor: Colors.redAccent,
              child: Icon(
                Icons.fast_rewind_outlined,
                color: Colors.black,
              ),
            ),
            FloatingActionButton(
              heroTag: null,
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => CoinFunctions(),),
                );
              },
              backgroundColor: Colors.black87,
              child: Icon(
                Icons.attach_money_rounded,
                color: Colors.lightGreenAccent,
              ),
            ),
          ],
        ),
      ),
    );
  }
}