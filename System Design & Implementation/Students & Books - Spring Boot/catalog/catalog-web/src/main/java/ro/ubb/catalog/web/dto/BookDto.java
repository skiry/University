package ro.ubb.catalog.web.dto;

import lombok.*;

@EqualsAndHashCode(callSuper =  true)
@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
@Builder
public class BookDto extends BaseDto {
    private String title, author, isbn;
    private int price, quantity;
}
