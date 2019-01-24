package ro.ubb.crud;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import ro.ubb.crud.model.Person;
import ro.ubb.crud.repository.PersonRepository;

/**
 * Created by radu.
 */
public class Main {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context =
                new AnnotationConfigApplicationContext("ro.ubb.crud.config");

        PersonRepository personRepository = context.getBean(
                PersonRepository.class);


        System.out.println("hello");
    }
}
