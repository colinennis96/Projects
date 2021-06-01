import 'firebase.dart';
import 'package:flutter/material.dart';
import 'home.dart';

class fireauth extends StatefulWidget{
  fireauth({Key key}) : super(key: key);
  @override
  fireauthState createState() => fireauthState();
}

class fireauthState extends State <fireauth>{
  TextEditingController email = TextEditingController();
  TextEditingController password = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        width: MediaQuery.of(context).size.width,
        height: MediaQuery.of(context).size.height,
        decoration: BoxDecoration(
          color: Colors.blueGrey,
        ),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Container(
              width: MediaQuery.of(context).size.width/1.2,
              child: TextFormField(
                style: TextStyle(color: Colors.black),
                controller: email,
                decoration: InputDecoration(
                  labelText: "Email",
                  labelStyle: TextStyle(
                    color: Colors.lightGreen,
                  ),
                ),
              ),
            ),
            SizedBox(height: MediaQuery.of(context).size.height/40),
            Container(
              width: MediaQuery.of(context).size.width/1.2,
              child: TextFormField(
                style: TextStyle(color: Colors.black),
                controller: password,
                obscureText: true,
                decoration: InputDecoration(
                  labelText: "Password",
                  labelStyle: TextStyle(
                    color: Colors.lightGreen,
                  ),
                ),
              ),
            ),
            SizedBox(height: MediaQuery.of(context).size.height/40),
            Container(
              width: MediaQuery.of(context).size.width/1.5,
              height: 42,
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(15.0),
                color: Colors.white,
              ),
              child: MaterialButton(
                onPressed: () async{
                  bool success = await register(email.text, password.text);
                  if(success){
                    Navigator.push(
                      context,
                      MaterialPageRoute(builder: (context) => Landing(),),
                    );
                  }
                },
                child: Text("Register"),
              ),
            ),
            SizedBox(height: MediaQuery.of(context).size.height/40),
            Container(
              width: MediaQuery.of(context).size.width/1.5,
              height: 42,
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(15.0),
                color: Colors.white,
              ),
              child: MaterialButton(
                  onPressed: () async{
                    bool success = await login(email.text, password.text);
                    if(success){
                      Navigator.push(
                        context,
                        MaterialPageRoute(builder: (context) => Landing(),),
                      );
                    }
                  },
                  child: Text("Login")),
            ),
          ],
        ),
      ),
    );
  }
}