import {NgModule} from '@angular/core';
import {RouterModule, Routes} from '@angular/router';
import {ClientsComponent} from "./clients/clients.component";
import {ClientDetailComponent} from "./clients/client-detail/client-detail.component";
import {BooksComponent} from "./books/books.component";
import {ClientNewComponent} from "./clients/client-new/client-new.component";
import {BookDetailComponent} from "./books/book-detail/book-detail.component";
import {BookNewComponent} from "./books/book-new/book-new.component";


const routes: Routes = [
  // { path: '', redirectTo: '/home', pathMatch: 'full' },
  {path: 'clients', component: ClientsComponent},
  {path: 'client/detail/:id', component: ClientDetailComponent},
  {path: 'client-new', component: ClientNewComponent},

  {path: 'books', component: BooksComponent},
  {path: 'book/detail/:id', component: BookDetailComponent},
  {path: 'book-new', component: BookNewComponent},

];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {
}
