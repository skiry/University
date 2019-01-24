package ro.ubb.catalog.web.controller;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;
import ro.ubb.catalog.core.model.Pizza;
import ro.ubb.catalog.core.service.PizzaService;
import ro.ubb.catalog.web.converter.PizzaConverter;
import ro.ubb.catalog.web.dto.PizzaDto;

import java.util.ArrayList;
import java.util.List;

/**
 * author: radu
 */

@RestController
public class PizzaController {

    private static final Logger log = LoggerFactory.getLogger(
            PizzaController.class);


    @Autowired
    private PizzaService pizzaService;
    @Autowired
    private PizzaConverter pizzaConverter;

    @RequestMapping(value = "/pizzas", method = RequestMethod.GET)
    public List<PizzaDto> getPizzas() {
        log.trace("getPizzas");

        List<Pizza> pizzas = pizzaService.findAll();

        log.trace("getPizzas: pizzas={}", pizzas);

        return new ArrayList<>(pizzaConverter.convertModelsToDtos(pizzas));
    }

}
