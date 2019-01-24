import {Component, OnInit} from '@angular/core';
import {Client} from "../shared/client.model";
import {ClientService} from "../shared/client.service";
import {Router} from "@angular/router";


@Component({
  moduleId: module.id,
  selector: 'ubb-client-list',
  templateUrl: './client-list.component.html',
  styleUrls: ['./client-list.component.css'],
})
export class ClientListComponent implements OnInit {
  errorMessage: string;
  clients: any = [];
  selectedClient: Client;

  constructor(private clientService: ClientService,
              private router: Router) {
  }

  ngOnInit(): void {
    this.getClients();
  }

  getClients() {
    this.clientService.getClients()
      .subscribe(
        clients => this.clients = clients,
        error => this.errorMessage = <any>error
      );
  }

  onSelect(client: Client): void {
    this.selectedClient = client;
  }

  gotoDetail(): void {
    this.router.navigate(['/client/detail', this.selectedClient.id]);
  }

}
