import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'fireauth.dart';

void main() async{
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(App());
}

class App extends StatelessWidget{
  @override
  Widget build(BuildContext context){
    return MaterialApp(
      title: 'Koin',
      home: fireauth(),
    );
  }
}