package ubb.repeatExam.ProducersAndSongs.web.dto;

import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@Data
@ToString(callSuper = true)
@EqualsAndHashCode(callSuper =  true)
@Builder
public class ProducerDto extends BaseDto{
    private String name;
    private String country;
    private int age;
}
