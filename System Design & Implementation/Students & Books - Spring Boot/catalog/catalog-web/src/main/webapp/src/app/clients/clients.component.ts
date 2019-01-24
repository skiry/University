import {Component} from "@angular/core";
import {Router} from "@angular/router"

@Component({
  moduleId: module.id,
  selector: 'ubb-clients',
  templateUrl: './clients.component.html',
  styleUrls: ['./clients.component.css'],
})
export class ClientsComponent {

  constructor(private router: Router) {

  }

  addClient() {
    console.log("addClient button pressed");
    this.router.navigate(["/client-new"]);
  }

}
