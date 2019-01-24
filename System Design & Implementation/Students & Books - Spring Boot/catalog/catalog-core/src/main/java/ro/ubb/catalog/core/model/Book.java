package ro.ubb.catalog.core.model;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table( name = "Books" )
@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@Builder
public class Book extends BaseEntity<Integer> {
    private String title;
    private String author;
    private String isbn;
    private int price;
    private int quantity;
}
