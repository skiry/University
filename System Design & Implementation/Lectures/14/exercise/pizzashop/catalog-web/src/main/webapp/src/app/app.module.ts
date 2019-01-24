import {BrowserModule} from '@angular/platform-browser';
import {NgModule} from '@angular/core';
import {HttpClientModule} from '@angular/common/http';
import {FormsModule} from '@angular/forms';

import {AppComponent} from './app.component';
import {AppRoutingModule} from "./app-routing.module";
import { PizzasComponent } from './pizzas/pizzas.component';
import {PizzaListComponent} from "./pizzas/pizza-list/pizza-list.component";
import {PizzaService} from "./pizzas/shared/pizza.service";
import { PizzaDetailsComponent } from './pizzas/pizza-details/pizza-details.component';


@NgModule({
  declarations: [
    AppComponent,
    PizzasComponent,
    PizzaListComponent,
    PizzaDetailsComponent,



  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpClientModule,
    AppRoutingModule,
  ],
  providers: [PizzaService],
  bootstrap: [AppComponent]
})
export class AppModule {
}
