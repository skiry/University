package ro.ubb.catalog.core.service;

import ro.ubb.catalog.core.model.Book;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import ro.ubb.catalog.core.repository.catalog.BookCatalog;

import java.util.List;

public class BookServiceImpl implements BookService {
    public static final Logger log = LoggerFactory.getLogger(BookServiceImpl.class);

    @Autowired
    private BookCatalog bookCatalog;

    @Override
    public List<Book> findAll() {
        log.trace("findAll --- method entered");

        List<Book> books = bookCatalog.findAll();

        log.trace("findAll: books={}", books);

        return books;
    }
}
