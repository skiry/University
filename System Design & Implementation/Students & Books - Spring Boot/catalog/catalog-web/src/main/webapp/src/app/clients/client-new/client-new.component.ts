import {Component, OnInit} from '@angular/core';
import {ClientService} from "../shared/client.service";
import {Location} from "@angular/common"

@Component({
  selector: 'app-client-new',
  templateUrl: './client-new.component.html',
  styleUrls: ['./client-new.component.css']
})
export class ClientNewComponent implements OnInit {

  constructor(private clientService: ClientService,
              private location: Location) {
  }

  ngOnInit() {
  }

  save(firstName, lastName, money) {
    console.log("save button pressed", firstName, lastName, money);

    this.clientService.save(firstName, lastName, money)
      .subscribe(_ => {
          console.debug("client saved");
          this.location.back();
        },
        err => console.error("error saving client", err));
  }

}
