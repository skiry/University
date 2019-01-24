package ro.ubb.catalog.web.converter;

import ro.ubb.catalog.core.model.Client;
import org.springframework.stereotype.Component;
import ro.ubb.catalog.web.dto.ClientDto;

@Component
public class ClientConverter extends BaseConverter<Client, ClientDto> {
    @Override
    public Client convertDtoToModel(ClientDto dto) {
        Client client = Client.builder()
                .firstName(dto.getFirstName())
                .lastName(dto.getLastName())
                .money(dto.getMoney())
                .build();
        client.setId(dto.getId());

        return client;
    }

    @Override
    public ClientDto convertModelToDto(Client model) {
        ClientDto dto = ClientDto.builder()
                .firstName(model.getFirstName())
                .lastName(model.getLastName())
                .money(model.getMoney())
                .build();
        dto.setId(model.getId());

        return dto;
    }
}
