package ro.ubb.catalog.core.model;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table( name = "Clients" )
@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@Builder
public class Client extends BaseEntity<Integer> {
    private String firstName;
    private String lastName;
    private int money;
}
