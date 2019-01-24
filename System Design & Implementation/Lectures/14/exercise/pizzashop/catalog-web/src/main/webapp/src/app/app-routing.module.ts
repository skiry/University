import {NgModule} from '@angular/core';
import {RouterModule, Routes} from '@angular/router';
import {PizzasComponent} from "./pizzas/pizzas.component";
import {PizzaDetailsComponent} from "./pizzas/pizza-details/pizza-details.component";


const routes: Routes = [
  // { path: '', redirectTo: '/home', pathMatch: 'full' },
  {path: 'students', component: PizzasComponent},

  {path: 'pizza/detail/:id', component: PizzaDetailsComponent},



];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {
}
