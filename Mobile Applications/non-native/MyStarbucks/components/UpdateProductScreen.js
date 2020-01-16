import React, { Component } from 'react';
import { Alert, StyleSheet, ScrollView, ActivityIndicator, View, Text, TextInput } from 'react-native';
import { Button } from 'react-native-elements';
import Database from '../Database';
import ServerHelper from '../ServerHelper';
 
const db = new Database();
const serverHelper = new ServerHelper();

export default class UpdateProductScreen extends Component {
  static navigationOptions = {
    title: 'Update a product',
  };

  constructor() {
    super();
    this.state = {
      id: 0,
      remoteid: 0,
      name: '',
      price: '',
      weight: '',
      description: '',
      isLoading: false,
    };
  }

  updateTextInput = (text, field) => {
    const state = this.state
    state[field] = text;
    this.setState(state);
  }

  componentDidMount() {
    const { navigation } = this.props;
    db.productById(navigation.getParam('id')).then((data) => {
      console.log(data);
      const product = data;
      this.setState({
        id: product.id,
        remoteid: product.remoteid,
        name: product.name,
        price: product.price,
        weight: product.weight,
        description: product.description,
        isLoading: false,
      });
    }).catch((err) => {
      console.log(err);
      this.setState = {
        isLoading: false
      }
    })
  }

  updateProduct() {
    this.setState({
      isLoading: true,
    });
    const { navigation } = this.props;
    serverHelper.update(this.state.id, this.state.name, this.state.price, this.state.weight, this.state.description)
    let data = {
      name: this.state.name,
      price: this.state.price,
      weight: this.state.weight,
      description: this.state.description
    }
    db.updateProduct(this.state.remoteid, data).then((result) => {
      console.log(result);
      console.log("PRIMII CV RESULT")
      Alert.alert("Product updated")
      this.setState({
        isLoading: false,
      });
      console.log("WILL SEND BACK")
      this.props.navigation.state.params.returnData('update', navigation.getParam('position'), navigation.getParam('id'));
      this.props.navigation.goBack();
    }).catch((err) => {
      console.log(err);
      this.setState({
        isLoading: false,
      });
    })
  }

deleteProduct() {
    const { navigation } = this.props;
    this.setState({
      isLoading: true
    });
    serverHelper.delete(this.state.id)
    db.deleteProduct(this.state.id).then((result) => {
      console.log(result);
      this.props.navigation.state.params.returnData('delete', navigation.getParam('position'));
      this.props.navigation.goBack();
    }).catch((err) => {
      console.log(err);
      this.setState = {
        isLoading: false
      }
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
            leftIcon={{name: 'update'}}
            title='Update product'
            onPress={() => this.updateProduct()} />
        </View>

        <View style={styles.button}>
          <Button
            large
            title='Delete product'
            onPress={() => this.deleteProduct()} />
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