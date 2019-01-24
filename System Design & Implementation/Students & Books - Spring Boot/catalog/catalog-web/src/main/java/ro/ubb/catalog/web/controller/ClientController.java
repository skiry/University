package ro.ubb.catalog.web.controller;

import ro.ubb.catalog.core.model.Client;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ro.ubb.catalog.web.converter.ClientConverter;
import ro.ubb.catalog.web.dto.ClientDto;
import ro.ubb.catalog.web.dto.Clients;
import ro.ubb.catalog.web.service.MonolithicService;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@RestController
public class ClientController {
    @Autowired
    private MonolithicService monolithicService;

    @Autowired
    private ClientConverter converter;

    @RequestMapping(value = "/clients", method = RequestMethod.GET)
    List<ClientDto> getAllClients() {
        monolithicService.inject();
        List<Client> clients = monolithicService.getClients();
        return new ArrayList<>(converter.convertModelsToDtos(clients));
    }

    @RequestMapping(value = "/clients", method = RequestMethod.POST)
    Boolean addClient(@RequestBody ClientDto data) {
        monolithicService.inject();
        Client client = converter.convertDtoToModel(data);
        Optional<Client> prevEntity = monolithicService.addClient(client);
        return prevEntity.isPresent();
    }

    @RequestMapping(value = "/clients/{clientId}", method = RequestMethod.PUT)
    Boolean updateClient(@PathVariable final Integer clientId,
                         @RequestBody ClientDto data) {
        monolithicService.inject();
        monolithicService.updateClient(clientId, data.getFirstName(), data.getLastName(), data.getMoney());
        return true;
    }

    @RequestMapping(value = "/clients/{id}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteClient(@PathVariable Integer id) {
        monolithicService.inject();
        monolithicService.deleteClient(id);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @RequestMapping(value = "/clients/no-funds", method = RequestMethod.GET)
    Clients getClientsWithoutFunds() {
        monolithicService.inject();
        Iterable<Client> clients = monolithicService.clientsWithoutFunds();
        return new Clients(
                StreamSupport
                        .stream(clients.spliterator(), false)
                        .map(converter::convertModelToDto)
                        .collect(Collectors.toList()));
    }

    @RequestMapping(value = "/clients/by-name", method = RequestMethod.GET)
    Clients getClientsByName() {
        monolithicService.inject();
        Iterable<Client> clients = monolithicService.sortClientsByName();
        return new Clients(
                StreamSupport
                        .stream(clients.spliterator(), false)
                        .map(converter::convertModelToDto)
                        .collect(Collectors.toList()));
    }
}
