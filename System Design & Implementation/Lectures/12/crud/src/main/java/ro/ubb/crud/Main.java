package ro.ubb.crud;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import ro.ubb.crud.model.Person;
import ro.ubb.crud.repository.PersonRepository;

import java.util.List;

/**
 * Created by radu.
 */
public class Main {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context =
                new AnnotationConfigApplicationContext("ro.ubb.crud.config");

        PersonRepository personRepository = context.getBean(
                PersonRepository.class);

        Person person = Person.builder().name("p1").build();
        personRepository.save(person);
        personRepository.save(Person.builder().name("p1").build());

        List<Person> persons = personRepository.getPersonsByName("p1");
        System.out.println("persons by name: " + persons);

        Person personFind1 = personRepository.findById1(persons.get(0).getId());
        System.out.println("main-find1-person: " + personFind1);

//        Person personFind2 = personRepository.findById2(persons.get(0)
//        .getId());
//        System.out.println("main-find2-person: " + personFind2);

        personRepository.update(persons.get(0));
        List<Person> updated = personRepository.getPersonsByName("p2");
        System.out.println("updated: " + updated);

        personRepository.deleteById(persons.get(0).getId());
        List<Person> deleted = personRepository.getPersonsByName("p2");
        System.out.println("deleted: " + deleted);

        List<Person> personsP1 = personRepository.getPersonsByName("p1");
        personRepository.merge1(personsP1.get(0));

//        List<Person> personsP1 = personRepository.getPersonsByName("p1");
        personRepository.merge2(Person.builder().name("p4").build());

        System.out.println("hello");
    }
}
