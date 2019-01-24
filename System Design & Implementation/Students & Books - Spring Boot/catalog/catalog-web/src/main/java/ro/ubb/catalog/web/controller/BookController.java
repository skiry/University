package ro.ubb.catalog.web.controller;

import ro.ubb.catalog.core.model.Book;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ro.ubb.catalog.web.converter.BookConverter;
import ro.ubb.catalog.web.dto.BookDto;
import ro.ubb.catalog.web.dto.Books;
import ro.ubb.catalog.web.service.MonolithicService;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@RestController
public class BookController {
    @Autowired
    private MonolithicService monolithicService;

    @Autowired
    private BookConverter converter;

    @RequestMapping(value = "/books", method = RequestMethod.GET)
    ArrayList<BookDto> getAllBooks() {
        monolithicService.inject();
        List<Book> books = monolithicService.getBooks();
        return new ArrayList<>(converter.convertModelsToDtos(books));
    }

    @RequestMapping(value = "/books", method = RequestMethod.POST)
    Boolean addBook(@RequestBody BookDto data) {
        monolithicService.inject();
        Book book = converter.convertDtoToModel(data);
        Optional<Book> prevEntity = monolithicService.addBook(book);
        return prevEntity.isPresent();
    }

    @RequestMapping(value = "/books/{bookId}", method = RequestMethod.PUT)
    Boolean updateBook(@PathVariable final Integer bookId,
                         @RequestBody BookDto data) {
        monolithicService.inject();
        monolithicService.updateBook(bookId, data.getTitle(), data.getAuthor(),
                data.getIsbn(), data.getPrice(), data.getQuantity());
        return true;
    }

    @RequestMapping(value = "/books/{id}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteBook(@PathVariable Integer id) {
        monolithicService.inject();
        monolithicService.deleteBook(id);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @RequestMapping(value = "/books/most-expensive", method = RequestMethod.GET)
    Books getMostExpensive(@RequestBody Integer n) {
        monolithicService.inject();

        Iterable<Book> books = monolithicService.mostExpensiveBooks(n);
        return new Books(
                StreamSupport
                        .stream(books.spliterator(), false)
                        .map(converter::convertModelToDto)
                        .collect(Collectors.toList()));
    }

    @RequestMapping(value = "/books/out-of-stock", method = RequestMethod.GET)
    Books getOutOfStock() {
        monolithicService.inject();

        Iterable<Book> books = monolithicService.outOfStockBooks();
        return new Books(
                StreamSupport
                        .stream(books.spliterator(), false)
                        .map(converter::convertModelToDto)
                        .collect(Collectors.toList()));
    }

    @RequestMapping(value = "/books/by-quantity", method = RequestMethod.GET)
    Books getBooksByQuantity() {
        monolithicService.inject();

        Iterable<Book> books = monolithicService.sortBooksByQuantity();
        return new Books(
                StreamSupport
                        .stream(books.spliterator(), false)
                        .map(converter::convertModelToDto)
                        .collect(Collectors.toList()));
    }
}
