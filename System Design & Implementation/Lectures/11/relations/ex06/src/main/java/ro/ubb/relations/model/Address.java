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
public class Address implements Serializable {
    @Id
    @GeneratedValue
    private Long id;

    private String city;
    private String street;

    @OneToOne
    private Publisher publisher;
}
