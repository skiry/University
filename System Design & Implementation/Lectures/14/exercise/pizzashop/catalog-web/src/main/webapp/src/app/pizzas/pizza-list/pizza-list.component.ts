import {Component, OnInit} from '@angular/core';
import {PizzaService} from "../shared/pizza.service";
import {Pizza} from "../shared/pizza.model";
import {Router} from "@angular/router";

@Component({
  selector: 'app-pizza-list',
  templateUrl: './pizza-list.component.html',
  styleUrls: ['./pizza-list.component.css']
})
export class PizzaListComponent implements OnInit {

  pizzaList: Pizza[];
  details: boolean;
  selectedPizza: Pizza;

  constructor(private pizzaService: PizzaService,
              private router: Router
              ) {
  }

  ngOnInit() {

    this.pizzaService.getPizzas()
      .subscribe(pizza => this.pizzaList = pizza);

  }

  showDetails(pizza: Pizza) {
    this.selectedPizza = pizza;
    this.details = true;

    this.router.navigate(['/pizza/detail', this.selectedPizza.id]);
  }


}
