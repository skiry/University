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
public class SongDto extends BaseDto{
    private String musicName;
    private String genre;
    private int mark;
}
