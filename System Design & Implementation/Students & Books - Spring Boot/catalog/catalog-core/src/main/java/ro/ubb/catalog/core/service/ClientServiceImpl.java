package ro.ubb.catalog.core.service;

import ro.ubb.catalog.core.model.Client;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.transaction.annotation.Transactional;
import ro.ubb.catalog.core.repository.catalog.ClientCatalog;

import java.util.List;
import java.util.Optional;

public class ClientServiceImpl implements ClientService {
    public static final Logger log = LoggerFactory.getLogger(ClientServiceImpl.class);

    @Autowired
    private ClientCatalog clientCatalog;

    @Override
    public Optional<Client> findClient(Integer id) {
        log.trace("findStudent: clientId={}", id);

        Optional<Client> clientOptional = clientCatalog.findById(id);

        log.trace("findStudent: clientOptional={}", clientOptional);

        return clientOptional;
    }

    @Override
    public List<Client> findAll() {
        log.trace("findAll --- method entered");

        List<Client> clients = clientCatalog.findAll();

        log.trace("findAll: clients={}", clients);

        return clients;
    }

    @Override
    @Transactional
    public Client updateClient(Integer id, String firstName, String lastName, int money) {
        log.trace("updateClient: firstName={}, lastName={}, money={}",
                firstName, lastName, money);

        Client newClient = clientCatalog.findById(id).get();
        newClient.setFirstName(firstName);
        newClient.setLastName(lastName);
        newClient.setMoney(money);

        return newClient;
    }

    @Override
    public void deleteClient(Integer id) {
        log.trace("deleteClient: id={}", id);

        clientCatalog.delete(clientCatalog.findById(id).get());
    }

    @Override
    public Client save(Client client) {
        return this.clientCatalog.save(client);
    }
}
