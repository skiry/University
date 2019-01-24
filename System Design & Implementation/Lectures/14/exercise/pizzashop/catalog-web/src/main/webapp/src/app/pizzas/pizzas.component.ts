import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-pizzas',
  templateUrl: './pizzas.component.html',
  styleUrls: ['./pizzas.component.css']
})
export class PizzasComponent implements OnInit {

  shouldShow: boolean;

  constructor() { }

  ngOnInit() {
  }

  private showPizzas(){
    this.shouldShow = true;
  }
}
