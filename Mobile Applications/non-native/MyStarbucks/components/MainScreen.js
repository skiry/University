import React, { Component } from 'react';
import { Alert, StyleSheet, ScrollView, ActivityIndicator, View, Text, TextInput } from 'react-native';
import { Button } from 'react-native-elements';
import Database from '../Database';
import ServerHelper from '../ServerHelper';

const db = new Database();
const serverHelper = new ServerHelper();

export default class MainScreen extends Component {
  static navigationOptions = {
    title: 'Add a product',
  };

  constructor() {
    super();
    this.state = {
      name: '',
      remoteid: 0,
      price: '',
      weight: '',
      description: '',
      isLoading: false,
      data: ''
    };
  }

  updateTextInput = (text, field) => {
    const state = this.state
    state[field] = text;
    this.setState(state);
  }

  clearInputs = () => {
    let arr = ['name', 'price', 'weight', 'description']
    for (let i = 0; i < arr.length; i++) {
      this.updateTextInput('', arr[i])
    }
  }

  saveProduct() {
    this.setState({
      isLoading: true,
    });
    console.log("O SA ADAUG IN SEVRER IAICI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
    const request = async () => {
      const response = await serverHelper.add(this.state.name,this.state.price,this.state.weight,this.state.description);
      const remoteid = await response.json();
      console.log(remoteid);
    }
    request();
    console.log("REMOTE ID AS VAR IS ");
    console.log(remoteid);
    this.state["remoteid"] = remoteid
    this.setState(state);
    console.log("REMOTE ID ESTE ");
    console.log(this.state.remoteid);
    let data = {
      remoteid: this.state.remoteid,
      name: this.state.name,
      price: this.state.price,
      weight: this.state.weight,
      description: this.state.description
    }
    db.addProduct(data).then((result) => {
      console.log(result);
      Alert.alert("Product added")
      this.setState({
        isLoading: false,
      });
      this.clearInputs()
    }).catch((err) => {
      console.log(err);
      this.setState({
        isLoading: false,
      });
    })
  }

  render() {
    if(this.state.isLoading){
      return(
        <View style={styles.activity}>
          <ActivityIndicator size="large" color="#0000ff"/>
        </View>
      )
    }
    return (
      <ScrollView style={styles.container}>

        <View style={styles.subContainer}>
          <TextInput
              placeholder={'Product Name'}
              value={this.state.name}
              onChangeText={(text) => this.updateTextInput(text, 'name')}
          />
        </View>
       
        <View style={styles.subContainer}>
          <TextInput
              placeholder={'Product Price'}
              value={this.state.price}
              keyboardType='numeric'
              onChangeText={(text) => this.updateTextInput(text, 'price')}
          />
        </View>

        <View style={styles.subContainer}>
          <TextInput
              placeholder={'Product Weight'}
              value={this.state.weight}
              keyboardType='numeric'
              onChangeText={(text) => this.updateTextInput(text, 'weight')}
          />
        </View>

         <View style={styles.subContainer}>
          <TextInput
              multiline={true}
              numberOfLines={4}
              placeholder={'Product Description'}
              value={this.state.description}
              onChangeText={(text) => this.updateTextInput(text, 'description')}
          />
        </View>

        <View style={styles.button}>
          <Button
            large
            leftIcon={{name: 'save'}}
            title='Add product'
            onPress={() => this.saveProduct()} />
        </View>

        <View style={styles.button}>
          <Button
            large
            title='View products'
            onPress={() => this.props.navigation.push('ViewProducts')} />
        </View>

      </ScrollView>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 20
  },
  subContainer: {
    flex: 1,
    marginBottom: 20,
    padding: 5,
    borderBottomWidth: 2,
    borderBottomColor: '#CCCCCC',
  },
  activity: {
    position: 'absolute',
    left: 0,
    right: 0,
    top: 0,
    bottom: 0,
    alignItems: 'center',
    justifyContent: 'center'
  }
})