export default class ServerHelper {
	getAll() {
	 fetch('http://10.0.2.2:8000/products/all/', {
	         method: 'GET'
	      })
	      .then((response) => response.json())
	      .then((responseJson) => {
	        console.log("PRINTING WHAT I GOT")
	         console.log(responseJson);
	      })
	      .catch((error) => {
	         console.error(error);
	      });
	}

	add(name, price, weight, description) {
		return fetch('http://10.0.2.2:8000/products/add/', {
		  method: 'POST',
		  headers: {
		    Accept: 'application/json',
		    'Content-Type': 'application/json',
		  },
		  body: JSON.stringify({
		    name: name,
		    price: price,
		    weight: weight,
		    description: description
		  }),
		})
		.catch((error) => {
	         console.error(error);
	      });
	}

	update(id, name, price, weight, description) {
		fetch('http://10.0.2.2:8000/products/update/' + id + '/', {
		  method: 'POST',
		  headers: {
		    Accept: 'application/json',
		    'Content-Type': 'application/json',
		  },
		  body: JSON.stringify({
		    name: name,
		    price: price,
		    weight: weight,
		    description: description
		  }),
		})
	      .then((response) => response.text())
	      .then((responseJson) => {
	        console.log("PRINTING WHAT I GOT")
	        console.log(responseJson);
	      })
	      .catch((error) => {
	         console.error(error);
	      });
	}

	delete(id) {
		fetch('http://10.0.2.2:8000/products/delete/' + id + '/', {
		  method: 'POST',
		  headers: {
		    Accept: 'application/json',
		    'Content-Type': 'application/json',
		  },
		})
	      .then((response) => response.text())
	      .then((responseJson) => {
	        console.log("PRINTING WHAT I GOT")
	        console.log(responseJson);
	      })
	      .catch((error) => {
	         console.error(error);
	      });
	}
}