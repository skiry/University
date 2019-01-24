package ro.ubb.relations.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.Embeddable;
import javax.persistence.Entity;
import javax.persistence.Table;

/**
 * author: radu
 */

@Embeddable
@NoArgsConstructor
@AllArgsConstructor
@Data
@Builder
public class Address {
    private String city;
    private String street;
}
