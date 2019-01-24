package ro.ubb.relations;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import ro.ubb.relations.model.Book;
import ro.ubb.relations.model.Publisher;
import ro.ubb.relations.repository.PublisherRepository;

import java.util.Arrays;

/**
 * Created by radu.
 */
public class Main {
    public static void main(String[] args) {

        AnnotationConfigApplicationContext context =
                new AnnotationConfigApplicationContext(
                        "ro.ubb.relations.config");

        PublisherRepository publisherRepository = context.getBean(
                PublisherRepository.class);


        Publisher publisher = Publisher.builder()
                                       .name("manning")
                                       .build();
        Book book1 = Book.builder()
                         .author("martin")
                         .title("got")
                         .publisher(publisher)
                         .build();
        Book book2 = Book.builder()
                         .author("dostoevsky")
                         .title("c&p")
                         .publisher(publisher)
                         .build();
        publisher.setBooks(Arrays.asList(book1, book2));

        publisherRepository.save(publisher);

        System.out.println("hello");
    }
}
