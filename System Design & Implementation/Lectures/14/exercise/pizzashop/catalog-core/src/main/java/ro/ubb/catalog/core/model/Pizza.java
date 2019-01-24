package ro.ubb.catalog.core.model;

import lombok.*;

import javax.persistence.Column;
import javax.persistence.Entity;

/**
 * author: radu
 */
@Entity
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString
@EqualsAndHashCode(callSuper = true)
public class Pizza extends BaseEntity<Long> {
    @Column(unique = true)
    private String name;
    private int price;


}
