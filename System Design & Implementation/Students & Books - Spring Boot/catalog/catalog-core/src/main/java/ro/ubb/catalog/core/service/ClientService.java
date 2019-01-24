package ro.ubb.catalog.core.service;

import ro.ubb.catalog.core.model.Client;

import java.util.List;
import java.util.Optional;

public interface ClientService {
    Optional<Client> findClient(Integer id);

    List<Client> findAll();

    Client updateClient(Integer id, String firstName, String lastName, int money);

    void deleteClient(Integer id);

    Client save(Client client);
}
