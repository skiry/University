package ro.ubb.catalog.core.service;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ro.ubb.catalog.core.model.Pizza;
import ro.ubb.catalog.core.repository.PizzaRepository;

import java.util.List;

/**
 * author: radu
 */
@Service
public class PizzaServiceImpl implements PizzaService{
    private static final Logger log =
            LoggerFactory.getLogger(  PizzaServiceImpl.class);
    @Autowired
    private PizzaRepository pizzaRepository;


    @Override
    public List<Pizza> findAll() {
        log.trace("findAll --- method entered");

        List<Pizza> pizzas = pizzaRepository.findAll();

        log.trace("findAll: pizzas={}", pizzas);

        return pizzas;
    }
}
