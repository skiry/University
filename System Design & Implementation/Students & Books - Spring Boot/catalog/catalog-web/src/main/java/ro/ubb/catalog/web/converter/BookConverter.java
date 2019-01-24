package ro.ubb.catalog.web.converter;

import ro.ubb.catalog.core.model.Book;
import org.springframework.stereotype.Component;
import ro.ubb.catalog.web.dto.BookDto;

@Component
public class BookConverter extends BaseConverter<Book, BookDto> {
    @Override
    public Book convertDtoToModel(BookDto dto) {
        Book book = Book.builder()
                .author(dto.getAuthor())
                .isbn(dto.getIsbn())
                .price(dto.getPrice())
                .quantity(dto.getQuantity())
                .title(dto.getTitle())
                .build();
        book.setId(dto.getId());

        return book;
    }

    @Override
    public BookDto convertModelToDto(Book model) {
        BookDto dto = BookDto.builder()
                .author(model.getAuthor())
                .isbn(model.getIsbn())
                .price(model.getPrice())
                .quantity(model.getQuantity())
                .title(model.getTitle())
                .build();
        dto.setId(model.getId());

        return dto;
    }
}
