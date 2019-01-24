import {Component, OnInit} from '@angular/core';
import {PizzaService} from "../shared/pizza.service";
import {ActivatedRoute, Params} from "@angular/router";
import {Pizza} from "../shared/pizza.model";
import {switchMap} from "rxjs/operators";

@Component({
  selector: 'app-pizza-details',
  templateUrl: './pizza-details.component.html',
  styleUrls: ['./pizza-details.component.css']
})
export class PizzaDetailsComponent implements OnInit {
  pizza: Pizza = <Pizza>{};

  constructor(private pizzaService: PizzaService,
              private route: ActivatedRoute
  ) {
  }

  ngOnInit() {
    // this.route.params
    //   .switchMap((params: Params) =>
    //     this.pizzaService.getPizza(+params['id']))
    //   .subscribe(pizza => this.pizza = pizza);

    this.route.params
      .pipe(switchMap((params: Params) =>
        this.pizzaService.getPizza(+params['id'])))
      .subscribe(pizza => this.pizza = pizza);
  }


}
