import {Injectable} from '@angular/core';

import {HttpClient} from "@angular/common/http";

import {Client} from "./client.model";

import {Observable} from "rxjs";

@Injectable()
export class ClientService {
  private clientsUrl = 'http://localhost:8080/clients';

  constructor(private httpClient: HttpClient) {
  }

  getClients(): Observable<Client[]> {
    return this.httpClient
      .get<Array<Client>>(this.clientsUrl);
  }

  getClient(id: number): Observable<Client> {
    return this.getClients()
      .map(clients => clients.find(client => client.id === id));
  }

  update(client): Observable<Client> {
    const url = `${this.clientsUrl}/${client.id}`;
    return this.httpClient
      .put<Client>(url, client);
  }

  save(firstName: string, lastName: string, money: number): Observable<Client> {
    let client = {firstName, lastName, money};
    return this.httpClient
      .post<Client>(this.clientsUrl, client);
  }

  delete(client): Observable<Client> {
    const url = `${this.clientsUrl}/${client.id}`;
    return this.httpClient
      .delete<Client>(url);
  }

}
