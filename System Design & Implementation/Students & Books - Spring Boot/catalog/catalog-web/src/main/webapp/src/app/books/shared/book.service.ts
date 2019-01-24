import {Injectable} from '@angular/core';

import {HttpClient} from "@angular/common/http";

import {Book} from "./book.model";

import {Observable} from "rxjs";
import 'rxjs/add/operator/catch';
import 'rxjs/add/operator/map';


@Injectable()
export class BookService {
  private booksUrl = 'http://localhost:8080/books';

  constructor(private httpBook: HttpClient) {
  }

  getBooks(): Observable<Book[]> {
    return this.httpBook
      .get<Array<Book>>(this.booksUrl);
  }

  getBook(id: number): Observable<Book> {
    return this.getBooks()
      .map(books => books.find(book => book.id === id));
  }

  update(book): Observable<Book> {
    const url = `${this.booksUrl}/${book.id}`;
    return this.httpBook
      .put<Book>(url, book);
  }

  save(title: string, author: string, isbn: string, price: number, quantity: number): Observable<Book> {
    let book = {title, author, isbn, price, quantity};
    return this.httpBook
      .post<Book>(this.booksUrl, book);
  }

  delete(book): Observable<Book> {
    const url = `${this.booksUrl}/${book.id}`;
    return this.httpBook
      .delete<Book>(url);
  }

}
