package ro.ubb.catalog.web.dto;

import lombok.*;

@EqualsAndHashCode(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
@Builder
@Getter
@Setter
public class ClientDto extends BaseDto {
    private String firstName, lastName;
    private int money;
}
