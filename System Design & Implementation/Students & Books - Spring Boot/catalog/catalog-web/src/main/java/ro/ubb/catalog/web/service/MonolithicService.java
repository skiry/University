package ro.ubb.catalog.web.service;

import ro.ubb.catalog.core.model.Book;
import ro.ubb.catalog.core.model.Client;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ro.ubb.catalog.core.repository.DbRepository;
import ro.ubb.catalog.core.repository.catalog.BookCatalog;
import ro.ubb.catalog.core.repository.catalog.ClientCatalog;
import ro.ubb.catalog.core.serializer.csv.BookSerializer;
import ro.ubb.catalog.core.serializer.csv.ClientSerializer;
import ro.ubb.catalog.core.serializer.csv.CsvSerializer;
import ro.ubb.catalog.core.validator.BookValidator;
import ro.ubb.catalog.core.validator.ClientValidator;

import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Service
public class MonolithicService {
    private DbRepository<Integer, Client> clientRepo;
    private DbRepository<Integer, Book> bookRepo;

    private final CsvSerializer<Integer, Client> clientSerializer = new ClientSerializer();
    private final CsvSerializer<Integer, Book> bookSerializer = new BookSerializer();

    private final Logger logger = LoggerFactory.getLogger( MonolithicService.class );

    private Boolean wasInjected = false;
    @Autowired
    private BookCatalog bookCatalog;
    @Autowired
    private ClientCatalog clientCatalog;

    public void inject() {
        if ( wasInjected ) {
            return;
        }

        wasInjected = true;
        logger.debug( "Trying to create the generic repositories..." );
        clientRepo = new DbRepository<>( clientCatalog, new ClientValidator() );
        bookRepo   = new DbRepository<>( bookCatalog, new BookValidator() );
        logger.debug( "Created the generic repositories successfully." );
    }

    public Optional<Client> addClient( Client client ) {
        logger.debug( "Adding client --" + client + "--" );
        Optional<Client> result = clientRepo.insert( client );
        logger.debug( "Result: " + result.toString() );
        return result;
    }

    public Optional<Client> updateClient( Integer id, String fName, String lName, int money ) {
        logger.debug( "Updating client --" + id + "--" );

        Optional<Client> result = clientRepo.findOne( id );
        result.ifPresent(c -> {
            c.setFirstName(fName);
            c.setLastName(lName);
            c.setMoney(money);
        });
        clientRepo.update(result.get());
        logger.debug( "Result: " + result.toString() );
        return result;
    }

    public Optional<Client> deleteClient( Integer id ) {
        logger.debug( "Deleting client by id: " + id );
        Optional<Client> result = clientRepo.delete( id );
        logger.debug( "Result: " + result.toString() );
        return result;
    }

    public List<Client> getClients() {
        logger.debug( "Trying to find all clients..." );
        List<Client> result = clientRepo.findAll();
        logger.debug( "Result: " + result.toString() );
        return result;
    }

    public Optional<Book> addBook( Book book ) {
        logger.debug( "Trying to add book: --" + book + "--" );
        Optional<Book> result = bookRepo.insert( book );
        logger.debug( "Result: " + result.toString() );
        return result;
    }

    public Optional<Book> updateBook( Integer id, String title, String author, String isbn,
                                      Integer price, Integer quantity) {
        logger.debug( "Updating book --" + id + "--" );

        Optional<Book> result = bookRepo.findOne( id );
        result.ifPresent(c -> {
            c.setTitle(title);
            c.setAuthor(author);
            c.setIsbn(isbn);
            c.setPrice(price);
            c.setQuantity(quantity);
        });
        bookRepo.update(result.get());
        logger.debug( "Result: " + result.toString() );
        return result;
    }

    public Optional<Book> deleteBook( Integer id ) {
        logger.debug( "Trying to delete book by: " + id );
        Optional<Book> result = bookRepo.delete( id );
        logger.debug( "Result: " + result.toString() );
        return result;
    }

    public List<Book> getBooks() {
        logger.debug( "Trying to get all books..." );
        List<Book> result = bookRepo.findAll();
        logger.debug( "Result: " + result );
        return result;
    }

    public Iterable<Book> mostExpensiveBooks( Integer nr ) {
        logger.debug( "Trying to get " + nr + " most expensive books..." );

        if ( nr < 0 ) {
            throw new RuntimeException( "Negative number given when positive was expected." );
        }

        Iterable<Book> result = StreamSupport
            .stream( bookRepo.findAll().spliterator(), false )
            .sorted( ( e1, e2 ) -> Integer.compare( e2.getPrice(), e1.getPrice() ) )
            .limit( nr )
            .collect( Collectors.toList() );
        logger.debug( "Result: " + result );
        return result;
    }

    public Iterable<Book> sortBooksByQuantity() {
        logger.debug( "Trying to get all books sorted by quantity..." );
        Iterable<Book> result = StreamSupport
            .stream( getBooks().spliterator(), false )
            .sorted( Comparator.comparing( Book::getQuantity ) )
            .collect( Collectors.toList() );
        logger.debug( "Result: " + result );
        return result;
    }

    public Iterable<Client> sortClientsByName() {
        logger.debug( "Trying to get all clients sorted by name..." );
        Iterable<Client> result = StreamSupport
            .stream( getClients().spliterator(), false )
            .sorted( Comparator.comparing( Client::getFirstName ) )
            .collect( Collectors.toList() );
        logger.debug( "Result: " + result );
        return result;
    }

    public Iterable<Client> clientsWithoutFunds() {
        logger.debug( "Trying to get all clients with 0 money..." );
        Iterable<Client> result = StreamSupport
            .stream( getClients().spliterator(), false )
            .filter( c -> c.getMoney() == 0 )
            .collect( Collectors.toList() );
        logger.debug( "Result: " + result );
        return result;
    }

    public Iterable<Book> outOfStockBooks() {
        logger.debug( "Trying to get all books of quantity = 0..." );
        Iterable<Book> result = StreamSupport
            .stream( getBooks().spliterator(), false )
            .filter( c -> c.getQuantity() == 0 )
            .collect( Collectors.toList() );
        logger.debug( "Result: " + result );
        return result;
    }
}
