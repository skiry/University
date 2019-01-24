package ro.ubb.catalog.web.converter;

import org.springframework.stereotype.Component;
import ro.ubb.catalog.core.model.Pizza;
import ro.ubb.catalog.web.dto.PizzaDto;

/**
 * author: radu
 */


@Component
public class PizzaConverter extends BaseConverter<Pizza, PizzaDto> {
    @Override
    public Pizza convertDtoToModel(PizzaDto dto) {
        Pizza pizza = new Pizza(dto.getName(), dto.getPrice());
        pizza.setId(dto.getId());
        return pizza;
    }

    @Override
    public PizzaDto convertModelToDto(Pizza pizza) {
        PizzaDto pizzaDto = new PizzaDto(pizza.getName(), pizza.getPrice());
        pizzaDto.setId(pizza.getId());
        return pizzaDto;
    }
}
