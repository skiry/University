package ro.ubb.crud.repository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import ro.ubb.crud.model.Person;

import javax.persistence.*;
import java.util.List;

/**
 * author: radu
 */
@Repository
public class PersonRepositoryImpl implements PersonRepository {
    @Autowired
    private EntityManagerFactory entityManagerFactory;

    @Override
    public void save(Person person) {
        EntityManager entityManager =
                entityManagerFactory.createEntityManager();
        EntityTransaction transaction = entityManager.getTransaction();
        transaction.begin();

        entityManager.persist(person);

        transaction.commit();
        entityManager.close();

    }

    @Override
    public List<Person> getPersonsByName(String name) {
        EntityManager entityManager =
                entityManagerFactory.createEntityManager();

        String sql = "select p from Person p where p.name=?1";
        TypedQuery<Person> query = entityManager.createQuery(sql, Person.class);
        query.setParameter(1, name);
        List<Person> persons = query.getResultList();

        entityManager.close();
        return persons;
    }

    @Override
    public Person findById1(Long id) {
        System.out.println("find1===========");
        EntityManager entityManager =
                entityManagerFactory.createEntityManager();

        Person person = entityManager.find(Person.class, id);
        System.out.println("find1-person: ");
        System.out.println(person);

        Person person2 = entityManager.find(Person.class, id);
        System.out.println("find1-person2: ");
        System.out.println(person2);

        entityManager.close();
        return person;
    }

    @Override
    public Person findById2(Long id) {
        System.out.println("find2===========");
        EntityManager entityManager =
                entityManagerFactory.createEntityManager();

        Person person = entityManager.getReference(Person.class, id);
        System.out.println("find2-person: ");
//        System.out.println(person);

        Person person2 = entityManager.getReference(Person.class, id);
        System.out.println("find2-person2: ");
//        System.out.println(person2);

        entityManager.close();
        return person;
    }

    @Override
    public void update(Person person) {
        System.out.println("update============");
        EntityManager entityManager =
                entityManagerFactory.createEntityManager();
        EntityTransaction transaction = entityManager.getTransaction();
        transaction.begin();

        Person updatePerson = entityManager
                .getReference(Person.class, person.getId());

        updatePerson.setName("p2");

        transaction.commit();
        entityManager.close();


    }

    @Override
    public void deleteById(Long id) {
        System.out.println("delete============");
        EntityManager entityManager =
                entityManagerFactory.createEntityManager();
        EntityTransaction transaction = entityManager.getTransaction();
        transaction.begin();

        Person personDelete = entityManager
                .getReference(Person.class, id);
        entityManager.remove(personDelete);

        transaction.commit();
        entityManager.close();
    }

    @Override
    public void merge1(Person person) {
        System.out.println("merge1");
        EntityManager entityManager =
                entityManagerFactory.createEntityManager();
        EntityTransaction transaction = entityManager.getTransaction();
        transaction.begin();

        person.setName("p3");
        entityManager.merge(person);

        transaction.commit();
        entityManager.close();
    }

    @Override
    public void merge2(Person person) {
        System.out.println("merge2");
        EntityManager entityManager =
                entityManagerFactory.createEntityManager();
        EntityTransaction transaction = entityManager.getTransaction();
        transaction.begin();

        entityManager.merge(person);

        transaction.commit();
        entityManager.close();
    }
}
