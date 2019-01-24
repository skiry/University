package ro.ubb.relations.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.io.Serializable;

/**
 * author: radu
 */

@Entity
@NoArgsConstructor
@AllArgsConstructor
@Data
@Builder
public class Book implements Serializable {
    @Id
    @GeneratedValue
    private Long id;

    private String author;

    private String title;

    @ManyToOne(cascade = CascadeType.ALL)
    private Publisher publisher;
}
