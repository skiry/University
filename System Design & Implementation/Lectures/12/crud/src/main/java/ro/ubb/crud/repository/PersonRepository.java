package ro.ubb.crud.repository;

import ro.ubb.crud.model.Person;

import java.util.List;

/**
 * Created by radu.
 */
public interface PersonRepository {

    void save(Person person);

    List<Person> getPersonsByName(String name);

    Person findById1(Long id);

    Person findById2(Long id);

    void update(Person person);

    void deleteById(Long id);

    void merge1(Person person);

    void merge2(Person person);
}
