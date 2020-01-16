import React, { Component } from 'react';
import { StyleSheet, FlatList, ActivityIndicator, View, Text } from 'react-native';
import { ListItem, Button } from 'react-native-elements';
import update from 'react-addons-update';
import Database from '../Database';

const db = new Database();

export default class ViewProductsScreen extends Component {
  static navigationOptions = ({ navigation }) => {
  return {
      title: 'Product List',
    };
  };

  constructor() {
    super();
    this.state = {
      isLoading: true,
      products: [],
      notFound: 'No products yet.',
      action: '',
      position: 0,
    };
  }

/*
  componentDidMount() {
    this._subscribe = this.props.navigation.addListener('didFocus', () => {
      this.getProducts();
    });
  }
  */

componentDidMount() {
    this.getProducts();
  }

  getProducts() {
    let products = [];
    db.listProduct().then((data) => {
      products = data;
      this.setState({
        products,
        isLoading: false,
      });
    }).catch((err) => {
      console.log(err);
      this.setState = {
        isLoading: false
      }
    })
  }

  keyExtractor = (item, index) => index.toString()

  renderItem = ({ item, index }) => (
    <ListItem
      title={item.name}
      subtitle={
        <Text>
          Costs ${item.price} and weights {item.weight}g
        </Text>
        }
      onPress={() => {
        this.props.navigation.navigate('UpdateProduct', {
          id: `${item.id}`,
          returnData: this.returnData.bind(this),
          position: index,
        });
      }}
      bottomDivider
    />
  )

  returnData(action, position, id = 0) {
    if (action === "delete") {
      this.state.products.splice(position, 1)
    }
    else if (action === "update") {
      db.productById(id).then((data) => {
        console.log(data);
        this.state.products[position] = data
        this.setState({
          products: this.state.products
        })
      }).catch((err) => {
        console.log(err);
      })
    }
    this.setState({ state: this.state })
  }

  render() {
    console.log("RERENDERED")
    if(this.state.isLoading){
      return(
        <View style={styles.activity}>
          <ActivityIndicator size="large" color="#0000ff"/>
        </View>
      )
    }
    for(let i = 0; i < this.state.products.length; i++) {
          console.log(this.state.products[i].name)
        }
    if(this.state.products.length === 0){
      return(
        <View>
          <Text style={styles.message}>{this.state.notFound}</Text>
        </View>
      )
    }
    return (
      <FlatList
        keyExtractor={this.keyExtractor}
        data={this.state.products}
        renderItem={this.renderItem}
        extraData={this.state}
      />
    );
  }

}

  const styles = StyleSheet.create({
    container: {
     flex: 1,
     paddingBottom: 22
    },
    item: {
      padding: 10,
      fontSize: 18,
      height: 44,
    },
    activity: {
      position: 'absolute',
      left: 0,
      right: 0,
      top: 0,
      bottom: 0,
      alignItems: 'center',
      justifyContent: 'center'
    },
    message: {
      padding: 16,
      fontSize: 18,
      color: 'red'
    }
});