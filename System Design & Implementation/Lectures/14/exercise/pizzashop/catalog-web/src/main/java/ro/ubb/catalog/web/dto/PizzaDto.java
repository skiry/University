package ro.ubb.catalog.web.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

/**
 * author: radu
 */
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class PizzaDto extends BaseDto {

    private String name;
    private int price;
}
