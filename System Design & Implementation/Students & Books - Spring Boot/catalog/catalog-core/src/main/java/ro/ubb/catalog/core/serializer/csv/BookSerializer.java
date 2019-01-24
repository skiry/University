package ro.ubb.catalog.core.serializer.csv;


import ro.ubb.catalog.core.model.Book;

public class BookSerializer extends CsvSerializer<Integer, Book> {
    public String serialize( Book book ) {
        return "" +
            book.getId() + "," +
            book.getTitle() + "," +
            book.getAuthor() + "," +
            book.getIsbn() + "," +
            book.getPrice() + "," +
            book.getQuantity();
    }

    public Book deserialize( String data ) {
        String[] fields = data.split( "," );

        if ( fields.length != 6 ) {
            throw new RuntimeException( "Bad book information given: " + data + "." );
        }

        Integer id       = Integer.parseInt(fields[0]);
        String title     = fields[1];
        String author    = fields[2];
        String isbn      = fields[3];
        Integer price    = Integer.parseInt( fields[5] );
        Integer quantity = Integer.parseInt( fields[5] );
        Book book = new Book( title, author, isbn, price, quantity );
        book.setId(id);

        return book;
    }
}
