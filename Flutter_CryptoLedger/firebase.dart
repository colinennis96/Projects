import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';

Future <bool> register(String email, String password) async{
  try{
    await FirebaseAuth.instance
        .createUserWithEmailAndPassword(email: email, password: password);
    return true;
  }on FirebaseAuthException catch(error){
    if(error.code == 'weak-password'){
      print('WEAK PASSWORD!');
    }
    else if(error.code == 'email-already-in-use'){
      print('EMAIL ALREADY REGISTERED!');
    }
    return false;
  }catch(error){
    print(error);
    return false;
  }
}

Future <bool> login(String email, String password) async{
  try{
    await FirebaseAuth.instance
        .signInWithEmailAndPassword(email: email, password: password);
    return true;
  }
  catch(error){
    print(error);
    return false;
  }
}

Future <bool> connect_to_api(String id, String amount) async{
  try{
    String uid = FirebaseAuth.instance.currentUser.uid;
    var _amount = double.parse(amount);
    DocumentReference firebaseID = FirebaseFirestore.instance
        .collection('Users')
        .doc(uid)
        .collection('Coins')
        .doc(id);
    FirebaseFirestore.instance.runTransaction((transaction) async{
      DocumentSnapshot ss = await transaction.get(firebaseID);
      if(!ss.exists){
        firebaseID.set({'Amount': _amount});
        return true;
      }
      double add = ss.data()['Amount'] + _amount;
      transaction.update(firebaseID, {'Amount': add});
      return true;
    });
    return true;
  } catch(error){
    return false;
  }
}

