import {BrowserModule} from '@angular/platform-browser';
import {NgModule} from '@angular/core';
import {HttpClientModule} from '@angular/common/http';
import {FormsModule} from '@angular/forms';

import {AppComponent} from './app.component';
import {AppRoutingModule} from "./app-routing.module";
import {ClientDetailComponent} from "./clients/client-detail/client-detail.component";
import {ClientsComponent} from "./clients/clients.component";
import {ClientListComponent} from "./clients/client-list/client-list.component";
import {ClientService} from "./clients/shared/client.service";
import {BooksComponent} from './books/books.component';
import {BookListComponent} from "./books/book-list/book-list.component";
import {BookService} from "./books/shared/book.service";
import { ClientNewComponent } from './clients/client-new/client-new.component';
import {BookNewComponent} from "./books/book-new/book-new.component";
import {BookDetailComponent} from "./books/book-detail/book-detail.component";


@NgModule({
  declarations: [
    AppComponent,
    ClientDetailComponent,
    ClientsComponent,
    ClientListComponent,

    BooksComponent,
    BookListComponent,
    ClientNewComponent,
    BookNewComponent,
    BookDetailComponent


  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpClientModule,
    AppRoutingModule,
  ],
  providers: [ClientService, BookService],
  bootstrap: [AppComponent]
})
export class AppModule {
}
